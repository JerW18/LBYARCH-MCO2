section .text
bits 64
default rel
global asm_dot_product

asm_dot_product:
	push rbx
	xor rbx, rbx
	subss xmm0, xmm0
	summation:
		movss xmm1, dword[rdx + rbx * 4]
		mulss xmm1, dword[r8 + rbx * 4]
		addss xmm0, xmm1
		inc rbx
		cmp rbx, rcx
		jnz summation
	pop rbx
	ret