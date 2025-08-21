	.text
	.global middleSum

middleSum:
	# Assume that RDI = x, RSI = y
  # Assume that y >= x and both are non-negative
	# Goal: Use a for loop to return the sum of all numbers between x and y inclusive.
	#       eg. if x is 3 and y is 6, then return the value 3 + 4 + 5 + 6
	#       eg. if x is 3 and y is 3, then return the value 3
  # 
	# ADD your code here

    mov ax, %RSI
	subq %RDI, %ax
	#need to subtract rdi from rsi, store in a value, iterate between those values adding that + RDI to ax
	MOV	CL, %RSI
	L1:
	<LOOP-BODY>
	
	DEC	CL
	JNZ	L1



	ret # Returns what is in RAX
# END your code

