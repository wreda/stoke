  .text
  .globl fnmatch__GLIBC_2_2_5
  .type fnmatch__GLIBC_2_2_5, @function

#! file-offset 0xd2580
#! rip-offset  0xd2580
#! capacity    944 bytes

# Text                            #  Line  RIP      Bytes  Opcode                
.fnmatch__GLIBC_2_2_5:            #        0xd2580  0      OPC=<label>           
  pushq %rbp                      #  1     0xd2580  1      OPC=pushq_r64_1       
  movq %rsp, %rbp                 #  2     0xd2581  3      OPC=movq_r64_r64      
  pushq %r15                      #  3     0xd2584  2      OPC=pushq_r64_1       
  pushq %r14                      #  4     0xd2586  2      OPC=pushq_r64_1       
  pushq %r13                      #  5     0xd2588  2      OPC=pushq_r64_1       
  pushq %r12                      #  6     0xd258a  2      OPC=pushq_r64_1       
  movl %edx, %r14d                #  7     0xd258c  3      OPC=movl_r32_r32      
  pushq %rbx                      #  8     0xd258f  1      OPC=pushq_r64_1       
  subq $0x48, %rsp                #  9     0xd2590  4      OPC=subq_r64_imm8     
  movq 0x2ee845(%rip), %rax       #  10    0xd2594  7      OPC=movq_r64_m64      
  movq %rdi, -0x48(%rbp)          #  11    0xd259b  4      OPC=movq_m64_r64      
  movq %rsi, -0x50(%rbp)          #  12    0xd259f  4      OPC=movq_m64_r64      
  movq (%rax), %rax               #  13    0xd25a3  3      OPC=movq_r64_m64      
  nop                             #  14    0xd25a6  1      OPC=nop               
  movq (%rax), %rax               #  15    0xd25a7  3      OPC=movq_r64_m64      
  cmpl $0x1, 0xa8(%rax)           #  16    0xd25aa  7      OPC=cmpl_m32_imm8     
  je .L_d2680                     #  17    0xd25b1  6      OPC=je_label_1        
  movl $0x400, %esi               #  18    0xd25b7  5      OPC=movl_r32_imm32    
  movq $0x0, -0x40(%rbp)          #  19    0xd25bc  8      OPC=movq_m64_imm32    
  movq %rdi, -0x38(%rbp)          #  20    0xd25c4  4      OPC=movq_m64_r64      
  callq .strnlen                  #  21    0xd25c8  5      OPC=callq_label       
  cmpq $0x3ff, %rax               #  22    0xd25cd  6      OPC=cmpq_rax_imm32    
  leaq -0x40(%rbp), %r13          #  23    0xd25d3  4      OPC=leaq_r64_m16      
  jbe .L_d2630                    #  24    0xd25d7  2      OPC=jbe_label         
  xorl %ebx, %ebx                 #  25    0xd25d9  2      OPC=xorl_r32_r32      
.L_d25db:                         #        0xd25db  0      OPC=<label>           
  leaq -0x48(%rbp), %r12          #  26    0xd25db  4      OPC=leaq_r64_m16      
  xorl %edx, %edx                 #  27    0xd25df  2      OPC=xorl_r32_r32      
  xorl %edi, %edi                 #  28    0xd25e1  2      OPC=xorl_r32_r32      
  movq %r13, %rcx                 #  29    0xd25e3  3      OPC=movq_r64_r64      
  movq %r12, %rsi                 #  30    0xd25e6  3      OPC=movq_r64_r64      
  callq .mbsrtowcs                #  31    0xd25e9  5      OPC=callq_label       
  cmpq $0xff, %rax                #  32    0xd25ee  4      OPC=cmpq_r64_imm8     
  je .L_d26c8                     #  33    0xd25f2  6      OPC=je_label_1        
  movq $0x3ffffffffffffffe, %rdx  #  34    0xd25f8  10     OPC=movq_r64_imm64    
  cmpq %rdx, %rax                 #  35    0xd2602  3      OPC=cmpq_r64_r64      
  jbe .L_d26e0                    #  36    0xd2605  6      OPC=jbe_label_1       
