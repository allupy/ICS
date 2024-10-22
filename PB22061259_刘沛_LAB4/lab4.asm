        .ORIG x3000
        LD R0, NLOC      ;R0 = X3100
        LDR R1, R0, #0 ;R1 STORE THE n
        LD R6, STACKLOC   ;R6 存了栈的基地址
        ADD R5, R0, #0   ;R5用来辅助输出计数，
        AND R2, R2, #0   ;//R2用来表示状态
REMOVEN  ;subroutine. To remove nth ring from the board
        STR R1, R6, #0   ;？R1->MEM[R6],R1 = N
        ADD R6, R6, #1  ; R6++,栈生长
        STR R7, R6, #0  ;R7 - >MEM[R6];
        ADD R6, R6, #1  ; 栈再次生长   //建立递归栈
        ADD R0, R1, #0	; //R0 = I
        BRz FINISH  ;NOTHING TO DO; //判断I是否为零,IF (I ==0)直接完成这次递归，出栈；
        ADD R0, R1, #-1  ;//R0 = R1 -1 
        BRnp REMOVE1  ;IF R1!=1 GOTO REMOVE1 //判断I是否为1，是1的话改变状态然后可以出栈；不是1的话进入下一次递归
        ADD R5, R5, #1  ; 完成一次对状态的变化，计数器加一
        ADD R2, R2, #1  ;I==1的时候，直接+1即可
        STR R2, R5, #0  ;R2->MEM[X3100+I]
        BR FINISH       ;完成一次递归，出栈
        
REMOVE1 
        ADD R1, R1, #-2   ;I-2
        JSR REMOVEN       ;完成R[I-2]，之后进行（I）的环remove；
        ADD R5, R5, #1  ;R5++，计数器加一 
        LEA R0, ARRAY     ;
        ADD R0, R0, R1  ;
        ADD R0, R0, #1   ;
        LDR R0, R0, #0  ;   MEM[R0]->R0，利用辅助数组完成状态的改变
        ADD R2, R0, R2  ;R2 = R2+R0
        STR R2, R5, #0  ;完成（I）的环remove，之后进行P(I-2)
        JSR PUTN        ;PUT (I-2),之后进行R(I-1)
        ADD R1, R1, #1  ;REMOVE I-1
        JSR REMOVEN
        BRnzp  FINISH    ;出栈！
        
        
PUTN      
        STR R1, R6, #0  
        ADD R6, R6, #1  
        STR R7, R6, #0
        ADD R6, R6, #1  ;//建立递归栈，跟前面一样的！
        ADD R0, R1, #0   ;R0 = I;
        BRz FINISH  ;I==0,无操作
        ADD R0, R1, #-1 ;判断I是否为1
        BRnp PUT1  ;IF R1!=1 GOTO REMOVE1,I=1,完成 I=1的环PUT
        ADD R5, R5, #1  ; 计数器++
        ADD R2, R2, #-1  ;I==1了，直接环put
        STR R2, R5, #0  ;储存结果
        BRnzp FINISH
       
PUT1
        ADD R1, R1, #-1
        JSR PUTN       ;完成P(I-1),之后完成R(I-2)
        ADD R1, R1, #-1
        JSR REMOVEN    ;完成R(I-2)，之后完成 I 的环PUT
        ADD R5, R5, #1  ; 计数器++
        LEA R0, ARRAY     ;
        ADD R0, R0, R1  ;
        ADD R0, R0, #1   ;
        LDR R0, R0, #0  ; 
        NOT R0, R0
        ADD R0, R0  #1  ;R0=-R0，实现减法改变状态
        ADD R2, R0, R2  ;改变状态
        STR R2, R5, #0  ;储存改变后的状态
        JSR PUTN        ;完成 P（I-2）
        
        
FINISH  ADD R6, R6, #-1  ;//辅助出栈函数
        LDR R7, R6, #0
        ADD R6, R6, #-1
        LDR R1, R6, #0
        RET
        
        
TRAP X25;       
        
ARRAY   .FILL x0001
        .FILL x0002
        .FILL x0004
        .FILL x0008
        .FILL x0010
        .FILL x0020
        .FILL x0040
        .FILL x0080
        .FILL x0100
        .FILL x0200
        .FILL x0400
        .FILL x0800 
        
NLOC    .FILL x3100
STACKLOC .FILL x4000
.END