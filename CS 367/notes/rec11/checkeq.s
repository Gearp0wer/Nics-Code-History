	.text
	.global checkeq
#Parameter 1 is in %rdi
#Parameter 2 is in %rsi
#Parameter 3 is in %rdx
#Parameter 4 is in %rcx
#• For reasons we will explain later, only use the following registers in your code:
#%rax, %rdi, %rsi, %rdx, %rcx, %r8, %r9, %r10, %r11
checkeq:
	# Assume that RDI = a and RSI = b
	# Goal: return 1 if a == b, or 0 otherwise
	# YOUR CODE HERE

    movq $1, %rax #rax = 1 preemp
	cmpq %rsi, %RDI # RDI ? RSI
	je done  #rdi = rsi, exit
    decq %RAX # RAX = 0
	
done: 

	ret # returns what is in RAX
	# END YOUR CODE
