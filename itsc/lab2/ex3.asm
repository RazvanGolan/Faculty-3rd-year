; Square root of a number given as input
; C = SUM(A) WHILE(B > 0) WHILE (D > 0)

        INP             ; Input the base number A
        STA A           ; Store the input value A in memory
        INP             ; Input the exponent D
        STA D           ; Store the input value D in memory
        LDA A           ; Load the value of A into the accumulator
        STA B           ; Copy A to B (used as a counter for the inner loop)
        LDA ONE         ; Load the value 1 into the accumulator
        STA C           ; Initialize C to 1 (this will hold the result, starting at the multiplicative identity)
        LDA D           ; Load the value of D into the accumulator
        BRZ EQZERO      ; If D is 0, we can jump to EQZERO since A^0 = 1

        LDA ZERO        ; Load the value 0 into the accumulator
        STA C           ; Reinitialize C to 0

EXPONENT LDA D          ; Load the current value of D
        BRZ EQZERO      ; If D is 0, we are done (A^0 = 1)
        SUB ONE         ; Decrement D by 1
        STA D           ; Store the decremented value of D
        
; Now we will multiply A by itself (A is stored in B) as many times as the original D
MULTIPLYBYA LDA C       ; Load current value of C (accumulator holding the result)
        ADD B           ; Add A to C (accumulate the product)
        STA C           ; Store the updated value of C 
        
        LDA B           ; Load the value of B (the counter for the multiplication)
        SUB ONE         ; Decrement B 
        STA B           ; Store the decremented value of B
        VERIFYB BRZ DONE ; Check if B has reached 0; if so, jump to DONE
        BRA MULTIPLYBYA ; If B is not 0, repeat the multiplication step

DONE    LDA A           ; After completing the inner loop, load A again (to reset for the next exponent)
        STA B           ; Copy the value of A to B for the next round of exponentiation
        BRA EXPONENT    ; Jump back to EXPONENT to repeat the outer loop for the next exponent

EQZERO  LDA C           ; Once we hit the exponent 0, load the accumulated result in C
        OUT             ; Output the final result (this is A^D)
        HLT             ; Halt the program

; Data section for variable storage
A       DAT             ; Memory location to store input number A
B       DAT             ; Counter for inner loop (initially holds the value of A)
C       DAT             ; Memory location to accumulate the result (A^D)
D       DAT             ; Memory location to hold the exponent D
ZERO    DAT 0           ; Constant 0 for initialization
ONE     DAT 1           ; Constant 1 (for multiplicative identity)
