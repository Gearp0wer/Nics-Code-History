	.text
	.global collatzLength

collatzLength:

	# Assume that RDI = x
        # Goal: return the number of terms in the Collatz sequence from x.
        #       If x = 1 then done.
        #       Else if x is even then the next x is x/2.
        #       Else if x is odd then the next x is x*3 + 1.
	# ADD your code here



	ret # Returns what is in RAX
	# END your code
