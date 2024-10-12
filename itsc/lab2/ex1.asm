; Multiply two numbers given as input
; THIRD = SUM(FIRST) WHILE (SECOND > 0)

INP           ; Take first input (stored in FIRST)
STA FIRST     ; Store input in FIRST
INP           ; Take second input (stored in SECOND)
STA SECOND    ; Store input in SECOND

EQUALS0 LDA SECOND   ; Load SECOND
BRZ ZERO       ; If SECOND is 0, jump to ZERO

SUB ONE        ; Subtract 1 from SECOND
STA SECOND     ; Store the new SECOND value

LDA THIRD      ; Load THIRD
ADD FIRST      ; Add FIRST to THIRD
STA THIRD      ; Store the result in THIRD

LDA SECOND     ; Load SECOND again
BRA EQUALS0    ; Repeat the loop until SECOND is 0

ZERO LDA THIRD ; Once SECOND is 0, load THIRD
OUT            ; Output the result (THIRD)
HLT            ; Halt the program

FIRST DAT      ; Variable to store the first input
SECOND DAT     ; Variable to store the second input
THIRD DAT      ; Variable to accumulate the result
ONE DAT 1      ; Constant value of 1
