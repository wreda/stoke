  .text
  .globl faccessat
  .type faccessat, @function

#! file-offset 0xd9a20
#! rip-offset  0xd9a20
#! capacity    432 bytes

# Text                       #  Line  RIP      Bytes  Opcode                
.faccessat:                  #        0xd9a20  0      OPC=<label>           
  pushq %r13                 #  1     0xd9a20  2      OPC=pushq_r64_1       
  pushq %r12                 #  2     0xd9a22  2      OPC=pushq_r64_1       
  pushq %rbp                 #  3     0xd9a24  1      OPC=pushq_r64_1       
  pushq %rbx                 #  4     0xd9a25  1      OPC=pushq_r64_1       
  subq $0x98, %rsp           #  5     0xd9a26  7      OPC=subq_r64_imm32    
  testl $0xfffffcff, %ecx    #  6     0xd9a2d  6      OPC=testl_r32_imm32   
  jne .L_d9b88               #  7     0xd9a33  6      OPC=jne_label_1       
  testl %ecx, %ecx           #  8     0xd9a39  2      OPC=testl_r32_r32     
  jne .L_d9a70               #  9     0xd9a3b  2      OPC=jne_label         
.L_d9a3d:                    #        0xd9a3d  0      OPC=<label>           
  movslq %edx, %rdx          #  10    0xd9a3d  3      OPC=movslq_r64_r32    
  movslq %edi, %rdi          #  11    0xd9a40  3      OPC=movslq_r64_r32    
  movl $0x10d, %eax          #  12    0xd9a43  5      OPC=movl_r32_imm32    
  syscall                    #  13    0xd9a48  2      OPC=syscall           
  cmpq $0xfffff000, %rax     #  14    0xd9a4a  6      OPC=cmpq_rax_imm32    
  ja .L_d9b40                #  15    0xd9a50  6      OPC=ja_label_1        
  movl %eax, %ebx            #  16    0xd9a56  2      OPC=movl_r32_r32      
.L_d9a58:                    #        0xd9a58  0      OPC=<label>           
  addq $0x98, %rsp           #  17    0xd9a58  7      OPC=addq_r64_imm32    
  movl %ebx, %eax            #  18    0xd9a5f  2      OPC=movl_r32_r32      
  popq %rbx                  #  19    0xd9a61  1      OPC=popq_r64_1        
  popq %rbp                  #  20    0xd9a62  1      OPC=popq_r64_1        
  popq %r12                  #  21    0xd9a63  2      OPC=popq_r64_1        
  popq %r13                  #  22    0xd9a65  2      OPC=popq_r64_1        
  retq                       #  23    0xd9a67  1      OPC=retq              
  nop                        #  24    0xd9a68  1      OPC=nop               
  nop                        #  25    0xd9a69  1      OPC=nop               
  nop                        #  26    0xd9a6a  1      OPC=nop               
  nop                        #  27    0xd9a6b  1      OPC=nop               
  nop                        #  28    0xd9a6c  1      OPC=nop               
  nop                        #  29    0xd9a6d  1      OPC=nop               
  nop                        #  30    0xd9a6e  1      OPC=nop               
  nop                        #  31    0xd9a6f  1      OPC=nop               
.L_d9a70:                    #        0xd9a70  0      OPC=<label>           
  testl $0xfffffdff, %ecx    #  32    0xd9a70  6      OPC=testl_r32_imm32   
  jne .L_d9a85               #  33    0xd9a76  2      OPC=jne_label         
  movq 0x2c13c1(%rip), %rax  #  34    0xd9a78  7      OPC=movq_r64_m64      
  movl (%rax), %eax          #  35    0xd9a7f  2      OPC=movl_r32_m32      
  testl %eax, %eax           #  36    0xd9a81  2      OPC=testl_r32_r32     
  je .L_d9a3d                #  37    0xd9a83  2      OPC=je_label          
