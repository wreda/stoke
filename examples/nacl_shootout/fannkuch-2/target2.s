  .text
  .globl fannkuchredux
  .type fannkuchredux, @function

#! file-offset 0x60490
#! rip-offset  0x20490
#! capacity    272 bytes

# Text                           #  Line  RIP      Bytes  Opcode    
.fannkuchredux:                  #        0x201e0  0      OPC=0     
  movl %r9d, %edx                #  407   0x204d4  3      OPC=1157  
  xorl %r13d, %r13d              #  408   0x204d7  3      OPC=3758  
  movl %r14d, %r11d              #  409   0x204da  3      OPC=1157  
  movl %r14d, %r12d              #  410   0x204dd  3      OPC=1157  
  movl %r10d, -0x24(%rbp)        #  411   0x204e0  4      OPC=1136  
  movq %rbx, -0x30(%rbp)         #  412   0x204e4  4      OPC=1138  
  movl %edx, %r10d
  testl %r10d, %r10d             #  415   0x204ef  3      OPC=2436  
  jle .L_20560                   #  416   0x204f2  6      OPC=919   
  nop
  nop
  nop
  nop
  nop                            #  417   0x204f8  1      OPC=1343  
  nop                            #  418   0x204f9  1      OPC=1343  
  nop                            #  419   0x204fa  1      OPC=1343  
  nop                            #  420   0x204fb  1      OPC=1343  
  nop                            #  421   0x204fc  1      OPC=1343  
  nop                            #  422   0x204fd  1      OPC=1343  
  nop                            #  423   0x204fe  1      OPC=1343  
  nop                            #  424   0x204ff  1      OPC=1343  
  nop                            #  425   0x20500  1      OPC=1343  
  nop                            #  426   0x20501  1      OPC=1343  
  nop                            #  427   0x20502  1      OPC=1343  
  nop                            #  428   0x20503  1      OPC=1343  
.L_204c0:                        #        0x20504  0      OPC=0     
  leal -0x4(%r14,%rdx,4), %edx       #  429   0x20504  4      OPC=1066  
  movl %r11d, %ecx               #  430   0x20508  3      OPC=1157  
  xorl %eax, %eax                #  431   0x2050b  2      OPC=3758  
  movl %r12d, %esi                #
  movl %r12d, %ecx
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop                            #  445   0x20520  1      OPC=1343  
  nop                            #  446   0x20521  1      OPC=1343  
  nop                            #  447   0x20522  1      OPC=1343  
.L_204e0:                        #        0x20549  0      OPC=0     
  movl %ecx, %esi                #  454   0x20529  2      OPC=1157  
  movq (%r15,%rsi,1), %r9
  rorq $0x20, %r9
  movl %edx, %ebx                #  481   0x20549  2      OPC=1157  
  movq (%r15,%rbx,1), %r8 
  rorq $0x20, %r8
  addl $0x4, %eax                #  488   0x2055d  3      OPC=65    
  movl %ebx, %ebx                #  486   0x20557  2      OPC=1157  
  movq %r9, (%r15,%rbx,1)
  subl $0x8, %edx                #  489   0x20560  3      OPC=2384  
  addl $0x8, %ecx                #  490   0x20563  3      OPC=65    
  movl %esi, %esi                #  484   0x20551  2      OPC=1157  
  movq %r8, (%r15,%rsi,1)
  cmpl %r10d, %eax               #  491   0x20566  3      OPC=472   
  jl .L_204e0 
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
.L_20520:
  movl %r14d, %r14d              #  495   0x20571  3      OPC=1157  
  movl (%r15,%r14,1), %edx       #  496   0x20574  4      OPC=1156  
  addl $0x1, %r13d               #  497   0x20578  4      OPC=65    
  testl %edx, %edx               #  498   0x2057c  2      OPC=2436  
  je .L_20580                    #  499   0x2057e  6      OPC=893   
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
.L_20540:                        #        0x20595  0      OPC=0     
  movl %edx, %r9d                #  517   0x20595  3      OPC=1157  
  movl %edx, %r10d
  testl %r10d, %r10d             #  520   0x2059f  3      OPC=2436  
  jg .L_204c0                    #  521   0x205a2  6      OPC=901   
  nop
  nop
  nop
  nop
  nop                            #  522   0x205a8  1      OPC=1343  
  nop                            #  523   0x205a9  1      OPC=1343  
  nop                            #  524   0x205aa  1      OPC=1343  
  nop                            #  525   0x205ab  1      OPC=1343  
  nop                            #  526   0x205ac  1      OPC=1343  
  nop                            #  527   0x205ad  1      OPC=1343  
  nop                            #  528   0x205ae  1      OPC=1343  
  nop                            #  529   0x205af  1      OPC=1343  
  nop                            #  530   0x205b0  1      OPC=1343  
  nop                            #  531   0x205b1  1      OPC=1343  
  nop                            #  532   0x205b2  1      OPC=1343  
  nop                            #  533   0x205b3  1      OPC=1343  
  nop                            #  534   0x205b4  1      OPC=1343  
