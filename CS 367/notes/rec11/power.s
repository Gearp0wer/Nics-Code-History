	.text
	.global power

power:

	# Assume that RDI = x and RSI = n
        # Goal: Compute x to the power of n
	# ADD your code here
	
    mov ax,1
	MOV	CL, %RSI
	L1:
	<LOOP-BODY>
	IMULQ ax, %RDI
	DEC	CL
	JNZ	L1
    



	ret # Returns what is in RAX (result)
	# END your code
