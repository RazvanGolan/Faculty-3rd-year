; Same requirement with n and m. For each number, it checks whether the read number is a Fibonacci number. 
; It returns 1 if true, 0 if false. The returned value is found in the stack.

INP R0, 2           ; Read integer n (number of elements) into register R0
INP R1, 2           ; Read integer m (starting memory address for array storage) into register R1

JMS CHECK_ARRAY     ; Jump to the CHECK_ARRAY procedure to process each number
STOP HLT            ; Halt the program when all elements have been processed

; CHECK_ARRAY procedure
CHECK_ARRAY CMP R0, #0 ; Compare n (R0) to 0 to check if all elements have been processed
BEQ STOP               ; If n is 0, branch to STOP (end of the array)
INP R2, 2              ; Read the next number from input and store it in register R2
STR R2, (R1)           ; Store the number in memory at the address pointed by R1
ADD R1, #1             ; Increment the memory address pointer (R1) to the next position
SUB R0, #1             ; Decrement n (R0), reducing the count of elements left to process
JMS FIB                ; Jump to the FIB procedure to check if the number is a Fibonacci number
POP R7                 ; Pop the result of the Fibonacci check from the stack into R7
OUT R7, 4              ; Output the result (1 if it's a Fibonacci number, 0 otherwise)
BRA CHECK_ARRAY        ; Branch back to CHECK_ARRAY to process the next number
RET                    ; Return to the main program after processing all numbers

; FIB procedure (checks if the number in R2 is a Fibonacci number)
FIB MOV R3, #0         ; Initialize R3 to 0 (first Fibonacci number)
MOV R4, #1             ; Initialize R4 to 1 (second Fibonacci number)

; Start of the Fibonacci comparison loop
CMP R3, R2             ; Compare R3 (current Fibonacci number) to R2 (input number)
BEQ RET1               ; If R3 equals R2, it's a Fibonacci number, branch to RET1 (return 1)
COMPARE CMP R4, R2     ; Compare R4 (next Fibonacci number) to R2
BEQ RET1               ; If R4 equals R2, it's a Fibonacci number, branch to RET1 (return 1)
MOV R5, R3             ; Move the current Fibonacci number (R3) to R5
ADD R5, R4             ; Add the current and next Fibonacci numbers (R5 = R3 + R4)
MOV R3, R4             ; Move R4 to R3 (R3 becomes the previous R4)
MOV R4, R5             ; Move the sum (R5) to R4 (R4 becomes the next Fibonacci number)
CMP R2, R5             ; Compare the input number (R2) with the new Fibonacci number (R5)
BLT RET0               ; If R5 exceeds R2, the input number is not a Fibonacci number, branch to RET0
BRA COMPARE            ; If R5 is still less than or equal to R2, continue comparing

; Return paths
RETURN RET             ; Return to the calling procedure

RET0 MOV R6, #0        ; Set R6 to 0 (not a Fibonacci number)
PSH R6                 ; Push 0 onto the stack
BRA RETURN             ; Branch to the return sequence

RET1 MOV R6, #1        ; Set R6 to 1 (is a Fibonacci number)
PSH R6                 ; Push 1 onto the stack
BRA RETURN             ; Branch to the return sequence
