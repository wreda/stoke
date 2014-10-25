#include "handlers.h"
#include "switch.h"
#include <sstream>
using namespace std;
using namespace stoke;
using namespace x64asm;

#include "helpers.cc"

#ifdef DEBUG_VALIDATOR
#define ADD_CONS(s) {cout << "Adding constraint: " << endl << s << endl;}
#else
#define ADD_CONS(S) 
#endif

//The variable pred is captured by the context. It represents the predicate for conditional moves and conditional sets
//V_CC_A is cf==0 and zf==0
#define V_CC_A   pred = vc_andExpr(vc, vc_notExpr(vc, getBoolExpr(vc,V_CF,d.pre_suffix, d.Vn)), vc_notExpr(vc, getBoolExpr(vc,V_ZF,d.pre_suffix, d.Vn)));
#define V_CC_AE   pred = vc_notExpr(vc, getBoolExpr(vc,V_CF,d.pre_suffix, d.Vn));
#define V_CC_B   pred = getBoolExpr(vc,V_CF,d.pre_suffix, d.Vn);
#define V_CC_BE   pred = vc_orExpr(vc, getBoolExpr(vc,V_CF,d.pre_suffix, d.Vn), getBoolExpr(vc,V_ZF,d.pre_suffix, d.Vn));
#define V_CC_E   pred = getBoolExpr(vc,V_ZF,d.pre_suffix, d.Vn);
#define V_CC_G   pred = vc_andExpr(vc, vc_notExpr(vc, getBoolExpr(vc,V_ZF,d.pre_suffix, d.Vn)), vc_iffExpr(vc, getBoolExpr(vc,V_SF,d.pre_suffix, d.Vn), getBoolExpr(vc,V_OF,d.pre_suffix, d.Vn)));
#define V_CC_GE   pred = vc_iffExpr(vc, getBoolExpr(vc,V_SF,d.pre_suffix, d.Vn), getBoolExpr(vc,V_OF,d.pre_suffix, d.Vn));
#define V_CC_L   pred = vc_notExpr(vc, vc_iffExpr(vc, getBoolExpr(vc,V_SF,d.pre_suffix, d.Vn), getBoolExpr(vc,V_OF,d.pre_suffix, d.Vn)));
#define V_CC_LE   pred = vc_orExpr(vc, getBoolExpr(vc,V_ZF,d.pre_suffix, d.Vn), vc_notExpr(vc, vc_iffExpr(vc, getBoolExpr(vc,V_SF,d.pre_suffix, d.Vn), getBoolExpr(vc,V_OF,d.pre_suffix, d.Vn))));
#define V_CC_NE   pred = vc_notExpr(vc, getBoolExpr(vc,V_ZF,d.pre_suffix, d.Vn));
#define V_CC_NS   pred = vc_notExpr(vc, getBoolExpr(vc,V_SF,d.pre_suffix, d.Vn));
#define V_CC_S   pred = getBoolExpr(vc,V_SF,d.pre_suffix, d.Vn);
#define V_CC_NO   pred = vc_notExpr(vc, getBoolExpr(vc,V_OF,d.pre_suffix, d.Vn));
#define V_CC_NP   pred = vc_notExpr(vc, getBoolExpr(vc,V_PF,d.pre_suffix, d.Vn));
#define V_CC_O   pred = getBoolExpr(vc,V_OF,d.pre_suffix, d.Vn);
#define V_CC_P   pred = getBoolExpr(vc,V_PF,d.pre_suffix, d.Vn);

#define CMOV_FLUFF  \
  Expr retval = vc_iteExpr(vc, pred, EqExpr(vc, E_dest, E_src), EqExpr(vc, E_dest, E_dest_pre));\
if(bitWidth < V_UNITSIZE)\
{\
  SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));\
  retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));\
}\
d.constraints.push_back(retval);  


#define SET_FLUFF 	Expr retval = vc_iteExpr(vc, pred, EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 1)), EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0)));\
                                  if(dest_is_reg && bitWidth < V_UNITSIZE)\
{\
  SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));\
  retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));\
}\
d.constraints.push_back(retval);  




//Add with carry. Promote arguments to bitWidth+2 (66 from 64) bits, do the additions, and set the flags.
//If the destination register is not 64 bit then model the effects on the rest of the parent register of the destination register.
//E_dest, E_src1, E_src2 all have the same bitWidth
void adcHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;

  //This contains n+2 bit result.
  Expr E_result = vc_varExpr(vc, ("ADCTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth+2) );

  //Promote arguments to n bits
  Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 2, 0), E_src1);
  Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 2, 0), E_src2);

  //Get a bitWidth+2 bitvector with the lsb as carry
  Expr E_carry = vc_varExpr(vc, ("CARRY"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth+2));
  Expr retval = vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_carry, 0), getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, vc_bvExtract(vc, E_carry, bitWidth+1, 1),  vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 1, 0),vc_bvConstExprFromLL(vc, bitWidth, 0))));

  //E_src1 + E_src2 + Carry
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_result,vc_bvPlusExpr(vc, bitWidth+2, vc_bvPlusExpr(vc, bitWidth+2, E_arg1, E_arg2), E_carry)));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, E_dest, vc_bvExtract(vc, E_result, bitWidth-1, 0)));  

  //Handle effects on parent register
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }

  //Push the constraints
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

  //Set flags accordingly
  setFlag(vc, d.Vnprime, V_OF, getOFExpr(vc, vc_bvBoolExtract_One(vc, E_arg1, bitWidth - 1), vc_bvBoolExtract_One(vc, E_arg2, bitWidth - 1),
        vc_bvBoolExtract_One(vc, E_result, bitWidth - 1)), d.constraints, d.post_suffix);
  setFlag(vc, d.Vnprime, V_CF, vc_orExpr(vc, vc_bvBoolExtract_One(vc, E_result, bitWidth), vc_bvBoolExtract_One(vc, E_result, bitWidth+1)), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}

void addHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr E_result = vc_varExpr(vc, ("ADDTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth+2) );
  Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 2, 0), E_src1);
  Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 2, 0), E_src2);  

  Expr retval = vc_trueExpr(vc);
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_result, vc_bvPlusExpr(vc, bitWidth+2, E_arg1, E_arg2)));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, E_dest, vc_bvExtract(vc, E_result, bitWidth-1, 0)));  

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
  setFlag(vc, d.Vnprime, V_OF, getOFExpr(vc, vc_bvBoolExtract_One(vc, E_arg1, bitWidth - 1), vc_bvBoolExtract_One(vc, E_arg2, bitWidth - 1),
        vc_bvBoolExtract_One(vc, E_result, bitWidth - 1)), d.constraints, d.post_suffix);
  setFlag(vc, d.Vnprime, V_CF, vc_orExpr(vc, vc_bvBoolExtract_One(vc, E_result, bitWidth), vc_bvBoolExtract_One(vc, E_result, bitWidth+1)), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}



void adddHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

#define DADDPATT(x)\
  {\
    Expr E_result = vc_bvExtract(vc, E_dest, x+63, x);\
    Expr E_arg1 = vc_bvExtract(vc, E_src1, x+63, x);\
    Expr E_arg2 = vc_bvExtract(vc, E_src2, x+63, x);\
    retval = vc_andExpr(vc, retval, (E_result == dadd(E_arg1,E_arg2)));\
  }

  VC&vc = d.vc;
  uint bitWidth = numops*64; 
  z3::sort fl = vc->bv_sort(64);
  z3::func_decl dadd = z3::function("addd", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);
  if(numops==1)
  {
    DADDPATT(0)
  }
  else
  {
    DADDPATT(0)
      DADDPATT(64)
  }
  if(dest_is_reg && numops == 1)
  {
    SS_Id id_dest = XMM_BEG+getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

#undef DADDPATT
}




void addfHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

#define FADDPATT(x)\
  {\
    Expr E_result = vc_bvExtract(vc, E_dest, x+31, x);\
    Expr E_arg1 = vc_bvExtract(vc, E_src1, x+31, x);\
    Expr E_arg2 = vc_bvExtract(vc, E_src2, x+31, x);\
    retval = vc_andExpr(vc, retval, (E_result == fadd(E_arg1,E_arg2)));\
  }

  VC&vc = d.vc;
  uint bitWidth = numops*32; 
  z3::sort fl = vc->bv_sort(32);
  z3::func_decl fadd = z3::function("addf", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);
  if(numops==1)
  {
    FADDPATT(0)
  }
  else
  {
    FADDPATT(0)
      FADDPATT(32)
      FADDPATT(64)
      FADDPATT(96)	  
  }
  if(dest_is_reg && numops < 4)
  {
    SS_Id id_dest = XMM_BEG+getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

#undef FADDPATT
}

//This is more general than what the name suggests
void addmul64rr(VC& vc, Expr E_arg1, Expr E_arg2, Expr E_dest, v_data d, bool add_sym=true) {

  VALIDATOR_ERROR("addmul64rr suspisciously commented out -- aborting.");
  /*	muldata tuple(vc);
      tuple.arg1 = E_arg1;
      tuple.arg2 = E_arg2;
      tuple.result = E_dest;

      Expr cond = vc_eqExpr(vc, E_arg1, vc_bvConstExprFromLL(vc, V_UNITSIZE, 0));
      Expr retval = vc_impliesExpr(vc, cond, EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, V_UNITSIZE, 0)));
#ifdef DEBUG_VALIDATOR
  //cout << "Adding congruence constraint ";  vc_printExpr(vc, retval);  cout << endl;
#endif
d.constraints.push_back(retval); 

for(vector<muldata>::iterator iter = mul.begin(); iter != mul.end(); iter++)
{
Expr e1 = vc_eqExpr(vc, E_arg1, iter->arg1);
Expr e2 = vc_eqExpr(vc, E_arg2, iter->arg2);
Expr cond = vc_andExpr(vc, e1, e2);
Expr retval = vc_impliesExpr(vc, cond, vc_eqExpr(vc, E_dest, iter->result));
#ifdef DEBUG_VALIDATOR
  //cout << "Adding congruence constraint ";  vc_printExpr(vc, retval);  cout << endl;
#endif
d.constraints.push_back(retval); 
if(add_sym){
Expr cond = vc_andExpr(vc, vc_eqExpr(vc, E_arg1, iter->arg2), vc_eqExpr(vc, E_arg2, iter->arg1));
Expr retval = vc_impliesExpr(vc, cond, vc_eqExpr(vc, E_dest, iter->result));
  //cout << "Adding commutativity constraint ";  vc_printExpr(vc, retval); cout << endl;
  d.constraints.push_back(retval); 
  }

  }
  mul.push_back(tuple);*/
}




void andHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr E_result = vc_bvAndExpr(vc,E_src1, E_src2 );
  Expr retval = EqExpr(vc, E_dest, E_result);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 
  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}


void andpsHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;

  Expr E_result = vc_bvAndExpr(vc,E_src1, E_src2 );
  Expr retval = EqExpr(vc, E_dest, E_result);
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}


//If E_src[0]==1 then 0 else if E_src[1]==1 then 1 else ...
//A new unconstrained variable if E_src == 0
void bsfHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src) {

  VC&vc = d.vc;
  setFlag(vc,d.Vnprime,V_ZF, EqExpr(vc, E_src, vc_bvConstExprFromLL(vc, bitWidth, 0)), d.constraints, d.post_suffix);


  //	Expr E_result = vc_varExpr(vc, ("BSFTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth));
  Expr E_result = vc_bvConstExprFromLL(vc, bitWidth,0);
  for(int i = (int)bitWidth - 1; i>=0; i-- )
  {
    E_result = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_src, i), vc_bvConstExprFromLL(vc, bitWidth, i), E_result);
  }
  Expr retval = EqExpr(vc, E_dest, E_result);

  if(bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}

//If E_src[bitWidth-1]==1 then bitWidth else if E_src[bitWidth-2]==1 then bitWidth-2 else ...
//A new unconstrained variable if E_src == 0
void bsrHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src) {

  VC&vc = d.vc;
  setFlag(vc,d.Vnprime,V_ZF, EqExpr(vc, E_src, vc_bvConstExprFromLL(vc, bitWidth, 0)), d.constraints, d.post_suffix);


  //	Expr E_result = vc_varExpr(vc, ("BSRTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth));
  Expr E_result = vc_bvConstExprFromLL(vc, bitWidth,0);
  for(unsigned int i = 0 ; i<bitWidth; i++ )
  {
    E_result = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_src, i), vc_bvConstExprFromLL(vc, bitWidth, i), E_result);
  }
  Expr retval = EqExpr(vc, E_dest, E_result);

  if(bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 
}

//Do a byte by byte swap
void bswapHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src) {

  VC&vc = d.vc;
  unsigned int ratio = bitWidth/8;
  Expr retval = vc_trueExpr(vc);
  for(unsigned int i = 0; i<ratio; i++)
  {
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, ((i+1)*8)-1, i*8), vc_bvExtract(vc, E_src, (ratio - i)*8-1, (ratio -i -1)*8)));
  }

  if(bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 
}


void btHandler(v_data d, unsigned int bitWidth, Expr E_operand, Expr E_offset) {

  VC&vc = d.vc;
  Expr E_idx = vc_bvAndExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, bitWidth -1), E_offset);
  Expr E_result = vc_trueExpr(vc);
  for(unsigned int i = 0; i<bitWidth; i++)
  {
    E_result = vc_iteExpr(vc, EqExpr(vc, E_idx, vc_bvConstExprFromLL(vc, bitWidth, i)), vc_bvBoolExtract_One(vc, E_operand, i), E_result);
  }
  setFlag(vc,d.Vnprime,V_CF, E_result, d.constraints, d.post_suffix);	 
}


void btcHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_operand, Expr E_offset, bool dest_is_reg = true) {

  VC&vc = d.vc;
  Expr E_carry = getBoolExpr(vc, V_CF, d.post_suffix, d.Vnprime);
  Expr E_idx = vc_bvAndExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, bitWidth -1), E_offset);
  Expr retval = vc_trueExpr(vc);
  for(unsigned int i = 0; i<bitWidth; i++)
  {
    retval = vc_iteExpr(vc, EqExpr(vc, E_idx, vc_bvConstExprFromLL(vc, bitWidth, i)), 
        vc_andExpr(vc, 
          vc_iffExpr(vc, E_carry, vc_bvBoolExtract_One(vc, E_operand, i)),
          setBit(vc, E_dest, E_operand, i, vc_bvNotExpr(vc, vc_bvExtract(vc, E_operand, i, i)), bitWidth)
          ), 
        retval);
  }
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }	
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 		 
} 

void btvalHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_operand, Expr E_offset, bool val, bool dest_is_reg = true) {

  VC&vc = d.vc;
  Expr E_carry = getBoolExpr(vc, V_CF, d.post_suffix, d.Vnprime);
  Expr E_idx = vc_bvAndExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, bitWidth -1), E_offset);
  Expr retval = vc_trueExpr(vc);
  for(unsigned int i = 0; i<bitWidth; i++)
  {
    retval = vc_iteExpr(vc, EqExpr(vc, E_idx, vc_bvConstExprFromLL(vc, bitWidth, i)), 
        vc_andExpr(vc, 
          vc_iffExpr(vc, E_carry, vc_bvBoolExtract_One(vc, E_operand, i)),
          setBit(vc, E_dest, E_operand, i, vc_bvConstExprFromInt(vc, 1, val), bitWidth)
          ), 
        retval);
  }
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }	
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 		 
} 


void cmovHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src, Expr pred) {
  VC&vc = d.vc;
#ifdef DEBUG_VALIDATOR
  cout << "Inside CMOV "; vc_printExpr(vc, E_dest); vc_printExpr(vc, E_dest_pre); vc_printExpr(vc, E_src); cout << endl ;
#endif
  Expr retval = vc_iteExpr(vc, pred, EqExpr(vc, E_dest, E_src), EqExpr(vc, E_dest, E_dest_pre));
  if(bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}

void cmovaHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_A
  CMOV_FLUFF
}

void cmovaeHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_AE
  CMOV_FLUFF
}

void cmovbHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_B
  CMOV_FLUFF
}

void cmovbeHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_BE
  CMOV_FLUFF
}

void cmoveHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_E
  CMOV_FLUFF
}

void cmovgHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_G
  CMOV_FLUFF
}


void cmovgeHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_GE
  CMOV_FLUFF
}

void cmovlHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_L
  CMOV_FLUFF
}


void cmovleHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_LE
  CMOV_FLUFF
}


void cmovneHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_NE
  CMOV_FLUFF
}

void cmovnsHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_NS
  CMOV_FLUFF
}


void cmovsHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src) {

  VC& vc = d.vc;
  Expr V_CC_S
  CMOV_FLUFF
}

