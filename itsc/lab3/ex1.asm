; A / B - C * D

INP R0,2      ; Input the value of A and store it in register R0
INP R1,2      ; Input the value of B and store it in register R1
INP R2,2      ; Input the value of C and store it in register R2
INP R3,2      ; Input the value of D and store it in register R3

DIV R0, R1    ; Divide A by B (R0 = A / B), store the result in R0
MUL R2, R3    ; Multiply C by D (R2 = C * D), store the result in R2
SUB R4, R0, R2; Subtract the result of C * D from A / B (R4 = A/B - C*D)

OUT R4,4      ; Output the result stored in register R4
HLT           ; Halt the program