.L_d260b:                         #        0xd260b  0      OPC=<label>           
  movq 0x2ee86e(%rip), %rax       #  37    0xd260b  7      OPC=movq_r64_m64      
  movl $0xc, (%rax)               #  38    0xd2612  6      OPC=movl_m32_imm32    
  nop                             #  39    0xd2618  1      OPC=nop               
.L_d2619:                         #        0xd2619  0      OPC=<label>           
  movl $0xfffffffe, %eax          #  40    0xd2619  6      OPC=movl_r32_imm32_1  
.L_d261e:                         #        0xd261f  0      OPC=<label>           
  leaq -0x28(%rbp), %rsp          #  41    0xd261f  4      OPC=leaq_r64_m16      
  popq %rbx                       #  42    0xd2623  1      OPC=popq_r64_1        
  popq %r12                       #  43    0xd2624  2      OPC=popq_r64_1        
  popq %r13                       #  44    0xd2626  2      OPC=popq_r64_1        
  popq %r14                       #  45    0xd2628  2      OPC=popq_r64_1        
  popq %r15                       #  46    0xd262a  2      OPC=popq_r64_1        
  popq %rbp                       #  47    0xd262c  1      OPC=popq_r64_1        
  retq                            #  48    0xd262d  1      OPC=retq              
  nop                             #  49    0xd262e  1      OPC=nop               
  nop                             #  50    0xd262f  1      OPC=nop               
  nop                             #  51    0xd2630  1      OPC=nop               
.L_d2630:                         #        0xd2631  0      OPC=<label>           
  movq %rsp, %rbx                 #  52    0xd2631  3      OPC=movq_r64_r64      
  leaq 0x1(%rax), %rdx            #  53    0xd2634  4      OPC=leaq_r64_m16      
  leaq 0x1e(,%rdx,4), %rax        #  54    0xd2638  8      OPC=leaq_r64_m16      
  andq $0xf0, %rax                #  55    0xd2640  4      OPC=andq_r64_imm8     
  subq %rax, %rsp                 #  56    0xd2644  3      OPC=subq_r64_r64      
  leaq 0xf(%rsp), %r12            #  57    0xd2647  5      OPC=leaq_r64_m16      
  andq $0xf0, %r12                #  58    0xd264c  4      OPC=andq_r64_imm8     
  subq %rsp, %rbx                 #  59    0xd2650  3      OPC=subq_r64_r64      
  leaq -0x38(%rbp), %rsi          #  60    0xd2653  4      OPC=leaq_r64_m16      
  movq %r13, %rcx                 #  61    0xd2657  3      OPC=movq_r64_r64      
  movq %r12, %rdi                 #  62    0xd265a  3      OPC=movq_r64_r64      
  callq .mbsrtowcs                #  63    0xd265d  5      OPC=callq_label       
  cmpq $0xff, %rax                #  64    0xd2662  4      OPC=cmpq_r64_imm8     
  je .L_d26c8                     #  65    0xd2666  2      OPC=je_label          
  cmpq $0x0, -0x38(%rbp)          #  66    0xd2668  5      OPC=cmpq_m64_imm8     
  je .L_d2800                     #  67    0xd266d  6      OPC=je_label_1        
  movq $0x0, (%r13)               #  68    0xd2673  8      OPC=movq_m64_imm32    
  jmpq .L_d25db                   #  69    0xd267b  5      OPC=jmpq_label_1      
  nop                             #  70    0xd2680  1      OPC=nop               
