section .text

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
