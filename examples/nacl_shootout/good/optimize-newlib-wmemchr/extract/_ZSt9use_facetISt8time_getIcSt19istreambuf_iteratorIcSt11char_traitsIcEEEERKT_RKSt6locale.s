  .text
  .globl _ZSt9use_facetISt8time_getIcSt19istreambuf_iteratorIcSt11char_traitsIcEEEERKT_RKSt6locale
  .type _ZSt9use_facetISt8time_getIcSt19istreambuf_iteratorIcSt11char_traitsIcEEEERKT_RKSt6locale, @function

#! file-offset 0xbaec0
#! rip-offset  0x7aec0
#! capacity    192 bytes

# Text                                                                                       #  Line  RIP      Bytes  Opcode              
._ZSt9use_facetISt8time_getIcSt19istreambuf_iteratorIcSt11char_traitsIcEEEERKT_RKSt6locale:  #        0x7aec0  0      OPC=<label>         
  pushq %rbx                                                                                 #  1     0x7aec0  1      OPC=pushq_r64_1     
  movl %edi, %ebx                                                                            #  2     0x7aec1  2      OPC=movl_r32_r32    
  movl $0x10073508, %edi                                                                     #  3     0x7aec3  5      OPC=movl_r32_imm32  
  nop                                                                                        #  4     0x7aec8  1      OPC=nop             
  nop                                                                                        #  5     0x7aec9  1      OPC=nop             
  nop                                                                                        #  6     0x7aeca  1      OPC=nop             
  nop                                                                                        #  7     0x7aecb  1      OPC=nop             
  nop                                                                                        #  8     0x7aecc  1      OPC=nop             
  nop                                                                                        #  9     0x7aecd  1      OPC=nop             
  nop                                                                                        #  10    0x7aece  1      OPC=nop             
  nop                                                                                        #  11    0x7aecf  1      OPC=nop             
  nop                                                                                        #  12    0x7aed0  1      OPC=nop             
  nop                                                                                        #  13    0x7aed1  1      OPC=nop             
  nop                                                                                        #  14    0x7aed2  1      OPC=nop             
  nop                                                                                        #  15    0x7aed3  1      OPC=nop             
  nop                                                                                        #  16    0x7aed4  1      OPC=nop             
  nop                                                                                        #  17    0x7aed5  1      OPC=nop             
  nop                                                                                        #  18    0x7aed6  1      OPC=nop             
  nop                                                                                        #  19    0x7aed7  1      OPC=nop             
  nop                                                                                        #  20    0x7aed8  1      OPC=nop             
  nop                                                                                        #  21    0x7aed9  1      OPC=nop             
  nop                                                                                        #  22    0x7aeda  1      OPC=nop             
  callq ._ZNKSt6locale2id5_M_idEv                                                            #  23    0x7aedb  5      OPC=callq_label     
  movl %ebx, %ebx                                                                            #  24    0x7aee0  2      OPC=movl_r32_r32    
  movl (%r15,%rbx,1), %edx                                                                   #  25    0x7aee2  4      OPC=movl_r32_m32    
  movl %edx, %edx                                                                            #  26    0x7aee6  2      OPC=movl_r32_r32    
  cmpl 0x8(%r15,%rdx,1), %eax                                                                #  27    0x7aee8  5      OPC=cmpl_r32_m32    
  movl %edx, %edx                                                                            #  28    0x7aeed  2      OPC=movl_r32_r32    
  movl 0x4(%r15,%rdx,1), %ecx                                                                #  29    0x7aeef  5      OPC=movl_r32_m32    
  jae .L_7af40                                                                               #  30    0x7aef4  2      OPC=jae_label       
  leal (%rcx,%rax,4), %eax                                                                   #  31    0x7aef6  3      OPC=leal_r32_m16    
  movl %eax, %eax                                                                            #  32    0x7aef9  2      OPC=movl_r32_r32    
  movl (%r15,%rax,1), %edi                                                                   #  33    0x7aefb  4      OPC=movl_r32_m32    
  nop                                                                                        #  34    0x7aeff  1      OPC=nop             
  testq %rdi, %rdi                                                                           #  35    0x7af00  3      OPC=testq_r64_r64   
  je .L_7af40                                                                                #  36    0x7af03  2      OPC=je_label        
  xorl %ecx, %ecx                                                                            #  37    0x7af05  2      OPC=xorl_r32_r32    
  movl $0x1003b1c0, %edx                                                                     #  38    0x7af07  5      OPC=movl_r32_imm32  
  movl $0x1003a2f4, %esi                                                                     #  39    0x7af0c  5      OPC=movl_r32_imm32  
  nop                                                                                        #  40    0x7af11  1      OPC=nop             
  nop                                                                                        #  41    0x7af12  1      OPC=nop             
  nop                                                                                        #  42    0x7af13  1      OPC=nop             
  nop                                                                                        #  43    0x7af14  1      OPC=nop             
  nop                                                                                        #  44    0x7af15  1      OPC=nop             
  nop                                                                                        #  45    0x7af16  1      OPC=nop             
  nop                                                                                        #  46    0x7af17  1      OPC=nop             
  nop                                                                                        #  47    0x7af18  1      OPC=nop             
  nop                                                                                        #  48    0x7af19  1      OPC=nop             
  nop                                                                                        #  49    0x7af1a  1      OPC=nop             
  callq .__dynamic_cast                                                                      #  50    0x7af1b  5      OPC=callq_label     
  movl %eax, %eax                                                                            #  51    0x7af20  2      OPC=movl_r32_r32    
  testq %rax, %rax                                                                           #  52    0x7af22  3      OPC=testq_r64_r64   
  je .L_7af60                                                                                #  53    0x7af25  2      OPC=je_label        
  popq %rbx                                                                                  #  54    0x7af27  1      OPC=popq_r64_1      
  popq %r11                                                                                  #  55    0x7af28  2      OPC=popq_r64_1      
  andl $0xffffffe0, %r11d                                                                    #  56    0x7af2a  7      OPC=andl_r32_imm32  
  nop                                                                                        #  57    0x7af31  1      OPC=nop             
  nop                                                                                        #  58    0x7af32  1      OPC=nop             
  nop                                                                                        #  59    0x7af33  1      OPC=nop             
  nop                                                                                        #  60    0x7af34  1      OPC=nop             
  addq %r15, %r11                                                                            #  61    0x7af35  3      OPC=addq_r64_r64    
  jmpq %r11                                                                                  #  62    0x7af38  3      OPC=jmpq_r64        
  nop                                                                                        #  63    0x7af3b  1      OPC=nop             
  nop                                                                                        #  64    0x7af3c  1      OPC=nop             
  nop                                                                                        #  65    0x7af3d  1      OPC=nop             
  nop                                                                                        #  66    0x7af3e  1      OPC=nop             
  nop                                                                                        #  67    0x7af3f  1      OPC=nop             
  nop                                                                                        #  68    0x7af40  1      OPC=nop             
  nop                                                                                        #  69    0x7af41  1      OPC=nop             
  nop                                                                                        #  70    0x7af42  1      OPC=nop             
  nop                                                                                        #  71    0x7af43  1      OPC=nop             
  nop                                                                                        #  72    0x7af44  1      OPC=nop             
  nop                                                                                        #  73    0x7af45  1      OPC=nop             
  nop                                                                                        #  74    0x7af46  1      OPC=nop             
