; Top of the file
extern	printf
extern scanf
global main

; Code section start
SECTION .text
    main:

; Start of data section
SECTION .data
print_int: db "%d", 10, 0
scan_int: db "%d", 0

; Define integer x = 10
x:	dd	10

; Define array x[2]
x:	times 2 dd	0

; Store ith value of array in eax
mov eax, [x + i * 4]

; Exit
mov	eax, 0
ret

; Scan x
push    x
push    dword scan_int
call scanf
add     esp, 8

; Print x
push    dword [x]
push    dword print_int
call    printf
add     esp, 8

; Assign x:= y
mov	eax, [y]
mov	[x], eax

; add, sub, and, or
mov	eax, [x]
add	eax, [y]
mov	[z], eax

; Multiply
mov	eax, [x]
imul dword [y]
mov	[z], eax

; Divide
mov	eax, [x]
mov	edx, 0
idiv dword [y]
mov	[z], eax

; z = (x op y)
; (lt le gt ge eq ne) (jl jle jg jge je jne)
mov	eax, [x]
cmp	eax, [y]
je .true
jmp .end
; not true
mov eax, 0
mov	[z], eax
.true:
mov eax, 1
mov	[z], eax
.end:

; for (i = z; i < z; i++)
mov eax, [x]
cmp	eax, [z]
jge .end
.for:
; op
mov eax, [x]
add eax, 1
mov [x], eax
cmp	eax, [z]
jl .for
.end:

; while z is true
mov eax, [z]
cmp	eax, 0
jle .end
.while:
; op
mov eax, [z]
cmp	eax, 0
jg .while
.end:
