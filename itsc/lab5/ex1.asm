; Read n, m and n numbers stored each one at the memory address starting from m. Print the factorial for every number in the array.
; The factorial is calulcated recursively

INP R0, 2 ; read n
INP R1, 2 ; read m
JMS CHECK_ARRAY
STOP HLT
CHECK_ARRAY CMP R0, #0 ; read n numbers
BEQ STOP
INP R2, 2
STR R2, (R1) ; read array number in  R2
ADD R1, #1
SUB R0, #1
JMS FAC
BRA CHECK_ARRAY
RET
FAC MOV R3, #1 ; R3 = 1
RECFAC CMP R2, #0
BEQ RETURN
MUL R3, R2 ; R3 *= R2
SUB R2, #1
BRA RECFAC
RETURN OUT R3
RET