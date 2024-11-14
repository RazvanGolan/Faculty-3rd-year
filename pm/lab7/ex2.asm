; Write a program that reads two strings from the keyboard one at a time and stores them in two variables msg1 and msg2. The end of each character string will be signaled by the special character $, which will be saved at the last position in each string. The program will create and display on the screen a new string obtained by concatenating the two.

dosseg
.model small
.stack 100h
.data
    ; Input buffers (add 2 for length byte and actual length)
    input1 DB 102 DUP(0)     ; Buffer for first input
    input2 DB 102 DUP(0)     ; Buffer for second input
    
    ; Final storage for processed strings
    msg1 DB 100 DUP('$')     ; First string storage
    msg2 DB 100 DUP('$')     ; Second string storage
    result DB 200 DUP('$')   ; Combined string storage
    
    ; Prompts
    prompt1 DB 'Enter first string: $'
    prompt2 DB 13, 10, 'Enter second string: $'
    output_msg DB 13, 10, 'Concatenated string: $'

.code
main proc
    ; Initialize data segment
    MOV AX, @data
    MOV DS, AX
    MOV ES, AX

    ; Display first prompt
    MOV AH, 9
    MOV DX, OFFSET prompt1
    INT 21h

    ; Read first string
    MOV AH, 0Ah             ; Function 0Ah - buffered input
    MOV DX, OFFSET input1   ; Point to input buffer
    MOV input1, 100         ; Set maximum length
    INT 21h

    ; Copy first string to msg1
    XOR CH, CH              ; Clear CH
    MOV CL, input1 + 1      ; Get length of input
    MOV SI, OFFSET input1 + 2  ; Source: actual characters
    MOV DI, OFFSET msg1     ; Destination: msg1
    
copy_first:
    MOV AL, [SI]            ; Get character
    MOV [DI], AL           ; Store character
    INC SI
    INC DI
    LOOP copy_first
    MOV BYTE PTR [DI], '$'  ; Add terminator

    ; Display second prompt
    MOV AH, 9
    MOV DX, OFFSET prompt2
    INT 21h

    ; Read second string
    MOV AH, 0Ah
    MOV DX, OFFSET input2
    MOV input2, 100         ; Set maximum length
    INT 21h

    ; Copy second string to msg2
    XOR CH, CH
    MOV CL, input2 + 1      ; Get length of input
    MOV SI, OFFSET input2 + 2
    MOV DI, OFFSET msg2
    
copy_second:
    MOV AL, [SI]
    MOV [DI], AL
    INC SI
    INC DI
    LOOP copy_second
    MOV BYTE PTR [DI], '$'

    ; Concatenate strings into result
    ; First, copy msg1
    MOV SI, OFFSET msg1
    MOV DI, OFFSET result
    
copy_msg1:
    MOV AL, [SI]
    CMP AL, '$'
    JE copy_msg2_prep       ; If we hit $, start copying msg2
    MOV [DI], AL
    INC SI
    INC DI
    JMP copy_msg1

copy_msg2_prep:
    MOV SI, OFFSET msg2     ; Set up to copy msg2

copy_msg2:
    MOV AL, [SI]
    MOV [DI], AL           ; Copy character (including final $)
    CMP AL, '$'
    JE display_result      ; If we copied $, we're done
    INC SI
    INC DI
    JMP copy_msg2

display_result:
    ; Display output message
    MOV AH, 9
    MOV DX, OFFSET output_msg
    INT 21h

    ; Display concatenated string
    MOV DX, OFFSET result
    INT 21h

    ; Exit program
    MOV AX, 4C00h
    INT 21h
main endp
end main