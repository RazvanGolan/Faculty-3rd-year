; Read n, m and n numbers stored each one at the memory address starting from m. Sort them using bubble sort and print the result
; Bubblesort used
; for(i = 0; i < n; i++)
; for(j = 0; j < m; j++)
;     if(a[i] < a[j])
;         swap()

        INP R0, 2 ; read n
        PSH R0 ; put n in stack
        INP R1, 2 ; read m
        MOV R5, R1 ; move m to R5
        JMS CHECK_ARRAY
DONE_ARRAY JMS SORT
        HLT
STOP    RET
SORTED  MOV R6, #0
        MOV R1, R5
PRINT   CMP R6, R0 ; for (i)
        BEQ STOP
        LDR R4, (R1) ; R4 = a[i]
        OUT R4, 4 ; print(a[i])
        ADD R6, #1 ; i++
        ADD R1, #1 ; adress of a[i]++
        BRA PRINT
CHECK_ARRAY CMP R0, #0 ; read n numbers
        BEQ DONE_ARRAY
        INP R2, 2 
        STR R2, (R1) ; store them starting at m adress
        ADD R1, #1
        SUB R0, #1
        BRA CHECK_ARRAY
SORT    MOV R6, #0 ; this is the i
        MOV R1, R5 ; R1 = m
        POP R0 ; R0 = n
FORI    CMP R6, R0 ; for (i)
        BEQ SORTED 
        LDR R2, (R1) ; R2 = a[i]
        MOV R7, #0 ; this is the j
        MOV R3, R1 ; R3 = adress of a[i]
FORJ    CMP R7, R0 ; for (j)
        BEQ INCREMI
        LDR R4, (R3) ; R4 = a[j]
        CMP R4, R2 ; if (a[i] < a[j])
        BLT SWAP
        BRA INCREMJ
SWAP    STR R4, (R1) ; a[i] = a[j]
        STR R2, (R3) ; a[j] = a[i]
        BRA INCREMJ
INCREMI ADD R1, #1 ; adress of a[i]++
        ADD R6, #1 ; i++
        BRA FORI
INCREMJ ADD R3, #1 ; adress of a[j]++
        ADD R7, #1 ;j++
        BRA FORJ
