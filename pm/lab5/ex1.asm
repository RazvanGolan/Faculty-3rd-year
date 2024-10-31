; calculate n! for a single digit number read from the keyboard

dosseg
.model small ; this instruction selects the memory model being used
.stack 100h ; declaration of the stack segment
.data ; represents the data declaration section
N DB 0
factorial_result DW 1 ; initialize the factorial result to 1
X DW 7
number_string DB "Enter the number:$"
result DB "The factorial is:$"
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
    ; diplay read the number from the keyboard
    MOV AH, 9
    MOV DX, OFFSET number_string
    INT 21h

    ; read the number from the keyboard
    MOV AH, 1 ; input service associated with interrupt INT 21H – Keyboard input with echo
    INT 21H
    SUB AL, '0' ; convert ASCII to integer (0-9)
    MOV N, AL
    CALL new_line

    ; Initialize factorial_result to 1
    MOV factorial_result, 1

    ; Calculate N! using a loop
    MOV CL, N ; CX register will act as the counter, initialized with N

factorial_loop: 
    CMP CL, 1 ; if CX <= 1 end loop
    JLE end_factorial

    MOV AX, factorial_result ; AX = factorial_result
    MUL CX ; AX *= CX 
    MOV factorial_result, AX ; factorial_result = AX

    DEC CX ; decrement CX, the counter
    JMP factorial_loop

end_factorial:
    ; display the line “The factorial is:” on the screen
    MOV AH, 9
    MOV DX, OFFSET result
    INT 21h

    ; display the result
    MOV AX, factorial_result
    CALL display_number ; call subroutine to display the result

    ; exit the subprogram
    MOV AH, 4Ch
    INT 21h
main endp ; endp is the keyword indicating the end of a procedure

; Subroutine to display a number in AX (in decimal)
display_number proc
    ; Convert number to ASCII and display
    PUSH AX ; save AX to stack
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

    POP AX ; restore AX
    ret
display_number endp
end main
