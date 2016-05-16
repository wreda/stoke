  .text
  .globl execle
  .type execle, @function

#! file-offset 0xb6600
#! rip-offset  0xb6600
#! capacity    432 bytes

# Text                       #  Line  RIP      Bytes  Opcode                
.execle:                     #        0xb6600  0      OPC=<label>           
  pushq %r15                 #  1     0xb6600  2      OPC=pushq_r64_1       
  pushq %r14                 #  2     0xb6602  2      OPC=pushq_r64_1       
  pushq %r13                 #  3     0xb6604  2      OPC=pushq_r64_1       
  pushq %r12                 #  4     0xb6606  2      OPC=pushq_r64_1       
  pushq %rbp                 #  5     0xb6608  1      OPC=pushq_r64_1       
  pushq %rbx                 #  6     0xb6609  1      OPC=pushq_r64_1       
  subq $0x2068, %rsp         #  7     0xb660a  7      OPC=subq_r64_imm32    
  testq %rsi, %rsi           #  8     0xb6611  3      OPC=testq_r64_r64     
  leaq 0x20a0(%rsp), %rax    #  9     0xb6614  8      OPC=leaq_r64_m16      
  leaq 0x30(%rsp), %rbx      #  10    0xb661c  5      OPC=leaq_r64_m16      
  movq %rdi, 0x8(%rsp)       #  11    0xb6621  5      OPC=movq_m64_r64      
  movq %rdx, 0x2040(%rsp)    #  12    0xb6626  8      OPC=movq_m64_r64      
  movq %rcx, 0x2048(%rsp)    #  13    0xb662e  8      OPC=movq_m64_r64      
  movq %rax, 0x20(%rsp)      #  14    0xb6636  5      OPC=movq_m64_r64      
  leaq 0x2030(%rsp), %rax    #  15    0xb663b  8      OPC=leaq_r64_m16      
  movq %r8, 0x2050(%rsp)     #  16    0xb6643  8      OPC=movq_m64_r64      
  movq %r9, 0x2058(%rsp)     #  17    0xb664b  8      OPC=movq_m64_r64      
  movq %rsi, 0x30(%rsp)      #  18    0xb6653  5      OPC=movq_m64_r64      
  movq %rbx, %r14            #  19    0xb6658  3      OPC=movq_r64_r64      
  movl $0x10, 0x18(%rsp)     #  20    0xb665b  8      OPC=movl_m32_imm32    
  movq %rax, 0x28(%rsp)      #  21    0xb6663  5      OPC=movq_m64_r64      
  je .L_b6720                #  22    0xb6668  6      OPC=je_label_1        
  leaq 0x30(%rsp), %rbx      #  23    0xb666e  5      OPC=leaq_r64_m16      
  movl $0x1, %r13d           #  24    0xb6673  6      OPC=movl_r32_imm32    
  movl $0x1, %ebp            #  25    0xb6679  5      OPC=movl_r32_imm32    
  movl $0x400, %r12d         #  26    0xb667e  6      OPC=movl_r32_imm32    
  movq %rbx, %r14            #  27    0xb6684  3      OPC=movq_r64_r64      
  nop                        #  28    0xb6687  1      OPC=nop               
  nop                        #  29    0xb6688  1      OPC=nop               
  nop                        #  30    0xb6689  1      OPC=nop               
  nop                        #  31    0xb668a  1      OPC=nop               
  nop                        #  32    0xb668b  1      OPC=nop               
  nop                        #  33    0xb668c  1      OPC=nop               
  nop                        #  34    0xb668d  1      OPC=nop               
  nop                        #  35    0xb668e  1      OPC=nop               
  nop                        #  36    0xb668f  1      OPC=nop               
.L_b6690:                    #        0xb6690  0      OPC=<label>           
  movl 0x18(%rsp), %eax      #  37    0xb6690  4      OPC=movl_r32_m32      
  leaq (%r14,%rbp,8), %rsi   #  38    0xb6694  4      OPC=leaq_r64_m16      
  cmpl $0x30, %eax           #  39    0xb6698  3      OPC=cmpl_r32_imm8     
  jae .L_b6703               #  40    0xb669b  2      OPC=jae_label         