.L_d9a85:                    #        0xd9a85  0      OPC=<label>           
  movl %ecx, %ebp            #  38    0xd9a85  2      OPC=movl_r32_r32      
  movl %edx, %r12d           #  39    0xd9a87  3      OPC=movl_r32_r32      
  movq %rsp, %rcx            #  40    0xd9a8a  3      OPC=movq_r64_r64      
  movl %ebp, %r8d            #  41    0xd9a8d  3      OPC=movl_r32_r32      
  movq %rsi, %rdx            #  42    0xd9a90  3      OPC=movq_r64_r64      
  movl %edi, %esi            #  43    0xd9a93  2      OPC=movl_r32_r32      
  andl $0x100, %r8d          #  44    0xd9a95  7      OPC=andl_r32_imm32    
  movl $0x1, %edi            #  45    0xd9a9c  5      OPC=movl_r32_imm32    
  callq .__fxstatat          #  46    0xd9aa1  5      OPC=callq_label       
  testl %eax, %eax           #  47    0xd9aa6  2      OPC=testl_r32_r32     
  movl %eax, %ebx            #  48    0xd9aa8  2      OPC=movl_r32_r32      
  jne .L_d9bb8               #  49    0xd9aaa  6      OPC=jne_label_1       
  movl %r12d, %r13d          #  50    0xd9ab0  3      OPC=movl_r32_r32      
  andl $0x7, %r13d           #  51    0xd9ab3  4      OPC=andl_r32_imm8     
  je .L_d9a58                #  52    0xd9ab7  2      OPC=je_label          
  andl $0x200, %ebp          #  53    0xd9ab9  6      OPC=andl_r32_imm32    
  je .L_d9b38                #  54    0xd9abf  2      OPC=je_label          
  callq .geteuid             #  55    0xd9ac1  5      OPC=callq_label       
.L_d9ac6:                    #        0xd9ac6  0      OPC=<label>           
  testl %eax, %eax           #  56    0xd9ac6  2      OPC=testl_r32_r32     
  jne .L_d9ad7               #  57    0xd9ac8  2      OPC=jne_label         
  andl $0x1, %r12d           #  58    0xd9aca  4      OPC=andl_r32_imm8     
  je .L_d9a58                #  59    0xd9ace  2      OPC=je_label          
  testb $0x49, 0x18(%rsp)    #  60    0xd9ad0  5      OPC=testb_m8_imm8     
  jne .L_d9a58               #  61    0xd9ad5  2      OPC=jne_label         
.L_d9ad7:                    #        0xd9ad7  0      OPC=<label>           
  cmpl 0x1c(%rsp), %eax      #  62    0xd9ad7  4      OPC=cmpl_r32_m32      
  je .L_d9ba0                #  63    0xd9adb  6      OPC=je_label_1        
  testl %ebp, %ebp           #  64    0xd9ae1  2      OPC=testl_r32_r32     
  movl 0x20(%rsp), %r12d     #  65    0xd9ae3  5      OPC=movl_r32_m32      
  jne .L_d9b60               #  66    0xd9ae8  2      OPC=jne_label         
  callq .getgid              #  67    0xd9aea  5      OPC=callq_label       
.L_d9aef:                    #        0xd9aef  0      OPC=<label>           
  cmpl %eax, %r12d           #  68    0xd9aef  3      OPC=cmpl_r32_r32      
  je .L_d9b70                #  69    0xd9af2  2      OPC=je_label          
  movl 0x20(%rsp), %edi      #  70    0xd9af4  4      OPC=movl_r32_m32      
  callq .group_member        #  71    0xd9af8  5      OPC=callq_label       
  testl %eax, %eax           #  72    0xd9afd  2      OPC=testl_r32_r32     
  jne .L_d9b70               #  73    0xd9aff  2      OPC=jne_label         
  movl 0x18(%rsp), %eax      #  74    0xd9b01  4      OPC=movl_r32_m32      
  andl %r13d, %eax           #  75    0xd9b05  3      OPC=andl_r32_r32      
  nop                        #  76    0xd9b08  1      OPC=nop               
  nop                        #  77    0xd9b09  1      OPC=nop               
  nop                        #  78    0xd9b0a  1      OPC=nop               
  nop                        #  79    0xd9b0b  1      OPC=nop               
  nop                        #  80    0xd9b0c  1      OPC=nop               
  nop                        #  81    0xd9b0d  1      OPC=nop               
  nop                        #  82    0xd9b0e  1      OPC=nop               
  nop                        #  83    0xd9b0f  1      OPC=nop               
