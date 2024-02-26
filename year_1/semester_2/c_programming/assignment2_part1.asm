extern printf
extern scanf

%define SENTINEL 9999

section .text

global main

main:
    fild DWORD [int_buffer]		; Prime float register with 0 (sum)
    xor ebx, ebx			; EBX = 0 (number_count)

    .input_loop:
    push question
    call printf				; printf(question)
    add esp, 4				; Cleanup stack

    push int_buffer
    push scan_int
    call scanf				; scanf(scan_int, buffer)
    add esp, 8				; Cleanup stack

    cmp DWORD [int_buffer], SENTINEL
    jz .input_loop_after		; if(buffer == SENTINEL) break

    fiadd DWORD [int_buffer]		; sum += buffer
    inc ebx				; number_count++
    jmp .input_loop			; Jump to the beginning of the loop

    .input_loop_after:

    test ebx, ebx
    jnz .skip_nc_zero_chk		; if(number_count == 0)
    mov ebx, 1				; number_count = 1

    .skip_nc_zero_chk:
    mov [int_buffer], ebx
    fidiv DWORD [int_buffer]		; sum /= number_count

    sub esp, 8				; Reserve space on stack for double
    fstp QWORD [esp]			; Write double from register to stack
    push answer
    call printf				; printf(answer, sum)
    add esp, 12				; Cleanup stack

    mov eax, 1
    mov ebx, 0
    int 0x80				; Exit with exit code 0

section .data

question db "Please enter a number to get the average of: ", 0
answer db "The average of the provided numbers is: %.2f", 10, 0

int_buffer dd 0

scan_int db "%d", 0

section .note.GNU-stack