.L_b669d:                    #        0xb669d  0      OPC=<label>           
  movl %eax, %ecx            #  41    0xb669d  2      OPC=movl_r32_r32      
  addq 0x28(%rsp), %rcx      #  42    0xb669f  5      OPC=addq_r64_m64      
  addl $0x8, %eax            #  43    0xb66a4  3      OPC=addl_r32_imm8     
  movl %eax, 0x18(%rsp)      #  44    0xb66a7  4      OPC=movl_m32_r32      
  addl $0x1, %r13d           #  45    0xb66ab  4      OPC=addl_r32_imm8     
  movq (%rcx), %rax          #  46    0xb66af  3      OPC=movq_r64_m64      
  testq %rax, %rax           #  47    0xb66b2  3      OPC=testq_r64_r64     
  movq %rax, (%rsi)          #  48    0xb66b5  3      OPC=movq_m64_r64      
  je .L_b6720                #  49    0xb66b8  2      OPC=je_label          
.L_b66ba:                    #        0xb66ba  0      OPC=<label>           
  movl %r13d, %ebp           #  50    0xb66ba  3      OPC=movl_r32_r32      
  cmpq %rbp, %r12            #  51    0xb66bd  3      OPC=cmpq_r64_r64      
  jne .L_b6690               #  52    0xb66c0  2      OPC=jne_label         
  movq %r12, %rsi            #  53    0xb66c2  3      OPC=movq_r64_r64      
  movl $0x0, %edi            #  54    0xb66c5  5      OPC=movl_r32_imm32    
  leaq (%r12,%r12,1), %r15   #  55    0xb66ca  4      OPC=leaq_r64_m16      
  shlq $0x4, %rsi            #  56    0xb66ce  4      OPC=shlq_r64_imm8     
  cmpq %rbx, %r14            #  57    0xb66d2  3      OPC=cmpq_r64_r64      
  cmovneq %r14, %rdi         #  58    0xb66d5  4      OPC=cmovneq_r64_r64   
  callq .__tls_get_addr_plt  #  59    0xb66d9  5      OPC=callq_label       
  testq %rax, %rax           #  60    0xb66de  3      OPC=testq_r64_r64     
  je .L_b6790                #  61    0xb66e1  6      OPC=je_label_1        
  cmpq %rbx, %r14            #  62    0xb66e7  3      OPC=cmpq_r64_r64      
  je .L_b6770                #  63    0xb66ea  6      OPC=je_label_1        
  movq %rax, %r14            #  64    0xb66f0  3      OPC=movq_r64_r64      
  movl 0x18(%rsp), %eax      #  65    0xb66f3  4      OPC=movl_r32_m32      
  movq %r15, %r12            #  66    0xb66f7  3      OPC=movq_r64_r64      
  leaq (%r14,%rbp,8), %rsi   #  67    0xb66fa  4      OPC=leaq_r64_m16      
  cmpl $0x30, %eax           #  68    0xb66fe  3      OPC=cmpl_r32_imm8     
  jb .L_b669d                #  69    0xb6701  2      OPC=jb_label          
.L_b6703:                    #        0xb6703  0      OPC=<label>           
  movq 0x20(%rsp), %rcx      #  70    0xb6703  5      OPC=movq_r64_m64      
  addl $0x1, %r13d           #  71    0xb6708  4      OPC=addl_r32_imm8     
  leaq 0x8(%rcx), %rax       #  72    0xb670c  4      OPC=leaq_r64_m16      
  movq %rax, 0x20(%rsp)      #  73    0xb6710  5      OPC=movq_m64_r64      
  movq (%rcx), %rax          #  74    0xb6715  3      OPC=movq_r64_m64      
  testq %rax, %rax           #  75    0xb6718  3      OPC=testq_r64_r64     
  movq %rax, (%rsi)          #  76    0xb671b  3      OPC=movq_m64_r64      
  jne .L_b66ba               #  77    0xb671e  2      OPC=jne_label         
.L_b6720:                    #        0xb6720  0      OPC=<label>           
  movl 0x18(%rsp), %eax      #  78    0xb6720  4      OPC=movl_r32_m32      
  cmpl $0x30, %eax           #  79    0xb6724  3      OPC=cmpl_r32_imm8     
  jae .L_b6768               #  80    0xb6727  2      OPC=jae_label         
  addq 0x28(%rsp), %rax      #  81    0xb6729  5      OPC=addq_r64_m64      