void cmpHandler(v_data d, unsigned int bitWidth, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  Expr E_dest = vc_varExpr(vc, ("CMPTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth) );
  Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1, 0), E_src1);
  Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1, 0), E_src2);

  Expr retval = EqExpr(vc, E_dest, vc_bvExtract(vc, vc_bvMinusExpr(vc, bitWidth+1, E_arg1, E_arg2), bitWidth - 1, 0));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
  setFlag(vc, d.Vnprime, V_OF, getOFExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth - 1), vc_bvBoolExtract(vc, E_src2, bitWidth - 1),  vc_bvBoolExtract_One(vc, E_dest, bitWidth - 1)),
      d.constraints, d.post_suffix);
  setFlag(vc, d.Vnprime, V_CF, vc_bvLtExpr(vc, E_src1, E_src2), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}



void cmppsHandler(v_data d, int imm, Expr E_dest, Expr E_dest_pre, Expr E_src, Expr E_imm) {

#define FCMPPATT(x)\
  {\
    Expr E_dest_part = vc_bvExtract(vc, E_dest, x+31, x);\
    Expr E_src1 = vc_bvExtract(vc, E_src, x+31, x);\
    Expr E_src2 = vc_bvExtract(vc, E_dest_pre, x+31, x);\
    Expr E_cmp_res = fcmp(E_src1, E_src2);\
    Expr E_gt = vc_andExpr(vc, vc_notExpr(vc, vc_bvBoolExtract_One(vc, E_cmp_res, 1)),vc_bvBoolExtract_One(vc, E_cmp_res, 0)); \
    retval = vc_andExpr(vc, retval, vc_iteExpr(vc, E_gt, EqExpr(vc, E_dest_part, ones), EqExpr(vc, E_dest_part, zeros)));\
  }

#define FCMPPATT2(x)\
  {\
    Expr E_dest_part = vc_bvExtract(vc, E_dest, x+31, x);\
    Expr E_src1 = vc_bvExtract(vc, E_dest_pre, x+31, x);\
    Expr E_src2 = vc_bvExtract(vc, E_src, x+31, x);\
    Expr E_cmp_res = fcmp(E_src1, E_src2);\
    Expr E_gt = vc_andExpr(vc, vc_notExpr(vc, vc_bvBoolExtract_One(vc, E_cmp_res, 1)),vc_bvBoolExtract_One(vc, E_cmp_res, 0)); \
    retval = vc_andExpr(vc, retval, vc_iteExpr(vc, E_gt, EqExpr(vc, E_dest_part, zeros), EqExpr(vc, E_dest_part, ones)));\
  }	

  VC&vc = d.vc;
  imm =imm &0x7;
  if (imm != 1 && imm != 2)
    throw VALIDATOR_ERROR("cmpps is only implemented for immediate of 1 or 2");
  if(imm==1)
  {
    z3::sort fl = vc->bv_sort(32);
    z3::sort cmp_res = vc->bv_sort(2);
    z3::func_decl fcmp = z3::function("cmpf", fl, fl, cmp_res);
    Expr retval = vc_trueExpr(vc);
    Expr zeros = vc_bvConstExprFromLL(vc, 32, 0);
    Expr ones = vc_bvConstExprFromLL(vc, 32, -1);

    FCMPPATT(0);
    FCMPPATT(32);
    FCMPPATT(64);
    FCMPPATT(96);

#ifdef DEBUG_VALIDATOR
    cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
    d.constraints.push_back(retval);
  }
  if(imm==2)
  {
    z3::sort fl = vc->bv_sort(32);
    z3::sort cmp_res = vc->bv_sort(2);
    z3::func_decl fcmp = z3::function("cmpf", fl, fl, cmp_res);
    Expr retval = vc_trueExpr(vc);
    Expr zeros = vc_bvConstExprFromLL(vc, 32, 0);
    Expr ones = vc_bvConstExprFromLL(vc, 32, -1);

    FCMPPATT2(0);
    FCMPPATT2(32);
    FCMPPATT2(64);
    FCMPPATT2(96);

#ifdef DEBUG_VALIDATOR
    cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
    d.constraints.push_back(retval);	  
  }
#undef FCMPPATT
}


void cmpxchgHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src, Expr E_dest_pre, bool dest_is_reg = true) {
  if(bitWidth == 32)
    throw VALIDATOR_ERROR("Internal error: for bitWidth=32 support, use chmxchg32Handler");
  VC&vc = d.vc;
  Expr E_rax_pre = regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE);
  Expr E_rax_post = regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE);
  Expr E_acc_pre = vc_bvExtract(vc, E_rax_pre, bitWidth - 1, 0);
  Expr E_acc_post = vc_bvExtract(vc, E_rax_post, bitWidth - 1, 0);

  cmpHandler(d, bitWidth, E_acc_pre, E_dest_pre);
  Expr retval = vc_iteExpr(vc, getBoolExpr(vc, V_ZF, d.post_suffix, d.Vnprime),
      vc_andExpr(vc, EqExpr(vc, E_dest, E_src), EqExpr(vc, E_acc_post, E_acc_pre)),
      vc_andExpr(vc, EqExpr(vc, E_acc_post, E_dest), EqExpr(vc, E_dest, E_dest_pre))
      );

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, bitWidth));


  }    
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}


void cmpxchg32Handler(v_data d, unsigned int bitWidth, Expr E_dest_post, Expr E_src, Expr E_dest_pre, bool dest_is_reg = true) {

  if(bitWidth != 32)
    throw VALIDATOR_ERROR("Internal error: for bitWidth!=32 support, use chmxchgHandler");

  VC&vc = d.vc;

  Expr E_rax_pre = regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE);
  Expr E_rax_post = regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE);
  Expr E_acc_pre = vc_bvExtract(vc, E_rax_pre, bitWidth - 1, 0);
  Expr E_acc_post = vc_bvExtract(vc, E_rax_post, bitWidth - 1, 0);

  cmpHandler(d, bitWidth, E_acc_pre, E_dest_pre);
  Expr retval = vc_iteExpr(vc, getBoolExpr(vc, V_ZF, d.post_suffix, d.Vnprime),
      vc_andExpr(vc, EqExpr(vc, E_dest_post, E_src), EqExpr(vc, E_acc_post, E_acc_pre)),
      vc_andExpr(vc, EqExpr(vc, E_acc_post, E_dest_post), EqExpr(vc, E_dest_post, E_dest_pre))
      );

  if(dest_is_reg)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    Expr E_full_dest_pre = regExprWVN(vc, id_dest, d.pre_suffix, d.Vn, V_UNITSIZE);
    Expr E_full_dest_post = regExprWVN(vc, id_dest, d.post_suffix, d.Vnprime, V_UNITSIZE);

    retval = vc_iteExpr(vc, getBoolExpr(vc, V_ZF, d.post_suffix, d.Vnprime),
        vc_andExpr(vc, EqExpr(vc, vc_bvExtract(vc, E_rax_pre, 63, 32), vc_bvExtract(vc, E_rax_post, 63, 32))
          , EqExpr(vc, vc_bvConstExprFromLL(vc, 32, 0), vc_bvExtract(vc, E_full_dest_post, 63, 32))
          ),	  
        vc_andExpr(vc, EqExpr(vc, vc_bvExtract(vc, E_full_dest_pre, 63, 32), vc_bvExtract(vc, E_full_dest_post, 63, 32))
          , EqExpr(vc, vc_bvConstExprFromLL(vc, 32, 0), vc_bvExtract(vc, E_rax_post, 63, 32))
          )
        );
  }    
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}


void convert_cdq_Handler(v_data d, Expr pred, unsigned int bitWidth) {

  VC&vc = d.vc;
  SS_Id id_dest = rdx;
  Expr E_dest = vc_bvExtract(vc, regExprWVN(vc, id_dest, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
  Expr E_src = vc_iteExpr(vc, pred, vc_bvConstExprFromLL(vc, bitWidth, -1),  vc_bvConstExprFromLL(vc, bitWidth, 0));
  Expr retval = EqExpr(vc, E_dest, E_src);
  if(bitWidth < V_UNITSIZE)
    retval = vc_andExpr(vc, retval, UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));   
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}  

void convert_e_Handler(v_data d, unsigned int bitWidth) {

  if(bitWidth >= 64)
    throw VALIDATOR_ERROR("Internal error: bitWidth should be for the source, not the destination");
  VC&vc = d.vc;
  SS_Id id_dest = rax;
  Expr E_dest = vc_bvExtract(vc, regExprWVN(vc, id_dest, d.post_suffix, d.Vnprime, V_UNITSIZE), 2*bitWidth - 1, 0);
  Expr E_src = vc_bvExtract(vc, regExprWVN(vc, id_dest, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0);
  Expr E_result = vc_bvSignExtend(vc, E_src, 2*bitWidth);
  Expr retval = EqExpr(vc, E_dest, E_result);
  if(2*bitWidth < V_UNITSIZE)
    retval = vc_andExpr(vc, retval, UnmodifiedBitsPreserve(vc, id_dest, d, 2*bitWidth));   
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}

void crc32r32Handler(v_data d, Expr E_dest, Expr E_dest_pre, Expr E_src) {
//These are for CRC32
#define REFLECT_INNER(x,firstshift, firsthex, secondshift, secondhex)\
  vc_bvOrExpr(vc,\
      vc_bvLeftShiftExprExpr(vc, 32, vc_bvAndExpr(vc, (x), vc_bvConstExprFromLL(vc, 32,  (firsthex))), vc_bvConstExprFromLL(vc, 32, (firstshift))),\
      vc_bvRightShiftExprExpr(vc, 32, vc_bvAndExpr(vc,(x), vc_bvConstExprFromLL(vc, 32, (secondhex))), vc_bvConstExprFromLL(vc, 32,(secondshift)))\
      );

#define REFLECT(x, s1, s2, s3, s4, s5)\
  s1 = REFLECT_INNER(x,  1,  0x55555555, 1,  0xAAAAAAAA);\
s2 = REFLECT_INNER(s1, 2,  0x33333333, 2,  0xCCCCCCCC);\
s3 = REFLECT_INNER(s2, 4,  0x0F0F0F0F, 4,  0xF0F0F0F0);\
s4 = REFLECT_INNER(s3, 8,  0x00FF00FF, 8,  0xFF00FF00);\
s5 = REFLECT_INNER(s4, 16, 0x0000FFFF, 16, 0xFFFF0000);\

#define POLYDIV(dest, src, poly, idx,n, s)\
  Expr dest = vc_varExpr(vc, ("DIVCRCTEMP"+itoa((idx))+s+itoa((n))).c_str(), vc_bvType(vc, 64));\
temp = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, src, (idx)+32),\
    vc_bvXorExpr(vc, src, vc_bvConcatExpr(vc,\
        vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 31 -(idx), 0), poly),\
        vc_bvConstExprFromLL(vc, idx, 0)\
        )\
      ),\
    src\
    );\
retval = vc_andExpr(vc, retval, EqExpr(vc, dest, temp));



  VC& vc = d.vc;
  Expr retval = vc_trueExpr(vc);
  Expr E_temp1(*vc), E_temp1_1(*vc), E_temp1_2(*vc), E_temp1_3(*vc), E_temp1_4(*vc), E_temp1_5(*vc);
  E_temp1 = vc_varExpr(vc, ("TEMP1CRC"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, 32));

  REFLECT(E_src, E_temp1_1, E_temp1_2, E_temp1_3, E_temp1_4, E_temp1_5)  

#ifdef DEBUG_VALIDATOR
    //cout << "TEMP1CRC done" << endl ;
#endif

    retval =vc_andExpr(vc, retval, EqExpr(vc, E_temp1, E_temp1_5));

  Expr E_temp2(*vc), E_temp2_1(*vc), E_temp2_2(*vc), E_temp2_3(*vc), E_temp2_4(*vc), E_temp2_5(*vc);
  E_temp2 = vc_varExpr(vc, ("TEMP2CRC"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, 32));

  REFLECT(E_dest_pre, E_temp2_1, E_temp2_2, E_temp2_3, E_temp2_4, E_temp2_5)  
    retval =vc_andExpr(vc, retval, EqExpr(vc, E_temp2, E_temp2_5));  

  Expr E_temp3 = vc_bvConcatExpr(vc, E_temp1, vc_bvConstExprFromLL(vc, 32, 0));
  Expr E_temp4 = vc_bvConcatExpr(vc, E_temp2, vc_bvConstExprFromLL(vc, 32, 0));

  Expr E_temp5 = vc_varExpr(vc, ("TEMP5CRC"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, 64));
  retval =vc_andExpr(vc, retval, EqExpr(vc, E_temp5, vc_bvXorExpr(vc, E_temp3, E_temp4)));  

  Expr E_temp6(*vc), E_temp6_1(*vc), E_temp6_2(*vc), E_temp6_3(*vc), E_temp6_4(*vc), E_temp6_5(*vc);
  E_temp6 = vc_varExpr(vc, ("TEMP6CRC"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, 32));

  Expr temp(*vc);
  //E_temp6 = E_temp5 mod2 0x11EDC6F41

  Expr E_poly = vc_bvConstExprFromLL(vc, 33, 0x11EDC6F41);
  Expr E_var31 = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_temp5, 63), vc_bvXorExpr(vc, vc_bvConcatExpr(vc, E_poly, vc_bvConstExprFromLL(vc, 31, 0)), E_temp5), E_temp5);

  POLYDIV(E_var30, E_var31, E_poly, 30, d.instr_no, d.pre_suffix)
    POLYDIV(E_var29, E_var30, E_poly, 29, d.instr_no, d.pre_suffix)
    POLYDIV(E_var28, E_var29, E_poly, 28, d.instr_no, d.pre_suffix)
    POLYDIV(E_var27, E_var28, E_poly, 27, d.instr_no, d.pre_suffix)
    POLYDIV(E_var26, E_var27, E_poly, 26, d.instr_no, d.pre_suffix)
    POLYDIV(E_var25, E_var26, E_poly, 25, d.instr_no, d.pre_suffix)
    POLYDIV(E_var24, E_var25, E_poly, 24, d.instr_no, d.pre_suffix)
    POLYDIV(E_var23, E_var24, E_poly, 23, d.instr_no, d.pre_suffix)
    POLYDIV(E_var22, E_var23, E_poly, 22, d.instr_no, d.pre_suffix)
    POLYDIV(E_var21, E_var22, E_poly, 21, d.instr_no, d.pre_suffix)
    POLYDIV(E_var20, E_var21, E_poly, 20, d.instr_no, d.pre_suffix)
    POLYDIV(E_var19, E_var20, E_poly, 19, d.instr_no, d.pre_suffix)
    POLYDIV(E_var18, E_var19, E_poly, 18, d.instr_no, d.pre_suffix)
    POLYDIV(E_var17, E_var18, E_poly, 17, d.instr_no, d.pre_suffix)
    POLYDIV(E_var16, E_var17, E_poly, 16, d.instr_no, d.pre_suffix)
    POLYDIV(E_var15, E_var16, E_poly, 15, d.instr_no, d.pre_suffix)
    POLYDIV(E_var14, E_var15, E_poly, 14, d.instr_no, d.pre_suffix)
    POLYDIV(E_var13, E_var14, E_poly, 13, d.instr_no, d.pre_suffix)
    POLYDIV(E_var12, E_var13, E_poly, 12, d.instr_no, d.pre_suffix)
    POLYDIV(E_var11, E_var12, E_poly, 11, d.instr_no, d.pre_suffix)
    POLYDIV(E_var10, E_var11, E_poly, 10, d.instr_no, d.pre_suffix)
    POLYDIV(E_var9 , E_var10, E_poly,  9, d.instr_no, d.pre_suffix)
    POLYDIV(E_var8 , E_var9 , E_poly,  8, d.instr_no, d.pre_suffix)
    POLYDIV(E_var7 , E_var8 , E_poly,  7, d.instr_no, d.pre_suffix)
    POLYDIV(E_var6 , E_var7 , E_poly,  6, d.instr_no, d.pre_suffix)
    POLYDIV(E_var5 , E_var6 , E_poly,  5, d.instr_no, d.pre_suffix)
    POLYDIV(E_var4 , E_var5 , E_poly,  4, d.instr_no, d.pre_suffix)
    POLYDIV(E_var3 , E_var4 , E_poly,  3, d.instr_no, d.pre_suffix)
    POLYDIV(E_var2 , E_var3 , E_poly,  2, d.instr_no, d.pre_suffix)
    POLYDIV(E_var1 , E_var2 , E_poly,  1, d.instr_no, d.pre_suffix)

    Expr E_var0 = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_var1, 32), vc_bvXorExpr(vc, vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 31, 0), E_poly), E_var1), E_var1);
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_temp6, vc_bvExtract(vc, E_var0, 31, 0)));  

  REFLECT(E_temp6, E_temp6_1, E_temp6_2, E_temp6_3, E_temp6_4, E_temp6_5)    
    retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, E_temp6_5));  

#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 

#undef REFLECT
#undef REFLECT_INNER
#undef POLYDIV
}