.L_d9b10:                    #        0xd9b10  0      OPC=<label>           
  cmpl %r13d, %eax           #  84    0xd9b10  3      OPC=cmpl_r32_r32      
  je .L_d9a58                #  85    0xd9b13  6      OPC=je_label_1        
  movq 0x2c1360(%rip), %rax  #  86    0xd9b19  7      OPC=movq_r64_m64      
  movl $0xffffffff, %ebx     #  87    0xd9b20  6      OPC=movl_r32_imm32_1  
  movl $0xd, (%rax)          #  88    0xd9b26  6      OPC=movl_m32_imm32    
  nop                        #  89    0xd9b2c  1      OPC=nop               
  jmpq .L_d9a58              #  90    0xd9b2d  5      OPC=jmpq_label_1      
  nop                        #  91    0xd9b32  1      OPC=nop               
  nop                        #  92    0xd9b33  1      OPC=nop               
  nop                        #  93    0xd9b34  1      OPC=nop               
  nop                        #  94    0xd9b35  1      OPC=nop               
  nop                        #  95    0xd9b36  1      OPC=nop               
  nop                        #  96    0xd9b37  1      OPC=nop               
  nop                        #  97    0xd9b38  1      OPC=nop               
.L_d9b38:                    #        0xd9b39  0      OPC=<label>           
  callq .getuid              #  98    0xd9b39  5      OPC=callq_label       
  jmpq .L_d9ac6              #  99    0xd9b3e  2      OPC=jmpq_label        
  nop                        #  100   0xd9b40  1      OPC=nop               
.L_d9b40:                    #        0xd9b41  0      OPC=<label>           
  movq 0x2c1339(%rip), %rdx  #  101   0xd9b41  7      OPC=movq_r64_m64      
  negl %eax                  #  102   0xd9b48  2      OPC=negl_r32          
  movl $0xffffffff, %ebx     #  103   0xd9b4a  6      OPC=movl_r32_imm32_1  
  movl %eax, (%rdx)          #  104   0xd9b50  2      OPC=movl_m32_r32      
  nop                        #  105   0xd9b52  1      OPC=nop               
  jmpq .L_d9a58              #  106   0xd9b53  5      OPC=jmpq_label_1      
  nop                        #  107   0xd9b58  1      OPC=nop               
  nop                        #  108   0xd9b59  1      OPC=nop               
  nop                        #  109   0xd9b5a  1      OPC=nop               
  nop                        #  110   0xd9b5b  1      OPC=nop               
  nop                        #  111   0xd9b5c  1      OPC=nop               
  nop                        #  112   0xd9b5d  1      OPC=nop               
  nop                        #  113   0xd9b5e  1      OPC=nop               
  nop                        #  114   0xd9b5f  1      OPC=nop               
  nop                        #  115   0xd9b60  1      OPC=nop               
  nop                        #  116   0xd9b61  1      OPC=nop               
.L_d9b60:                    #        0xd9b62  0      OPC=<label>           
  callq .getegid             #  117   0xd9b62  5      OPC=callq_label       
  jmpq .L_d9aef              #  118   0xd9b67  2      OPC=jmpq_label        
  nop                        #  119   0xd9b69  1      OPC=nop               
  nop                        #  120   0xd9b6a  1      OPC=nop               
  nop                        #  121   0xd9b6b  1      OPC=nop               
  nop                        #  122   0xd9b6c  1      OPC=nop               
  nop                        #  123   0xd9b6d  1      OPC=nop               
  nop                        #  124   0xd9b6e  1      OPC=nop               
  nop                        #  125   0xd9b6f  1      OPC=nop               
  nop                        #  126   0xd9b70  1      OPC=nop               
  nop                        #  127   0xd9b71  1      OPC=nop               
