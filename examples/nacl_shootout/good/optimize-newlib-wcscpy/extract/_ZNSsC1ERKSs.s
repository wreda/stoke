  .text
  .globl _ZNSsC1ERKSs
  .type _ZNSsC1ERKSs, @function

#! file-offset 0xecdc0
#! rip-offset  0xacdc0
#! capacity    224 bytes

# Text                                 #  Line  RIP      Bytes  Opcode              
._ZNSsC1ERKSs:                         #        0xacdc0  0      OPC=<label>         
  pushq %rbx                           #  1     0xacdc0  1      OPC=pushq_r64_1     
  movl %esi, %esi                      #  2     0xacdc1  2      OPC=movl_r32_r32    
  movl %edi, %ebx                      #  3     0xacdc3  2      OPC=movl_r32_r32    
  subl $0x10, %esp                     #  4     0xacdc5  3      OPC=subl_r32_imm8   
  addq %r15, %rsp                      #  5     0xacdc8  3      OPC=addq_r64_r64    
  movl %esi, %esi                      #  6     0xacdcb  2      OPC=movl_r32_r32    
  movl (%r15,%rsi,1), %edi             #  7     0xacdcd  4      OPC=movl_r32_m32    
  subl $0xc, %edi                      #  8     0xacdd1  3      OPC=subl_r32_imm8   
  movl %edi, %edi                      #  9     0xacdd4  2      OPC=movl_r32_r32    
  movl 0x8(%r15,%rdi,1), %eax          #  10    0xacdd6  5      OPC=movl_r32_m32    
  testl %eax, %eax                     #  11    0xacddb  2      OPC=testl_r32_r32   
  nop                                  #  12    0xacddd  1      OPC=nop             
  nop                                  #  13    0xacdde  1      OPC=nop             
  nop                                  #  14    0xacddf  1      OPC=nop             
  js .L_ace20                          #  15    0xacde0  2      OPC=js_label        
  cmpl $0x10073580, %edi               #  16    0xacde2  6      OPC=cmpl_r32_imm32  
  jne .L_ace60                         #  17    0xacde8  2      OPC=jne_label       
  nop                                  #  18    0xacdea  1      OPC=nop             
  nop                                  #  19    0xacdeb  1      OPC=nop             
  nop                                  #  20    0xacdec  1      OPC=nop             
  nop                                  #  21    0xacded  1      OPC=nop             
  nop                                  #  22    0xacdee  1      OPC=nop             
  nop                                  #  23    0xacdef  1      OPC=nop             
  nop                                  #  24    0xacdf0  1      OPC=nop             
  nop                                  #  25    0xacdf1  1      OPC=nop             
  nop                                  #  26    0xacdf2  1      OPC=nop             
  nop                                  #  27    0xacdf3  1      OPC=nop             
  nop                                  #  28    0xacdf4  1      OPC=nop             
  nop                                  #  29    0xacdf5  1      OPC=nop             
  nop                                  #  30    0xacdf6  1      OPC=nop             
  nop                                  #  31    0xacdf7  1      OPC=nop             
  nop                                  #  32    0xacdf8  1      OPC=nop             
  nop                                  #  33    0xacdf9  1      OPC=nop             
  nop                                  #  34    0xacdfa  1      OPC=nop             
  nop                                  #  35    0xacdfb  1      OPC=nop             
  nop                                  #  36    0xacdfc  1      OPC=nop             
  nop                                  #  37    0xacdfd  1      OPC=nop             
  nop                                  #  38    0xacdfe  1      OPC=nop             
  nop                                  #  39    0xacdff  1      OPC=nop             