// This handles CWD, CDQ, CQO
void cwd_cdq_cqoHandler(v_data d, int width) {

  VC&vc = d.vc;

  // Unfortunately, we need to manually get the symbols for the "source" and
  // "destination".  By "source" I mean the sub-register of RAX and by
  // "destination" I mean the subregister of RDX.

  Expr rax_expr       = regExprWVN(vc, rax, d.post_suffix, d.Vn, 64);
  Expr rdx_end_expr   = regExprWVN(vc, rdx, d.post_suffix, d.Vnprime, 64);
  Expr rdx_start_expr = regExprWVN(vc, rdx, d.post_suffix, d.Vn, 64);


  // Extract the top bit of the source register
  Expr last_bit_of_src = vc_bvExtract(vc, rax_expr, width - 1, width - 1);

  // Constrain all the bits of the destination register.
  for(int i = 0; i < width; ++i) {
    Expr bit_of_dst = vc_bvExtract(vc, rdx_end_expr, i, i); 
    Expr equal = EqExpr(vc, bit_of_dst, last_bit_of_src);
    d.constraints.push_back(equal);
  }

  // Constrain remaining bits of rdx.
  if (width < 64) {
    Expr rdx_start_remaining = vc_bvExtract(vc, rdx_start_expr, 63, width);
    Expr rdx_end_remaining = vc_bvExtract(vc, rdx_end_expr, 63, width);
    Expr equal = EqExpr(vc, rdx_start_remaining, rdx_end_remaining);
    d.constraints.push_back(equal);
  }
}

//OF is SET iff original value is 0
void decHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src, bool dest_is_reg=true) {

  VC&vc = d.vc;
#ifdef DEBUG_VALIDATOR
  //vc_printExpr(vc, E_dest); vc_printExpr(vc, E_src); cout << endl << bitWidth << endl ;
#endif

  Expr E_result = vc_bvMinusExpr(vc, bitWidth+1, 
      vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1, 0), E_src),
      vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1, 0), vc_bvConstExprFromLL(vc, bitWidth, 1)));
  Expr retval = EqExpr(vc, E_dest, vc_bvExtract(vc, E_result, bitWidth - 1, 0));
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval); 

  setFlag(vc,d.Vnprime,V_OF, EqExpr(vc,E_dest,vc_bvConstExprFromLL(vc, bitWidth,0)), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}



void divHandler(v_data d, unsigned int bitWidth, Expr E_src2) {

  VC&vc = d.vc;
  //	SS_Id rdx = rdx;
  //	SS_Id rax = rax;
  if(bitWidth > 8)
  {
    Expr E_src1 = vc_bvConcatExpr(vc, vc_bvExtract(vc, regExprWVN(vc, rdx, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
    E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
    //E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
    Expr E_quotient = vc_bvExtract(vc, vc_bvDivExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_remainder = vc_bvExtract(vc, vc_bvModExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_rem_dest = vc_bvExtract(vc, regExprWVN(vc, rdx, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_quot_dest = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);

    Expr retval = vc_andExpr(vc, EqExpr(vc, E_quot_dest, E_quotient), EqExpr(vc, E_rem_dest, E_remainder)) ;
    if( bitWidth < V_UNITSIZE)
    {
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rdx, d, bitWidth));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, bitWidth));

    }
#ifdef DEBUG_VALIDATOR
    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
    d.constraints.push_back(retval); 
  }
  else
  {
    Expr E_src1 = vc_bvConcatExpr(vc, vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), (2*bitWidth) - 1, bitWidth), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
    E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
    //E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
    Expr E_quotient = vc_bvExtract(vc, vc_bvDivExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_remainder = vc_bvExtract(vc, vc_bvModExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_rem_dest = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), (2*bitWidth) - 1, bitWidth);
    Expr E_quot_dest = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);

    Expr retval = vc_andExpr(vc, EqExpr(vc, E_quot_dest, E_quotient), EqExpr(vc, E_rem_dest, E_remainder)) ;

    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, 2*bitWidth));

#ifdef DEBUG_VALIDATOR
    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
    d.constraints.push_back(retval); 	  	  
  }
}

void div_uif_Handler(v_data d, unsigned int bitWidth, Expr E_src2 ) {
  VALIDATOR_ERROR("div_uif suspisciously commented out -- aborting.");
  /*	assert(bitWidth==32 && "only for 32 remainder right now");
      VC&vc = d.vc;
      Expr E_src1 = vc_bvConcatExpr(vc, vc_bvExtract(vc, regExprWVN(vc, rdx, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
      E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
      Expr E_rem_dest = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), vc_bvExtract(vc, regExprWVN(vc, rdx, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0));
      addmul64rr(vc, E_src1, E_src2, E_rem_dest, mul, d, false);
   */
}


void dppdHandler(v_data d, int imm, Expr E_dest, Expr E_dest_pre, Expr E_src, Expr E_imm) {

  imm = imm & 0xFF;
  VC&vc = d.vc;

  Expr E_temp1 = vc_varExpr(vc, ("DPPD_TEMP1"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, V_XMMUNIT) );
  Expr E_temp2 = vc_varExpr(vc, ("DPPD_TEMP2"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, V_UNITSIZE) );
  Expr retval = vc_trueExpr(vc);

  if(imm & 0x10)
    retval = vc_andExpr(vc, retval, dmul(vc, vc_bvExtract(vc, E_temp1, 63, 0), vc_bvExtract(vc, E_dest_pre, 63, 0), vc_bvExtract(vc, E_src, 63, 0)));
  else
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_temp1, 63, 0), vc_bvConstExprFromLL(vc, 64,0)));	  

  if(imm & 0x20)
    retval = vc_andExpr(vc, retval, dmul(vc, vc_bvExtract(vc, E_temp1, 127, 64), vc_bvExtract(vc, E_dest_pre, 127, 64), vc_bvExtract(vc, E_src, 127, 64)));
  else
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_temp1, 127, 64), vc_bvConstExprFromLL(vc, 64,0)));	  

  retval = vc_andExpr(vc, retval, dadd(vc, E_temp2, vc_bvExtract(vc, E_temp1, 127, 64), vc_bvExtract(vc, E_temp1, 63, 0)));

  if( imm & 0x1)
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc,E_dest,63,0), E_temp2)); 
  else
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc,E_dest,63,0), vc_bvConstExprFromLL(vc, 64,0) )); 	  

  if( imm & 0x2)
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc,E_dest,127,64), E_temp2)); 	  
  else
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc,E_dest,127,64), vc_bvConstExprFromLL(vc, 64,0) )); 	  

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}



void haddpdHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;

  z3::sort fl = vc->bv_sort(64);
  z3::func_decl dadd = z3::function("addd", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);

  Expr e1_src1 = vc_bvExtract(vc,E_src1, 63, 0);
  Expr e2_src1 = vc_bvExtract(vc,E_src1, 127, 64);	

  Expr e1_src2 = vc_bvExtract(vc,E_src2, 63, 0);
  Expr e2_src2 = vc_bvExtract(vc,E_src2, 127, 64);


  Expr e1_dest = vc_bvExtract(vc,E_dest, 63, 0);
  Expr e2_dest = vc_bvExtract(vc,E_dest, 127, 64);

  retval = vc_andExpr(vc, retval, e1_dest == dadd(e2_src1,e1_src1)); 
  retval = vc_andExpr(vc, retval, e2_dest == dadd(e2_src2,e1_src2)); 

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

}

void haddpsHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;

  z3::sort fl = vc->bv_sort(32);
  z3::func_decl fadd = z3::function("addf", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);

  Expr e1_src1 = vc_bvExtract(vc,E_src1, 31, 0);
  Expr e2_src1 = vc_bvExtract(vc,E_src1, 63, 32);
  Expr e3_src1 = vc_bvExtract(vc,E_src1, 95, 64);
  Expr e4_src1 = vc_bvExtract(vc,E_src1, 127, 96);


  Expr e1_src2 = vc_bvExtract(vc,E_src2, 31, 0);
  Expr e2_src2 = vc_bvExtract(vc,E_src2, 63, 32);
  Expr e3_src2 = vc_bvExtract(vc,E_src2, 95, 64);
  Expr e4_src2 = vc_bvExtract(vc,E_src2, 127, 96);


  Expr e1_dest = vc_bvExtract(vc,E_dest, 31, 0);
  Expr e2_dest = vc_bvExtract(vc,E_dest, 63, 32);
  Expr e3_dest = vc_bvExtract(vc,E_dest, 95, 64);
  Expr e4_dest = vc_bvExtract(vc,E_dest, 127, 96);

  retval = vc_andExpr(vc, retval, e1_dest == fadd(e2_src1,e1_src1)); 
  retval = vc_andExpr(vc, retval, e2_dest == fadd(e4_src1,e3_src1)); 
  retval = vc_andExpr(vc, retval, e3_dest == fadd(e2_src2,e1_src2)); 
  retval = vc_andExpr(vc, retval, e4_dest == fadd(e4_src2,e3_src2)); 

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

}


void idivHandler(v_data d, unsigned int bitWidth, Expr E_src2) {

  VC&vc = d.vc;
  //	SS_Id rdx = rdx;
  //	SS_Id rax = rax;
  if(bitWidth > 8)
  {
    Expr E_src1 = vc_bvConcatExpr(vc, vc_bvExtract(vc, regExprWVN(vc, rdx, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
    E_src2 = vc_bvSignExtend(vc, E_src2, 2*bitWidth);
    //E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
    Expr E_quotient = vc_bvExtract(vc, vc_sbvDivExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_remainder = vc_bvExtract(vc, vc_sbvModExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_rem_dest = vc_bvExtract(vc, regExprWVN(vc, rdx, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_quot_dest = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);

    Expr retval = vc_andExpr(vc, EqExpr(vc, E_quot_dest, E_quotient), EqExpr(vc, E_rem_dest, E_remainder)) ;
    if( bitWidth < V_UNITSIZE)
    {
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rdx, d, bitWidth));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, bitWidth));

    }
    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
    d.constraints.push_back(retval); 
  }
  else
  {
    Expr E_src1 = vc_bvConcatExpr(vc, vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), (2*bitWidth) - 1, bitWidth), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
    E_src2 = vc_bvSignExtend(vc, E_src2, 2*bitWidth);
    //E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2);
    Expr E_quotient = vc_bvExtract(vc, vc_sbvDivExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_remainder = vc_bvExtract(vc, vc_sbvModExpr(vc, 2*bitWidth, E_src1, E_src2), bitWidth -1, 0);
    Expr E_rem_dest = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), (2*bitWidth) - 1, bitWidth);
    Expr E_quot_dest = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);

    Expr retval = vc_andExpr(vc, EqExpr(vc, E_quot_dest, E_quotient), EqExpr(vc, E_rem_dest, E_remainder)) ;

    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, 2*bitWidth));

    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
    d.constraints.push_back(retval); 	  
  }
}


void imul1Handler(v_data d, unsigned int bitWidth, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;
  //	SS_Id rdx = rdx;
  //	SS_Id rax = rax;
  if(bitWidth > 8)
  {
    E_src2 = vc_bvSignExtend(vc, E_src2, 2*bitWidth);
    Expr E_src1 = vc_bvSignExtend(vc, vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0), 2*bitWidth);
    Expr E_rdx = vc_bvExtract(vc, regExprWVN(vc, rdx, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_rax = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_dest = vc_bvConcatExpr(vc, E_rdx, E_rax);

    Expr E_result = vc_bvMultExpr(vc, 2*bitWidth, E_src1, E_src2 );
    Expr retval = EqExpr(vc, E_dest, E_result);

    if(dest_is_reg && bitWidth < V_UNITSIZE)
    {
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rdx, d, bitWidth));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, bitWidth));

    }

    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
    d.constraints.push_back(retval);

    unsigned int flagBitWidth = 2*bitWidth;
    Expr E_flag_src1 = vc_bvSignExtend(vc, E_rax, flagBitWidth);
    Expr E_flag_src2 = E_dest;
    Expr E_flag_result = vc_notExpr(vc, EqExpr(vc, E_flag_src1, E_flag_src2));
    setFlag(vc,d.Vnprime,V_OF, setFlag(vc,d.Vnprime,V_CF, E_flag_result, d.constraints, d.post_suffix), d.constraints, d.post_suffix);
    //Rest flags are undefined
  }
  else
  {
    E_src2 = vc_bvSignExtend(vc, E_src2, 2*bitWidth);
    Expr E_src1 = vc_bvSignExtend(vc, vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0), 2*bitWidth);
    Expr E_rdx = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), (2*bitWidth) - 1, bitWidth);
    Expr E_rax = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_dest = vc_bvConcatExpr(vc, E_rdx, E_rax);

    Expr E_result = vc_bvMultExpr(vc, 2*bitWidth, E_src1, E_src2 );
    Expr retval = EqExpr(vc, E_dest, E_result);

    if(dest_is_reg) retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, 2*bitWidth));

    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
    d.constraints.push_back(retval);

    unsigned int flagBitWidth = 2*bitWidth;
    Expr E_flag_src1 = vc_bvSignExtend(vc, E_rax, flagBitWidth);
    Expr E_flag_src2 = E_dest;
    Expr E_flag_result = vc_notExpr(vc, EqExpr(vc, E_flag_src1, E_flag_src2));
    setFlag(vc,d.Vnprime,V_OF, setFlag(vc,d.Vnprime,V_CF, E_flag_result, d.constraints, d.post_suffix), d.constraints, d.post_suffix);	  	  
  }
}



void imul3Handler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;

  Expr E_result = vc_bvMultExpr(vc, bitWidth, E_src1, E_src2 );
  Expr retval = EqExpr(vc, E_dest, E_result);

  if( bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }

  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);

  unsigned int flagBitWidth = 2*bitWidth;
  Expr E_flag_src1 = vc_bvSignExtend(vc, E_src1, flagBitWidth);
  Expr E_flag_src2 = vc_bvSignExtend(vc, E_src2, flagBitWidth);
  Expr E_prod = vc_bvMultExpr(vc, flagBitWidth, E_flag_src1, E_flag_src2 );
  //TODO Expr E_old_prod = vc_bvSignExtend(vc, E_result, flagBitWidth);
  //Expr E_flag_result = vc_notExpr(vc, EqExpr(vc, E_prod, E_old_prod));
  Expr E_flag_result = vc_andExpr(vc, 
      vc_notExpr(vc, EqExpr(vc, vc_bvExtract(vc, E_prod, flagBitWidth-1, bitWidth), vc_bvConstExprFromLL(vc, bitWidth, 0))),
      vc_notExpr(vc, EqExpr(vc, vc_bvExtract(vc, E_prod, flagBitWidth-1, bitWidth), vc_bvConstExprFromLL(vc, bitWidth, -1))));
  //CF = OF = (temp=/=dest)
  setFlag(vc,d.Vnprime,V_OF, setFlag(vc,d.Vnprime,V_CF, E_flag_result, d.constraints, d.post_suffix), d.constraints, d.post_suffix);
  //Rest flags are undefined
}

//imul when mul is an uninterpreted function
void imul64rrHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VALIDATOR_ERROR("imul64rr suspisciously commented out -- aborting");
  /*	VC&vc = d.vc;

      addmul64rr(vc, E_src1, E_src2, E_dest, mul, d);*/
}

//OF is SET iff original value is -1
void incHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src, bool dest_is_reg=true) {
  VC&vc = d.vc;
  //vc_printExpr(vc, E_dest); vc_printExpr(vc, E_src); cout << endl << bitWidth << endl ;

  Expr E_result = vc_bvPlusExpr(vc, bitWidth+1, 
      vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1, 0), E_src),
      vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1, 0), vc_bvConstExprFromLL(vc, bitWidth, 1)));
  Expr retval = EqExpr(vc, E_dest, vc_bvExtract(vc, E_result, bitWidth - 1, 0));
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval); 

  setFlag(vc,d.Vnprime,V_OF, EqExpr(vc,E_dest,vc_bvConstExprFromLL(vc, bitWidth,0)), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}


void lahfHandler(v_data d) {

  VC&vc = d.vc;
  Expr E_rax_post = regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE);
  Expr E_src = regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE);
  Expr retval = vc_trueExpr(vc);
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_src, 63, 16),  vc_bvExtract(vc, E_rax_post, 63, 16)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_src, 7, 0),  vc_bvExtract(vc, E_rax_post, 7, 0)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 15), getBoolExpr(vc, V_SF, d.pre_suffix, d.Vn)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 14), getBoolExpr(vc, V_ZF, d.pre_suffix, d.Vn)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 13), vc_falseExpr(vc)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 12), getBoolExpr(vc, V_AF, d.pre_suffix, d.Vn)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 11), vc_falseExpr(vc)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 10), getBoolExpr(vc, V_PF, d.pre_suffix, d.Vn)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 9), vc_trueExpr(vc)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_rax_post, 8), getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}



void leaHandler(v_data d, unsigned int bitWidth) {

  VC&vc = d.vc;

  SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
  Expr E_dest = vc_bvExtract(vc,regExprWVN(vc, id_dest, d.post_suffix, d.Vnprime, V_UNITSIZE),bitWidth - 1, 0);
  auto addr = d.instr.get_operand<M8>(1);
  Expr E_addr = vc_varExpr(vc, ("ADDRTEMPEXPR"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, V_UNITSIZE));

  Expr retval = ConstrainAddr(vc, E_addr, addr, d); //Compute 64 bit address
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, vc_bvExtract(vc, E_addr, bitWidth-1,0)));

  if(bitWidth < V_UNITSIZE)
    retval = vc_andExpr(vc, retval, UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));   

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval);  
}



void maxpsHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  z3::sort pfl = vc->bv_sort(128);
  z3::func_decl fpmax = z3::function("maxfp", pfl, pfl, pfl);
  Expr E_result = fpmax(E_src1, E_src2);
  Expr retval = EqExpr(vc, E_dest, E_result);
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}


void movHandler(v_data d, unsigned int bitWidthTarget, unsigned int bitWidthSource, Expr E_dest, Expr E_src, bool signExtend,  bool dest_is_reg=true) {

  VC&vc = d.vc;
  E_dest = vc_bvExtract(vc, E_dest, bitWidthTarget-1,0); //Noop except for xmm
  if(signExtend && bitWidthTarget>bitWidthSource)
    E_src = vc_bvSignExtend(vc, E_src, bitWidthTarget);
  else if(bitWidthTarget > bitWidthSource)
    E_src = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidthTarget-bitWidthSource, 0), E_src);
  else if ( bitWidthSource > bitWidthTarget)
    E_src = vc_bvExtract(vc, E_src, bitWidthTarget-1, 0);
  Expr retval = EqExpr(vc, E_dest, E_src);
  if(dest_is_reg /*&& bitWidthTarget < full_size*/)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0))) + (is_dest_xmm(E_dest) ? XMM_BEG : 0);
    uint full_size = V_UNITSIZE*all_state_info.second[id_dest];
    if(bitWidthTarget<full_size)
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidthTarget));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}


void movddupHandler(v_data d, Expr E_dest, Expr E_src) {

  VC&vc = d.vc;
  E_src = vc_bvExtract(vc, E_src, 63, 0);
  Expr retval = vc_trueExpr(vc);
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63,0), vc_bvExtract(vc, E_src, 63,0))); 
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127,64), vc_bvExtract(vc, E_src, 63,0))); 

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

}



void movhHandler(v_data d, Expr E_dest, Expr E_src, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr retval = vc_trueExpr(vc);
  if(dest_is_reg)
  {
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 64), vc_bvExtract(vc, E_src, 63, 0))); 
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0))) + (is_dest_xmm(E_dest) ? XMM_BEG : 0);
    Expr E_dest_pre = regExprWVN(vc, id_dest, d.pre_suffix, d.Vn, 128);
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 0), vc_bvExtract(vc, E_dest_pre, 63, 0))); 	  
  }
  else
  {
    retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, vc_bvExtract(vc, E_src, 127, 64))); 	  
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}

void movhlpsHandler(v_data d, Expr E_dest, Expr E_src, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr retval = vc_trueExpr(vc);
  if (!dest_is_reg)
    throw VALIDATOR_ERROR("movhlps only supports register destination");
  {
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 0), vc_bvExtract(vc, E_src, 127, 64))); 
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0))) + (is_dest_xmm(E_dest) ? XMM_BEG : 0);
    Expr E_dest_pre = regExprWVN(vc, id_dest, d.pre_suffix, d.Vn, 128);
    retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 64), vc_bvExtract(vc, E_dest_pre, 127, 64))); 	  
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}





void muldHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

#define DMULPATT(x)\
  {\
    Expr E_result = vc_bvExtract(vc, E_dest, x+63, x);\
    Expr E_arg1 = vc_bvExtract(vc, E_src1, x+63, x);\
    Expr E_arg2 = vc_bvExtract(vc, E_src2, x+63, x);\
    retval = vc_andExpr(vc, retval, (E_result == dmul(E_arg1,E_arg2)));\
  }

  VC&vc = d.vc;
  uint bitWidth = numops*64; 
  z3::sort fl = vc->bv_sort(64);
  z3::func_decl dmul = z3::function("muld", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);
  if(numops==1)
  {
    DMULPATT(0)
  }
  else
  {
    DMULPATT(0)
      DMULPATT(64)
  }
  if(dest_is_reg && numops == 1)
  {
    SS_Id id_dest = XMM_BEG+getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

#undef DMULPATT	
}



void mulfHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

#define FMULPATT(x)\
  {\
    Expr E_result = vc_bvExtract(vc, E_dest, x+31, x);\
    Expr E_arg1 = vc_bvExtract(vc, E_src1, x+31, x);\
    Expr E_arg2 = vc_bvExtract(vc, E_src2, x+31, x);\
    retval = vc_andExpr(vc, retval, (E_result == fmul(E_arg1,E_arg2)));\
  }

  VC&vc = d.vc;
  uint bitWidth = numops*32; 
  z3::sort fl = vc->bv_sort(32);
  z3::func_decl fmul = z3::function("mulf", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);
  if(numops==1)
  {
    FMULPATT(0)
  }
  else
  {
    FMULPATT(0)
    FMULPATT(32)
    FMULPATT(64)
    FMULPATT(96)	  
  }
  if(dest_is_reg && numops < 4)
  {
    SS_Id id_dest = XMM_BEG+getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

#undef FMULPATT
}

//mul64r handler writes a 64 bit unsigned multiplication with 128 bit results in terms of
//four 64-bit signed multiplications each having a 64 bit result
void mul64rHandler(v_data d) {

  VALIDATOR_ERROR("mul64r suspisciously commented out -- aborting.");
  /*	VC&vc = d.vc;
      const VersionNumber& Vn = d.Vn;
      const VersionNumber& Vnprime = d.Vnprime;
      string pre_suffix = d.pre_suffix;
      string post_suffix = d.post_suffix;

      SS_Id id_src =
      getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));

      Expr E_rax = regExprWVN(vc, rax, post_suffix, Vnprime, V_UNITSIZE);
      Expr E_rdx = regExprWVN(vc, rdx, post_suffix, Vnprime, V_UNITSIZE);

      Expr E_arg1 = regExprWVN(vc, rax, pre_suffix, Vn, V_UNITSIZE);
      Expr E_arg2 = regExprWVN(vc, id_src, pre_suffix, Vn, V_UNITSIZE);

      Expr E_A = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 32, 0),
      vc_bvExtract(vc, E_arg1, 63, 32));
      Expr E_B = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 32, 0),
      vc_bvExtract(vc, E_arg1, 31, 0));
      Expr E_C = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 32, 0),
      vc_bvExtract(vc, E_arg2, 63, 32));
      Expr E_D = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 32, 0),
      vc_bvExtract(vc, E_arg2, 31, 0));

      Expr E_AC = regExpr(vc, "AC"+d.pre_suffix+itoa(d.instr_no));
      Expr E_BD = regExpr(vc, "BD"+d.pre_suffix+itoa(d.instr_no));
      Expr E_AD = regExpr(vc, "AD"+d.pre_suffix+itoa(d.instr_no));
      Expr E_BC = regExpr(vc, "BC"+d.pre_suffix+itoa(d.instr_no));

      addmul64rr(vc,E_A, E_C, E_AC, mul,d);
      addmul64rr(vc,E_B, E_D, E_BD, mul,d);
      addmul64rr(vc,E_A, E_D, E_AD, mul,d);
      addmul64rr(vc,E_B, E_C, E_BC, mul,d);

      Expr carry1 = regExpr(vc, "carry1"+d.pre_suffix+itoa(d.instr_no),
      V_UNITSIZE);
      Expr carry2 = regExpr(vc, "carry2"+d.pre_suffix+itoa(d.instr_no),
      V_UNITSIZE);

      Expr E_ADpBC = regExpr(vc, "ADpBC"+d.pre_suffix+itoa(d.instr_no));

      {
      Expr E_result = vc_varExpr(vc,
      ("ADpBCtemp"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, 66)
      );
      Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 2, 0), E_AD);
      Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 2, 0), E_BC);
      Expr retval = vc_eqExpr(vc, E_result, vc_bvPlusExpr(vc, 66,
      E_arg1, E_arg2));
      retval = vc_andExpr(vc, retval, vc_eqExpr(vc, E_ADpBC,
      vc_bvExtract(vc, E_result, 63, 0)));
      retval = vc_andExpr(vc, retval, vc_iffExpr(vc,
      vc_bvBoolExtract_One(vc, carry1, 32), vc_orExpr(vc,
      vc_bvBoolExtract_One(vc, E_result, 64), vc_bvBoolExtract_One(vc,
      E_result, 65))));
      retval = vc_andExpr(vc, retval, vc_eqExpr(vc, vc_bvExtract(vc,
      carry1, 63, 33), vc_bvConstExprFromInt(vc, 31, 0)));
      retval = vc_andExpr(vc, retval, vc_eqExpr(vc, vc_bvExtract(vc,
      carry1, 31, 0), vc_bvConstExprFromInt(vc, 32, 0)));
  //cout << "Adding constraint ";  vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
  }

  {
  Expr E_result = vc_varExpr(vc,
  ("BDpADpBCtemp"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc,
  66) );
  Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 2, 0), E_BD);
  Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 2, 0),
  vc_bvConcatExpr(vc, vc_bvExtract(vc, E_ADpBC, 31, 0),
  vc_bvConstExprFromInt(vc, 32, 0)));
  Expr retval = vc_eqExpr(vc, E_result, vc_bvPlusExpr(vc, 66,
        E_arg1, E_arg2));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, E_rax,
        vc_bvExtract(vc, E_result, 63, 0)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc,
        vc_bvBoolExtract_One(vc, carry2, 0), vc_orExpr(vc,
          vc_bvBoolExtract_One(vc, E_result, 64), vc_bvBoolExtract_One(vc,
            E_result, 65))));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, vc_bvExtract(vc,
          carry2, 63, 1), vc_bvConstExprFromInt(vc, 63, 0)));
  //cout << "Adding constraint ";  vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
}

Expr E_sumexpr = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 32,
      0), vc_bvExtract(vc, E_ADpBC, 63, 32));
E_sumexpr = vc_bvPlusExpr(vc, V_UNITSIZE, E_sumexpr, E_AC);
E_sumexpr = vc_bvPlusExpr(vc, V_UNITSIZE, E_sumexpr, carry1);
E_sumexpr = vc_bvPlusExpr(vc, V_UNITSIZE, E_sumexpr, carry2);
Expr retval = vc_eqExpr(vc, E_rdx, E_sumexpr);

//cout << "Adding constraint ";  vc_printExpr(vc, retval);  cout << "\n";
d.constraints.push_back(retval);
*/
}




void negHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr E_result = vc_bvUMinusExpr(vc, E_src );
  Expr retval = EqExpr(vc, E_dest, E_result);
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval); 
  setFlag(vc,d.Vnprime,V_CF, vc_notExpr(vc, EqExpr(vc, E_src, vc_bvConstExprFromLL(vc, bitWidth, 0))), d.constraints, d.post_suffix);     
  setFlag(vc,d.Vnprime,V_OF, vc_andExpr(vc, vc_bvBoolExtract_One(vc, E_src, bitWidth -1 ), vc_bvBoolExtract_One(vc, E_dest, bitWidth -1 )), d.constraints, d.post_suffix);     	
  setSFPFZF(E_result, d, bitWidth);
}

void notHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr E_result = vc_bvNotExpr(vc, E_src );
  Expr retval = EqExpr(vc, E_dest, E_result);
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval); 
}


void orHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr retval = EqExpr(vc, E_dest, vc_bvOrExpr(vc, E_src1, E_src2));
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}

#define ALTZZA(D,B,S) retval = vc_andExpr(vc, retval, EqExpr(vc, D, \
                               vc_iteExpr(vc, vc_sbvLtExpr(vc, B, vc_bv32ConstExprFromInt(vc, 0)), vc_bvConstExprFromLL(vc, 16, 0), S )));
                               
#define AGTFFA(D,B,S) retval = vc_andExpr(vc, retval, EqExpr(vc, D, \
                               vc_iteExpr(vc, vc_sbvGtExpr(vc, B, vc_bv32ConstExprFromInt(vc, 0x0FFFF)), vc_bvConstExprFromLL(vc, 16, 0xFFFF), S )));
                     
#define HALTZZAAGFTFFA(X,Y)   ALTZZA(vc_bvExtract(vc, E_temp, (16*X)-1,16*(X-1)), vc_bvExtract(vc, Y, ((32*X)-1)%128, (32*(X-1))%128), vc_bvExtract(vc, E_src1, (16*X)-1, 16*(X-1))) \
                              AGTFFA(vc_bvExtract(vc, E_dest, (16*X)-1,16*(X-1)), vc_bvExtract(vc, Y, ((32*X)-1)%128, (32*(X-1))%128), vc_bvExtract(vc, E_temp, (16*X)-1, 16*(X-1)))

void packusdwHandler(v_data d, unsigned int bitWidthSrc, unsigned int bitWidthTarget,  Expr E_dest, Expr E_src1, Expr E_src2) 
{
  VC&vc = d.vc;
  Expr retval = vc_trueExpr(vc);
 
  Expr E_temp = vc_varExpr(vc, ("PACKTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, 128) );
  HALTZZAAGFTFFA(1,E_src1)
  HALTZZAAGFTFFA(2,E_src1)
  HALTZZAAGFTFFA(3,E_src1)
  HALTZZAAGFTFFA(4,E_src1)
  HALTZZAAGFTFFA(5,E_src2)
  HALTZZAAGFTFFA(6,E_src2)
  HALTZZAAGFTFFA(7,E_src2)
  HALTZZAAGFTFFA(8,E_src2)
  
  ADD_CONS(retval)
  d.constraints.push_back(retval);
}


void paddHandler(v_data d, unsigned int opWidth, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;
  if (opWidth != 32 || bitWidth != 128) {
    throw VALIDATOR_ERROR("Only opWidth of 32 and bitWidth of 128 is supported for padd");
  }
  Expr retval = vc_trueExpr(vc);
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 31, 0), vc_bvPlusExpr(vc, 32, vc_bvExtract(vc, E_src1, 31, 0), vc_bvExtract(vc, E_src2, 31, 0))));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 32), vc_bvPlusExpr(vc, 32, vc_bvExtract(vc, E_src1, 63, 32), vc_bvExtract(vc, E_src2, 63, 32))));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 95, 64), vc_bvPlusExpr(vc, 32, vc_bvExtract(vc, E_src1, 95, 64), vc_bvExtract(vc, E_src2, 95, 64))));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 96), vc_bvPlusExpr(vc, 32, vc_bvExtract(vc, E_src1, 127, 96), vc_bvExtract(vc, E_src2, 127, 96))));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}

void palignrHandler(v_data d, unsigned int numops, unsigned int bitWidth, unsigned int immediate, Expr E_dest, Expr E_src1, Expr E_src2) {

  //FIXME: this is unsound for memory: memory must be aligned to a 128 bit boundary.

  if (bitWidth != 128 || numops != 3) {
    VALIDATOR_ERROR("palign only implemented for 128-bit operands and 3 arguments");
    //to make this work for 128-bits and 4 arguments, you just need to clear the
    //ymm register bits.
  }

  VC&vc = d.vc;

  // The trick to doing this efficiently is matching which bits of the sources
  // are going to go to which bits of the destination, without actually doing
  // bitshifting or introducting temporaries.

  // First, figure out how many bits we need to "shift" by
  int bits_to_shift = ((immediate & 0xff) * 8);

  // If it's too high, then we zero the output registers.
  if (bits_to_shift > 255) {
    Expr zero_bv = vc_bvConstExprFromInt(vc, 128, 0); 
    Expr equals = EqExpr(vc, E_dest, zero_bv);
    d.constraints.push_back(equals);
    return;
  }

  // If it's between 129 and 255 (inclusive), we copy bits only from src1.
  if (129 <= bits_to_shift && bits_to_shift <= 255) {
    // DEST[0, 255-i] <- SRC1[i-128, 127]  (256 - i bits)

    Expr src1_extract = vc_bvExtract(vc, E_src1, 127, bits_to_shift - 128);
    Expr dest_to_src1 = vc_bvExtract(vc, E_dest, 255 - bits_to_shift, 0);

    Expr dest_src1_equal = EqExpr(vc, dest_to_src1, src1_extract);
    d.constraints.push_back(dest_src1_equal);

    // DEST[256-i, 127] <- zero (i - 128 bits)
    Expr zero = vc_bvConstExprFromInt(vc, bits_to_shift-128, 0);
    Expr dest_zero = vc_bvExtract(vc, E_dest, 127, 256 - bits_to_shift);
    assert(bits_to_shift - 128 == 127 - (256 - bits_to_shift) + 1);

    Expr equal = EqExpr(vc, dest_zero, zero);
    d.constraints.push_back(equal);

    return;
  }

  // If it's exactly 128 bits, we copy src1 into dest
  if (bits_to_shift == 128) {
    Expr equals = EqExpr(vc, E_dest, E_src1);
    d.constraints.push_back(equals);
    return;
  }

  // If it's between 1 and 127 (inclusive) we copy parts of src1 and src2
  if (1 <= bits_to_shift && bits_to_shift <= 127) {
    // DEST[0, 127-i] = SRC2[i, 127]  (128-i bits)
    Expr src2_extract = vc_bvExtract(vc, E_src2, 127, bits_to_shift);
    Expr dest_to_src2 = vc_bvExtract(vc, E_dest, 127-bits_to_shift, 0);

    Expr dest_src2_equal = EqExpr(vc, dest_to_src2, src2_extract);
    d.constraints.push_back(dest_src2_equal);

    // DEST[128-i, 127] = SRC1[i-1, 0]  (i bits)
    Expr src1_extract = vc_bvExtract(vc, E_src1, bits_to_shift - 1, 0);
    Expr dest_to_src1 = vc_bvExtract(vc, E_dest, 127, 128 - bits_to_shift);

    Expr dest_src1_equal = EqExpr(vc, dest_to_src1, src1_extract);
    d.constraints.push_back(dest_src1_equal);
  }

  // If it's 0, we just copy SRC2 into the destination
  if (bits_to_shift == 0) {
    Expr equals = EqExpr(vc, E_dest, E_src2);
    d.constraints.push_back(equals);
    return;
  }

  VALIDATOR_ERROR("palignr internal error; bits_to_shift out of bounds?");

}

void pandnHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;

  Expr E_result = vc_bvAndExpr(vc,vc_bvNotExpr(vc, E_src1) , E_src2 );
  Expr retval = EqExpr(vc, E_dest, E_result);
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}

#define MAXMACRO(R,X,Y, U, L)  Expr R = vc_iteExpr(vc, vc_bvGtExpr(vc, vc_bvExtract(vc, X, U,L), vc_bvExtract(vc, Y, U,L)),\
                                    vc_bvExtract(vc, X, U,L), vc_bvExtract(vc, Y, U,L));
#define RETMACRO(D,R, U, L) retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, D, U, L), R));                                    
void pmaxsdHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  MAXMACRO(E_result1,E_src1, E_src2, 31,0) 
  MAXMACRO(E_result2,E_src1, E_src2, 63,32) 
  MAXMACRO(E_result3,E_src1, E_src2, 95,64) 
  MAXMACRO(E_result4,E_src1, E_src2, 127,96) 

  Expr retval = vc_trueExpr(vc);
  RETMACRO(E_dest, E_result1,31,0)
  RETMACRO(E_dest, E_result2,63,32)
  RETMACRO(E_dest, E_result3,95,64)
  RETMACRO(E_dest, E_result4,127,96)
  
  ADD_CONS(retval);
  d.constraints.push_back(retval); 
}

#define MINMACRO(R,X,Y, U, L)  Expr R = vc_iteExpr(vc, vc_bvLtExpr(vc, vc_bvExtract(vc, X, U,L), vc_bvExtract(vc, Y, U,L)),\
                                    vc_bvExtract(vc, X, U,L), vc_bvExtract(vc, Y, U,L));
void pminuwHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  MINMACRO(E_result1,E_src1, E_src2, 15,0) 
  MINMACRO(E_result2,E_src1, E_src2, 31,16) 
  MINMACRO(E_result3,E_src1, E_src2, 47,32) 
  MINMACRO(E_result4,E_src1, E_src2, 63,48) 
  MINMACRO(E_result5,E_src1, E_src2, 79,64) 
  MINMACRO(E_result6,E_src1, E_src2, 95,80) 
  MINMACRO(E_result7,E_src1, E_src2, 111,96) 
  MINMACRO(E_result8,E_src1, E_src2, 127,112) 

  Expr retval = vc_trueExpr(vc);
  RETMACRO(E_dest, E_result1,15,0)
  RETMACRO(E_dest, E_result2,31,16)
  RETMACRO(E_dest, E_result3,47,32)
  RETMACRO(E_dest, E_result4,63,48)
  RETMACRO(E_dest, E_result5,79,64)
  RETMACRO(E_dest, E_result6,95,80)
  RETMACRO(E_dest, E_result7,111,96)
  RETMACRO(E_dest, E_result8,127,112)
  
  ADD_CONS(retval);
  d.constraints.push_back(retval); 
}
#undef MINMACRO
#undef MAXMACRO

void pmovsxdqHandler(v_data d, Expr E_dest, Expr E_src)
{
  VC&vc = d.vc;
  
  Expr E_first = vc_bvSignExtend(vc, vc_bvExtract(vc, E_src, 31, 0), 64);
  Expr E_second = vc_bvSignExtend(vc, vc_bvExtract(vc, E_src, 63, 32), 64);
  Expr retval = vc_andExpr(vc, EqExpr(vc, E_first, vc_bvExtract(vc, E_dest, 127, 64)),EqExpr(vc, E_second, vc_bvExtract(vc, E_dest, 63, 0)));

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}

void pmovsxwqHandler(v_data d, Expr E_dest, Expr E_src)
{
  VC&vc = d.vc;
  
  Expr E_first = vc_bvSignExtend(vc, vc_bvExtract(vc, E_src, 31, 16), 64);
  Expr E_second = vc_bvSignExtend(vc, vc_bvExtract(vc, E_src, 15, 0), 64);
  Expr retval = vc_andExpr(vc, EqExpr(vc, E_first, vc_bvExtract(vc, E_dest, 127, 64)),EqExpr(vc, E_second, vc_bvExtract(vc, E_dest, 63, 0)));

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}

void pmovzxbdHandler(v_data d, Expr E_dest, Expr E_src)
{
  VC&vc = d.vc;
  
  Expr E_first = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,24,0), vc_bvExtract(vc, E_src, 7, 0));
  Expr E_second = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,24,0), vc_bvExtract(vc, E_src, 15, 8));
  Expr E_third = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,24,0), vc_bvExtract(vc, E_src, 23, 16));
  Expr E_fourth = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,24,0), vc_bvExtract(vc, E_src, 31, 24));
  Expr retval = vc_andExpr(vc, EqExpr(vc, E_first, vc_bvExtract(vc, E_dest, 31, 0)),EqExpr(vc, E_second, vc_bvExtract(vc, E_dest, 63, 32)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_third, vc_bvExtract(vc, E_dest, 95, 64)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_fourth, vc_bvExtract(vc, E_dest, 127, 96)));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}


void pmovzxbwHandler(v_data d, Expr E_dest, Expr E_src)
{
  VC&vc = d.vc;
  
  Expr E_first = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 7, 0));
  Expr E_second = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 15, 8));
  Expr E_third = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 23, 16));
  Expr E_fourth = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 31, 24));
  Expr E_fifth = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 39, 32));
  Expr E_sixth = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 47, 40));
  Expr E_seventh = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 55, 48));
  Expr E_eight = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,8,0), vc_bvExtract(vc, E_src, 63, 56));
  Expr retval = vc_andExpr(vc, EqExpr(vc, E_first, vc_bvExtract(vc, E_dest, 15, 0)),EqExpr(vc, E_second, vc_bvExtract(vc, E_dest, 31, 16)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_third, vc_bvExtract(vc, E_dest, 47, 32)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_fourth, vc_bvExtract(vc, E_dest, 63, 48)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_fifth, vc_bvExtract(vc, E_dest, 79, 64)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_sixth, vc_bvExtract(vc, E_dest, 95, 80)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_seventh, vc_bvExtract(vc, E_dest, 111, 96)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_eight, vc_bvExtract(vc, E_dest, 127, 112)));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}

void pmovzxwdHandler(v_data d, Expr E_dest, Expr E_src)
{
  VC&vc = d.vc;
  
  Expr E_first = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,16,0), vc_bvExtract(vc, E_src, 15, 0));
  Expr E_second = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,16,0), vc_bvExtract(vc, E_src, 31, 16));
  Expr E_third = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,16,0), vc_bvExtract(vc, E_src, 47, 32));
  Expr E_fourth = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,16,0), vc_bvExtract(vc, E_src, 63, 48));
  Expr retval = vc_andExpr(vc, EqExpr(vc, E_first, vc_bvExtract(vc, E_dest, 31, 0)),EqExpr(vc, E_second, vc_bvExtract(vc, E_dest, 63, 32)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_third, vc_bvExtract(vc, E_dest, 95, 64)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_fourth, vc_bvExtract(vc, E_dest, 127, 96)));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}


void pmovzxwqHandler(v_data d, Expr E_dest, Expr E_src)
{
  VC&vc = d.vc;
  
  Expr E_first = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,48,0), vc_bvExtract(vc, E_src, 31, 16));
  Expr E_second = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc,48,0), vc_bvExtract(vc, E_src, 15, 0));
  Expr retval = vc_andExpr(vc, EqExpr(vc, E_first, vc_bvExtract(vc, E_dest, 127, 64)),EqExpr(vc, E_second, vc_bvExtract(vc, E_dest, 63, 0)));

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval); 
}


void popcnt16Handler(v_data d, Expr E_dest, Expr E_src) {

#define SUM_INNER(x, shift, hex)\
  vc_bvPlusExpr(vc, 16,\
      vc_bvAndExpr(vc, (x), vc_bvConstExprFromLL(vc, 16,  (hex))),\
      vc_bvAndExpr(vc, vc_bvRightShiftExprExpr(vc, 16, (x), vc_bvConstExprFromInt(vc, 16, (shift))), vc_bvConstExprFromLL(vc, 16, (hex)))\
      )\

#define SUM_OUTER(x, s1, s2, s3, s4)\
  retval = vc_andExpr(vc, retval, EqExpr(vc, (s1), SUM_INNER(x,  1,  0x55555)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s2), SUM_INNER(s1, 2,  0x3333)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s3), SUM_INNER(s2, 4,  0x0F0F)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s4), SUM_INNER(s3, 8,  0x00FF)));\

#define VAR_EXPR(s,w)\
  vc_varExpr(vc, ((s)+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, (w)));



  VC&vc = d.vc;
  Expr retval = vc_trueExpr(vc);

  Expr E_temp1 = VAR_EXPR("TEMP1POPCNT",16);
  Expr E_temp2 = VAR_EXPR("TEMP2POPCNT",16);
  Expr E_temp3 = VAR_EXPR("TEMP3POPCNT",16);
  Expr E_temp4 = VAR_EXPR("TEMP4POPCNT",16);

  SUM_OUTER(E_src, E_temp1, E_temp2, E_temp3, E_temp4)

    retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, E_temp4));


  SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
  retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, 16));

  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);  
  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_PF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_SF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_ZF, EqExpr(vc, E_src, vc_bvConstExprFromLL(vc, 16, 0)), d.constraints, d.post_suffix);
#undef SUM_INNER
#undef SUM_OUTER
#undef VAR_EXPR



}

void popcnt32Handler(v_data d, Expr E_dest, Expr E_src) {

#define SUM_INNER(x, shift, hex)\
  vc_bvPlusExpr(vc, 32,\
      vc_bvAndExpr(vc, (x), vc_bvConstExprFromLL(vc, 32,  (hex))),\
      vc_bvAndExpr(vc, vc_bvRightShiftExprExpr(vc, 32, (x), vc_bv32ConstExprFromInt(vc, (shift))), vc_bvConstExprFromLL(vc, 32, (hex)))\
      )\

#define SUM_OUTER(x, s1, s2, s3, s4, s5)\
  retval = vc_andExpr(vc, retval, EqExpr(vc, (s1), SUM_INNER(x,  1,  0x55555555)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s2), SUM_INNER(s1, 2,  0x33333333)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s3), SUM_INNER(s2, 4,  0x0F0F0F0F)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s4), SUM_INNER(s3, 8,  0x00FF00FF)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s5), SUM_INNER(s4, 16, 0x0000FFFF)));\

#define VAR_EXPR(s,w)\
  vc_varExpr(vc, ((s)+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, (w)));



  VC&vc = d.vc;
  Expr retval = vc_trueExpr(vc);

  Expr E_temp1 = VAR_EXPR("TEMP1POPCNT",32);
  Expr E_temp2 = VAR_EXPR("TEMP2POPCNT",32);
  Expr E_temp3 = VAR_EXPR("TEMP3POPCNT",32);
  Expr E_temp4 = VAR_EXPR("TEMP4POPCNT",32);
  Expr E_temp5 = VAR_EXPR("TEMP5POPCNT",32);

  SUM_OUTER(E_src, E_temp1, E_temp2, E_temp3, E_temp4, E_temp5)

    retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, E_temp5));


  SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
  retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, 32));

  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);  
  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_PF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_SF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_ZF, EqExpr(vc, E_src, vc_bvConstExprFromLL(vc, 32, 0)), d.constraints, d.post_suffix);

#undef SUM_INNER
#undef SUM_OUTER
#undef VAR_EXPR


}

void popcnt64Handler(v_data d, Expr E_dest, Expr E_src) {

#define SUM_INNER(x, shift, hex)\
  vc_bvPlusExpr(vc, 64,\
      vc_bvAndExpr(vc, (x), vc_bvConstExprFromLL(vc, 64,  (hex))),\
      vc_bvAndExpr(vc, vc_bvRightShiftExprExpr(vc, 64, (x), vc_bvConstExprFromInt(vc, 64, (shift))), vc_bvConstExprFromLL(vc, 64, (hex)))\
      )\

#define SUM_OUTER(x, s1, s2, s3, s4, s5, s6)\
  retval = vc_andExpr(vc, retval, EqExpr(vc, (s1), SUM_INNER(x,  1,  0x5555555555555555)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s2), SUM_INNER(s1, 2,  0x3333333333333333)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s3), SUM_INNER(s2, 4,  0x0F0F0F0F0F0F0F0F)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s4), SUM_INNER(s3, 8,  0x00FF00FF00FF00FF)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s5), SUM_INNER(s4, 16, 0x0000FFFF0000FFFF)));\
retval = vc_andExpr(vc, retval, EqExpr(vc, (s6), SUM_INNER(s4, 32, 0x00000000FFFFFFFF)));\

#define VAR_EXPR(s,w)\
  vc_varExpr(vc, ((s)+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, (w)));

  VC&vc = d.vc;
  Expr retval = vc_trueExpr(vc);

  Expr E_temp1 = VAR_EXPR("TEMP1POPCNT",64);
  Expr E_temp2 = VAR_EXPR("TEMP2POPCNT",64);
  Expr E_temp3 = VAR_EXPR("TEMP3POPCNT",64);
  Expr E_temp4 = VAR_EXPR("TEMP4POPCNT",64);
  Expr E_temp5 = VAR_EXPR("TEMP5POPCNT",64);
  Expr E_temp6 = VAR_EXPR("TEMP6POPCNT",64);

  SUM_OUTER(E_src, E_temp1, E_temp2, E_temp3, E_temp4, E_temp5,E_temp6)

    retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, E_temp6));


  SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
  retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, 64));

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_PF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_SF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_ZF, EqExpr(vc, E_src, vc_bvConstExprFromLL(vc, 64, 0)), d.constraints, d.post_suffix);
#undef SUM_INNER
#undef SUM_OUTER
#undef VAR_EXPR

}




void pshufdHandler(v_data d, int imm, Expr E_dest, Expr E_src, Expr E_imm) {

  VC& vc = d.vc;
  
  // We have a nice helper to get (SRC >> x)[y:z]
  // With that in mind:

  // DEST[31:0]   <- (SRC >> (Order[1:0]*32))[31:0]
  // DEST[63:32]  <- (SRC >> (Order[3:2]*32))[31:0]
  // DEST[95:64]  <- (SRC >> (Order[5:4]*32))[31:0]
  // DEST[127:96] <- (SRC >> (Order[7:6]*32))[31:0]
  for (int i = 0; i < 4; i++) {

    int first_bit  = (1 << (2*i));
    int second_bit = (1 << (2*i + 1));
    int mask = (first_bit | second_bit);
    int shift = ((mask & imm) >> (2*i))*32;

    int high = 32*(i+1) - 1;
    int low  = 32*i;

    d.constraints.push_back( 
        EqExpr(vc,
          vc_bvExtract(vc, E_dest, high, low),
          pshuf_shift_right_and_extract(vc, E_src, shift, 31, 0, 128)));
  }


  //--------------------------------------------------------------------
  //  Here's an old version of the handler.
  //  We don't need it, but could use to test the new implementation.
  //--------------------------------------------------------------------
  /*
  if (imm != 5)
    throw VALIDATOR_ERROR("Validator only supports pshufd with immediate 5");

  VC&vc = d.vc;
  Expr E_srcl = vc_bvExtract(vc, E_src, 31, 0);
  Expr E_srch = vc_bvExtract(vc, E_src, 63, 32);
  Expr retval = EqExpr(vc, vc_bvExtract(vc, E_dest, 31, 0), E_srch);
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 32), E_srch));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 95, 64), E_srcl));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 96), E_srcl));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval);
  */

}

