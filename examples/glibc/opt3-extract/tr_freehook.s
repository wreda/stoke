  .text
  .globl tr_freehook
  .type tr_freehook, @function

#! file-offset 0x86f10
#! rip-offset  0x86f10
#! capacity    448 bytes

# Text                              #  Line  RIP      Bytes  Opcode                
.tr_freehook:                       #        0x86f10  0      OPC=<label>           
  testq %rdi, %rdi                  #  1     0x86f10  3      OPC=testq_r64_r64     
  je .L_87025                       #  2     0x86f13  6      OPC=je_label_1        
  pushq %r12                        #  3     0x86f19  2      OPC=pushq_r64_1       
  pushq %rbp                        #  4     0x86f1b  1      OPC=pushq_r64_1       
  movq %rsi, %rbp                   #  5     0x86f1c  3      OPC=movq_r64_r64      
  pushq %rbx                        #  6     0x86f1f  1      OPC=pushq_r64_1       
  movq %rdi, %rbx                   #  7     0x86f20  3      OPC=movq_r64_r64      
  subq $0x20, %rsp                  #  8     0x86f23  4      OPC=subq_r64_imm8     
  testq %rsi, %rsi                  #  9     0x86f27  3      OPC=testq_r64_r64     
  je .L_870c0                       #  10    0x86f2a  6      OPC=je_label_1        
  xorl %ecx, %ecx                   #  11    0x86f30  2      OPC=xorl_r32_r32      
  xorl %edx, %edx                   #  12    0x86f32  2      OPC=xorl_r32_r32      
  movq %rsp, %rsi                   #  13    0x86f34  3      OPC=movq_r64_r64      
  movq %rbp, %rdi                   #  14    0x86f37  3      OPC=movq_r64_r64      
  movq %rsp, %r12                   #  15    0x86f3a  3      OPC=movq_r64_r64      
  callq ._dl_addr                   #  16    0x86f3d  5      OPC=callq_label       
  movl $0x0, %esi                   #  17    0x86f42  5      OPC=movl_r32_imm32    
  testl %eax, %eax                  #  18    0x86f47  2      OPC=testl_r32_r32     
  cmoveq %rsi, %r12                 #  19    0x86f49  4      OPC=cmoveq_r64_r64    
  movb $0x1, %sil                   #  20    0x86f4d  3      OPC=movb_r8_imm8      
  xorl %eax, %eax                   #  21    0x86f50  2      OPC=xorl_r32_r32      
  cmpl $0x0, 0x33fca7(%rip)         #  22    0x86f52  7      OPC=cmpl_m32_imm8     
  je .L_86f67                       #  23    0x86f59  2      OPC=je_label          
  lock                              #  24    0x86f5b  1      OPC=lock              
  cmpxchgl %esi, 0x33cb8d(%rip)     #  25    0x86f5c  7      OPC=cmpxchgl_m32_r32  
  nop                               #  26    0x86f63  1      OPC=nop               
  jne .L_86f70                      #  27    0x86f64  2      OPC=jne_label         
  jmpq .L_86f8a                     #  28    0x86f66  2      OPC=jmpq_label        
.L_86f67:                           #        0x86f68  0      OPC=<label>           
  cmpxchgl %esi, 0x33cb82(%rip)     #  29    0x86f68  7      OPC=cmpxchgl_m32_r32  
  je .L_86f8a                       #  30    0x86f6f  2      OPC=je_label          
.L_86f70:                           #        0x86f71  0      OPC=<label>           
  leaq 0x33cb79(%rip), %rdi         #  31    0x86f71  7      OPC=leaq_r64_m16      
  subq $0x80, %rsp                  #  32    0x86f78  7      OPC=subq_r64_imm32    
  callq .__lll_lock_wait_private    #  33    0x86f7f  5      OPC=callq_label       
  addq $0x80, %rsp                  #  34    0x86f84  7      OPC=addq_r64_imm32    
.L_86f8a:                           #        0x86f8b  0      OPC=<label>           
  movq %r12, %rsi                   #  35    0x86f8b  3      OPC=movq_r64_r64      
.L_86f8d:                           #        0x86f8e  0      OPC=<label>           
  movq %rbp, %rdi                   #  36    0x86f8e  3      OPC=movq_r64_r64      
  callq .tr_where                   #  37    0x86f91  5      OPC=callq_label       
  movq 0x33cb64(%rip), %rdi         #  38    0x86f96  7      OPC=movq_r64_m64      
  leaq 0x104a4a(%rip), %rsi         #  39    0x86f9d  7      OPC=leaq_r64_m16      
  xorl %eax, %eax                   #  40    0x86fa4  2      OPC=xorl_r32_r32      
  movq %rbx, %rdx                   #  41    0x86fa6  3      OPC=movq_r64_r64      
  callq .fprintf                    #  42    0x86fa9  5      OPC=callq_label       
  movq 0x339e74(%rip), %rax         #  43    0x86fae  7      OPC=movq_r64_m64      
  cmpq (%rax), %rbx                 #  44    0x86fb5  3      OPC=cmpq_r64_m64      
  je .L_87030                       #  45    0x86fb8  2      OPC=je_label          
