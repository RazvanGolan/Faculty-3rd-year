; Read n, m and n numbers stored each one at the memory address starting from m, incrementing the address for each element.

INP R0, 2        ; Read integer n (number of elements in the array) into register R0
INP R1, 2        ; Read integer m (starting memory address for array storage) into register R1

COMPARE CMP R0, #0 ; Compare n (R0) to 0 to check if there are any elements left to process
BEQ STOP         ; If n (R0) is 0, branch to STOP (no elements to process)
INP R2, 2        ; Read the next array element from input and store it in register R2
STR R2, (R1)     ; Store the array element in memory at the address in R1 (starting at m)
ADD R1, #1       ; Increment the memory address pointer (R1) to the next position
OUT R2, 4        ; Output the value of the current array element (R2) to the output device
SUB R0, #1       ; Decrement n (R0), reducing the count of elements left to input
BRA COMPARE      ; Branch back to COMPARE to continue the loop until all elements are processed

STOP HLT         ; Halt the program after all elements are processed and stored
