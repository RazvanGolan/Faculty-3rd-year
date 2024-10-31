; read A, B, C and output A+B-C

dosseg
.model small ; this instruction selects the memory model being used
.stack 100h ; declaration of the stack segment
.data ; represents the data declaration section
A DB 0
B DB 0
C DB 0
X DW 7
n1 DB "Enter the first number:$"
n2 DB "Enter the second number:$"
n3 DB "Enter the third number:$"
result DB "The result is:$"
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
; read the first number from the keyboard
MOV AH, 9
MOV DX, OFFSET n1
INT 21h
MOV AH, 1 ; input service associated with interrupt INT 21H – Keyboard input with echo
INT 21H
MOV A, AL
CALL new_line
; read the second number from the keyboard
MOV AH, 9
MOV DX, OFFSET n2
INT 21h
MOV AH, 1
INT 21H
MOV B, AL
CALL new_line
; read the third number from the keyboard
MOV AH, 9
MOV DX, OFFSET n3
INT 21h
MOV AH, 1
INT 21H
MOV C, AL
CALL new_line
; display the line “The result is:” on the screen
MOV AH, 9
MOV DX, OFFSET result
INT 21h
; calculate the sum A + B
MOV AL, A ; the first number A is moved to the 8-bit AL register
ADD AL, B ; the result of A+B is stored in the 8-bit AL register
; subtract C from the result
SUB AL, C
; display the result on the screen
MOV AH, 2 ; output display service associated with interrupt INT 21H – Display output
MOV DL, AL ; the result is copied to the DL register
INT 21h
MOV AH, 4Ch
INT 21h
main endp ; endp is the keyword indicating the end of a procedure
end main
