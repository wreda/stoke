  .text
  .globl _ZNSt13basic_filebufIcSt11char_traitsIcEE7seekposESt4fposI10_mbstate_tESt13_Ios_Openmode
  .type _ZNSt13basic_filebufIcSt11char_traitsIcEE7seekposESt4fposI10_mbstate_tESt13_Ios_Openmode, @function

#! file-offset 0x12d820
#! rip-offset  0xed820
#! capacity    352 bytes

# Text                                                                                      #  Line  RIP      Bytes  Opcode              
._ZNSt13basic_filebufIcSt11char_traitsIcEE7seekposESt4fposI10_mbstate_tESt13_Ios_Openmode:  #        0xed820  0      OPC=<label>         
  pushq %r12                                                                                #  1     0xed820  2      OPC=pushq_r64_1     
  movq %rsi, %r12                                                                           #  2     0xed822  3      OPC=movq_r64_r64    
  pushq %rbx                                                                                #  3     0xed825  1      OPC=pushq_r64_1     
  movl %edi, %ebx                                                                           #  4     0xed826  2      OPC=movl_r32_r32    
  leal 0x34(%rbx), %edi                                                                     #  5     0xed828  3      OPC=leal_r32_m16    
  subl $0x48, %esp                                                                          #  6     0xed82b  3      OPC=subl_r32_imm8   
  addq %r15, %rsp                                                                           #  7     0xed82e  3      OPC=addq_r64_r64    
  movq %rsi, 0x10(%rsp)                                                                     #  8     0xed831  5      OPC=movq_m64_r64    
  movq %rdx, 0x18(%rsp)                                                                     #  9     0xed836  5      OPC=movq_m64_r64    
  nop                                                                                       #  10    0xed83b  1      OPC=nop             
  nop                                                                                       #  11    0xed83c  1      OPC=nop             
  nop                                                                                       #  12    0xed83d  1      OPC=nop             
  nop                                                                                       #  13    0xed83e  1      OPC=nop             
  nop                                                                                       #  14    0xed83f  1      OPC=nop             
  movq $0x0, 0x38(%rsp)                                                                     #  15    0xed840  9      OPC=movq_m64_imm32  
  nop                                                                                       #  16    0xed849  1      OPC=nop             
  nop                                                                                       #  17    0xed84a  1      OPC=nop             
  nop                                                                                       #  18    0xed84b  1      OPC=nop             
  nop                                                                                       #  19    0xed84c  1      OPC=nop             
  nop                                                                                       #  20    0xed84d  1      OPC=nop             
  nop                                                                                       #  21    0xed84e  1      OPC=nop             
  nop                                                                                       #  22    0xed84f  1      OPC=nop             
  nop                                                                                       #  23    0xed850  1      OPC=nop             
  nop                                                                                       #  24    0xed851  1      OPC=nop             
  nop                                                                                       #  25    0xed852  1      OPC=nop             
  nop                                                                                       #  26    0xed853  1      OPC=nop             
  nop                                                                                       #  27    0xed854  1      OPC=nop             
  nop                                                                                       #  28    0xed855  1      OPC=nop             
  nop                                                                                       #  29    0xed856  1      OPC=nop             
  nop                                                                                       #  30    0xed857  1      OPC=nop             
  nop                                                                                       #  31    0xed858  1      OPC=nop             
  nop                                                                                       #  32    0xed859  1      OPC=nop             
  nop                                                                                       #  33    0xed85a  1      OPC=nop             
  callq ._ZNKSt12__basic_fileIcE7is_openEv                                                  #  34    0xed85b  5      OPC=callq_label     
  movl %eax, %edx                                                                           #  35    0xed860  2      OPC=movl_r32_r32    
  movq $0xffffffff, %rax                                                                    #  36    0xed862  7      OPC=movq_r64_imm32  
  testb %dl, %dl                                                                            #  37    0xed869  2      OPC=testb_r8_r8     
  je .L_ed8c0                                                                               #  38    0xed86b  2      OPC=je_label        
  movl %ebx, %ebx                                                                           #  39    0xed86d  2      OPC=movl_r32_r32    
  cmpb $0x0, 0x6c(%r15,%rbx,1)                                                              #  40    0xed86f  6      OPC=cmpb_m8_imm8    
  jne .L_ed8e0                                                                              #  41    0xed875  2      OPC=jne_label       
  nop                                                                                       #  42    0xed877  1      OPC=nop             
  nop                                                                                       #  43    0xed878  1      OPC=nop             
  nop                                                                                       #  44    0xed879  1      OPC=nop             
  nop                                                                                       #  45    0xed87a  1      OPC=nop             
  nop                                                                                       #  46    0xed87b  1      OPC=nop             
  nop                                                                                       #  47    0xed87c  1      OPC=nop             
  nop                                                                                       #  48    0xed87d  1      OPC=nop             
  nop                                                                                       #  49    0xed87e  1      OPC=nop             
  nop                                                                                       #  50    0xed87f  1      OPC=nop             
