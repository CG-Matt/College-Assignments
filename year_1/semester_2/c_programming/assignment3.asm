extern printf
extern scanf

%define INPUT_SIZE 15

section .text

global main

main:
    fild DWORD [inputs]			; Prime float register with 0 (average)
    xor ebx, ebx			; EBX = 0 (i)

    .input_loop:
    inc ebx				; Increment i by 1
    push ebx				; Push i to stack
    dec ebx				; Restore i to its original value
    push question
    call printf				; printf(question, i + 1)
    add esp, 8				; Cleanup stack

    mov eax, inputs			; Copy inputs* to EAX
    mov ecx, ebx			; Copy i to ECX
    shl ecx, 2				; Multiply i by 4 to get correct offset
    add eax, ecx			; Add offset to inputs*
    push eax				; Push the address of inputs[i] onto stack
    push scan_int
    call scanf				; scanf(scan_int, inputs[i])
    add esp, 8				; Cleanup stack

    mov ecx, ebx			; Copy i
    shl ecx, 2				; Multiply i by 4 to get correct offset
    fiadd DWORD [inputs + ecx]		; average += inputs[i]

    inc ebx
    cmp ebx, INPUT_SIZE
    jnz .input_loop			; Loop while i < INPUT_SIZE

    sub esp, 4
    mov DWORD [esp], INPUT_SIZE
    fidiv DWORD [esp]			; average /= INPUT_SIZE
    add esp, 4				; Cleanup stack

    fstp QWORD [average]		; Store average for later use

    xor ebx, ebx			; i = 0
    fld QWORD [average]			; Push average into float registers
    sub esp, 4				; Reserve 4 bytes on stack
    mov DWORD [esp], 2			; Store int 2 to stack
    fidiv DWORD [esp]			; st0 now holds half the average
    add esp, 4				; Cleanup stack

    .print_loop:
    mov ecx, ebx			; Copy i
    shl ecx, 2				; Multiply i by 4 to get correct offset
    fild DWORD [inputs + ecx]		; Push current input into float registers
    fcomip st0, st1			; Compare with half average and remove current input from float registers
    jnb .skip_value_print		; Skip printing the value if not below half the average

    sub esp, 8				; Make space on stack for double
    fld QWORD [average]			; Move avearge into float registers
    fstp QWORD [esp]			; Write avearge to stack
    inc ebx				; Increment i
    push ebx				; Push i + 1 to stack for printf
    dec ebx				; Restore i
    mov ecx, ebx			; Copy i
    shl ecx, 2				; Multiply i by 4 to get correct offset
    push DWORD [inputs + ecx]
    push answer
    call printf				; printf (answer, inputs[i], i + 1, average)
    add esp, 20				; Cleanup stack

    .skip_value_print:
    inc ebx
    cmp ebx, INPUT_SIZE
    jb .print_loop			; Loop while i < INPUT_SIZE

    fcomp				; Cleanup float registers

    mov eax, 1
    mov ebx, 0
    int 0x80				; Exit with exit code 0

section .data

question db "Please input value no.%d ", 0
answer db "The value of %d, in position %d, is less than half of the average (%.2f).", 10, 0

scan_int db "%d", 0

section .bss

inputs resd INPUT_SIZE
average resq 1

section .note.GNU-stack
