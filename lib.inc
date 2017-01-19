section .text

string_length:
	push rbx
	mov rbx, rdi
	xor rax, rax
	.loop:
		cmp byte[rbx + rax], 0
		je .finish
		inc rax
		jmp .loop
	.finish:
	pop rbx
ret

print_string:
	mov rsi, rdi
	call string_length
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	syscall
	ret

print_uint:
	mov r9, rsp

	dec rsp
	mov byte[rsp], 0
	
	mov r8, 10
	mov rax, rdi
	.loop:
		xor rdx, rdx
		div r8
		add rdx, 48
		dec rsp
		mov byte[rsp], dl
		test rax, rax
		jnz .loop
	
	mov rdi, rsp
	call print_string
	
	mov rsp, r9
	ret