.L_ace00:                              #        0xace00  0      OPC=<label>         
  addl $0xc, %edi                      #  40    0xace00  3      OPC=addl_r32_imm8   
  movl %ebx, %ebx                      #  41    0xace03  2      OPC=movl_r32_r32    
  movl %edi, (%r15,%rbx,1)             #  42    0xace05  4      OPC=movl_m32_r32    
  addl $0x10, %esp                     #  43    0xace09  3      OPC=addl_r32_imm8   
  addq %r15, %rsp                      #  44    0xace0c  3      OPC=addq_r64_r64    
  popq %rbx                            #  45    0xace0f  1      OPC=popq_r64_1      
  popq %r11                            #  46    0xace10  2      OPC=popq_r64_1      
  andl $0xffffffe0, %r11d              #  47    0xace12  7      OPC=andl_r32_imm32  
  nop                                  #  48    0xace19  1      OPC=nop             
  nop                                  #  49    0xace1a  1      OPC=nop             
  nop                                  #  50    0xace1b  1      OPC=nop             
  nop                                  #  51    0xace1c  1      OPC=nop             
  addq %r15, %r11                      #  52    0xace1d  3      OPC=addq_r64_r64    
  jmpq %r11                            #  53    0xace20  3      OPC=jmpq_r64        
  nop                                  #  54    0xace23  1      OPC=nop             
  nop                                  #  55    0xace24  1      OPC=nop             
  nop                                  #  56    0xace25  1      OPC=nop             
  nop                                  #  57    0xace26  1      OPC=nop             
.L_ace20:                              #        0xace27  0      OPC=<label>         
  leal 0xf(%rsp), %esi                 #  58    0xace27  4      OPC=leal_r32_m16    
  xorl %edx, %edx                      #  59    0xace2b  2      OPC=xorl_r32_r32    
  nop                                  #  60    0xace2d  1      OPC=nop             
  nop                                  #  61    0xace2e  1      OPC=nop             
  nop                                  #  62    0xace2f  1      OPC=nop             
  nop                                  #  63    0xace30  1      OPC=nop             
  nop                                  #  64    0xace31  1      OPC=nop             
  nop                                  #  65    0xace32  1      OPC=nop             
  nop                                  #  66    0xace33  1      OPC=nop             
  nop                                  #  67    0xace34  1      OPC=nop             
  nop                                  #  68    0xace35  1      OPC=nop             
  nop                                  #  69    0xace36  1      OPC=nop             
  nop                                  #  70    0xace37  1      OPC=nop             
  nop                                  #  71    0xace38  1      OPC=nop             
  nop                                  #  72    0xace39  1      OPC=nop             
  nop                                  #  73    0xace3a  1      OPC=nop             
  nop                                  #  74    0xace3b  1      OPC=nop             
  nop                                  #  75    0xace3c  1      OPC=nop             
  nop                                  #  76    0xace3d  1      OPC=nop             
  nop                                  #  77    0xace3e  1      OPC=nop             
  nop                                  #  78    0xace3f  1      OPC=nop             
  nop                                  #  79    0xace40  1      OPC=nop             
  nop                                  #  80    0xace41  1      OPC=nop             
  callq ._ZNSs4_Rep8_M_cloneERKSaIcEj  #  81    0xace42  5      OPC=callq_label     
  movl %eax, %edi                      #  82    0xace47  2      OPC=movl_r32_r32    
  movl %ebx, %ebx                      #  83    0xace49  2      OPC=movl_r32_r32    
  movl %edi, (%r15,%rbx,1)             #  84    0xace4b  4      OPC=movl_m32_r32    
  addl $0x10, %esp                     #  85    0xace4f  3      OPC=addl_r32_imm8   
  addq %r15, %rsp                      #  86    0xace52  3      OPC=addq_r64_r64    
  popq %rbx                            #  87    0xace55  1      OPC=popq_r64_1      
  popq %r11                            #  88    0xace56  2      OPC=popq_r64_1      
  andl $0xffffffe0, %r11d              #  89    0xace58  7      OPC=andl_r32_imm32  
  nop                                  #  90    0xace5f  1      OPC=nop             
  nop                                  #  91    0xace60  1      OPC=nop             
  nop                                  #  92    0xace61  1      OPC=nop             
  nop                                  #  93    0xace62  1      OPC=nop             
  addq %r15, %r11                      #  94    0xace63  3      OPC=addq_r64_r64    
  jmpq %r11                            #  95    0xace66  3      OPC=jmpq_r64        
  nop                                  #  96    0xace69  1      OPC=nop             
  nop                                  #  97    0xace6a  1      OPC=nop             
  nop                                  #  98    0xace6b  1      OPC=nop             
  nop                                  #  99    0xace6c  1      OPC=nop             
  nop                                  #  100   0xace6d  1      OPC=nop             
