; calculate the first 8 numbers in the fibonacci sequence and print them

dosseg
.model small ; this instruction selects the memory model being used
.stack 100h ; declaration of the stack segment
.data ; represents the data declaration section
A DW 0 ; first Fibonacci number
B DW 1 ; second Fibonacci number
C DW 0 ; next Fibonacci number
sequence_count DW 8 ; number of fibonacci numbers to display
fib_string DB "The fibonacci sequence is:$"

.code ; represents the section where the program’s source code is written
new_line proc
    MOV AH, 2
    MOV DL, 10 ; the hex value 0x0A (decimal 10) corresponds to the ASCII code of the special character LF – line feed, corresponding to '\n' (new line character) in C
    INT 21H
    ret
new_line endp

main proc ; proc is the keyword to start a procedure
    MOV AX, @data ; standard instructions to load the data segment
    MOV DS, AX

    ; Display the message "Fibonacci Sequence (First 8 Numbers):"
    MOV AH, 9
    MOV DX, OFFSET fib_string
    INT 21h
    CALL new_line

    ; Display first Fibonacci number (0)
    MOV AX, A
    CALL display_number
    CALL new_line

    ; Display second Fibonacci number (1)
    MOV AX, B
    CALL display_number
    CALL new_line

    ; sequence -= 2 (printed the first two numbers)
    DEC sequence_count
    DEC sequence_count

    ; Loop to calculate and display the remaining Fibonacci numbers
    MOV CX, sequence_count ; Set loop counter for 6 iterations

fib_loop:
    MOV AX, A ; AX = A
    ADD AX, B ; AX += B
    MOV C, AX ; C = AX

    ; Display the current Fibonacci number
    CALL display_number
    CALL new_line

    ; Update A and B for the next iteration
    MOV AX, B ; AX = B
    MOV A, AX ; A = AX
    MOV AX, C ; AX = C
    MOV B, AX ; B = AX

    LOOP fib_loop ; Decrement CX and jump if CX != 0

exit_program:
    ; Exit program
    MOV AH, 4Ch
    INT 21h
main endp ; endp is the keyword indicating the end of a procedure

; Subroutine to display a number in AX (in decimal)
display_number proc
    ; Convert number to ASCII and display
    PUSH AX ; save AX to stack
    PUSH CX ; save CX to stack
    MOV CX, 10 ; divisor for modulus operation
    MOV BX, 0 ; initialize BX (BX will store individual digits)

print_digit:
    XOR DX, DX ; clear DX before DIV
    DIV CX ; AX / 10, remainder in DX
    ADD DL, '0' ; convert remainder to ASCII
    PUSH DX ; push remainder onto stack
    INC BX ; increment BX to count digits
    CMP AX, 0 ; check if AX is 0
    JNE print_digit ; if not zero, continue to next digit

display_stack_digits:
    POP DX ; pop digits from stack (in reverse order)
    MOV AH, 2 ; display character
    INT 21H
    DEC BX ; decrement BX (to check if we've displayed all digits)
    JNZ display_stack_digits ; repeat until all digits displayed

    POP CX; restore CX
    POP AX ; restore AX
    ret
display_number endp
end main