.L_d2680:                         #        0xd2681  0      OPC=<label>           
  movq %rsi, %rdi                 #  71    0xd2681  3      OPC=movq_r64_r64      
  movq %rsi, %rbx                 #  72    0xd2684  3      OPC=movq_r64_r64      
  callq .strlen                   #  73    0xd2687  5      OPC=callq_label       
  subq $0x8, %rsp                 #  74    0xd268c  4      OPC=subq_r64_imm8     
  movq -0x48(%rbp), %rdi          #  75    0xd2690  4      OPC=movq_r64_m64      
  leaq (%rbx,%rax,1), %rdx        #  76    0xd2694  4      OPC=leaq_r64_m16      
  pushq $0x0                      #  77    0xd2698  2      OPC=pushq_imm8        
  movl %r14d, %ecx                #  78    0xd269a  3      OPC=movl_r32_r32      
  movl %r14d, %r8d                #  79    0xd269d  3      OPC=movl_r32_r32      
  andl $0x4, %ecx                 #  80    0xd26a0  3      OPC=andl_r32_imm8     
  movq %rbx, %rsi                 #  81    0xd26a3  3      OPC=movq_r64_r64      
  xorl %r9d, %r9d                 #  82    0xd26a6  3      OPC=xorl_r32_r32      
  callq .internal_fnmatch         #  83    0xd26a9  5      OPC=callq_label       
  popq %rdx                       #  84    0xd26ae  1      OPC=popq_r64_1        
  popq %rcx                       #  85    0xd26af  1      OPC=popq_r64_1        
  leaq -0x28(%rbp), %rsp          #  86    0xd26b0  4      OPC=leaq_r64_m16      
  popq %rbx                       #  87    0xd26b4  1      OPC=popq_r64_1        
  popq %r12                       #  88    0xd26b5  2      OPC=popq_r64_1        
  popq %r13                       #  89    0xd26b7  2      OPC=popq_r64_1        
  popq %r14                       #  90    0xd26b9  2      OPC=popq_r64_1        
  popq %r15                       #  91    0xd26bb  2      OPC=popq_r64_1        
  popq %rbp                       #  92    0xd26bd  1      OPC=popq_r64_1        
  retq                            #  93    0xd26be  1      OPC=retq              
  xchgw %ax, %ax                  #  94    0xd26bf  2      OPC=xchgw_ax_r16      
.L_d26c0:                         #        0xd26c1  0      OPC=<label>           
  movq %r15, %rdi                 #  95    0xd26c1  3      OPC=movq_r64_r64      
  callq .L_1f8c0                  #  96    0xd26c4  5      OPC=callq_label       
.L_d26c8:                         #        0xd26c9  0      OPC=<label>           
  leaq -0x28(%rbp), %rsp          #  97    0xd26c9  4      OPC=leaq_r64_m16      
  movl $0xffffffff, %eax          #  98    0xd26cd  6      OPC=movl_r32_imm32_1  
  popq %rbx                       #  99    0xd26d3  1      OPC=popq_r64_1        
  popq %r12                       #  100   0xd26d4  2      OPC=popq_r64_1        
  popq %r13                       #  101   0xd26d6  2      OPC=popq_r64_1        
  popq %r14                       #  102   0xd26d8  2      OPC=popq_r64_1        
  popq %r15                       #  103   0xd26da  2      OPC=popq_r64_1        
  popq %rbp                       #  104   0xd26dc  1      OPC=popq_r64_1        
  retq                            #  105   0xd26dd  1      OPC=retq              
  nop                             #  106   0xd26de  1      OPC=nop               
  nop                             #  107   0xd26df  1      OPC=nop               
  nop                             #  108   0xd26e0  1      OPC=nop               
  nop                             #  109   0xd26e1  1      OPC=nop               
