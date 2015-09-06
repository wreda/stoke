  .text
  .globl __cxa_get_globals
  .type __cxa_get_globals, @function

#! file-offset 0x120b00
#! rip-offset  0xe0b00
#! capacity    320 bytes

# Text                          #  Line  RIP      Bytes  Opcode              
.__cxa_get_globals:             #        0xe0b00  0      OPC=<label>         
  cmpb $0x0, 0xff92b31(%rip)    #  1     0xe0b00  7      OPC=cmpb_m8_imm8    
  pushq %rbx                    #  2     0xe0b07  1      OPC=pushq_r64_1     
  movl $0x1007363c, %eax        #  3     0xe0b08  5      OPC=movl_r32_imm32  
  jne .L_e0b40                  #  4     0xe0b0d  2      OPC=jne_label       
  xchgw %ax, %ax                #  5     0xe0b0f  2      OPC=xchgw_ax_r16    
  nop                           #  6     0xe0b11  1      OPC=nop             
  nop                           #  7     0xe0b12  1      OPC=nop             
  nop                           #  8     0xe0b13  1      OPC=nop             
  nop                           #  9     0xe0b14  1      OPC=nop             
  nop                           #  10    0xe0b15  1      OPC=nop             
  nop                           #  11    0xe0b16  1      OPC=nop             
  nop                           #  12    0xe0b17  1      OPC=nop             
  nop                           #  13    0xe0b18  1      OPC=nop             
  nop                           #  14    0xe0b19  1      OPC=nop             
  nop                           #  15    0xe0b1a  1      OPC=nop             
  nop                           #  16    0xe0b1b  1      OPC=nop             
  nop                           #  17    0xe0b1c  1      OPC=nop             
  nop                           #  18    0xe0b1d  1      OPC=nop             
  nop                           #  19    0xe0b1e  1      OPC=nop             
  nop                           #  20    0xe0b1f  1      OPC=nop             
.L_e0b20:                       #        0xe0b20  0      OPC=<label>         
  popq %rbx                     #  21    0xe0b20  1      OPC=popq_r64_1      
  popq %r11                     #  22    0xe0b21  2      OPC=popq_r64_1      
  andl $0xffffffe0, %r11d       #  23    0xe0b23  7      OPC=andl_r32_imm32  
  nop                           #  24    0xe0b2a  1      OPC=nop             
  nop                           #  25    0xe0b2b  1      OPC=nop             
  nop                           #  26    0xe0b2c  1      OPC=nop             
  nop                           #  27    0xe0b2d  1      OPC=nop             
  addq %r15, %r11               #  28    0xe0b2e  3      OPC=addq_r64_r64    
  jmpq %r11                     #  29    0xe0b31  3      OPC=jmpq_r64        
  nop                           #  30    0xe0b34  1      OPC=nop             
  nop                           #  31    0xe0b35  1      OPC=nop             
  nop                           #  32    0xe0b36  1      OPC=nop             
  nop                           #  33    0xe0b37  1      OPC=nop             
  nop                           #  34    0xe0b38  1      OPC=nop             
  nop                           #  35    0xe0b39  1      OPC=nop             
  nop                           #  36    0xe0b3a  1      OPC=nop             
  nop                           #  37    0xe0b3b  1      OPC=nop             
  nop                           #  38    0xe0b3c  1      OPC=nop             
  nop                           #  39    0xe0b3d  1      OPC=nop             
  nop                           #  40    0xe0b3e  1      OPC=nop             
  nop                           #  41    0xe0b3f  1      OPC=nop             
  nop                           #  42    0xe0b40  1      OPC=nop             
  nop                           #  43    0xe0b41  1      OPC=nop             
  nop                           #  44    0xe0b42  1      OPC=nop             
  nop                           #  45    0xe0b43  1      OPC=nop             
  nop                           #  46    0xe0b44  1      OPC=nop             
  nop                           #  47    0xe0b45  1      OPC=nop             
  nop                           #  48    0xe0b46  1      OPC=nop             
