  .text
  .globl ConstantOutput
  .type ConstantOutput, @function

#! file-offset 0x66660
#! rip-offset  0x26660
#! capacity    192 bytes

# Text                           #  Line  RIP      Bytes  Opcode    
.ConstantOutput:                 #        0x26660  0      OPC=0     
  movl %edi, %edi                #  1     0x26660  2      OPC=1157  
  movl %edi, %edi                #  2     0x26662  2      OPC=1157  
  movl 0x4(%r15,%rdi,1), %r8d    #  3     0x26664  5      OPC=1156  
  testl %r8d, %r8d               #  4     0x26669  3      OPC=2436  
  jne .L_26700                   #  5     0x2666c  6      OPC=963   
  movl %edi, %edi                #  6     0x26672  2      OPC=1157  
  movsbl 0xc(%r15,%rdi,1), %eax  #  7     0x26674  6      OPC=1280  
  cltq                           #  8     0x2667a  2      OPC=263   
  leaq (%rdi,%rax,1), %rax       #  9     0x2667c  4      OPC=1069  
  movl %eax, %eax                #  10    0x26680  2      OPC=1157  
  movsbl 0xf(%r15,%rax,1), %r8d  #  11    0x26682  6      OPC=1280  
  movl %edi, %edi                #  12    0x26688  2      OPC=1157  
  movsbl 0xe(%r15,%rdi,1), %edx  #  13    0x2668a  6      OPC=1280  
  movl %edx, %ecx                #  14    0x26690  2      OPC=1157  
  subl $0x1, %ecx                #  15    0x26692  3      OPC=2384  
  js .L_266e0                    #  16    0x26695  6      OPC=1043  
  nop                            #  17    0x2669b  1      OPC=1343  
  nop                            #  18    0x2669c  1      OPC=1343  
  leal 0x14(%rdi,%rdx,4), %edx   #  19    0x2669d  4      OPC=1066  
  xorl %eax, %eax                #  20    0x266a1  2      OPC=3758  
  nop                            #  21    0x266a3  1      OPC=1343  
  nop                            #  22    0x266a4  1      OPC=1343  
  nop                            #  23    0x266a5  1      OPC=1343  
.L_266a0:                        #        0x266a6  0      OPC=0     
  movl %ecx, %esi                #  24    0x266a6  2      OPC=1157  
  subl %eax, %esi                #  25    0x266a8  2      OPC=2386  
  cmpl %r8d, %esi                #  26    0x266aa  3      OPC=472   
  je .L_266c0                    #  27    0x266ad  6      OPC=893   
  nop                            #  28    0x266b3  1      OPC=1343  
  nop                            #  29    0x266b4  1      OPC=1343  
  movl %edx, %esi                #  30    0x266b5  2      OPC=1157  
  movl %esi, %esi                #  31    0x266b7  2      OPC=1157  
  movl (%r15,%rsi,1), %esi       #  32    0x266b9  4      OPC=1156  
  movl %esi, %esi                #  33    0x266bd  2      OPC=1157  
  movl 0x14(%r15,%rsi,1), %esi   #  34    0x266bf  5      OPC=1156  
  testl %esi, %esi               #  35    0x266c4  2      OPC=2436  
  je .L_26700                    #  36    0x266c6  6      OPC=893   
  nop                            #  37    0x266cc  1      OPC=1343  
  nop                            #  38    0x266cd  1      OPC=1343  
  nop                            #  39    0x266ce  1      OPC=1343  
  nop                            #  40    0x266cf  1      OPC=1343  
  nop                            #  41    0x266d0  1      OPC=1343  
  nop                            #  42    0x266d1  1      OPC=1343  