.L_ed880:                                                                                   #        0xed880  0      OPC=<label>         
  movq 0x18(%rsp), %rcx                                                                     #  51    0xed880  5      OPC=movq_r64_m64    
  xorl %edx, %edx                                                                           #  52    0xed885  2      OPC=xorl_r32_r32    
  movq %r12, %rsi                                                                           #  53    0xed887  3      OPC=movq_r64_r64    
  movl %ebx, %edi                                                                           #  54    0xed88a  2      OPC=movl_r32_r32    
  nop                                                                                       #  55    0xed88c  1      OPC=nop             
  nop                                                                                       #  56    0xed88d  1      OPC=nop             
  nop                                                                                       #  57    0xed88e  1      OPC=nop             
  nop                                                                                       #  58    0xed88f  1      OPC=nop             
  nop                                                                                       #  59    0xed890  1      OPC=nop             
  nop                                                                                       #  60    0xed891  1      OPC=nop             
  nop                                                                                       #  61    0xed892  1      OPC=nop             
  nop                                                                                       #  62    0xed893  1      OPC=nop             
  nop                                                                                       #  63    0xed894  1      OPC=nop             
  nop                                                                                       #  64    0xed895  1      OPC=nop             
  nop                                                                                       #  65    0xed896  1      OPC=nop             
  nop                                                                                       #  66    0xed897  1      OPC=nop             
  nop                                                                                       #  67    0xed898  1      OPC=nop             
  nop                                                                                       #  68    0xed899  1      OPC=nop             
  nop                                                                                       #  69    0xed89a  1      OPC=nop             
  callq ._ZNSt13basic_filebufIcSt11char_traitsIcEE7_M_seekExSt12_Ios_Seekdir10_mbstate_t    #  70    0xed89b  5      OPC=callq_label     
  movq %rdx, 0x38(%rsp)                                                                     #  71    0xed8a0  5      OPC=movq_m64_r64    
  nop                                                                                       #  72    0xed8a5  1      OPC=nop             
  nop                                                                                       #  73    0xed8a6  1      OPC=nop             
  nop                                                                                       #  74    0xed8a7  1      OPC=nop             
  nop                                                                                       #  75    0xed8a8  1      OPC=nop             
  nop                                                                                       #  76    0xed8a9  1      OPC=nop             
  nop                                                                                       #  77    0xed8aa  1      OPC=nop             
  nop                                                                                       #  78    0xed8ab  1      OPC=nop             
  nop                                                                                       #  79    0xed8ac  1      OPC=nop             
  nop                                                                                       #  80    0xed8ad  1      OPC=nop             
  nop                                                                                       #  81    0xed8ae  1      OPC=nop             
  nop                                                                                       #  82    0xed8af  1      OPC=nop             
  nop                                                                                       #  83    0xed8b0  1      OPC=nop             
  nop                                                                                       #  84    0xed8b1  1      OPC=nop             
  nop                                                                                       #  85    0xed8b2  1      OPC=nop             
  nop                                                                                       #  86    0xed8b3  1      OPC=nop             
  nop                                                                                       #  87    0xed8b4  1      OPC=nop             
  nop                                                                                       #  88    0xed8b5  1      OPC=nop             
  nop                                                                                       #  89    0xed8b6  1      OPC=nop             
  nop                                                                                       #  90    0xed8b7  1      OPC=nop             
  nop                                                                                       #  91    0xed8b8  1      OPC=nop             
  nop                                                                                       #  92    0xed8b9  1      OPC=nop             
  nop                                                                                       #  93    0xed8ba  1      OPC=nop             
  nop                                                                                       #  94    0xed8bb  1      OPC=nop             
  nop                                                                                       #  95    0xed8bc  1      OPC=nop             
  nop                                                                                       #  96    0xed8bd  1      OPC=nop             
  nop                                                                                       #  97    0xed8be  1      OPC=nop             
  nop                                                                                       #  98    0xed8bf  1      OPC=nop             
