; Print max(A,B) or A^B if they are equal

INP R0,2       ; Input the value of A and store it in register R0
INP R1,2       ; Input the value of B and store it in register R1

CMP R0,R1      ; Compare A (R0) with B (R1)
BLT PRINTB     ; If A < B, jump to PRINTB (print B)
BLT PRINTA     ; If A > B, jump to PRINTA (print A)

; If A == B, proceed to calculate A^B (A raised to the power of B)
CMP R1,#0      ; Compare B with 0
BEQ PRNTONE    ; If B == 0, jump to PRNTONE and print 1 (since A^0 = 1)

SUB R1,#1      ; Decrement B by 1 (to start the exponentiation loop)
MOV R2,R0      ; Move A to R2 (used for storing the result of A^B)

COMPARE CMP R1,#0  ; Compare the decremented B with 0
BEQ PRINTC     ; If B == 0, jump to PRINTC (print the result of A^B)
MUL R2,R0      ; Multiply R2 by A (R2 = A * A)
SUB R1,#1      ; Decrement B by 1
BRA COMPARE    ; Loop back to COMPARE to continue multiplying until B == 0

PRINTA OUT R0,4    ; Print A (since A > B)
HLT           ; Halt the program

PRINTB OUT R1,4    ; Print B (since A < B)
HLT           ; Halt the program

PRINTC OUT R2,4    ; Print the result of A^B
HLT           ; Halt the program

PRNTONE OUT R7,4   ; Output 1 (A^0 = 1)
HLT           ; Halt the program