.L_d26e0:                         #        0xd26e2  0      OPC=<label>           
  leaq 0x1(%rax), %rdx            #  110   0xd26e2  4      OPC=leaq_r64_m16      
  leaq (,%rdx,4), %rdi            #  111   0xd26e6  8      OPC=leaq_r64_m16      
  movq %rdx, -0x58(%rbp)          #  112   0xd26ee  4      OPC=movq_m64_r64      
  callq .memalign_plt             #  113   0xd26f2  5      OPC=callq_label       
  movl -0x40(%rbp), %r11d         #  114   0xd26f7  4      OPC=movl_r32_m32      
  movq %rax, %r15                 #  115   0xd26fb  3      OPC=movq_r64_r64      
  movq -0x58(%rbp), %rdx          #  116   0xd26fe  4      OPC=movq_r64_m64      
  testl %r11d, %r11d              #  117   0xd2702  3      OPC=testl_r32_r32     
  jne .L_d28e6                    #  118   0xd2705  6      OPC=jne_label_1       
  testq %rax, %rax                #  119   0xd270b  3      OPC=testq_r64_r64     
  je .L_d2619                     #  120   0xd270e  6      OPC=je_label_1        
  movq %r12, %rsi                 #  121   0xd2714  3      OPC=movq_r64_r64      
  movq %r13, %rcx                 #  122   0xd2717  3      OPC=movq_r64_r64      
  movq %rax, %rdi                 #  123   0xd271a  3      OPC=movq_r64_r64      
  movq %r15, %r12                 #  124   0xd271d  3      OPC=movq_r64_r64      
  callq .mbsrtowcs                #  125   0xd2720  5      OPC=callq_label       
.L_d2723:                         #        0xd2725  0      OPC=<label>           
  movl -0x40(%rbp), %r10d         #  126   0xd2725  4      OPC=movl_r32_m32      
  testl %r10d, %r10d              #  127   0xd2729  3      OPC=testl_r32_r32     
  jne .L_d28c7                    #  128   0xd272c  6      OPC=jne_label_1       
  movq -0x50(%rbp), %rcx          #  129   0xd2732  4      OPC=movq_r64_m64      
  movl $0x400, %esi               #  130   0xd2736  5      OPC=movl_r32_imm32    
  movq %rcx, %rdi                 #  131   0xd273b  3      OPC=movq_r64_r64      
  movq %rcx, -0x58(%rbp)          #  132   0xd273e  4      OPC=movq_m64_r64      
  callq .strnlen                  #  133   0xd2742  5      OPC=callq_label       
  movq -0x58(%rbp), %rcx          #  134   0xd2747  4      OPC=movq_r64_m64      
  cmpq $0x3ff, %rax               #  135   0xd274b  6      OPC=cmpq_rax_imm32    
  movq %rcx, -0x38(%rbp)          #  136   0xd2751  4      OPC=movq_m64_r64      
  ja .L_d27b9                     #  137   0xd2755  2      OPC=ja_label          
  movq %rsp, %r9                  #  138   0xd2757  3      OPC=movq_r64_r64      
  leaq 0x1(%rax), %rdx            #  139   0xd275a  4      OPC=leaq_r64_m16      
  leaq 0x1e(,%rdx,4), %rax        #  140   0xd275e  8      OPC=leaq_r64_m16      
  andq $0xf0, %rax                #  141   0xd2766  4      OPC=andq_r64_imm8     
  subq %rax, %rsp                 #  142   0xd276a  3      OPC=subq_r64_r64      
  leaq 0xf(%rsp), %r11            #  143   0xd276d  5      OPC=leaq_r64_m16      
  andq $0xf0, %r11                #  144   0xd2772  4      OPC=andq_r64_imm8     
  subq %rsp, %r9                  #  145   0xd2776  3      OPC=subq_r64_r64      
  leaq -0x38(%rbp), %rsi          #  146   0xd2779  4      OPC=leaq_r64_m16      
  movq %r11, %rdi                 #  147   0xd277d  3      OPC=movq_r64_r64      
  movq %r13, %rcx                 #  148   0xd2780  3      OPC=movq_r64_r64      
  movq %r9, -0x60(%rbp)           #  149   0xd2783  4      OPC=movq_m64_r64      
  movq %r11, -0x58(%rbp)          #  150   0xd2787  4      OPC=movq_m64_r64      
  callq .mbsrtowcs                #  151   0xd278b  5      OPC=callq_label       
  cmpq $0xff, %rax                #  152   0xd2790  4      OPC=cmpq_r64_imm8     
  movq %rax, %r8                  #  153   0xd2794  3      OPC=movq_r64_r64      
  movq -0x58(%rbp), %r11          #  154   0xd2797  4      OPC=movq_r64_m64      
  movq -0x60(%rbp), %r9           #  155   0xd279b  4      OPC=movq_r64_m64      
  je .L_d26c0                     #  156   0xd279f  6      OPC=je_label_1        
  addq %r9, %rbx                  #  157   0xd27a5  3      OPC=addq_r64_r64      
  cmpq $0x0, -0x38(%rbp)          #  158   0xd27a8  5      OPC=cmpq_m64_imm8     
  je .L_d28b0                     #  159   0xd27ad  6      OPC=je_label_1        
  movq $0x0, (%r13)               #  160   0xd27b3  8      OPC=movq_m64_imm32    