.L_e0b40:                       #        0xe0b47  0      OPC=<label>         
  movl 0xff92aee(%rip), %edi    #  49    0xe0b47  6      OPC=movl_r32_m32    
  nop                           #  50    0xe0b4d  1      OPC=nop             
  nop                           #  51    0xe0b4e  1      OPC=nop             
  nop                           #  52    0xe0b4f  1      OPC=nop             
  nop                           #  53    0xe0b50  1      OPC=nop             
  nop                           #  54    0xe0b51  1      OPC=nop             
  nop                           #  55    0xe0b52  1      OPC=nop             
  nop                           #  56    0xe0b53  1      OPC=nop             
  nop                           #  57    0xe0b54  1      OPC=nop             
  nop                           #  58    0xe0b55  1      OPC=nop             
  nop                           #  59    0xe0b56  1      OPC=nop             
  nop                           #  60    0xe0b57  1      OPC=nop             
  nop                           #  61    0xe0b58  1      OPC=nop             
  nop                           #  62    0xe0b59  1      OPC=nop             
  nop                           #  63    0xe0b5a  1      OPC=nop             
  nop                           #  64    0xe0b5b  1      OPC=nop             
  nop                           #  65    0xe0b5c  1      OPC=nop             
  nop                           #  66    0xe0b5d  1      OPC=nop             
  nop                           #  67    0xe0b5e  1      OPC=nop             
  nop                           #  68    0xe0b5f  1      OPC=nop             
  nop                           #  69    0xe0b60  1      OPC=nop             
  nop                           #  70    0xe0b61  1      OPC=nop             
  callq .pthread_getspecific    #  71    0xe0b62  5      OPC=callq_label     
  movl %eax, %eax               #  72    0xe0b67  2      OPC=movl_r32_r32    
  testq %rax, %rax              #  73    0xe0b69  3      OPC=testq_r64_r64   
  jne .L_e0b20                  #  74    0xe0b6c  2      OPC=jne_label       
  movl $0x8, %edi               #  75    0xe0b6e  5      OPC=movl_r32_imm32  
  nop                           #  76    0xe0b73  1      OPC=nop             
  nop                           #  77    0xe0b74  1      OPC=nop             
  nop                           #  78    0xe0b75  1      OPC=nop             
  nop                           #  79    0xe0b76  1      OPC=nop             
  nop                           #  80    0xe0b77  1      OPC=nop             
  nop                           #  81    0xe0b78  1      OPC=nop             
  nop                           #  82    0xe0b79  1      OPC=nop             
  nop                           #  83    0xe0b7a  1      OPC=nop             
  nop                           #  84    0xe0b7b  1      OPC=nop             
  nop                           #  85    0xe0b7c  1      OPC=nop             
  nop                           #  86    0xe0b7d  1      OPC=nop             
  nop                           #  87    0xe0b7e  1      OPC=nop             
  nop                           #  88    0xe0b7f  1      OPC=nop             
  nop                           #  89    0xe0b80  1      OPC=nop             
  nop                           #  90    0xe0b81  1      OPC=nop             
  callq .malloc                 #  91    0xe0b82  5      OPC=callq_label     
  movl %eax, %ebx               #  92    0xe0b87  2      OPC=movl_r32_r32    
  testq %rbx, %rbx              #  93    0xe0b89  3      OPC=testq_r64_r64   
  je .L_e0bc0                   #  94    0xe0b8c  2      OPC=je_label        
  movl 0xff92aa7(%rip), %edi    #  95    0xe0b8e  6      OPC=movl_r32_m32    
  movl %ebx, %esi               #  96    0xe0b94  2      OPC=movl_r32_r32    
  nop                           #  97    0xe0b96  1      OPC=nop             
  nop                           #  98    0xe0b97  1      OPC=nop             
  nop                           #  99    0xe0b98  1      OPC=nop             
  nop                           #  100   0xe0b99  1      OPC=nop             
  nop                           #  101   0xe0b9a  1      OPC=nop             
  nop                           #  102   0xe0b9b  1      OPC=nop             
  nop                           #  103   0xe0b9c  1      OPC=nop             
  nop                           #  104   0xe0b9d  1      OPC=nop             
  nop                           #  105   0xe0b9e  1      OPC=nop             
  nop                           #  106   0xe0b9f  1      OPC=nop             
  nop                           #  107   0xe0ba0  1      OPC=nop             
  nop                           #  108   0xe0ba1  1      OPC=nop             
  callq .pthread_setspecific    #  109   0xe0ba2  5      OPC=callq_label     
  testl %eax, %eax              #  110   0xe0ba7  2      OPC=testl_r32_r32   
  je .L_e0be0                   #  111   0xe0ba9  2      OPC=je_label        
  nop                           #  112   0xe0bab  1      OPC=nop             
  nop                           #  113   0xe0bac  1      OPC=nop             
  nop                           #  114   0xe0bad  1      OPC=nop             
  nop                           #  115   0xe0bae  1      OPC=nop             
  nop                           #  116   0xe0baf  1      OPC=nop             
  nop                           #  117   0xe0bb0  1      OPC=nop             
  nop                           #  118   0xe0bb1  1      OPC=nop             
  nop                           #  119   0xe0bb2  1      OPC=nop             
  nop                           #  120   0xe0bb3  1      OPC=nop             
  nop                           #  121   0xe0bb4  1      OPC=nop             
  nop                           #  122   0xe0bb5  1      OPC=nop             
  nop                           #  123   0xe0bb6  1      OPC=nop             
  nop                           #  124   0xe0bb7  1      OPC=nop             
  nop                           #  125   0xe0bb8  1      OPC=nop             
  nop                           #  126   0xe0bb9  1      OPC=nop             
  nop                           #  127   0xe0bba  1      OPC=nop             
  nop                           #  128   0xe0bbb  1      OPC=nop             
  nop                           #  129   0xe0bbc  1      OPC=nop             
  nop                           #  130   0xe0bbd  1      OPC=nop             
  nop                           #  131   0xe0bbe  1      OPC=nop             
  nop                           #  132   0xe0bbf  1      OPC=nop             
  nop                           #  133   0xe0bc0  1      OPC=nop             
  nop                           #  134   0xe0bc1  1      OPC=nop             
  nop                           #  135   0xe0bc2  1      OPC=nop             
  nop                           #  136   0xe0bc3  1      OPC=nop             
  nop                           #  137   0xe0bc4  1      OPC=nop             
  nop                           #  138   0xe0bc5  1      OPC=nop             
  nop                           #  139   0xe0bc6  1      OPC=nop             
