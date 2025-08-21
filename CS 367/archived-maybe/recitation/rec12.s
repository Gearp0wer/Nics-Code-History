	.file	"rec12.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"error - wrong number of arguments.\n\n"
.LC1:
	.string	"\tusage: %s %s"
.LC2:
	.string	" arg%d"
.LC3:
	.string	"\n\n"
	.text
	.type	check_func_params, @function
check_func_params:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, -40(%rbp)
	movl	-40(%rbp), %eax
	addl	$2, %eax
	cmpl	%eax, -36(%rbp)
	jne	.L2
	movl	$1, %eax
	jmp	.L6
.L2:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$36, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	call	fwrite
	movq	stderr(%rip), %rax
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movl	$.LC1, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$1, -4(%rbp)
	jmp	.L4
.L5:
	movq	stderr(%rip), %rax
	movl	-4(%rbp), %edx
	movl	$.LC2, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	addl	$1, -4(%rbp)
.L4:
	movl	-4(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jle	.L5
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	$.LC3, %edi
	call	fwrite
	movl	$1, %edi
	call	exit
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	check_func_params, .-check_func_params
	.section	.rodata
	.align 8
.LC4:
	.string	"error - not enough arguments.\n\n\tusage: %s funcname [args ...]\n\n"
	.align 8
.LC5:
	.string	"error - memory allocation failed.\n\n"
.LC6:
	.string	"call_dot4"
.LC7:
	.string	"%ld\n"
.LC8:
	.string	"dot4"
.LC9:
	.string	"call_scale"
.LC10:
	.string	"scale"
.LC11:
	.string	"%ld, %ld\n"
.LC12:
	.string	"call_sum"
.LC13:
	.string	"pow2"
.LC14:
	.string	"rec_fib"
	.align 8
.LC15:
	.string	"error - unrecognized command '%s'.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	movl	%edi, -116(%rbp)
	movq	%rsi, -128(%rbp)
	cmpl	$1, -116(%rbp)
	jg	.L8
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %eax
	jmp	.L9
.L8:
	movl	-116(%rbp), %eax
	cltq
	movl	$8, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -40(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L10
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$35, %edx
	movl	$1, %esi
	movl	$.LC5, %edi
	call	fwrite
	movl	$1, %eax
	jmp	.L9
.L10:
	movl	-116(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movl	$2, -20(%rbp)
	jmp	.L11
.L12:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-128(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-32(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol
	movq	%rax, (%rbx)
	addl	$1, -20(%rbp)
.L11:
	movl	-20(%rbp), %eax
	cmpl	-116(%rbp), %eax
	jl	.L12
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-128(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movl	$.LC6, %edx
	movl	$10, %ecx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	repz cmpsb
	seta	%dl
	setb	%al
	subl	%eax, %edx
	movl	%edx, %eax
	movsbl	%al, %eax
	testl	%eax, %eax
	jne	.L13
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$0, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movl	$0, %eax
	call	call_dot4
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L13:
	movq	-56(%rbp), %rax
	movl	$.LC8, %edx
	movl	$5, %ecx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	repz cmpsb
	seta	%dl
	setb	%al
	subl	%eax, %edx
	movl	%edx, %eax
	movsbl	%al, %eax
	testl	%eax, %eax
	jne	.L15
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$8, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movq	-40(%rbp), %rax
	addq	$64, %rax
	movq	(%rax), %r8
	movq	-40(%rbp), %rax
	addq	$56, %rax
	movq	(%rax), %rdi
	movq	-40(%rbp), %rax
	addq	$48, %rax
	movq	(%rax), %r9
	movq	-40(%rbp), %rax
	addq	$40, %rax
	movq	(%rax), %r10
	movq	-40(%rbp), %rax
	addq	$32, %rax
	movq	(%rax), %rcx
	movq	-40(%rbp), %rax
	addq	$24, %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rsi
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	pushq	%r8
	pushq	%rdi
	movq	%r10, %r8
	movq	%rax, %rdi
	call	dot4
	addq	$16, %rsp
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L15:
	movq	-56(%rbp), %rax
	movl	$10, %edx
	movq	%rax, %rsi
	movl	$.LC9, %edi
	call	strncmp
	testl	%eax, %eax
	jne	.L16
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$0, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movl	$0, %eax
	call	call_scale
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L16:
	movq	-56(%rbp), %rax
	movl	$5, %edx
	movq	%rax, %rsi
	movl	$.LC10, %edi
	call	strncmp
	testl	%eax, %eax
	jne	.L17
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$3, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -104(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdx
	leaq	-112(%rbp), %rcx
	leaq	-104(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	scale
	movq	-112(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC11, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L17:
	movq	-56(%rbp), %rax
	movl	$.LC12, %edx
	movl	$9, %ecx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	repz cmpsb
	seta	%dl
	setb	%al
	subl	%eax, %edx
	movl	%edx, %eax
	movsbl	%al, %eax
	testl	%eax, %eax
	jne	.L18
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$2, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -72(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	call_sum
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L18:
	movq	-56(%rbp), %rax
	movl	$.LC13, %edx
	movl	$5, %ecx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	repz cmpsb
	seta	%dl
	setb	%al
	subl	%eax, %edx
	movl	%edx, %eax
	movsbl	%al, %eax
	testl	%eax, %eax
	jne	.L19
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$1, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	pow2
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L19:
	movq	-56(%rbp), %rax
	movl	$.LC14, %edx
	movl	$8, %ecx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	repz cmpsb
	seta	%dl
	setb	%al
	subl	%eax, %edx
	movl	%edx, %eax
	movsbl	%al, %eax
	testl	%eax, %eax
	jne	.L20
	movl	-116(%rbp), %edx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	$1, %ecx
	movq	%rax, %rdi
	call	check_func_params
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	rec_fib
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L14
.L20:
	movq	-128(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC15, %edi
	movl	$0, %eax
	call	printf
	movl	$2, %eax
	jmp	.L9
.L14:
	movl	$0, %eax
.L9:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.5.0 20210514 (Red Hat 8.5.0-4)"
	.section	.note.GNU-stack,"",@progbits