.L_d27b9:                         #        0xd27bb  0      OPC=<label>           
  leaq -0x50(%rbp), %rax          #  161   0xd27bb  4      OPC=leaq_r64_m16      
  xorl %edx, %edx                 #  162   0xd27bf  2      OPC=xorl_r32_r32      
  xorl %edi, %edi                 #  163   0xd27c1  2      OPC=xorl_r32_r32      
  movq %r13, %rcx                 #  164   0xd27c3  3      OPC=movq_r64_r64      
  movq %rax, %rsi                 #  165   0xd27c6  3      OPC=movq_r64_r64      
  movq %rax, -0x58(%rbp)          #  166   0xd27c9  4      OPC=movq_m64_r64      
  callq .mbsrtowcs                #  167   0xd27cd  5      OPC=callq_label       
  cmpq $0xff, %rax                #  168   0xd27d2  4      OPC=cmpq_r64_imm8     
  movq %rax, %r8                  #  169   0xd27d6  3      OPC=movq_r64_r64      
  je .L_d26c0                     #  170   0xd27d9  6      OPC=je_label_1        
  movq $0x3ffffffffffffffe, %rax  #  171   0xd27df  10     OPC=movq_r64_imm64    
  cmpq %rax, %r8                  #  172   0xd27e9  3      OPC=cmpq_r64_r64      
  jbe .L_d2810                    #  173   0xd27ec  2      OPC=jbe_label         
  movq %r15, %rdi                 #  174   0xd27ee  3      OPC=movq_r64_r64      
  callq .L_1f8c0                  #  175   0xd27f1  5      OPC=callq_label       
  jmpq .L_d260b                   #  176   0xd27f6  5      OPC=jmpq_label_1      
  nop                             #  177   0xd27fb  1      OPC=nop               
  nop                             #  178   0xd27fc  1      OPC=nop               
  nop                             #  179   0xd27fd  1      OPC=nop               
  nop                             #  180   0xd27fe  1      OPC=nop               
  nop                             #  181   0xd27ff  1      OPC=nop               
  nop                             #  182   0xd2800  1      OPC=nop               
  nop                             #  183   0xd2801  1      OPC=nop               
.L_d2800:                         #        0xd2802  0      OPC=<label>           
  xorl %r15d, %r15d               #  184   0xd2802  3      OPC=xorl_r32_r32      
  jmpq .L_d2723                   #  185   0xd2805  5      OPC=jmpq_label_1      
  nop                             #  186   0xd280a  1      OPC=nop               
  nop                             #  187   0xd280b  1      OPC=nop               
  nop                             #  188   0xd280c  1      OPC=nop               
  nop                             #  189   0xd280d  1      OPC=nop               
  nop                             #  190   0xd280e  1      OPC=nop               
  nop                             #  191   0xd280f  1      OPC=nop               
  nop                             #  192   0xd2810  1      OPC=nop               
  nop                             #  193   0xd2811  1      OPC=nop               