.L_e0bc0:                       #        0xe0bc7  0      OPC=<label>         
  nop                           #  140   0xe0bc7  1      OPC=nop             
  nop                           #  141   0xe0bc8  1      OPC=nop             
  nop                           #  142   0xe0bc9  1      OPC=nop             
  nop                           #  143   0xe0bca  1      OPC=nop             
  nop                           #  144   0xe0bcb  1      OPC=nop             
  nop                           #  145   0xe0bcc  1      OPC=nop             
  nop                           #  146   0xe0bcd  1      OPC=nop             
  nop                           #  147   0xe0bce  1      OPC=nop             
  nop                           #  148   0xe0bcf  1      OPC=nop             
  nop                           #  149   0xe0bd0  1      OPC=nop             
  nop                           #  150   0xe0bd1  1      OPC=nop             
  nop                           #  151   0xe0bd2  1      OPC=nop             
  nop                           #  152   0xe0bd3  1      OPC=nop             
  nop                           #  153   0xe0bd4  1      OPC=nop             
  nop                           #  154   0xe0bd5  1      OPC=nop             
  nop                           #  155   0xe0bd6  1      OPC=nop             
  nop                           #  156   0xe0bd7  1      OPC=nop             
  nop                           #  157   0xe0bd8  1      OPC=nop             
  nop                           #  158   0xe0bd9  1      OPC=nop             
  nop                           #  159   0xe0bda  1      OPC=nop             
  nop                           #  160   0xe0bdb  1      OPC=nop             
  nop                           #  161   0xe0bdc  1      OPC=nop             
  nop                           #  162   0xe0bdd  1      OPC=nop             
  nop                           #  163   0xe0bde  1      OPC=nop             
  nop                           #  164   0xe0bdf  1      OPC=nop             
  nop                           #  165   0xe0be0  1      OPC=nop             
  nop                           #  166   0xe0be1  1      OPC=nop             
  callq ._ZSt9terminatev        #  167   0xe0be2  5      OPC=callq_label     