.L_b672e:                    #        0xb672e  0      OPC=<label>           
  movq (%rax), %rdx          #  82    0xb672e  3      OPC=movq_r64_m64      
  movq 0x8(%rsp), %rdi       #  83    0xb6731  5      OPC=movq_r64_m64      
  movq %r14, %rsi            #  84    0xb6736  3      OPC=movq_r64_r64      
  callq .execve              #  85    0xb6739  5      OPC=callq_label       
  cmpq %rbx, %r14            #  86    0xb673e  3      OPC=cmpq_r64_r64      
  je .L_b6753                #  87    0xb6741  2      OPC=je_label          
  movq %r14, %rdi            #  88    0xb6743  3      OPC=movq_r64_r64      
  movl %eax, 0x8(%rsp)       #  89    0xb6746  4      OPC=movl_m32_r32      
  callq .L_1f8c0             #  90    0xb674a  5      OPC=callq_label       
  movl 0x8(%rsp), %eax       #  91    0xb674f  4      OPC=movl_r32_m32      
.L_b6753:                    #        0xb6753  0      OPC=<label>           
  addq $0x2068, %rsp         #  92    0xb6753  7      OPC=addq_r64_imm32    
  popq %rbx                  #  93    0xb675a  1      OPC=popq_r64_1        
  popq %rbp                  #  94    0xb675b  1      OPC=popq_r64_1        
  popq %r12                  #  95    0xb675c  2      OPC=popq_r64_1        
  popq %r13                  #  96    0xb675e  2      OPC=popq_r64_1        
  popq %r14                  #  97    0xb6760  2      OPC=popq_r64_1        
  popq %r15                  #  98    0xb6762  2      OPC=popq_r64_1        
  retq                       #  99    0xb6764  1      OPC=retq              
  nop                        #  100   0xb6765  1      OPC=nop               
  nop                        #  101   0xb6766  1      OPC=nop               
  nop                        #  102   0xb6767  1      OPC=nop               
.L_b6768:                    #        0xb6768  0      OPC=<label>           
  movq 0x20(%rsp), %rax      #  103   0xb6768  5      OPC=movq_r64_m64      
  jmpq .L_b672e              #  104   0xb676d  2      OPC=jmpq_label        
  nop                        #  105   0xb676f  1      OPC=nop               
.L_b6770:                    #        0xb6770  0      OPC=<label>           
  leaq (,%r12,8), %rdx       #  106   0xb6770  8      OPC=leaq_r64_m16      
  movq %r14, %rsi            #  107   0xb6778  3      OPC=movq_r64_r64      
  movq %rax, %rdi            #  108   0xb677b  3      OPC=movq_r64_r64      
  movq %r15, %r12            #  109   0xb677e  3      OPC=movq_r64_r64      
  callq .__GI_memcpy         #  110   0xb6781  5      OPC=callq_label       
  movq %rax, %r14            #  111   0xb6786  3      OPC=movq_r64_r64      
  jmpq .L_b6690              #  112   0xb6789  5      OPC=jmpq_label_1      
  xchgw %ax, %ax             #  113   0xb678e  2      OPC=xchgw_ax_r16      
.L_b6790:                    #        0xb6790  0      OPC=<label>           
  cmpq %rbx, %r14            #  114   0xb6790  3      OPC=cmpq_r64_r64      
  je .L_b679d                #  115   0xb6793  2      OPC=je_label          
  movq %r14, %rdi            #  116   0xb6795  3      OPC=movq_r64_r64      
  callq .L_1f8c0             #  117   0xb6798  5      OPC=callq_label       
.L_b679d:                    #        0xb679d  0      OPC=<label>           
  movl $0xffffffff, %eax     #  118   0xb679d  6      OPC=movl_r32_imm32_1  
  jmpq .L_b6753              #  119   0xb67a3  2      OPC=jmpq_label        
  nop                        #  120   0xb67a5  1      OPC=nop               
  nop                        #  121   0xb67a6  1      OPC=nop               
  nop                        #  122   0xb67a7  1      OPC=nop               
  nop                        #  123   0xb67a8  1      OPC=nop               
  nop                        #  124   0xb67a9  1      OPC=nop               
  nop                        #  125   0xb67aa  1      OPC=nop               
  nop                        #  126   0xb67ab  1      OPC=nop               
  nop                        #  127   0xb67ac  1      OPC=nop               
  nop                        #  128   0xb67ad  1      OPC=nop               
  nop                        #  129   0xb67ae  1      OPC=nop               
  xchgw %ax, %ax             #  130   0xb67af  2      OPC=xchgw_ax_r16      
                                                                            
.size execle, .-execle