.L_266c0:                        #        0x266d2  0      OPC=0     
  addl $0x1, %eax                #  43    0x266d2  3      OPC=65    
  subl $0x4, %edx                #  44    0x266d5  3      OPC=2384  
  cmpl %eax, %ecx                #  45    0x266d8  2      OPC=472   
  jns .L_266a0                   #  46    0x266da  6      OPC=1005  
  nop                            #  47    0x266e0  1      OPC=1343  
  nop                            #  48    0x266e1  1      OPC=1343  
  nop                            #  49    0x266e2  1      OPC=1343  
  nop                            #  50    0x266e3  1      OPC=1343  
  nop                            #  51    0x266e4  1      OPC=1343  
  nop                            #  52    0x266e5  1      OPC=1343  
  nop                            #  53    0x266e6  1      OPC=1343  
  nop                            #  54    0x266e7  1      OPC=1343  
  nop                            #  55    0x266e8  1      OPC=1343  
  nop                            #  56    0x266e9  1      OPC=1343  
  nop                            #  57    0x266ea  1      OPC=1343  
  nop                            #  58    0x266eb  1      OPC=1343  
  nop                            #  59    0x266ec  1      OPC=1343  
  nop                            #  60    0x266ed  1      OPC=1343  
  nop                            #  61    0x266ee  1      OPC=1343  
  nop                            #  62    0x266ef  1      OPC=1343  
  nop                            #  63    0x266f0  1      OPC=1343  
  nop                            #  64    0x266f1  1      OPC=1343  
  nop                            #  65    0x266f2  1      OPC=1343  
  nop                            #  66    0x266f3  1      OPC=1343  
  nop                            #  67    0x266f4  1      OPC=1343  
  nop                            #  68    0x266f5  1      OPC=1343  
  nop                            #  69    0x266f6  1      OPC=1343  
  nop                            #  70    0x266f7  1      OPC=1343  
.L_266e0:                        #        0x266f8  0      OPC=0     
  movl $0x1, %eax                #  71    0x266f8  5      OPC=1154  
  popq %r11                      #  72    0x266fd  2      OPC=1694  
  andl $0xffffffe0, %r11d        #  73    0x266ff  7      OPC=131   
  nop                            #  74    0x26706  1      OPC=1343  
  nop                            #  75    0x26707  1      OPC=1343  
  nop                            #  76    0x26708  1      OPC=1343  
  nop                            #  77    0x26709  1      OPC=1343  
  addq %r15, %r11                #  78    0x2670a  3      OPC=72    
  jmpq %r11                      #  79    0x2670d  3      OPC=928   
  nop                            #  80    0x26710  1      OPC=1343  
  nop                            #  81    0x26711  1      OPC=1343  
  nop                            #  82    0x26712  1      OPC=1343  
  nop                            #  83    0x26713  1      OPC=1343  
  nop                            #  84    0x26714  1      OPC=1343  
  nop                            #  85    0x26715  1      OPC=1343  
  nop                            #  86    0x26716  1      OPC=1343  
  nop                            #  87    0x26717  1      OPC=1343  
  nop                            #  88    0x26718  1      OPC=1343  
  nop                            #  89    0x26719  1      OPC=1343  
  nop                            #  90    0x2671a  1      OPC=1343  
  nop                            #  91    0x2671b  1      OPC=1343  
  nop                            #  92    0x2671c  1      OPC=1343  
  nop                            #  93    0x2671d  1      OPC=1343  
  nop                            #  94    0x2671e  1      OPC=1343  
.L_26700:                        #        0x2671f  0      OPC=0     
  xorl %eax, %eax                #  95    0x2671f  2      OPC=3758  
  popq %r11                      #  96    0x26721  2      OPC=1694  
  andl $0xffffffe0, %r11d        #  97    0x26723  7      OPC=131   
  nop                            #  98    0x2672a  1      OPC=1343  
  nop                            #  99    0x2672b  1      OPC=1343  
  nop                            #  100   0x2672c  1      OPC=1343  
  nop                            #  101   0x2672d  1      OPC=1343  
  addq %r15, %r11                #  102   0x2672e  3      OPC=72    
  jmpq %r11                      #  103   0x26731  3      OPC=928   
  nop                            #  104   0x26734  1      OPC=1343  
  nop                            #  105   0x26735  1      OPC=1343  
  nop                            #  106   0x26736  1      OPC=1343  
  nop                            #  107   0x26737  1      OPC=1343  
  nop                            #  108   0x26738  1      OPC=1343  
  nop                            #  109   0x26739  1      OPC=1343  
  nop                            #  110   0x2673a  1      OPC=1343  
  nop                            #  111   0x2673b  1      OPC=1343  
  nop                            #  112   0x2673c  1      OPC=1343  
  nop                            #  113   0x2673d  1      OPC=1343  
  nop                            #  114   0x2673e  1      OPC=1343  
  nop                            #  115   0x2673f  1      OPC=1343  
  nop                            #  116   0x26740  1      OPC=1343  
  nop                            #  117   0x26741  1      OPC=1343  
  nop                            #  118   0x26742  1      OPC=1343  
  nop                            #  119   0x26743  1      OPC=1343  
  nop                            #  120   0x26744  1      OPC=1343  
  nop                            #  121   0x26745  1      OPC=1343  
                                                                    
.size ConstantOutput, .-ConstantOutput