.L_7af40:                                                                                    #        0x7af47  0      OPC=<label>         
  nop                                                                                        #  75    0x7af47  1      OPC=nop             
  nop                                                                                        #  76    0x7af48  1      OPC=nop             
  nop                                                                                        #  77    0x7af49  1      OPC=nop             
  nop                                                                                        #  78    0x7af4a  1      OPC=nop             
  nop                                                                                        #  79    0x7af4b  1      OPC=nop             
  nop                                                                                        #  80    0x7af4c  1      OPC=nop             
  nop                                                                                        #  81    0x7af4d  1      OPC=nop             
  nop                                                                                        #  82    0x7af4e  1      OPC=nop             
  nop                                                                                        #  83    0x7af4f  1      OPC=nop             
  nop                                                                                        #  84    0x7af50  1      OPC=nop             
  nop                                                                                        #  85    0x7af51  1      OPC=nop             
  nop                                                                                        #  86    0x7af52  1      OPC=nop             
  nop                                                                                        #  87    0x7af53  1      OPC=nop             
  nop                                                                                        #  88    0x7af54  1      OPC=nop             
  nop                                                                                        #  89    0x7af55  1      OPC=nop             
  nop                                                                                        #  90    0x7af56  1      OPC=nop             
  nop                                                                                        #  91    0x7af57  1      OPC=nop             
  nop                                                                                        #  92    0x7af58  1      OPC=nop             
  nop                                                                                        #  93    0x7af59  1      OPC=nop             
  nop                                                                                        #  94    0x7af5a  1      OPC=nop             
  nop                                                                                        #  95    0x7af5b  1      OPC=nop             
  nop                                                                                        #  96    0x7af5c  1      OPC=nop             
  nop                                                                                        #  97    0x7af5d  1      OPC=nop             
  nop                                                                                        #  98    0x7af5e  1      OPC=nop             
  nop                                                                                        #  99    0x7af5f  1      OPC=nop             
  nop                                                                                        #  100   0x7af60  1      OPC=nop             
  nop                                                                                        #  101   0x7af61  1      OPC=nop             
  callq ._ZSt16__throw_bad_castv                                                             #  102   0x7af62  5      OPC=callq_label     
