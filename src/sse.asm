section .text

global sse
extern byte_to_float

align 16

max_values: dd 255.0, 255.0, 255.0, 255.0

section .data

align 16
c0: dd 0.393, 0.349, 0.272, 0.393
align 16
c1: dd 0.769, 0.686, 0.543 ,0.769
align 16
c2: dd 0.189, 0.168, 0.131, 0.189

section .text

char_to_float:
	mov r10, rax
	lea r10, [r10+r10 * 2]
	shl r10, 2
	push rbx
	push rcx
	push rax
	.loop:
		add r10, rcx
		xor rcx, rcx
		mov eax, [rsi + r10]
		mov ebx, [rel byte_to_float +  4 * ebx]
		mov [rsi + r10], ebx
		inc rcx
		cmp rcx, 12
		jb .loop	
	pop rax
	pop rcx
	pop rbx
	ret

; rdi = count, rsi = array, rdx - transformed_array
sse:
	mov rcx, rdi
	xor rax, rax
	.for:
		call char_to_float

		mov r10, [rsi + rax * 4]
		mov [rdx + rax * 4], r10
		inc rax
		dec rcx
		test rcx, rcx
		jnz .for
ret