.L_ace60:                              #        0xace6e  0      OPC=<label>         
  addl $0x1, %eax                      #  101   0xace6e  3      OPC=addl_r32_imm8   
  movl %edi, %edi                      #  102   0xace71  2      OPC=movl_r32_r32    
  movl %eax, 0x8(%r15,%rdi,1)          #  103   0xace73  5      OPC=movl_m32_r32    
  jmpq .L_ace00                        #  104   0xace78  2      OPC=jmpq_label      
  nop                                  #  105   0xace7a  1      OPC=nop             
  nop                                  #  106   0xace7b  1      OPC=nop             
  nop                                  #  107   0xace7c  1      OPC=nop             
  nop                                  #  108   0xace7d  1      OPC=nop             
  nop                                  #  109   0xace7e  1      OPC=nop             
  nop                                  #  110   0xace7f  1      OPC=nop             
  nop                                  #  111   0xace80  1      OPC=nop             
  nop                                  #  112   0xace81  1      OPC=nop             
  nop                                  #  113   0xace82  1      OPC=nop             
  nop                                  #  114   0xace83  1      OPC=nop             
  nop                                  #  115   0xace84  1      OPC=nop             
  nop                                  #  116   0xace85  1      OPC=nop             
  nop                                  #  117   0xace86  1      OPC=nop             
  nop                                  #  118   0xace87  1      OPC=nop             
  nop                                  #  119   0xace88  1      OPC=nop             
  nop                                  #  120   0xace89  1      OPC=nop             
  nop                                  #  121   0xace8a  1      OPC=nop             
  nop                                  #  122   0xace8b  1      OPC=nop             
  nop                                  #  123   0xace8c  1      OPC=nop             
  nop                                  #  124   0xace8d  1      OPC=nop             
  movl %eax, %edi                      #  125   0xace8e  2      OPC=movl_r32_r32    
  nop                                  #  126   0xace90  1      OPC=nop             
  nop                                  #  127   0xace91  1      OPC=nop             
  nop                                  #  128   0xace92  1      OPC=nop             
  nop                                  #  129   0xace93  1      OPC=nop             
  nop                                  #  130   0xace94  1      OPC=nop             
  nop                                  #  131   0xace95  1      OPC=nop             
  nop                                  #  132   0xace96  1      OPC=nop             
  nop                                  #  133   0xace97  1      OPC=nop             
  nop                                  #  134   0xace98  1      OPC=nop             
  nop                                  #  135   0xace99  1      OPC=nop             
  nop                                  #  136   0xace9a  1      OPC=nop             
  nop                                  #  137   0xace9b  1      OPC=nop             
  nop                                  #  138   0xace9c  1      OPC=nop             
  nop                                  #  139   0xace9d  1      OPC=nop             
  nop                                  #  140   0xace9e  1      OPC=nop             
  nop                                  #  141   0xace9f  1      OPC=nop             
  nop                                  #  142   0xacea0  1      OPC=nop             
  nop                                  #  143   0xacea1  1      OPC=nop             
  nop                                  #  144   0xacea2  1      OPC=nop             
  nop                                  #  145   0xacea3  1      OPC=nop             
  nop                                  #  146   0xacea4  1      OPC=nop             
  nop                                  #  147   0xacea5  1      OPC=nop             
  nop                                  #  148   0xacea6  1      OPC=nop             
  nop                                  #  149   0xacea7  1      OPC=nop             
  nop                                  #  150   0xacea8  1      OPC=nop             
  callq ._Unwind_Resume                #  151   0xacea9  5      OPC=callq_label     
                                                                                    
.size _ZNSsC1ERKSs, .-_ZNSsC1ERKSs
