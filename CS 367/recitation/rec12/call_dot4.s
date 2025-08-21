	.text
	.global call_dot4
call_dot4:

	# YOUR CODE HERE
	movq $1, %rdi
	movq $2, %rsi
	movq $3, %rdx
	movq $4, %rcx
	movq $4, %r8
	movq $3, %r9 
	pushq $1
	pushq $2

	callq dot4



	ret
	# END YOUR CODE
	# I wish I knew what I was doing, 