.L_20560:                        #        0x205b5  0      OPC=0     
  movl %r9d, %edx                #  535   0x205b5  3      OPC=1157  
  addl $0x1, %r13d               #  536   0x205b8  4      OPC=65    
  testl %edx, %edx               #  537   0x205bc  2      OPC=2436  
  jne .L_20540                   #  538   0x205be  6      OPC=963   
  nop                            #  545   0x205ca  1      OPC=1343  
  nop                            #  546   0x205cb  1      OPC=1343  
  nop                            #  547   0x205cc  1      OPC=1343  
  nop                            #  548   0x205cd  1      OPC=1343  
  nop                            #  549   0x205ce  1      OPC=1343  
  nop                            #  550   0x205cf  1      OPC=1343  
  nop                            #  551   0x205d0  1      OPC=1343  
  nop                            #  552   0x205d1  1      OPC=1343  
  nop                            #  553   0x205d2  1      OPC=1343  
  nop                            #  554   0x205d3  1      OPC=1343  
  nop                            #  555   0x205d4  1      OPC=1343  
  nop                            #  556   0x205d5  1      OPC=1343  
  nop                            #  557   0x205d6  1      OPC=1343  
  nop                            #  558   0x205d7  1      OPC=1343  
  nop                            #  559   0x205d8  1      OPC=1343  
  nop                            #  560   0x205d9  1      OPC=1343  
  nop                            #  561   0x205da  1      OPC=1343  
.L_20580:                        #        0x205db  0      OPC=0     
  movl -0x24(%rbp), %r10d        #  562   0x205db  4      OPC=1156  
  movq -0x30(%rbp), %rbx         #  563   0x205df  4      OPC=1161  
  nop                            #  564   0x205e3  1      OPC=1343  
  nop                            #  565   0x205e4  1      OPC=1343  
  nop                            #  566   0x205e5  1      OPC=1343  
  nop                            #  567   0x205e6  1      OPC=1343  
  nop                            #  568   0x205e7  1      OPC=1343  
  nop                            #  569   0x205e8  1      OPC=1343  
  nop                            #  570   0x205e9  1      OPC=1343  
  nop                            #  571   0x205ea  1      OPC=1343  
  nop                            #  572   0x205eb  1      OPC=1343  
  nop                            #  573   0x205ec  1      OPC=1343  
  nop                            #  574   0x205ed  1      OPC=1343  
  nop                            #  575   0x205ee  1      OPC=1343  
  nop                            #  576   0x205ef  1      OPC=1343  
  nop                            #  577   0x205f0  1      OPC=1343  
  nop                            #  578   0x205f1  1      OPC=1343  
  nop                            #  579   0x205f2  1      OPC=1343  
  nop                            #  580   0x205f3  1      OPC=1343  
  nop                            #  581   0x205f4  1      OPC=1343  
  nop                            #  582   0x205f5  1      OPC=1343  
  nop                            #  583   0x205f6  1      OPC=1343  
  nop                            #  584   0x205f7  1      OPC=1343  
  nop                            #  585   0x205f8  1      OPC=1343  
  nop                            #  586   0x205f9  1      OPC=1343  
  retq
                                                                   
.size fannkuchredux, .-fannkuchredux