void pshufhwHandler(v_data d, int bitWidth, bool avx, int imm, Expr E_dest, Expr E_src) {

  if ( avx || bitWidth != 128 ) 
    throw VALIDATOR_ERROR("pshufhw only supported in non-avx form");

  VC &vc = d.vc;

  // DEST[63:0] <- SRC[63:0]
  d.constraints.push_back( 
      EqExpr(vc,
        vc_bvExtract(vc, E_dest, 63, 0),
        vc_bvExtract(vc, E_src,  63, 0)));

  // We have a nice helper to get (SRC >> x)[y:z]
  // With that in mind:

  // DEST[79:64] <- (SRC >> (imm[1:0]*16))[79:64]
  // DEST[95:80] <- (SRC >> (imm[3:2]*16))[79:64]
  // DEST[111:96] <- (SRC >> (imm[5:4]*16))[79:64]
  // DEST[127:112] <- (SRC >> (imm[7:6]*16))[79:64]
  for(int i = 0; i < 4; i++) {

    int first_bit  = (1 << (2*i));
    int second_bit = (1 << (2*i + 1));
    int mask = (first_bit | second_bit);
    int shift = ((mask & imm) >> (2*i))*16;

    int low = 64 + 16*i;
    int high = 79 + 16*i;

    d.constraints.push_back( 
        EqExpr(vc,
          vc_bvExtract(vc, E_dest, high, low),
          pshuf_shift_right_and_extract(vc, E_src, shift, 79, 64, 128)));

  }


}


void pshuflwHandler(v_data d, int bitWidth, bool avx, int imm, Expr E_dest, Expr E_src) {

  if ( avx || bitWidth != 128 ) 
    throw VALIDATOR_ERROR("pshulhw only supported in non-avx form");

  VC &vc = d.vc;

  // We have a nice helper to get (SRC >> x)[y:z]
  // With that in mind:

  // DEST[15:0] <- (SRC >> (imm[1:0]*16))[15:0]
  // DEST[31:16] <- (SRC >> (imm[3:2]*16))[31:16]
  // DEST[47:32] <- (SRC >> (imm[5:4]*16))[47:32]
  // DEST[63:48] <- (SRC >> (imm[7:6]*16))[63:48]
  for(int i = 0; i < 4; i++) {

    int first_bit  = (1 << (2*i));
    int second_bit = (1 << (2*i + 1));
    int mask = (first_bit | second_bit);
    int shift = ((mask & imm) >> (2*i))*16;

    int low =  16*i;
    int high = 15 + 16*i;

    d.constraints.push_back( 
        EqExpr(vc,
          vc_bvExtract(vc, E_dest, high, low),
          pshuf_shift_right_and_extract(vc, E_src, shift, 15, 0, 128)));

  }

  // DEST[63:0] <- SRC[63:0]
  d.constraints.push_back( 
      EqExpr(vc,
        vc_bvExtract(vc, E_dest, 127, 64),
        vc_bvExtract(vc, E_src,  127, 64)));

}

void psllHandler(v_data d, unsigned int bitWidth, unsigned int shamt,  Expr E_dest, Expr E_src1) 
{
  VC&vc = d.vc;
   Expr retval = vc_trueExpr(vc);
  if(shamt>=bitWidth)
      retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, 128, 0 )));
  else if(shamt==0)
      retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, E_src1));
  else  
  {
    for(int i =bitWidth; i<=128;i+=bitWidth)
    {
      retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, i-1, i-bitWidth),
	         vc_bvConcatExpr(vc, vc_bvExtract(vc, E_src1, i-shamt-1, i-bitWidth), vc_bvConstExprFromLL(vc, shamt, 0) )
                 ));
    }
  }
  ADD_CONS(retval)
  d.constraints.push_back(retval);
}

void punpckldqHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  Expr retval = EqExpr(vc, vc_bvExtract(vc, E_dest, 31, 0), vc_bvExtract(vc, E_src1, 31, 0));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 32), vc_bvExtract(vc, E_src2, 31, 0)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 95, 64), vc_bvExtract(vc, E_src1, 63, 32)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 96), vc_bvExtract(vc, E_src2, 63, 32)));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval);

}


void punpcklwdHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  Expr retval = EqExpr(vc, vc_bvExtract(vc, E_dest, 15, 0), vc_bvExtract(vc, E_src1, 15, 0));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 31, 16), vc_bvExtract(vc, E_src2, 15, 0)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 47, 32), vc_bvExtract(vc, E_src1, 31, 16)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 48), vc_bvExtract(vc, E_src2, 31, 16)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 79, 64), vc_bvExtract(vc, E_src1, 47, 32)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 95, 80), vc_bvExtract(vc, E_src2, 47, 32)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 111, 96), vc_bvExtract(vc, E_src1, 63, 48)));
  retval = vc_andExpr(vc, retval, EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 112), vc_bvExtract(vc, E_src2, 63, 48)));
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval);

}


void pxorHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;

  Expr E_result = vc_bvXorExpr(vc,E_src1, E_src2 );
  Expr retval = EqExpr(vc, E_dest, E_result);
  ADD_CONS(retval);
  d.constraints.push_back(retval); 
}

void rclHandler(v_data d, unsigned int bitWidth, unsigned int rotamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr E_arg = vc_bvConcatExpr(vc, vc_boolToBVExpr(vc, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)), E_src1);
  Expr retval(*vc);
  retval = rotamt!=0 ?
    EqExpr(vc, E_dest, 
        vc_bvExtract(vc, vc_bvConcatExpr(vc, vc_bvExtract(vc, E_arg, bitWidth-rotamt, 0), vc_bvExtract(vc, E_arg, bitWidth, bitWidth+1 - rotamt) ), bitWidth-1, 0))
    : EqExpr(vc, E_dest, E_src1);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  if(rotamt != 0)
  {
    //OF = msb dest xor CF when shift by 1
    if(rotamt == 1)   
      setFlag(vc, d.Vnprime, V_OF,
          vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1), setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, bitWidth-rotamt), d.constraints, d.post_suffix)),
          d.constraints, d.post_suffix);
    else
      setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, bitWidth-rotamt), d.constraints, d.post_suffix);
  }
  else
  {
    //when rotamt is 0, preserve CF and OF
    setFlag(vc, d.Vnprime, V_CF, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn), d.constraints, d.post_suffix);
    setFlag(vc, d.Vnprime, V_OF, getBoolExpr(vc, V_OF, d.pre_suffix, d.Vn), d.constraints, d.post_suffix);
  }

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}


void rcrHandler(v_data d, unsigned int bitWidth, unsigned int rotamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;
  //OF = MSB xor CF
  if(rotamt == 1)   
    setFlag(vc, d.Vnprime, V_OF,
        vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth -1), getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)), d.constraints, d.post_suffix);

  Expr E_arg = vc_bvConcatExpr(vc, vc_boolToBVExpr(vc, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)), E_src1);
  Expr retval(*vc);
  retval = rotamt!=0 ?
    EqExpr(vc, E_dest, 
        vc_bvExtract(vc, vc_bvConcatExpr(vc, vc_bvExtract(vc, E_arg, rotamt-1, 0), vc_bvExtract(vc, E_arg, bitWidth, rotamt) ), bitWidth-1, 0))
    : EqExpr(vc, E_dest, E_src1);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  if(rotamt != 0)
  {
    setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, rotamt-1), d.constraints, d.post_suffix);
  }
  else
  {
    //when rotamt is 0, preserve CF
    setFlag(vc, d.Vnprime, V_CF, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn), d.constraints, d.post_suffix);
  }

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}

void rolHandler(v_data d, unsigned int bitWidth, unsigned int rotamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr retval(*vc);
  retval = rotamt!=0 ?
    EqExpr(vc, E_dest, vc_bvConcatExpr(vc, vc_bvExtract(vc, E_src1, bitWidth-rotamt-1, 0), vc_bvExtract(vc, E_src1, bitWidth - 1, bitWidth - rotamt) ))
    : EqExpr(vc, E_dest, E_src1);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //CF is LSB of dest
  Expr E_cf = setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_dest, 0), d.constraints, d.post_suffix);
  if(rotamt == 1)   
    setFlag(vc, d.Vnprime, V_OF,
        vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1), E_cf), d.constraints, d.post_suffix);

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}

void rorHandler(v_data d, unsigned int bitWidth, unsigned int rotamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr retval(*vc);
  retval = rotamt!=0 ?
    EqExpr(vc, E_dest, vc_bvConcatExpr(vc, vc_bvExtract(vc, E_src1, rotamt-1, 0), vc_bvExtract(vc, E_src1, bitWidth - 1, rotamt) ))
    : EqExpr(vc, E_dest, E_src1);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //CF is MSB of dest
  setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1), d.constraints, d.post_suffix);
  if(rotamt == 1)   
    setFlag(vc, d.Vnprime, V_OF,
        vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1),vc_bvBoolExtract_One(vc, E_dest, bitWidth -2)), d.constraints, d.post_suffix);

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);
}

void sahfHandler(v_data d) {

  VC&vc = d.vc;
  Expr E_src = regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE);
  Expr retval = vc_trueExpr(vc);
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_src, 15), getBoolExpr(vc, V_SF, d.post_suffix, d.Vnprime)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_src, 14), getBoolExpr(vc, V_ZF, d.post_suffix, d.Vnprime)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_src, 10), getBoolExpr(vc, V_PF, d.post_suffix, d.Vnprime)));
  retval = vc_andExpr(vc, retval, vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_src, 8), getBoolExpr(vc, V_CF, d.post_suffix, d.Vnprime)));

#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);  
}

//shamt has been masked
void sarHandler(v_data d, unsigned int bitWidth, unsigned int shamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr retval(*vc);
  if( shamt <= bitWidth )
  {
    if(shamt != 0 && shamt<bitWidth)
    {
      Expr E_result = vc_varExpr(vc, ("SARTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth) );
      Expr E_then = EqExpr(vc, E_result, vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, shamt, -1), vc_bvExtract(vc, E_src1, bitWidth-1, shamt) ));
      Expr E_else = EqExpr(vc, E_result, vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, shamt, 0), vc_bvExtract(vc, E_src1, bitWidth-1, shamt) ));
      retval = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth - 1), E_then, E_else);
      retval = vc_andExpr(vc, retval, EqExpr(vc, E_result, E_dest));
    }
    else if(shamt == 0)
      retval = EqExpr(vc, E_dest, E_src1);
    else
      retval = EqExpr(vc, E_dest, 
          vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth - 1), vc_bvConstExprFromLL(vc, bitWidth, -1), vc_bvConstExprFromLL(vc, bitWidth, 0)));

    if(dest_is_reg && bitWidth < V_UNITSIZE)
    {
      SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
    }
    if(shamt != 0)
    {
      if(shamt == 1)
        setFlag(vc, d.Vnprime, V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
      setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, shamt - 1), d.constraints, d.post_suffix);
      setSFPFZF(E_dest, d, bitWidth);
    }
    else
      preserveAllFlags(d);
  }
  else
  {
    retval = EqExpr(vc, E_dest, 
        vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth - 1), vc_bvConstExprFromLL(vc, bitWidth, -1), vc_bvConstExprFromLL(vc, bitWidth, 0)));
    setSFPFZF(E_dest, d, bitWidth);		
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval);
}



//Arithmetic shift right by a variable.
//if variable==0 then shift by 0 else if variable == 1 then shift by 1 else ... 
void sarVarHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_shamt, bool dest_is_reg=true) {
  //assert((bitWidth == 32  || bitWidth == 64) && "Unhandled CF");
  VC&vc = d.vc;
  //assume E_shamt is less than bitWidth
  //cout << "DEST "; vc_printExpr(vc, E_dest); cout << "SRC "; vc_printExpr(vc, E_src1); cout << "SHAMT "; vc_printExpr(vc, E_shamt); cout << endl ;
  Expr res = vc_iteExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth - 1), vc_bvConstExprFromLL(vc, bitWidth, -1), vc_bvConstExprFromLL(vc, bitWidth, 0));
  for( int i=bitWidth - 1; i>=0; i-- ) {
    //		cout << "In SAR VAR handler " << endl ;
    res = vc_iteExpr(vc,
        EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,i)),
        constructAShrByConstant(vc, i, E_src1, bitWidth),
        res);
    //		vc_printExpr(vc, res);
  }


  Expr retval = EqExpr(vc, E_dest, res);//vc_bvVar32RightShiftExpr(vc, E_shamt, E_src1));
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif


  //complicated handling of flags

  Expr sign = vc_varExpr(vc, (idToStr(V_SF)+d.post_suffix+itoa(d.Vnprime.get(V_SF))).c_str(), vc_boolType(vc));
  Expr zero = vc_varExpr(vc, (idToStr(V_ZF)+d.post_suffix+itoa(d.Vnprime.get(V_ZF))).c_str(), vc_boolType(vc));
  Expr parity = vc_varExpr(vc, (idToStr(V_PF)+d.post_suffix+itoa(d.Vnprime.get(V_PF))).c_str(), vc_boolType(vc));
  Expr carry = vc_varExpr(vc, (idToStr(V_CF)+d.post_suffix+itoa(d.Vnprime.get(V_CF))).c_str(), vc_boolType(vc));
  Expr overflow = vc_varExpr(vc, (idToStr(V_OF)+d.post_suffix+itoa(d.Vnprime.get(V_OF))).c_str(), vc_boolType(vc));

  Expr preserveall =  vc_andExpr(vc, vc_iffExpr(vc, sign, getBoolExpr(vc, V_SF, d.pre_suffix, d.Vn)),
      vc_andExpr(vc, vc_iffExpr(vc, zero, getBoolExpr(vc, V_ZF, d.pre_suffix, d.Vn) ), 
        vc_andExpr(vc, vc_iffExpr(vc, parity, getBoolExpr(vc, V_PF, d.pre_suffix, d.Vn)),
          vc_andExpr(vc, 
            vc_iffExpr(vc, carry, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)),
            vc_iffExpr(vc, overflow, getBoolExpr(vc, V_OF, d.pre_suffix, d.Vn))
            )
          )
        )
      );

  Expr setsfpfzf = vc_iffExpr(vc, sign, vc_bvBoolExtract_One(vc, E_dest, bitWidth - 1));
  setsfpfzf = vc_andExpr(vc, setsfpfzf, vc_iffExpr(vc, zero, vc_eqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0))));
  Expr REGPOST = E_dest;
  Expr E_temp_parity_1 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,0), vc_bvBoolExtract_One(vc, REGPOST,1));
  Expr E_temp_parity_2 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,2), vc_bvBoolExtract_One(vc, REGPOST,3));
  Expr E_temp_parity_3 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,4), vc_bvBoolExtract_One(vc, REGPOST,5));
  Expr E_temp_parity_4 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,6), vc_bvBoolExtract_One(vc, REGPOST,7));
  Expr E_temp_parity_5 = vc_xorExpr(vc, E_temp_parity_1, E_temp_parity_2);
  Expr E_temp_parity_6 = vc_xorExpr(vc, E_temp_parity_3, E_temp_parity_4);
  Expr E_temp_parity_7 = vc_notExpr(vc, vc_xorExpr(vc, E_temp_parity_5, E_temp_parity_6));

  setsfpfzf = vc_andExpr(vc, setsfpfzf, vc_iffExpr(vc, parity, E_temp_parity_7));

  Expr carryexpr = vc_iffExpr(vc, carry,  getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn) );
  for(int j = bitWidth - 1; j>=1; j--)
  {
    carryexpr = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, j)),  vc_iffExpr(vc, carry, vc_bvBoolExtract_One(vc, E_src1, j - 1)), carryexpr);

  }
  //If shamt is greater than bitWidth then carry is undefined
  carryexpr = vc_iteExpr(vc, vc_bvGtExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, bitWidth)), vc_trueExpr(vc), carryexpr);
  Expr temp = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, 0)), 
      preserveall, 
      vc_andExpr(vc, setsfpfzf, 
        vc_andExpr(vc, carryexpr, 
          vc_impliesExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, 1)), vc_iffExpr(vc, overflow, vc_falseExpr(vc)))
          )
        )
      );

  retval = vc_andExpr(vc, temp, retval);
  d.constraints.push_back(retval);
}




void sbbHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {
  
  VC&vc = d.vc;

  Expr E_result = vc_varExpr(vc, ("SBBTEMP"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth+2) );
  Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 2, 0), E_src1);
  Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 2, 0), vc_bvNotExpr(vc, E_src2));  
  Expr E_carry = vc_varExpr(vc, ("BORROW"+d.pre_suffix+itoa(d.instr_no)).c_str(), vc_bvType(vc, bitWidth+2));

  Expr retval = vc_iffExpr(vc, vc_bvBoolExtract_One(vc, E_carry, 0), vc_notExpr(vc, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, vc_bvExtract(vc, E_carry, bitWidth+1, 1),  vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, 1, 0),vc_bvConstExprFromLL(vc, bitWidth, 0))));

  retval = vc_andExpr(vc, retval, EqExpr(vc, E_result,vc_bvPlusExpr(vc, bitWidth+2, vc_bvPlusExpr(vc, bitWidth+2, E_arg1, E_arg2), E_carry)));
  retval = vc_andExpr(vc, retval, vc_eqExpr(vc, E_dest, vc_bvExtract(vc, E_result, bitWidth-1, 0)));  

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
  setFlag(vc, d.Vnprime, V_OF, getOFExpr(vc, vc_bvBoolExtract_One(vc, E_arg1, bitWidth - 1), vc_bvBoolExtract_One(vc, E_arg2, bitWidth - 1),
        vc_bvBoolExtract_One(vc, E_result, bitWidth - 1)), d.constraints, d.post_suffix);
  setFlag(vc, d.Vnprime, V_CF, vc_notExpr(vc, vc_orExpr(vc, vc_bvBoolExtract_One(vc, E_result, bitWidth), vc_bvBoolExtract_One(vc, E_result, bitWidth+1))), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}




void setHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr pred, bool dest_is_reg = true) {
  VC&vc = d.vc;

  Expr retval = vc_iteExpr(vc, pred, EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 1)), EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0)));

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif

  d.constraints.push_back(retval);  
}



void setaHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_A
  SET_FLUFF
}

void setaeHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_AE
  SET_FLUFF
}

void setbHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_B
  SET_FLUFF
}

void setbeHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_BE
  SET_FLUFF
}

void seteHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_E
  SET_FLUFF
}

void setgHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_G
  SET_FLUFF
}


void setgeHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_GE
  SET_FLUFF
}

void setlHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_L
  SET_FLUFF
}


void setleHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_LE
  SET_FLUFF
}

void setneHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_NE
  SET_FLUFF
}

void setnoHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_NO
  SET_FLUFF
}


void setnpHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_NP
  SET_FLUFF
}

void setnsHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_NS
  SET_FLUFF
}

void setoHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_O
  SET_FLUFF
}

void setpHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_P
  SET_FLUFF
}

void setsHandler(v_data d, unsigned int bitWidth, Expr E_dest,bool dest_is_reg = true) {
  
  VC& vc = d.vc;
  Expr V_CC_S
  SET_FLUFF
}	

void shlHandler(v_data d, unsigned int bitWidth, unsigned int shamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr retval(*vc);
  if(shamt <= bitWidth)
  {
    if(shamt < bitWidth)
      retval = EqExpr(vc, E_dest, vc_bvConcatExpr(vc, vc_bvExtract(vc, E_src1, bitWidth-shamt-1, 0), vc_bvConstExprFromLL(vc, shamt, 0) ));
    else
      retval = EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0));

    //vc_printExpr(vc, E_dest);vc_printExpr(vc, E_src1);vc_printExpr(vc, retval);cout << shamt << endl ;

    if(dest_is_reg && bitWidth < V_UNITSIZE)
    {
      SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
    }
    if(shamt != 0)
    {
      //OF = msb dest xor CF when shift by 1
      if(shamt == 1)   
        setFlag(vc, d.Vnprime, V_OF,
            vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1), setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, bitWidth-shamt), d.constraints, d.post_suffix)),
            d.constraints, d.post_suffix);
      else
      {
        //     				setFlag(vc, d.Vnprime, V_OF, getBoolExpr(vc, V_OF, d.pre_suffix, d.Vn), d.constraints, d.post_suffix);
        setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, bitWidth-shamt), d.constraints, d.post_suffix);
      }
      setSFPFZF(E_dest, d, bitWidth);
    }
    else
      preserveAllFlags(d);
  }
  else
  {
    retval = EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0));
    setSFPFZF(E_dest, d, bitWidth);
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
}


void shldHandler(v_data d, unsigned int bitWidth, unsigned int shamt,  Expr E_dest, Expr E_dest_pre, Expr E_src, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr retval(*vc);
  shamt = (bitWidth==64) ? (shamt & 0x3f) : shamt & (0x1f); 
  if(shamt != 0)
  {
    if(shamt <=bitWidth)
    {
      retval = EqExpr(vc, E_dest, vc_bvConcatExpr(vc, vc_bvExtract(vc, E_dest_pre, bitWidth-shamt-1, 0), vc_bvExtract(vc, E_src, bitWidth-1,bitWidth-shamt)  ));
      if(dest_is_reg && bitWidth < V_UNITSIZE)
      {
        SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
        retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));

      }
      // cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
      d.constraints.push_back(retval);
      setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_dest_pre, bitWidth-shamt), d.constraints, d.post_suffix);
      setSFPFZF(E_dest, d, bitWidth);
      if(shamt==1)
      {
        setFlag(vc, d.Vnprime, V_OF,
            vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1), vc_bvBoolExtract_One(vc, E_dest_pre, bitWidth -1)), d.constraints, d.post_suffix);
      }
    }
  }
  else 
  {
    retval = EqExpr(vc, E_dest, E_dest_pre);
    d.constraints.push_back(retval);
    //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
    preserveAllFlags(d);	  	  
  }
}

//deal with flags here
void shldHandler(v_data d, unsigned int bitWidth,   Expr E_dest, Expr E_dest_pre, Expr E_src, Expr E_shamt_pre, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr E_shamt=vc_bvAndExpr(vc, vc_bvConcatExpr(vc,vc_bvConstExprFromLL(vc, bitWidth-8,0),E_shamt_pre), vc_bvConstExprFromLL(vc, bitWidth, bitWidth -1));

  //cout << "Going to shift " << endl;
  Expr res = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,0)), E_dest_pre, vc_bvConstExprFromLL(vc, bitWidth,0)) ;
  for( unsigned int i=1; i<=bitWidth -1; i++ ) {
    //cout << "In SHL VAR handler " << endl ;
    res = vc_iteExpr(vc,
        EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,i)),
        vc_bvConcatExpr(vc, vc_bvExtract(vc, E_dest_pre, bitWidth-i-1, 0), vc_bvExtract(vc, E_src, bitWidth-1, bitWidth-i) ),
        res);
    //vc_printExpr(vc, res);
  }
  Expr retval = EqExpr(vc, E_dest, res);
  //	retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest, vc_bvLeftShiftExprExpr(vc, bitWidth, E_dest_pre,E_shamt)));
  //cout << "Shifted " << endl;
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));

  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
}


void shlVarHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;
  if(bitWidth != 32 && bitWidth != 64)
    throw VALIDATOR_ERROR("Only bitwidth 32 and 64 supported for shl");
  Expr  E_shamt = vc_bvAndExpr(vc, vc_bvConstExprFromInt(vc, bitWidth, bitWidth - 1), vc_bvExtract(vc, regExprWVN(vc, rcx, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth -1, 0));
  //assume E_shamt is less than bitWidth
  Expr res = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,0)), E_src1, vc_bvConstExprFromLL(vc, bitWidth,0)) ;
  //cout << "DEST "; vc_printExpr(vc, E_dest); cout << "SRC "; vc_printExpr(vc, E_src1); cout << "SHAMT "; vc_printExpr(vc, E_shamt); cout << endl ;
  for( unsigned int i=1; i<=bitWidth -1; i++ ) {
    //cout << "In SHL VAR handler " << endl ;
    res = vc_iteExpr(vc,
        EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,i)),
        vc_bvConcatExpr(vc, vc_bvExtract(vc, E_src1, bitWidth-i-1, 0), vc_bvConstExprFromLL(vc, i, 0) ),
        res);
    //vc_printExpr(vc, res);
  }

  Expr retval = EqExpr(vc, E_dest, res);
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";

  Expr sign = vc_varExpr(vc, (idToStr(V_SF)+d.post_suffix+itoa(d.Vnprime.get(V_SF))).c_str(), vc_boolType(vc));
  Expr zero = vc_varExpr(vc, (idToStr(V_ZF)+d.post_suffix+itoa(d.Vnprime.get(V_ZF))).c_str(), vc_boolType(vc));
  Expr parity = vc_varExpr(vc, (idToStr(V_PF)+d.post_suffix+itoa(d.Vnprime.get(V_PF))).c_str(), vc_boolType(vc));
  Expr carry = vc_varExpr(vc, (idToStr(V_CF)+d.post_suffix+itoa(d.Vnprime.get(V_CF))).c_str(), vc_boolType(vc));
  Expr overflow = vc_varExpr(vc, (idToStr(V_OF)+d.post_suffix+itoa(d.Vnprime.get(V_OF))).c_str(), vc_boolType(vc));

  Expr preserveall =  vc_andExpr(vc, vc_iffExpr(vc, sign, getBoolExpr(vc, V_SF, d.pre_suffix, d.Vn)),
      vc_andExpr(vc, vc_iffExpr(vc, zero, getBoolExpr(vc, V_ZF, d.pre_suffix, d.Vn) ), 
        vc_andExpr(vc, vc_iffExpr(vc, parity, getBoolExpr(vc, V_PF, d.pre_suffix, d.Vn)),
          vc_andExpr(vc, 
            vc_iffExpr(vc, carry, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)),
            vc_iffExpr(vc, overflow, getBoolExpr(vc, V_OF, d.pre_suffix, d.Vn))
            )
          )
        )
      );

  Expr setsfpfzf = vc_iffExpr(vc, sign, vc_bvBoolExtract_One(vc, E_dest, bitWidth - 1));
  setsfpfzf = vc_andExpr(vc, setsfpfzf, vc_iffExpr(vc, zero, vc_eqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0))));
  Expr REGPOST = E_dest;
  Expr E_temp_parity_1 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,0), vc_bvBoolExtract_One(vc, REGPOST,1));
  Expr E_temp_parity_2 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,2), vc_bvBoolExtract_One(vc, REGPOST,3));
  Expr E_temp_parity_3 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,4), vc_bvBoolExtract_One(vc, REGPOST,5));
  Expr E_temp_parity_4 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,6), vc_bvBoolExtract_One(vc, REGPOST,7));
  Expr E_temp_parity_5 = vc_xorExpr(vc, E_temp_parity_1, E_temp_parity_2);
  Expr E_temp_parity_6 = vc_xorExpr(vc, E_temp_parity_3, E_temp_parity_4);
  Expr E_temp_parity_7 = vc_notExpr(vc, vc_xorExpr(vc, E_temp_parity_5, E_temp_parity_6));

  setsfpfzf = vc_andExpr(vc, setsfpfzf, vc_iffExpr(vc, parity, E_temp_parity_7));

  Expr carryexpr = vc_iffExpr(vc, carry,  getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn) );

  for(int j = bitWidth - 1; j>=1; j--)
  {
    carryexpr = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, j)),  vc_iffExpr(vc, carry, vc_bvBoolExtract_One(vc, E_src1, bitWidth - j)), carryexpr);

  }
  carryexpr = vc_iteExpr(vc, vc_bvGtExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, bitWidth)), vc_trueExpr(vc), carryexpr);

  Expr temp = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, 0)), 
      preserveall, 
      vc_andExpr(vc, setsfpfzf, 
        vc_andExpr(vc, carryexpr, 
          vc_impliesExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, 1)),
            vc_iffExpr(vc, overflow, 
              vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_dest, bitWidth -1), carry)
              )
            )
          )
        )
      );

  retval = vc_andExpr(vc, temp, retval);
  d.constraints.push_back(retval);
}


void shrHandler(v_data d, unsigned int bitWidth, unsigned int shamt,  Expr E_dest, Expr E_src1, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr retval(*vc);
  if(shamt <= bitWidth)
  {
    retval =  EqExpr(vc, E_dest, vc_bvRightShiftExprExpr(vc, bitWidth, E_src1, vc_bvConstExprFromInt(vc, bitWidth ,shamt)));
    vc_printExpr(vc, E_dest);vc_printExpr(vc, E_src1);vc_printExpr(vc, retval);cout << shamt << endl ;

    if(dest_is_reg && bitWidth < V_UNITSIZE)
    {
      SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
    }
    if(shamt != 0)
    {
      //OF = msb dest xor CF when shift by 1
      if(shamt == 1)   
        setFlag(vc, d.Vnprime, V_OF,
            vc_bvBoolExtract_One(vc, E_src1, bitWidth -1),
            d.constraints, d.post_suffix);
      setFlag(vc, d.Vnprime, V_CF, vc_bvBoolExtract_One(vc, E_src1, bitWidth-shamt), d.constraints, d.post_suffix);
      setSFPFZF(E_dest, d, bitWidth);
    }
    else
      preserveAllFlags(d);
  }
  else
  {
    retval = EqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0));
    setSFPFZF(E_dest, d, bitWidth);
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
}

void shrVarHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_shamt, bool dest_is_reg=true) {

  VC&vc = d.vc;
  //assume E_shamt is less than bitWidth
  Expr res = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,0)), E_src1, vc_bvConstExprFromLL(vc, bitWidth,0)) ;
  //cout << "DEST "; vc_printExpr(vc, E_dest); cout << "SRC "; vc_printExpr(vc, E_src1); cout << "SHAMT "; vc_printExpr(vc, E_shamt); cout << endl ;
  for(unsigned int i=1; i<=bitWidth -1; i++ ) {

    res = vc_iteExpr(vc,
        EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth,i)),
        vc_bvRightShiftExprExpr(vc, bitWidth, E_src1, vc_bvConstExprFromInt(vc, bitWidth, i)),
        res);
  }

  Expr retval = EqExpr(vc, E_dest, res);
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";

  Expr sign = vc_varExpr(vc, (idToStr(V_SF)+d.post_suffix+itoa(d.Vnprime.get(V_SF))).c_str(), vc_boolType(vc));
  Expr zero = vc_varExpr(vc, (idToStr(V_ZF)+d.post_suffix+itoa(d.Vnprime.get(V_ZF))).c_str(), vc_boolType(vc));
  Expr parity = vc_varExpr(vc, (idToStr(V_PF)+d.post_suffix+itoa(d.Vnprime.get(V_PF))).c_str(), vc_boolType(vc));
  Expr carry = vc_varExpr(vc, (idToStr(V_CF)+d.post_suffix+itoa(d.Vnprime.get(V_CF))).c_str(), vc_boolType(vc));
  Expr overflow = vc_varExpr(vc, (idToStr(V_OF)+d.post_suffix+itoa(d.Vnprime.get(V_OF))).c_str(), vc_boolType(vc));

  Expr preserveall =  vc_andExpr(vc, vc_iffExpr(vc, sign, getBoolExpr(vc, V_SF, d.pre_suffix, d.Vn)),
      vc_andExpr(vc, vc_iffExpr(vc, zero, getBoolExpr(vc, V_ZF, d.pre_suffix, d.Vn) ), 
        vc_andExpr(vc, vc_iffExpr(vc, parity, getBoolExpr(vc, V_PF, d.pre_suffix, d.Vn)),
          vc_andExpr(vc, 
            vc_iffExpr(vc, carry, getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn)),
            vc_iffExpr(vc, overflow, getBoolExpr(vc, V_OF, d.pre_suffix, d.Vn))
            )
          )
        )
      );

  Expr setsfpfzf = vc_iffExpr(vc, sign, vc_bvBoolExtract_One(vc, E_dest, bitWidth - 1));
  setsfpfzf = vc_andExpr(vc, setsfpfzf, vc_iffExpr(vc, zero, vc_eqExpr(vc, E_dest, vc_bvConstExprFromLL(vc, bitWidth, 0))));
  Expr REGPOST = E_dest;
  Expr E_temp_parity_1 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,0), vc_bvBoolExtract_One(vc, REGPOST,1));
  Expr E_temp_parity_2 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,2), vc_bvBoolExtract_One(vc, REGPOST,3));
  Expr E_temp_parity_3 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,4), vc_bvBoolExtract_One(vc, REGPOST,5));
  Expr E_temp_parity_4 = vc_xorExpr(vc, vc_bvBoolExtract_One(vc, REGPOST,6), vc_bvBoolExtract_One(vc, REGPOST,7));
  Expr E_temp_parity_5 = vc_xorExpr(vc, E_temp_parity_1, E_temp_parity_2);
  Expr E_temp_parity_6 = vc_xorExpr(vc, E_temp_parity_3, E_temp_parity_4);
  Expr E_temp_parity_7 = vc_notExpr(vc, vc_xorExpr(vc, E_temp_parity_5, E_temp_parity_6));

  setsfpfzf = vc_andExpr(vc, setsfpfzf, vc_iffExpr(vc, parity, E_temp_parity_7));

  Expr carryexpr = vc_iffExpr(vc, carry,  getBoolExpr(vc, V_CF, d.pre_suffix, d.Vn) );

  for(int j = bitWidth - 1; j>=1; j--)
  {
    carryexpr = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, j)),  vc_iffExpr(vc, carry, vc_bvBoolExtract_One(vc, E_src1, j - 1)), carryexpr);

  }
  carryexpr = vc_iteExpr(vc, vc_bvGtExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, bitWidth)), vc_trueExpr(vc), carryexpr);


  Expr temp = vc_iteExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, 0)), 
      preserveall, 
      vc_andExpr(vc, setsfpfzf, 
        vc_andExpr(vc, carryexpr, 
          vc_impliesExpr(vc, EqExpr(vc, E_shamt, vc_bvConstExprFromLL(vc, bitWidth, 1)),
            vc_iffExpr(vc, overflow, vc_bvBoolExtract_One(vc, E_src1, bitWidth -1)	)
            )
          )
        )
      );

  retval = vc_andExpr(vc, temp, retval);
  d.constraints.push_back(retval);
}


