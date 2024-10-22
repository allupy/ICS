.ORIG  X3000
AND R0 R0 #0 ;初始化0
AND R1 R1 #0;   用R1来代表符号位，1为正,-1为负
LD R6 X00FF  ; X3003+X00EB=X3100  R6=N,计数器
LD R5  DATA1           ;-4096->R5 X3100
LD R4 DATA2           ;4096->R4
ADD R6 R6 #-1;计数器先-1方便后续判断
ADD R0 R0 #3; R0代表fn,f1初始化为3
ADD R1 R1 #1; R1 初始化为1，正数
ADD R6 R6 #0;
BRz  #24;如果N==0，则得到最终结果，可以直接存储->36
AND R7 R0 #7;  判断是否整除,结果为零则可以整除
BRz   #19          ;是0，可以整除，调到反转符号->33
ADD R3 R0 #0;   R3==R0一直减10直到为负数
ADD R3 R3 #-10;一直减10直到为负数
BRzp  #-2;
ADD R3 R3 #10; 得到R0的个位数
AND R7 R3 #8;判断是否为8
BRp #13;    是8则转到翻转符号goto 33
ADD R0 R0 R0    ;fn=2fn
ADD R1 R1 #0; 判断符号位是啥
BRn     #2        ;负号则goto  25行
ADD R0 R0 #2; fn=2fn+2
BR     #1;
ADD R0 R0 #-2;fn=2fn-2
ADD R3 R0 #0;   这里开始判断是否越界
ADD R3 R3 R5;
BRp #-2;
ADD R0 R3 R4;
ADD R6 R6 #-1;N=N-1; 
BRz   #4      ;if N==0,程序结束，得到结果存储goto36
BR    #-21       ;否则继续循环，goto->12
NOT R1 R1;
ADD R1 R1 #1;这里两步完成反转；
BR  #-16      ;无条件跳转到20行
ST R0 X0E0;
TRAP X25;
DATA1 .FILL #-4096
DATA2 .FILL #4096
.END