.ORIG X3000
LD R6, STACKLOC   ;R6 存了栈的基地址
START AND R5 R5 #0;
    ADD R5 R5 #3;R5用作计数器，记三次
    LEA R0 PROMPT1;
    PUTS;
    IN 
    LD R1 W;
    ADD R7 R0 R1;
    BRZ PASSWORDINPUT;
    BRNZP  START;
PASSWORDINPUT  LD R1 Y;
               ADD R5 R5 #0;
               BRZ START;
               ADD R5 R5 #-1;
               LEA R0 PROMPT2
               PUTS;
INPUT   IN 
        ADD R7 R0 R1;
        BRZ CMP;
        STR R0 R6 #0;R0->MEM[R6]
        ADD R6 R6 #1;栈生长
        BRNZP INPUT;
CMP     LEA R4 PASSWORD;
    LOOP    ADD R4 R4 #1;
            LDR R7 R4 #0;
            BRZ SUCCESS;
            LDR R3 R4 #0;R3存的是真正的密码
            NOT R3 R3 ;
            ADD R3 R3 #1; R3相反数
            ADD R6 R6 #-1;
            LDR R0 R6 #0; R0存的是从栈里拿出来的输入的密码
            ADD R7 R0 R3 ;IF R0-R3=0 ,这个密码是对的判断下一个
            BRZ LOOP
            LEA R0 PROMPT3;
            PUTS
            BRNZP PASSWORDINPUT ;否则输入密码错误，重新输入
SUCCESS     LEA R0 PROMPT4;
            PUTS;
            HALT;

W .FILL #-87;
Y .FILL #-89;
PROMPT1 .STRINGZ "Welcome to the bank system! Type 'W' to withdraw some fund.\n"
PROMPT2 .STRINGZ "Please input your password:\n"
PROMPT3 .STRINGZ "Fail!\n"
PROMPT4 .STRINGZ "Success!\n"
PASSWORD .STRINGZ "*95216022BP"
STACKLOC .FILL x4000
.END