.L_e0be0:                       #        0xe0be7  0      OPC=<label>         
  movq %rbx, %rax               #  168   0xe0be7  3      OPC=movq_r64_r64    
  movl %ebx, %ebx               #  169   0xe0bea  2      OPC=movl_r32_r32    
  movl $0x0, (%r15,%rbx,1)      #  170   0xe0bec  8      OPC=movl_m32_imm32  
  movl %ebx, %ebx               #  171   0xe0bf4  2      OPC=movl_r32_r32    
  movl $0x0, 0x4(%r15,%rbx,1)   #  172   0xe0bf6  9      OPC=movl_m32_imm32  
  jmpq .L_e0b20                 #  173   0xe0bff  5      OPC=jmpq_label_1    
  nop                           #  174   0xe0c04  1      OPC=nop             
  nop                           #  175   0xe0c05  1      OPC=nop             
  nop                           #  176   0xe0c06  1      OPC=nop             
  cmpq $0xff, %rdx              #  177   0xe0c07  4      OPC=cmpq_r64_imm8   
  movl %eax, %edi               #  178   0xe0c0b  2      OPC=movl_r32_r32    
  je .L_e0c20                   #  179   0xe0c0d  2      OPC=je_label        
  nop                           #  180   0xe0c0f  1      OPC=nop             
  nop                           #  181   0xe0c10  1      OPC=nop             
  nop                           #  182   0xe0c11  1      OPC=nop             
  nop                           #  183   0xe0c12  1      OPC=nop             
  nop                           #  184   0xe0c13  1      OPC=nop             
  nop                           #  185   0xe0c14  1      OPC=nop             
  nop                           #  186   0xe0c15  1      OPC=nop             
  nop                           #  187   0xe0c16  1      OPC=nop             
  nop                           #  188   0xe0c17  1      OPC=nop             
  nop                           #  189   0xe0c18  1      OPC=nop             
  nop                           #  190   0xe0c19  1      OPC=nop             
  nop                           #  191   0xe0c1a  1      OPC=nop             
  nop                           #  192   0xe0c1b  1      OPC=nop             
  nop                           #  193   0xe0c1c  1      OPC=nop             
  nop                           #  194   0xe0c1d  1      OPC=nop             
  nop                           #  195   0xe0c1e  1      OPC=nop             
  nop                           #  196   0xe0c1f  1      OPC=nop             
  nop                           #  197   0xe0c20  1      OPC=nop             
  nop                           #  198   0xe0c21  1      OPC=nop             
  callq ._Unwind_Resume         #  199   0xe0c22  5      OPC=callq_label     
.L_e0c20:                       #        0xe0c27  0      OPC=<label>         
  nop                           #  200   0xe0c27  1      OPC=nop             
  nop                           #  201   0xe0c28  1      OPC=nop             
  nop                           #  202   0xe0c29  1      OPC=nop             
  nop                           #  203   0xe0c2a  1      OPC=nop             
  nop                           #  204   0xe0c2b  1      OPC=nop             
  nop                           #  205   0xe0c2c  1      OPC=nop             
  nop                           #  206   0xe0c2d  1      OPC=nop             
  nop                           #  207   0xe0c2e  1      OPC=nop             
  nop                           #  208   0xe0c2f  1      OPC=nop             
  nop                           #  209   0xe0c30  1      OPC=nop             
  nop                           #  210   0xe0c31  1      OPC=nop             
  nop                           #  211   0xe0c32  1      OPC=nop             
  nop                           #  212   0xe0c33  1      OPC=nop             
  nop                           #  213   0xe0c34  1      OPC=nop             
  nop                           #  214   0xe0c35  1      OPC=nop             
  nop                           #  215   0xe0c36  1      OPC=nop             
  nop                           #  216   0xe0c37  1      OPC=nop             
  nop                           #  217   0xe0c38  1      OPC=nop             
  nop                           #  218   0xe0c39  1      OPC=nop             
  nop                           #  219   0xe0c3a  1      OPC=nop             
  nop                           #  220   0xe0c3b  1      OPC=nop             
  nop                           #  221   0xe0c3c  1      OPC=nop             
  nop                           #  222   0xe0c3d  1      OPC=nop             
  nop                           #  223   0xe0c3e  1      OPC=nop             
  nop                           #  224   0xe0c3f  1      OPC=nop             
  nop                           #  225   0xe0c40  1      OPC=nop             
  nop                           #  226   0xe0c41  1      OPC=nop             
  callq .__cxa_call_unexpected  #  227   0xe0c42  5      OPC=callq_label     
                                                                             
.size __cxa_get_globals, .-__cxa_get_globals
