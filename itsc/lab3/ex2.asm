; Print the interval [A, B)

INP R0,2       ; Input the value of A and store it in register R0 (lower bound of interval)
INP R1,2       ; Input the value of B and store it in register R1 (upper bound of interval)

COMPARE CMP R0,R1  ; Compare A (R0) with B (R1)
BGE STOP       ; If A >= B, jump to STOP (end the program)

OUT R0,4       ; Output the current value of R0 (starting from A)

ADD R0,#1      ; Increment R0 by 1 (move to the next number in the range)

BRA COMPARE    ; Unconditionally branch back to COMPARE to check the next number

STOP HLT       ; Halt the program when the loop is done