.L_d2810:                         #        0xd2812  0      OPC=<label>           
  leaq 0x1(%r8), %rdx             #  194   0xd2812  4      OPC=leaq_r64_m16      
  movq %r8, -0x68(%rbp)           #  195   0xd2816  4      OPC=movq_m64_r64      
  leaq (,%rdx,4), %rdi            #  196   0xd281a  8      OPC=leaq_r64_m16      
  movq %rdx, -0x60(%rbp)          #  197   0xd2822  4      OPC=movq_m64_r64      
  callq .memalign_plt             #  198   0xd2826  5      OPC=callq_label       
  testq %rax, %rax                #  199   0xd282b  3      OPC=testq_r64_r64     
  movq -0x60(%rbp), %rdx          #  200   0xd282e  4      OPC=movq_r64_m64      
  movq -0x68(%rbp), %r8           #  201   0xd2832  4      OPC=movq_r64_m64      
  je .L_d28b5                     #  202   0xd2836  2      OPC=je_label          
  movl -0x40(%rbp), %r9d          #  203   0xd2838  4      OPC=movl_r32_m32      
  testl %r9d, %r9d                #  204   0xd283c  3      OPC=testl_r32_r32     
  jne .L_d2905                    #  205   0xd283f  6      OPC=jne_label_1       
  movq -0x58(%rbp), %rsi          #  206   0xd2845  4      OPC=movq_r64_m64      
  movq %r13, %rcx                 #  207   0xd2849  3      OPC=movq_r64_r64      
  movq %rax, %rdi                 #  208   0xd284c  3      OPC=movq_r64_r64      
  movq %r8, -0x60(%rbp)           #  209   0xd284f  4      OPC=movq_m64_r64      
  movq %rax, -0x58(%rbp)          #  210   0xd2853  4      OPC=movq_m64_r64      
  callq .mbsrtowcs                #  211   0xd2857  5      OPC=callq_label       
  movq -0x58(%rbp), %r10          #  212   0xd285c  4      OPC=movq_r64_m64      
  movq -0x60(%rbp), %r8           #  213   0xd2860  4      OPC=movq_r64_m64      
  movq %r10, %r11                 #  214   0xd2864  3      OPC=movq_r64_r64      
.L_d2865:                         #        0xd2867  0      OPC=<label>           
  subq $0x8, %rsp                 #  215   0xd2867  4      OPC=subq_r64_imm8     
  leaq (%r11,%r8,4), %rdx         #  216   0xd286b  4      OPC=leaq_r64_m16      
  movl %r14d, %ecx                #  217   0xd286f  3      OPC=movl_r32_r32      
  pushq %rbx                      #  218   0xd2872  1      OPC=pushq_r64_1       
  movq %r11, %rsi                 #  219   0xd2873  3      OPC=movq_r64_r64      
  andl $0x4, %ecx                 #  220   0xd2876  3      OPC=andl_r32_imm8     
  xorl %r9d, %r9d                 #  221   0xd2879  3      OPC=xorl_r32_r32      
  movl %r14d, %r8d                #  222   0xd287c  3      OPC=movl_r32_r32      
  movq %r12, %rdi                 #  223   0xd287f  3      OPC=movq_r64_r64      
  movq %r10, -0x58(%rbp)          #  224   0xd2882  4      OPC=movq_m64_r64      
  callq .internal_fnwmatch        #  225   0xd2886  5      OPC=callq_label       
  movq -0x58(%rbp), %r10          #  226   0xd288b  4      OPC=movq_r64_m64      
  movl %eax, %ebx                 #  227   0xd288f  2      OPC=movl_r32_r32      
  movq %r10, %rdi                 #  228   0xd2891  3      OPC=movq_r64_r64      
  callq .L_1f8c0                  #  229   0xd2894  5      OPC=callq_label       
  movq %r15, %rdi                 #  230   0xd2899  3      OPC=movq_r64_r64      
  callq .L_1f8c0                  #  231   0xd289c  5      OPC=callq_label       
  popq %rsi                       #  232   0xd28a1  1      OPC=popq_r64_1        
  movl %ebx, %eax                 #  233   0xd28a2  2      OPC=movl_r32_r32      
  popq %rdi                       #  234   0xd28a4  1      OPC=popq_r64_1        
  jmpq .L_d261e                   #  235   0xd28a5  5      OPC=jmpq_label_1      
  nop                             #  236   0xd28aa  1      OPC=nop               
  nop                             #  237   0xd28ab  1      OPC=nop               
  nop                             #  238   0xd28ac  1      OPC=nop               
  nop                             #  239   0xd28ad  1      OPC=nop               
  nop                             #  240   0xd28ae  1      OPC=nop               
  nop                             #  241   0xd28af  1      OPC=nop               
  nop                             #  242   0xd28b0  1      OPC=nop               
  nop                             #  243   0xd28b1  1      OPC=nop               