.L_ed8c0:                                                                                   #        0xed8c0  0      OPC=<label>         
  movq 0x38(%rsp), %rdx                                                                     #  99    0xed8c0  5      OPC=movq_r64_m64    
  addl $0x48, %esp                                                                          #  100   0xed8c5  3      OPC=addl_r32_imm8   
  addq %r15, %rsp                                                                           #  101   0xed8c8  3      OPC=addq_r64_r64    
  popq %rbx                                                                                 #  102   0xed8cb  1      OPC=popq_r64_1      
  popq %r12                                                                                 #  103   0xed8cc  2      OPC=popq_r64_1      
  popq %r11                                                                                 #  104   0xed8ce  2      OPC=popq_r64_1      
  andl $0xffffffe0, %r11d                                                                   #  105   0xed8d0  7      OPC=andl_r32_imm32  
  nop                                                                                       #  106   0xed8d7  1      OPC=nop             
  nop                                                                                       #  107   0xed8d8  1      OPC=nop             
  nop                                                                                       #  108   0xed8d9  1      OPC=nop             
  nop                                                                                       #  109   0xed8da  1      OPC=nop             
  addq %r15, %r11                                                                           #  110   0xed8db  3      OPC=addq_r64_r64    
  jmpq %r11                                                                                 #  111   0xed8de  3      OPC=jmpq_r64        
  nop                                                                                       #  112   0xed8e1  1      OPC=nop             
  nop                                                                                       #  113   0xed8e2  1      OPC=nop             
  nop                                                                                       #  114   0xed8e3  1      OPC=nop             
  nop                                                                                       #  115   0xed8e4  1      OPC=nop             
  nop                                                                                       #  116   0xed8e5  1      OPC=nop             
  nop                                                                                       #  117   0xed8e6  1      OPC=nop             
.L_ed8e0:                                                                                   #        0xed8e7  0      OPC=<label>         
  movl %ebx, %ebx                                                                           #  118   0xed8e7  2      OPC=movl_r32_r32    
  movl 0x8(%r15,%rbx,1), %eax                                                               #  119   0xed8e9  5      OPC=movl_r32_m32    
  movl %ebx, %ebx                                                                           #  120   0xed8ee  2      OPC=movl_r32_r32    
  cmpl 0x4(%r15,%rbx,1), %eax                                                               #  121   0xed8f0  5      OPC=cmpl_r32_m32    
  movl %ebx, %ebx                                                                           #  122   0xed8f5  2      OPC=movl_r32_r32    
  movl 0x68(%r15,%rbx,1), %edx                                                              #  123   0xed8f7  5      OPC=movl_r32_m32    
  movl %ebx, %ebx                                                                           #  124   0xed8fc  2      OPC=movl_r32_r32    
  movl 0x58(%r15,%rbx,1), %ecx                                                              #  125   0xed8fe  5      OPC=movl_r32_m32    
  nop                                                                                       #  126   0xed903  1      OPC=nop             
  nop                                                                                       #  127   0xed904  1      OPC=nop             
  nop                                                                                       #  128   0xed905  1      OPC=nop             
  nop                                                                                       #  129   0xed906  1      OPC=nop             
  movl %ebx, %ebx                                                                           #  130   0xed907  2      OPC=movl_r32_r32    
  movb $0x0, 0x6c(%r15,%rbx,1)                                                              #  131   0xed909  6      OPC=movb_m8_imm8    
  setne %al                                                                                 #  132   0xed90f  3      OPC=setne_r8        
  movl %ebx, %ebx                                                                           #  133   0xed912  2      OPC=movl_r32_r32    
  movl %ecx, 0x4(%r15,%rbx,1)                                                               #  134   0xed914  5      OPC=movl_m32_r32    
  movzbl %al, %eax                                                                          #  135   0xed919  3      OPC=movzbl_r32_r8   
  movl %ebx, %ebx                                                                           #  136   0xed91c  2      OPC=movl_r32_r32    
  addl 0x64(%r15,%rbx,1), %eax                                                              #  137   0xed91e  5      OPC=addl_r32_m32    
  nop                                                                                       #  138   0xed923  1      OPC=nop             
  nop                                                                                       #  139   0xed924  1      OPC=nop             
  nop                                                                                       #  140   0xed925  1      OPC=nop             
  nop                                                                                       #  141   0xed926  1      OPC=nop             
  movl %ebx, %ebx                                                                           #  142   0xed927  2      OPC=movl_r32_r32    
  movl %edx, 0xc(%r15,%rbx,1)                                                               #  143   0xed929  5      OPC=movl_m32_r32    
  movl %ebx, %ebx                                                                           #  144   0xed92e  2      OPC=movl_r32_r32    
  movl %eax, 0x64(%r15,%rbx,1)                                                              #  145   0xed930  5      OPC=movl_m32_r32    
  movl %ebx, %ebx                                                                           #  146   0xed935  2      OPC=movl_r32_r32    
  movl %eax, 0x8(%r15,%rbx,1)                                                               #  147   0xed937  5      OPC=movl_m32_r32    
  jmpq .L_ed880                                                                             #  148   0xed93c  5      OPC=jmpq_label_1    
  nop                                                                                       #  149   0xed941  1      OPC=nop             
  nop                                                                                       #  150   0xed942  1      OPC=nop             
  nop                                                                                       #  151   0xed943  1      OPC=nop             
  nop                                                                                       #  152   0xed944  1      OPC=nop             
  nop                                                                                       #  153   0xed945  1      OPC=nop             
  nop                                                                                       #  154   0xed946  1      OPC=nop             
  cmpq $0xff, %rdx                                                                          #  155   0xed947  4      OPC=cmpq_r64_imm8   
  movl %eax, %edi                                                                           #  156   0xed94b  2      OPC=movl_r32_r32    
  je .L_ed960                                                                               #  157   0xed94d  2      OPC=je_label        
  nop                                                                                       #  158   0xed94f  1      OPC=nop             
  nop                                                                                       #  159   0xed950  1      OPC=nop             
  nop                                                                                       #  160   0xed951  1      OPC=nop             
  nop                                                                                       #  161   0xed952  1      OPC=nop             
  nop                                                                                       #  162   0xed953  1      OPC=nop             
  nop                                                                                       #  163   0xed954  1      OPC=nop             
  nop                                                                                       #  164   0xed955  1      OPC=nop             
  nop                                                                                       #  165   0xed956  1      OPC=nop             
  nop                                                                                       #  166   0xed957  1      OPC=nop             
  nop                                                                                       #  167   0xed958  1      OPC=nop             
  nop                                                                                       #  168   0xed959  1      OPC=nop             
  nop                                                                                       #  169   0xed95a  1      OPC=nop             
  nop                                                                                       #  170   0xed95b  1      OPC=nop             
  nop                                                                                       #  171   0xed95c  1      OPC=nop             
  nop                                                                                       #  172   0xed95d  1      OPC=nop             
  nop                                                                                       #  173   0xed95e  1      OPC=nop             
  nop                                                                                       #  174   0xed95f  1      OPC=nop             
  nop                                                                                       #  175   0xed960  1      OPC=nop             
  nop                                                                                       #  176   0xed961  1      OPC=nop             
  callq ._Unwind_Resume                                                                     #  177   0xed962  5      OPC=callq_label     
