extern printf

section .text

global main

main:

    xor edi, edi			; EDI = 0 (sum)
    mov ecx, 2				; ECX = 2 (i)

    .sum_loop:
    mov eax, ecx			; Copy i into eax
    and eax, 1				; i % 2

    test eax, eax
    jnz .add_sum_after			; if(i % 2 == 0) dont add to sum

    add edi, ecx			; sum += i

    .add_sum_after:
    inc ecx				; i++
    cmp ecx, 30				; i <= 30 ?
    jle .sum_loop			; If yes, loop

    .sum_loop_after:
    push edi
    push message
    call printf				; printf(message, sum)

    mov eax, 1
    mov ebx, 0
    int 0x80				; Exit with error code 0

section .data

message db "The sum of the even numbers is: %i", 10, 0

section .note.GNU-stack
