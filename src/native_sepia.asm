section .text 

global compute_four_pixels 
extern char_to_float

%define SOF 4

%macro compute_result 0
	mulps xmm3, xmm0
	mulps xmm4, xmm1
	mulps xmm5, xmm2

	addps xmm3, xmm4
	addps xmm3, xmm5
%endmacro

section .bss
	align 16
	comp_buffer: resd 36  
section .text

create_matrix:
	push rcx
	push rsi

	mov rcx, 4 
	mov rsi, comp_buffer

	
	.loop:
		test rcx, rcx
		jz .return


		xor eax, eax
		mov al, [ rdi ]
		mov eax, [ char_to_float + rax * SOF ]

		mov [ rsi ], eax
		mov [ rsi + SOF ], eax
		mov [ rsi + SOF * 2 ], eax

		xor eax, eax
		mov al, [ rdi + 1 ]
		mov eax, [ char_to_float + rax * SOF ]

		mov [ rsi + 12 * SOF ], eax
		mov [ rsi + 13 * SOF ], eax
		mov [ rsi + 14 * SOF ], eax

		xor eax, eax
		mov al, [ rdi + 2 ]
		mov eax, [ char_to_float + rax * SOF ]

		mov [ rsi + 24 * SOF ], eax
		mov [ rsi + 25 * SOF ], eax
		mov [ rsi + 26 * SOF ], eax

		add rdi, 3
		add rsi, 3 * SOF

		dec rcx
		jmp .loop

	.return:
		pop rsi
		pop rcx

		ret

; compute_four_pixels( float* components, float[3][12] c , float[12] result );

compute_four_pixels:
	push rcx
	mov rcx, 3

	call create_matrix
	mov rdi, comp_buffer 

	.loop:
		test rcx, rcx
		jz .return 

		movdqa xmm0, [ rdi ]
		movdqa xmm1, [ rdi + 12 * SOF ]
		movdqa xmm2, [ rdi + 24 * SOF ]

		movdqa xmm3, [ rsi ]
		movdqa xmm4, [ rsi + 12 * SOF ]
		movdqa xmm5, [ rsi + 24 * SOF ]	

		compute_result

		movdqa [ rdx ], xmm3 

		lea rdi, [ rdi + 4 * SOF ]
		lea rsi, [ rsi + 4 * SOF ]
		lea rdx, [ rdx + 4 * SOF ]

		dec rcx
		jmp .loop

	.return:
		pop rcx
		ret