.L_d28b0:                         #        0xd28b2  0      OPC=<label>           
  xorl %r10d, %r10d               #  244   0xd28b2  3      OPC=xorl_r32_r32      
  jmpq .L_d2865                   #  245   0xd28b5  2      OPC=jmpq_label        
.L_d28b5:                         #        0xd28b7  0      OPC=<label>           
  movq %r15, %rdi                 #  246   0xd28b7  3      OPC=movq_r64_r64      
  callq .L_1f8c0                  #  247   0xd28ba  5      OPC=callq_label       
  movl $0xfffffffe, %eax          #  248   0xd28bf  6      OPC=movl_r32_imm32_1  
  jmpq .L_d261e                   #  249   0xd28c5  5      OPC=jmpq_label_1      
.L_d28c7:                         #        0xd28ca  0      OPC=<label>           
  leaq 0xb973b(%rip), %rcx        #  250   0xd28ca  7      OPC=leaq_r64_m16      
  leaq 0xb9707(%rip), %rsi        #  251   0xd28d1  7      OPC=leaq_r64_m16      
  leaq 0xb970a(%rip), %rdi        #  252   0xd28d8  7      OPC=leaq_r64_m16      
  movl $0x182, %edx               #  253   0xd28df  5      OPC=movl_r32_imm32    
  callq .__assert_fail            #  254   0xd28e4  5      OPC=callq_label       
.L_d28e6:                         #        0xd28e9  0      OPC=<label>           
  leaq 0xb971c(%rip), %rcx        #  255   0xd28e9  7      OPC=leaq_r64_m16      
  leaq 0xb96e8(%rip), %rsi        #  256   0xd28f0  7      OPC=leaq_r64_m16      
  leaq 0xb96eb(%rip), %rdi        #  257   0xd28f7  7      OPC=leaq_r64_m16      
  movl $0x17c, %edx               #  258   0xd28fe  5      OPC=movl_r32_imm32    
  callq .__assert_fail            #  259   0xd2903  5      OPC=callq_label       
.L_d2905:                         #        0xd2908  0      OPC=<label>           
  leaq 0xb96fd(%rip), %rcx        #  260   0xd2908  7      OPC=leaq_r64_m16      
  leaq 0xb96c9(%rip), %rsi        #  261   0xd290f  7      OPC=leaq_r64_m16      
  leaq 0xb96cc(%rip), %rdi        #  262   0xd2916  7      OPC=leaq_r64_m16      
  movl $0x1b4, %edx               #  263   0xd291d  5      OPC=movl_r32_imm32    
  callq .__assert_fail            #  264   0xd2922  5      OPC=callq_label       
  nop                             #  265   0xd2927  1      OPC=nop               
  nop                             #  266   0xd2928  1      OPC=nop               
  nop                             #  267   0xd2929  1      OPC=nop               
  nop                             #  268   0xd292a  1      OPC=nop               
  nop                             #  269   0xd292b  1      OPC=nop               
  nop                             #  270   0xd292c  1      OPC=nop               
  nop                             #  271   0xd292d  1      OPC=nop               
  nop                             #  272   0xd292e  1      OPC=nop               
  nop                             #  273   0xd292f  1      OPC=nop               
  nop                             #  274   0xd2930  1      OPC=nop               
  xchgw %ax, %ax                  #  275   0xd2931  2      OPC=xchgw_ax_r16      
                                                                                 
.size fnmatch__GLIBC_2_2_5, .-fnmatch__GLIBC_2_2_5
