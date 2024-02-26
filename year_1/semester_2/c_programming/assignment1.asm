extern printf
extern scanf

section .text

global main

main:
    push str_assignment
    push question_fmt
    call printf
    add esp, 8				; Show message to user

    push flt_buf
    push scan_float
    call scanf
    add esp, 8
    fld DWORD [ flt_buf ]		; Get float input from user and store to float register

    push str_lab_exam
    push question_fmt
    call printf
    add esp, 8				; Show message to user

    push flt_buf
    push scan_float
    call scanf
    add esp, 8
    fld DWORD [ flt_buf ]		; Get float input from user and store to float register
    faddp				; Add the two float registers

    push str_final_exam
    push question_fmt
    call printf
    add esp, 8				; Show message to user

    push flt_buf
    push scan_float
    call scanf
    add esp, 8
    fld DWORD [ flt_buf ]		; Get float input from user and store to float register
    faddp				; Add the two float registers
    fld DWORD [ flt_buf ]		; Loading twice gives the same result as multiplying by 2
    faddp				; Add the two float registers

    xor eax, eax			; EAX = 0
    mov al, 0x41			; AL holds the grade_letter (0x41 == A)

    fidiv WORD [exam_grade_divisor]	; Divide the overall grade by 4
    fst DWORD [overall_grade]		; Store the overall grade for later use

    fild WORD [mark_threshold]		; Push the mark threshold into float registers

    .get_grade_letter:
    fcomi st0, st1				; Compare mark threshold to overall grade
    jbe .letter_end				; Jump to end if mark threshold is smaller than overall grade
    inc al					; Otherwise increment the grade letter
    fisub WORD [mark_threshold_decrement]	; Decrement the mark threshold by 10
    cmp al, 0x45				; Check if the grade letter is 'E' to exit loop
    jb .get_grade_letter			; Return to top

    .letter_end:
    sub esp, 4				; Make space on stack to dump floats
    fstp DWORD [esp]			; Dump mark threshold
    fstp DWORD [esp]			; Dump overall grade overwriting mark threshold
    add esp, 4				; Increment stack pointer to "delete" the floats

    push eax				; Push al on stack for printf
    sub esp, 8				; Reserve space on stack for float
    fld DWORD [overall_grade]		; Load into float registers value at overall grade
    fstp QWORD [esp]			; Write the value to the stack while converting to double
    push result_fmt			; Push the format string onto stack for printf
    call printf
    add esp, 16				; Cleanup stack

    mov eax, 1
    mov ebx, 0
    int 0x80

section .data

; Declaring int variables

exam_grade_divisor dw 4
mark_threshold_decrement dw 10
mark_threshold dw 70

; Declaring strings

question_fmt db "Please enter the %s grade of the student: ", 0
result_fmt db "The overall mark is: %.2f%, and the grade is: %c", 10, 0
str_assignment db "assignment", 0
str_lab_exam db "lab exam", 0
str_final_exam db "final exam", 0

scan_float db "%f", 0

section .bss

flt_buf resd 1
overall_grade resd 1

section .note.GNU-stack
