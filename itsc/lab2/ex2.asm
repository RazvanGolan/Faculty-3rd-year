; Square root of a number given as input
; C = SUM(A) WHILE(B > 0) WHILE (D > 0)
; D = 2 (POWER OF 2)

        INP             ; Input the number and store it in the accumulator
        STA A           ; Store the input value in variable A
        LDA A           ; Load the value of A into the accumulator
        STA B           ; Copy the value of A to B (used as the counter for the inner loop)
        LDA ZERO        ; Load the value 0 into the accumulator
        STA C           ; Initialize C to 0 (this will accumulate the result)
        LDA TWO         ; Load the value 2 into the accumulator
        STA D           ; Initialize D to 2 (used as a counter for the outer loop)

EXPONENT LDA D           ; Load the value of D into the accumulator
        SUB ONE         ; Decrement D by 1
        BRZ EQZERO      ; If D is 0, jump to EQZERO (end of inner loop)
        STA D           ; Store the decremented value of D

MULTIPLYBYA LDA C      ; Load the current value of C (result)
        ADD A          ; Add A to C (this is effectively accumulating the result)
        STA C          ; Store the updated value back in C
        LDA B          ; Load the value of B
        SUB ONE        ; Decrement B by 1
        STA B          ; Store the decremented value of B
VERIFYB BRZ DONE       ; If B is 0, we are done, jump to DONE
        BRA MULTIPLYBYA ; If B is not 0, repeat the multiplication step

DONE    LDA A          ; Once the outer loop is done, load A again
        STA B          ; Copy the value of A to B to prepare for the next iteration of EXPONENT
        BRA EXPONENT      ; Jump back to EXPONENT to repeat the outer loop 

EQZERO  LDA C          ; Once both loops are completed, load the accumulated result in C
        OUT             ; Output the value in C (this is the result of A^2, if that is the intention)
        HLT             ; Halt the program

; Data section for variable storage
A       DAT             ; Store input number A
B       DAT             ; Counter for inner loop (initially holds the value of A)
C       DAT             ; Accumulator for the result (sum of A added multiple times)
D       DAT             ; Counter for outer loop (initially set to 2)
ZERO    DAT 0           ; Constant 0 for initialization
ONE     DAT 1           ; Constant 1 for decrementing
TWO     DAT 2           ; Constant 2 for outer loop initialization