void shufpsHandler(v_data d, int imm, Expr E_dest, Expr E_src1, Expr E_src2, Expr E_imm) {

  // Macro for add A[ha:la] <- B[hb:lb]
#define SHUFPS_CON(A, ha, la, B, hb, lb) \
        (d.constraints.push_back(\
           EqExpr(vc,\
             vc_bvExtract(vc, A, ha, la),\
             vc_bvExtract(vc, B, hb, lb))));


  VC& vc = d.vc;

  // Implemented following intel manual's case statement
  switch(imm & 0x3) {
    case 0:
      SHUFPS_CON(E_dest, 31, 0, E_src1, 31, 0);
      break;
    case 1:
      SHUFPS_CON(E_dest, 31, 0, E_src1, 63, 32);
      break;
    case 2:
      SHUFPS_CON(E_dest, 31, 0, E_src1, 95, 64);
      break;
    case 3:
      SHUFPS_CON(E_dest, 31, 0, E_src1, 127, 96);
      break;
    default:
      throw VALIDATOR_ERROR("internal error in shufps");
  }

  switch((imm >> 2) & 0x3) {
    case 0:
      SHUFPS_CON(E_dest, 63, 32, E_src1, 31, 0);
      break;
    case 1:
      SHUFPS_CON(E_dest, 63, 32, E_src1, 63, 32);
      break;
    case 2:
      SHUFPS_CON(E_dest, 63, 32, E_src1, 95, 64);
      break;
    case 3:
      SHUFPS_CON(E_dest, 63, 32, E_src1, 127, 96);
      break;
    default:
      throw VALIDATOR_ERROR("internal error in shufps");
  }

  switch((imm >> 4) & 0x3) {
    case 0:
      SHUFPS_CON(E_dest, 95, 64, E_src2, 31, 0);
      break;
    case 1:
      SHUFPS_CON(E_dest, 95, 64, E_src2, 63, 32);
      break;
    case 2:
      SHUFPS_CON(E_dest, 95, 64, E_src2, 95, 64);
      break;
    case 3:
      SHUFPS_CON(E_dest, 95, 64, E_src2, 127, 96);
      break;
    default:
      throw VALIDATOR_ERROR("internal error in shufps");
  }

  switch((imm >> 6) & 0x3) {
    case 0:
      SHUFPS_CON(E_dest, 127, 96, E_src2, 31, 0);
      break;
    case 1:
      SHUFPS_CON(E_dest, 127, 96, E_src2, 63, 32);
      break;
    case 2:
      SHUFPS_CON(E_dest, 127, 96, E_src2, 95, 64);
      break;
    case 3:
      SHUFPS_CON(E_dest, 127, 96, E_src2, 127, 96);
      break;
    default:
      throw VALIDATOR_ERROR("internal error in shufps");
  }

#undef SHUFPS_CON
}


void subHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;
  Expr E_arg1 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1,0), E_src1);
  Expr E_arg2 = vc_bvConcatExpr(vc, vc_bvConstExprFromInt(vc, 1,0), E_src2);

  Expr retval = EqExpr(vc, E_dest, vc_bvExtract(vc, vc_bvMinusExpr(vc, bitWidth+1, E_arg1, E_arg2), bitWidth-1, 0));
  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  //cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
  d.constraints.push_back(retval);
  setFlag(vc, d.Vnprime, V_OF, getOFExpr(vc, vc_bvBoolExtract_One(vc, E_src1, bitWidth - 1), vc_bvBoolExtract(vc, E_src2, bitWidth - 1),  vc_bvBoolExtract_One(vc, E_dest, bitWidth - 1)),
      d.constraints, d.post_suffix);
  setFlag(vc, d.Vnprime, V_CF, vc_bvLtExpr(vc, E_src1, E_src2), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}


void subdHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

#define DSUBPATT(x)\
  {\
    Expr E_result = vc_bvExtract(vc, E_dest, x+63, x);\
    Expr E_arg1 = vc_bvExtract(vc, E_src1, x+63, x);\
    Expr E_arg2 = vc_bvExtract(vc, E_src2, x+63, x);\
    retval = vc_andExpr(vc, retval, (E_result == dsub(E_arg1,E_arg2)));\
  }

  VC&vc = d.vc;
  uint bitWidth = numops*64; 
  z3::sort fl = vc->bv_sort(64);
  z3::func_decl dsub = z3::function("subd", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);
  if(numops==1)
  {
    DSUBPATT(0)
  }
  else
  {
    DSUBPATT(0)
      DSUBPATT(64)
  }
  if(dest_is_reg && numops == 1)
  {
    SS_Id id_dest = XMM_BEG+getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

#undef DSUBPATT	
}


void subfHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

#define FSUBPATT(x)\
  {\
    Expr E_result = vc_bvExtract(vc, E_dest, x+31, x);\
    Expr E_arg1 = vc_bvExtract(vc, E_src1, x+31, x);\
    Expr E_arg2 = vc_bvExtract(vc, E_src2, x+31, x);\
    retval = vc_andExpr(vc, retval, (E_result == fsub(E_arg1,E_arg2)));\
  }

  VC&vc = d.vc;
  uint bitWidth = numops*32; 
  z3::sort fl = vc->bv_sort(32);
  z3::func_decl fsub = z3::function("subf", fl, fl, fl);
  Expr retval = vc_trueExpr(vc);
  if(numops==1)
  {
    FSUBPATT(0)
  }
  else
  {
    FSUBPATT(0)
      FSUBPATT(32)
      FSUBPATT(64)
      FSUBPATT(96)
  }
  if(dest_is_reg && numops == 1)
  {
    SS_Id id_dest = XMM_BEG+getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
#ifdef DEBUG_VALIDATOR
  cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
  d.constraints.push_back(retval);

#undef FSUBPATT	
}


void subpsHandler(v_data d, unsigned int numops, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;

  // Declare uninterpreted function
  z3::sort dword = vc->bv_sort(32);
  z3::func_decl subps_subf = z3::function("subps_subf", dword, dword, dword);

  // Generate these constraints:
  // DEST[31:0]   <- SRC1[31:0]   - SRC2[31:0]
  // DEST[63:32]  <- SRC1[63:32]  - SRC2[63:32]
  // DEST[95:64]  <- SRC1[95:64]  - SRC2[95:64]
  // DEST[127:96] <- SRC1[127:96] - SRC2[127:96]
  for(size_t i = 0; i < 128; i += 32) {

    Expr dst = vc_bvExtract(vc, E_dest, i+31, i);
    Expr s1  = vc_bvExtract(vc, E_src1, i+31, i);
    Expr s2  = vc_bvExtract(vc, E_src2, i+31, i);
    Expr equ = (dst == subps_subf(s1, s2));

    d.constraints.push_back(equ);
  }

}



void testHandler(v_data d, unsigned int bitWidth, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;

  Expr E_dest = vc_bvAndExpr(vc,E_src1, E_src2 );

  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}



void ucomissHandler(v_data d, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  E_src1 = vc_bvExtract(vc, E_src1, 31,0);
  E_src2 = vc_bvExtract(vc, E_src2, 31,0);
  z3::sort fl = vc->bv_sort(32);
  z3::sort cmp_res = vc->bv_sort(2);
  z3::func_decl fcmp = z3::function("cmpf", fl, fl, cmp_res);
  Expr E_cmp_res = fcmp(E_src1, E_src2);
  setFlag(vc,d.Vnprime,V_CF, vc_notExpr(vc, vc_bvBoolExtract_One(vc, E_cmp_res,0)), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_ZF, vc_notExpr(vc, vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_cmp_res,0),vc_bvBoolExtract_One(vc, E_cmp_res,1))), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_PF, vc_andExpr(vc, vc_bvBoolExtract(vc, E_cmp_res,0), vc_bvBoolExtract(vc, E_cmp_res,1)), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_SF, vc_falseExpr(vc), d.constraints, d.post_suffix);

}


void ucomisdHandler(v_data d, Expr E_src1, Expr E_src2) {

  VC&vc = d.vc;
  E_src1 = vc_bvExtract(vc, E_src1, 63,0);
  E_src2 = vc_bvExtract(vc, E_src2, 63,0);
  z3::sort fl = vc->bv_sort(64);
  z3::sort cmp_res = vc->bv_sort(2);
  z3::func_decl fcmp = z3::function("cmpd", fl, fl, cmp_res);
  Expr E_cmp_res = fcmp(E_src1, E_src2);
  setFlag(vc,d.Vnprime,V_CF, vc_notExpr(vc, vc_bvBoolExtract_One(vc, E_cmp_res,0)), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_ZF, vc_notExpr(vc, vc_xorExpr(vc, vc_bvBoolExtract_One(vc, E_cmp_res,0),vc_bvBoolExtract_One(vc, E_cmp_res,1))), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_PF, vc_andExpr(vc, vc_bvBoolExtract(vc, E_cmp_res,0), vc_bvBoolExtract(vc, E_cmp_res,1)), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_SF, vc_falseExpr(vc), d.constraints, d.post_suffix);

}

void umul1Handler(v_data d, unsigned int bitWidth, Expr E_src2) {

  VC&vc = d.vc;
  if(bitWidth > 8)
  {
    E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2 );
    Expr E_src1 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
    Expr E_rdx = vc_bvExtract(vc, regExprWVN(vc, rdx, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_rax = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_dest = vc_bvConcatExpr(vc, E_rdx, E_rax);

    Expr E_result = vc_bvMultExpr(vc, 2*bitWidth, E_src1, E_src2 );
    Expr retval = EqExpr(vc, E_dest, E_result);

    if( bitWidth < V_UNITSIZE)
    {
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rdx, d, bitWidth));
      retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, bitWidth));

    }

#ifdef DEBUG_VALIDATOR
    cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
    d.constraints.push_back(retval);

    Expr E_flag_result = vc_notExpr(vc, EqExpr(vc, E_rdx,  vc_bvConstExprFromLL(vc, bitWidth, 0)));
    setFlag(vc,d.Vnprime,V_OF, setFlag(vc,d.Vnprime,V_CF, E_flag_result, d.constraints, d.post_suffix), d.constraints, d.post_suffix);
    //Rest flags are undefined
  }
  else
  {
    E_src2 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), E_src2 );
    Expr E_src1 = vc_bvConcatExpr(vc, vc_bvConstExprFromLL(vc, bitWidth, 0), vc_bvExtract(vc, regExprWVN(vc, rax, d.pre_suffix, d.Vn, V_UNITSIZE), bitWidth - 1, 0));
    Expr E_rdx = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), (2*bitWidth) - 1, bitWidth);
    Expr E_rax = vc_bvExtract(vc, regExprWVN(vc, rax, d.post_suffix, d.Vnprime, V_UNITSIZE), bitWidth - 1, 0);
    Expr E_dest = vc_bvConcatExpr(vc, E_rdx, E_rax);

    Expr E_result = vc_bvMultExpr(vc, 2*bitWidth, E_src1, E_src2 );
    Expr retval = EqExpr(vc, E_dest, E_result);

    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, rax, d, 2*bitWidth));

#ifdef DEBUG_VALIDATOR
    cout << "Adding constraint "; vc_printExpr(vc, retval);  cout << "\n";
#endif
    d.constraints.push_back(retval);

    Expr E_flag_result = vc_notExpr(vc, EqExpr(vc, E_rdx,  vc_bvConstExprFromLL(vc, bitWidth, 0)));
    setFlag(vc,d.Vnprime,V_OF, setFlag(vc,d.Vnprime,V_CF, E_flag_result, d.constraints, d.post_suffix), d.constraints, d.post_suffix);
    //Rest flags are undefined	  
  }
}

/* The src1 and src2 are the same as the src1 and src2 in the "Operation"
 * section of the Intel manual.  In the case of two arguments, src1 is the same
 * as dest.  We need the bitWidth to disambiguate between the different
 * operations and the three_args argument to tell us if there are three
 * arguments or two.  The three argument version is VEX prefixed and behaves
 * differently. */
void unpcklpdHandler(v_data d, unsigned int bitWidth, bool three_args, Expr E_dest, Expr E_src1, Expr E_src2) {
  VC& vc = d.vc;

  if (three_args || bitWidth != 128) {
    VALIDATOR_ERROR("Berkeley only knows how to handle unpcklpd with two arguments and bit width 128.");
  }

  /* Force bits 0..63 of destination to match bits 0..63 of source1. */
  Expr lower_bits = EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 0), vc_bvExtract(vc, E_src1, 63, 0));
  d.constraints.push_back(lower_bits);
  ADD_CONS(lower_bits);

  /* Force bits 64..127 of destination to match bits 0..63 of source2. */
  Expr upper_bits = EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 64), vc_bvExtract(vc, E_src2, 63, 0));
  d.constraints.push_back(upper_bits);
  ADD_CONS(upper_bits);

}

void unpcklpsHandler(v_data d, unsigned int bitWidth, bool three_args, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC& vc = d.vc;

  if ( three_args || bitWidth != 128 ) {
    VALIDATOR_ERROR("unpcklps only supported in form 'unpcklps xmm1, xmm2/m128'")
  }

  // DEST[31:0] <- SRC1[31:0]
  Expr bits_31_0 = EqExpr(vc, vc_bvExtract(vc, E_dest, 31, 0), vc_bvExtract(vc, E_src1, 31, 0));

  // DEST[63:32] <- SRC2[31:0]
  Expr bits_63_32 = EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 32), vc_bvExtract(vc, E_src2, 31, 0));

  // DEST[95:64] <- SRC1[63:32]
  Expr bits_95_64 = EqExpr(vc, vc_bvExtract(vc, E_dest, 95, 64), vc_bvExtract(vc, E_src1, 63, 32));

  // DEST[127:96] <- SRC2[63:32]
  Expr bits_127_96 = EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 96), vc_bvExtract(vc, E_src2, 63, 32));

  // Add the four constraints
  d.constraints.push_back(bits_31_0);
  d.constraints.push_back(bits_63_32);
  d.constraints.push_back(bits_95_64);
  d.constraints.push_back(bits_127_96);

}



void vaddsdHandler(v_data d, unsigned int numops, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;
  adddHandler(d, numops,E_dest,E_src1, E_src2, dest_is_reg);
  Expr retval = EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 64), vc_bvExtract(vc, E_src1, 127, 64));

  ADD_CONS(retval);
  d.constraints.push_back(retval);

}


void vpunpcklqdqHandler(v_data d, Expr E_dest, Expr E_src1, Expr E_src2) {

  VC& vc = d.vc;

  // INTERLEAVE_QWORDS(SRC1, SRC2)
  // DEST[63:0] <- SRC1[63:0]
  Expr bits_63_0 = EqExpr(vc, vc_bvExtract(vc, E_dest, 63, 0), vc_bvExtract(vc, E_src1, 63, 0));

  // DEST[127:64] <- SRC2[63:0]
  Expr bits_127_64 = EqExpr(vc, vc_bvExtract(vc, E_dest, 127, 64), vc_bvExtract(vc, E_src2, 63, 0));

  d.constraints.push_back(bits_63_0);
  d.constraints.push_back(bits_127_64);


}

void xaddHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src, Expr E_src_post, bool dest_is_reg=true) {

  VC&vc = d.vc;
  addHandler(d, bitWidth, E_dest, E_dest_pre, E_src, dest_is_reg);
  Expr retval = EqExpr(vc, E_src_post, E_dest_pre);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));

    id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,d.instr.arity()-1)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  ADD_CONS(retval);
  d.constraints.push_back(retval);
}

void xchgHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_dest_pre, Expr E_src, Expr E_src_post,  bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr retval = EqExpr(vc, E_dest, E_src);
  retval = vc_andExpr(vc, retval, EqExpr(vc, E_dest_pre, E_src_post));

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));

    id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,d.instr.arity()-1)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  ADD_CONS(retval);
  d.constraints.push_back(retval);  
}


void xorHandler(v_data d, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2, bool dest_is_reg=true) {

  VC&vc = d.vc;

  Expr E_result = vc_bvXorExpr(vc,E_src1, E_src2 );
  Expr retval = EqExpr(vc, E_dest, E_result);

  if(dest_is_reg && bitWidth < V_UNITSIZE)
  {
    SS_Id id_dest = getOperandValue(parentRegister(getRegisterFromInstr(d.instr,0)));
    retval = vc_andExpr(vc, retval,  UnmodifiedBitsPreserve(vc, id_dest, d, bitWidth));
  }
  ADD_CONS(retval);
  d.constraints.push_back(retval); 
  setFlag(vc,d.Vnprime,V_CF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setFlag(vc,d.Vnprime,V_OF, vc_falseExpr(vc), d.constraints, d.post_suffix);
  setSFPFZF(E_dest, d, bitWidth);
}

void xorpsHandler(v_data d, unsigned int numops, unsigned int bitWidth, Expr E_dest, Expr E_src1, Expr E_src2) {

  if (bitWidth != 128 || numops != 2)
    VALIDATOR_ERROR("xorps only supported for two 128-bit operands");

  VC&vc = d.vc;

  // DEST[127:0] <- SRC1[127:0] ^ SRC2[127:0]
  // note: this only works when bitwidth is 129.
  Expr retval = EqExpr(vc, E_dest, vc_bvXorExpr(vc, E_src1, E_src2));

  d.constraints.push_back(retval);
  ADD_CONS(retval);

}