.L_7af60:                                                                                    #        0x7af67  0      OPC=<label>         
  nop                                                                                        #  103   0x7af67  1      OPC=nop             
  nop                                                                                        #  104   0x7af68  1      OPC=nop             
  nop                                                                                        #  105   0x7af69  1      OPC=nop             
  nop                                                                                        #  106   0x7af6a  1      OPC=nop             
  nop                                                                                        #  107   0x7af6b  1      OPC=nop             
  nop                                                                                        #  108   0x7af6c  1      OPC=nop             
  nop                                                                                        #  109   0x7af6d  1      OPC=nop             
  nop                                                                                        #  110   0x7af6e  1      OPC=nop             
  nop                                                                                        #  111   0x7af6f  1      OPC=nop             
  nop                                                                                        #  112   0x7af70  1      OPC=nop             
  nop                                                                                        #  113   0x7af71  1      OPC=nop             
  nop                                                                                        #  114   0x7af72  1      OPC=nop             
  nop                                                                                        #  115   0x7af73  1      OPC=nop             
  nop                                                                                        #  116   0x7af74  1      OPC=nop             
  nop                                                                                        #  117   0x7af75  1      OPC=nop             
  nop                                                                                        #  118   0x7af76  1      OPC=nop             
  nop                                                                                        #  119   0x7af77  1      OPC=nop             
  nop                                                                                        #  120   0x7af78  1      OPC=nop             
  nop                                                                                        #  121   0x7af79  1      OPC=nop             
  nop                                                                                        #  122   0x7af7a  1      OPC=nop             
  nop                                                                                        #  123   0x7af7b  1      OPC=nop             
  nop                                                                                        #  124   0x7af7c  1      OPC=nop             
  nop                                                                                        #  125   0x7af7d  1      OPC=nop             
  nop                                                                                        #  126   0x7af7e  1      OPC=nop             
  nop                                                                                        #  127   0x7af7f  1      OPC=nop             
  nop                                                                                        #  128   0x7af80  1      OPC=nop             
  nop                                                                                        #  129   0x7af81  1      OPC=nop             
  callq .__cxa_bad_cast                                                                      #  130   0x7af82  5      OPC=callq_label     
                                                                                                                                          
.size _ZSt9use_facetISt8time_getIcSt19istreambuf_iteratorIcSt11char_traitsIcEEEERKT_RKSt6locale, .-_ZSt9use_facetISt8time_getIcSt19istreambuf_iteratorIcSt11char_traitsIcEEEERKT_RKSt6locale