.L_ed960:                                                                                   #        0xed967  0      OPC=<label>         
  nop                                                                                       #  178   0xed967  1      OPC=nop             
  nop                                                                                       #  179   0xed968  1      OPC=nop             
  nop                                                                                       #  180   0xed969  1      OPC=nop             
  nop                                                                                       #  181   0xed96a  1      OPC=nop             
  nop                                                                                       #  182   0xed96b  1      OPC=nop             
  nop                                                                                       #  183   0xed96c  1      OPC=nop             
  nop                                                                                       #  184   0xed96d  1      OPC=nop             
  nop                                                                                       #  185   0xed96e  1      OPC=nop             
  nop                                                                                       #  186   0xed96f  1      OPC=nop             
  nop                                                                                       #  187   0xed970  1      OPC=nop             
  nop                                                                                       #  188   0xed971  1      OPC=nop             
  nop                                                                                       #  189   0xed972  1      OPC=nop             
  nop                                                                                       #  190   0xed973  1      OPC=nop             
  nop                                                                                       #  191   0xed974  1      OPC=nop             
  nop                                                                                       #  192   0xed975  1      OPC=nop             
  nop                                                                                       #  193   0xed976  1      OPC=nop             
  nop                                                                                       #  194   0xed977  1      OPC=nop             
  nop                                                                                       #  195   0xed978  1      OPC=nop             
  nop                                                                                       #  196   0xed979  1      OPC=nop             
  nop                                                                                       #  197   0xed97a  1      OPC=nop             
  nop                                                                                       #  198   0xed97b  1      OPC=nop             
  nop                                                                                       #  199   0xed97c  1      OPC=nop             
  nop                                                                                       #  200   0xed97d  1      OPC=nop             
  nop                                                                                       #  201   0xed97e  1      OPC=nop             
  nop                                                                                       #  202   0xed97f  1      OPC=nop             
  nop                                                                                       #  203   0xed980  1      OPC=nop             
  nop                                                                                       #  204   0xed981  1      OPC=nop             
  callq .__cxa_call_unexpected                                                              #  205   0xed982  5      OPC=callq_label     
                                                                                                                                         
.size _ZNSt13basic_filebufIcSt11char_traitsIcEE7seekposESt4fposI10_mbstate_tESt13_Ios_Openmode, .-_ZNSt13basic_filebufIcSt11char_traitsIcEE7seekposESt4fposI10_mbstate_tESt13_Ios_Openmode