.L_86fb9:                           #        0x86fba  0      OPC=<label>           
  movq 0x33cb28(%rip), %rax         #  46    0x86fba  7      OPC=movq_r64_m64      
  movq 0x339f39(%rip), %r12         #  47    0x86fc1  7      OPC=movq_r64_m64      
  testq %rax, %rax                  #  48    0x86fc8  3      OPC=testq_r64_r64     
  movq %rax, (%r12)                 #  49    0x86fcb  4      OPC=movq_m64_r64      
  je .L_870b0                       #  50    0x86fcf  6      OPC=je_label_1        
  movq %rbp, %rsi                   #  51    0x86fd5  3      OPC=movq_r64_r64      
  movq %rbx, %rdi                   #  52    0x86fd8  3      OPC=movq_r64_r64      
  callq %rax                        #  53    0x86fdb  2      OPC=callq_r64         
.L_86fdc:                           #        0x86fdd  0      OPC=<label>           
  leaq -0xd3(%rip), %rax            #  54    0x86fdd  7      OPC=leaq_r64_m16      
  movq %rax, (%r12)                 #  55    0x86fe4  4      OPC=movq_m64_r64      
  cmpl $0x0, 0x33fc12(%rip)         #  56    0x86fe8  7      OPC=cmpl_m32_imm8     
  je .L_86ffb                       #  57    0x86fef  2      OPC=je_label          
  lock                              #  58    0x86ff1  1      OPC=lock              
  decl 0x33caf9(%rip)               #  59    0x86ff2  6      OPC=decl_m32          
  nop                               #  60    0x86ff8  1      OPC=nop               
  jne .L_87003                      #  61    0x86ff9  2      OPC=jne_label         
  jmpq .L_8701d                     #  62    0x86ffb  2      OPC=jmpq_label        
.L_86ffb:                           #        0x86ffd  0      OPC=<label>           
  decl 0x33caef(%rip)               #  63    0x86ffd  6      OPC=decl_m32          
  je .L_8701d                       #  64    0x87003  2      OPC=je_label          
.L_87003:                           #        0x87005  0      OPC=<label>           
  leaq 0x33cae6(%rip), %rdi         #  65    0x87005  7      OPC=leaq_r64_m16      
  subq $0x80, %rsp                  #  66    0x8700c  7      OPC=subq_r64_imm32    
  callq .__lll_unlock_wake_private  #  67    0x87013  5      OPC=callq_label       
  addq $0x80, %rsp                  #  68    0x87018  7      OPC=addq_r64_imm32    
.L_8701d:                           #        0x8701f  0      OPC=<label>           
  addq $0x20, %rsp                  #  69    0x8701f  4      OPC=addq_r64_imm8     
  popq %rbx                         #  70    0x87023  1      OPC=popq_r64_1        
  popq %rbp                         #  71    0x87024  1      OPC=popq_r64_1        
  popq %r12                         #  72    0x87025  2      OPC=popq_r64_1        
.L_87025:                           #        0x87027  0      OPC=<label>           
  retq                              #  73    0x87027  1      OPC=retq              
  nop                               #  74    0x87028  1      OPC=nop               
  nop                               #  75    0x87029  1      OPC=nop               
  nop                               #  76    0x8702a  1      OPC=nop               
  nop                               #  77    0x8702b  1      OPC=nop               
  nop                               #  78    0x8702c  1      OPC=nop               
  nop                               #  79    0x8702d  1      OPC=nop               
  nop                               #  80    0x8702e  1      OPC=nop               
  nop                               #  81    0x8702f  1      OPC=nop               
  nop                               #  82    0x87030  1      OPC=nop               
  nop                               #  83    0x87031  1      OPC=nop               
.L_87030:                           #        0x87032  0      OPC=<label>           
  cmpl $0x0, 0x33fbc9(%rip)         #  84    0x87032  7      OPC=cmpl_m32_imm8     
  je .L_87044                       #  85    0x87039  2      OPC=je_label          
  lock                              #  86    0x8703b  1      OPC=lock              
  decl 0x33cab0(%rip)               #  87    0x8703c  6      OPC=decl_m32          
  nop                               #  88    0x87042  1      OPC=nop               
  jne .L_8704c                      #  89    0x87043  2      OPC=jne_label         
  jmpq .L_87066                     #  90    0x87045  2      OPC=jmpq_label        
