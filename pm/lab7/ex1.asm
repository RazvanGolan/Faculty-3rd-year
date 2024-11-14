; Write a program what reads a string as input and outputs a new string which contains only the vowels of the original string in the order in which they were found in the original string.

dosseg
.model small
.stack 100h
.data
    input_string DB 102 DUP(0)    ; Buffer for input string (including length byte and actual length)
    vowel_string DB 100 DUP('$')  ; Buffer for vowels only
    prompt DB "Enter a string: $"  ; Prompt message
    output_msg DB 13, 10, "Vowels: $" ; Output label with newline
    vowels DB "AEIOUaeiou"        ; List of vowels

.code
main proc
    MOV AX, @data                 ; Initialize data segment
    MOV DS, AX
    MOV ES, AX

    ; Display prompt
    MOV AH, 9
    MOV DX, OFFSET prompt
    INT 21h

    ; Read string from keyboard
    MOV AH, 0Ah                   ; Function 0Ah - Buffered input
    MOV DX, OFFSET input_string   ; DS:DX points to input buffer
    MOV input_string, 100         ; Set maximum length
    INT 21h

    ; Get string length and start position
    MOV SI, OFFSET input_string + 2  ; SI points to actual input characters
    XOR CH, CH                       ; Clear CH
    MOV CL, input_string + 1         ; Get actual length in CL
    MOV DI, OFFSET vowel_string      ; DI points to start of vowel string

filter_vowels:
    CMP CX, 0                     ; Check if we've processed all characters
    JE display_output             ; If done, display output
    
    PUSH CX                       ; Save main loop counter
    MOV AL, [SI]                  ; Load character from input string
    
    ; Check if it's a vowel
    PUSH SI
    MOV SI, OFFSET vowels         ; Point to vowels list
    MOV CX, 10                    ; Number of vowels to check

check_vowel_loop:
    CMP AL, [SI]                  ; Compare with current vowel
    JE found_vowel                ; If match, it's a vowel
    INC SI                        ; Move to next vowel
    LOOP check_vowel_loop         ; Continue checking vowels
    
    POP SI                        ; Restore SI if no vowel found
    JMP next_char

found_vowel:
    POP SI                        ; Restore SI
    MOV [DI], AL                  ; Store vowel in output string
    INC DI                        ; Move to next position in output

next_char:
    INC SI                        ; Move to next input character
    POP CX                        ; Restore main loop counter
    DEC CX                        ; Decrease counter
    JMP filter_vowels             ; Continue processing

display_output:
    MOV BYTE PTR [DI], '$'        ; Terminate vowel string

    ; Display output message
    MOV AH, 9
    MOV DX, OFFSET output_msg
    INT 21h

    ; Display vowel string
    MOV DX, OFFSET vowel_string
    INT 21h

    ; Exit program
    MOV AX, 4C00h
    INT 21h
main endp
end main