.L_d9b70:                    #        0xd9b72  0      OPC=<label>           
  leal (,%r13,8), %eax       #  128   0xd9b72  8      OPC=leal_r32_m16      
  andl 0x18(%rsp), %eax      #  129   0xd9b7a  4      OPC=andl_r32_m32      
  shrl $0x3, %eax            #  130   0xd9b7e  3      OPC=shrl_r32_imm8     
  jmpq .L_d9b10              #  131   0xd9b81  2      OPC=jmpq_label        
  nop                        #  132   0xd9b83  1      OPC=nop               
  nop                        #  133   0xd9b84  1      OPC=nop               
  nop                        #  134   0xd9b85  1      OPC=nop               
  nop                        #  135   0xd9b86  1      OPC=nop               
  nop                        #  136   0xd9b87  1      OPC=nop               
  nop                        #  137   0xd9b88  1      OPC=nop               
  nop                        #  138   0xd9b89  1      OPC=nop               
.L_d9b88:                    #        0xd9b8a  0      OPC=<label>           
  movq 0x2c12f1(%rip), %rax  #  139   0xd9b8a  7      OPC=movq_r64_m64      
  movl $0xffffffff, %ebx     #  140   0xd9b91  6      OPC=movl_r32_imm32_1  
  movl $0x16, (%rax)         #  141   0xd9b97  6      OPC=movl_m32_imm32    
  nop                        #  142   0xd9b9d  1      OPC=nop               
  jmpq .L_d9a58              #  143   0xd9b9e  5      OPC=jmpq_label_1      
.L_d9ba0:                    #        0xd9ba3  0      OPC=<label>           
  movl %r13d, %eax           #  144   0xd9ba3  3      OPC=movl_r32_r32      
  shll $0x6, %eax            #  145   0xd9ba6  3      OPC=shll_r32_imm8     
  andl 0x18(%rsp), %eax      #  146   0xd9ba9  4      OPC=andl_r32_m32      
  shrl $0x6, %eax            #  147   0xd9bad  3      OPC=shrl_r32_imm8     
  jmpq .L_d9b10              #  148   0xd9bb0  5      OPC=jmpq_label_1      
  nop                        #  149   0xd9bb5  1      OPC=nop               
  nop                        #  150   0xd9bb6  1      OPC=nop               
  nop                        #  151   0xd9bb7  1      OPC=nop               
  nop                        #  152   0xd9bb8  1      OPC=nop               
  nop                        #  153   0xd9bb9  1      OPC=nop               
  nop                        #  154   0xd9bba  1      OPC=nop               
.L_d9bb8:                    #        0xd9bbb  0      OPC=<label>           
  movl $0xffffffff, %ebx     #  155   0xd9bbb  6      OPC=movl_r32_imm32_1  
  jmpq .L_d9a58              #  156   0xd9bc1  5      OPC=jmpq_label_1      
  nop                        #  157   0xd9bc6  1      OPC=nop               
  nop                        #  158   0xd9bc7  1      OPC=nop               
  nop                        #  159   0xd9bc8  1      OPC=nop               
  nop                        #  160   0xd9bc9  1      OPC=nop               
  nop                        #  161   0xd9bca  1      OPC=nop               
  nop                        #  162   0xd9bcb  1      OPC=nop               
  nop                        #  163   0xd9bcc  1      OPC=nop               
  nop                        #  164   0xd9bcd  1      OPC=nop               
  nop                        #  165   0xd9bce  1      OPC=nop               
  nop                        #  166   0xd9bcf  1      OPC=nop               
  nop                        #  167   0xd9bd0  1      OPC=nop               
  nop                        #  168   0xd9bd1  1      OPC=nop               
  nop                        #  169   0xd9bd2  1      OPC=nop               
  nop                        #  170   0xd9bd3  1      OPC=nop               
                                                                            
.size faccessat, .-faccessat