.L_87044:                           #        0x87047  0      OPC=<label>           
  decl 0x33caa6(%rip)               #  91    0x87047  6      OPC=decl_m32          
  je .L_87066                       #  92    0x8704d  2      OPC=je_label          
.L_8704c:                           #        0x8704f  0      OPC=<label>           
  leaq 0x33ca9d(%rip), %rdi         #  93    0x8704f  7      OPC=leaq_r64_m16      
  subq $0x80, %rsp                  #  94    0x87056  7      OPC=subq_r64_imm32    
  callq .__lll_unlock_wake_private  #  95    0x8705d  5      OPC=callq_label       
  addq $0x80, %rsp                  #  96    0x87062  7      OPC=addq_r64_imm32    
.L_87066:                           #        0x87069  0      OPC=<label>           
  movl $0x1, %esi                   #  97    0x87069  5      OPC=movl_r32_imm32    
  xorl %eax, %eax                   #  98    0x8706e  2      OPC=xorl_r32_r32      
  cmpl $0x0, 0x33fb8c(%rip)         #  99    0x87070  7      OPC=cmpl_m32_imm8     
  je .L_87082                       #  100   0x87077  2      OPC=je_label          
  lock                              #  101   0x87079  1      OPC=lock              
  cmpxchgl %esi, 0x33ca72(%rip)     #  102   0x8707a  7      OPC=cmpxchgl_m32_r32  
  nop                               #  103   0x87081  1      OPC=nop               
  jne .L_8708b                      #  104   0x87082  2      OPC=jne_label         
  jmpq .L_870a5                     #  105   0x87084  2      OPC=jmpq_label        
.L_87082:                           #        0x87086  0      OPC=<label>           
  cmpxchgl %esi, 0x33ca67(%rip)     #  106   0x87086  7      OPC=cmpxchgl_m32_r32  
  je .L_870a5                       #  107   0x8708d  2      OPC=je_label          
.L_8708b:                           #        0x8708f  0      OPC=<label>           
  leaq 0x33ca5e(%rip), %rdi         #  108   0x8708f  7      OPC=leaq_r64_m16      
  subq $0x80, %rsp                  #  109   0x87096  7      OPC=subq_r64_imm32    
  callq .__lll_lock_wait_private    #  110   0x8709d  5      OPC=callq_label       
  addq $0x80, %rsp                  #  111   0x870a2  7      OPC=addq_r64_imm32    
.L_870a5:                           #        0x870a9  0      OPC=<label>           
  jmpq .L_86fb9                     #  112   0x870a9  5      OPC=jmpq_label_1      
  nop                               #  113   0x870ae  1      OPC=nop               
  nop                               #  114   0x870af  1      OPC=nop               
  nop                               #  115   0x870b0  1      OPC=nop               
  nop                               #  116   0x870b1  1      OPC=nop               
  nop                               #  117   0x870b2  1      OPC=nop               
  nop                               #  118   0x870b3  1      OPC=nop               
.L_870b0:                           #        0x870b4  0      OPC=<label>           
  movq %rbx, %rdi                   #  119   0x870b4  3      OPC=movq_r64_r64      
  callq .L_1f8c0                    #  120   0x870b7  5      OPC=callq_label       
  jmpq .L_86fdc                     #  121   0x870bc  5      OPC=jmpq_label_1      
  nop                               #  122   0x870c1  1      OPC=nop               
  nop                               #  123   0x870c2  1      OPC=nop               
  nop                               #  124   0x870c3  1      OPC=nop               
.L_870c0:                           #        0x870c4  0      OPC=<label>           
  xorl %esi, %esi                   #  125   0x870c4  2      OPC=xorl_r32_r32      
  jmpq .L_86f8d                     #  126   0x870c6  5      OPC=jmpq_label_1      
  nop                               #  127   0x870cb  1      OPC=nop               
  nop                               #  128   0x870cc  1      OPC=nop               
  nop                               #  129   0x870cd  1      OPC=nop               
  nop                               #  130   0x870ce  1      OPC=nop               
  nop                               #  131   0x870cf  1      OPC=nop               
  nop                               #  132   0x870d0  1      OPC=nop               
  nop                               #  133   0x870d1  1      OPC=nop               
  nop                               #  134   0x870d2  1      OPC=nop               
  nop                               #  135   0x870d3  1      OPC=nop               
                                                                                   
.size tr_freehook, .-tr_freehook
