# Code for HW5, CS 51, Nicole Pavlovich
# Set memory for array
.data
	A: .space 16
	
.text
	# Part 0
	# x = 25; y = 17;
	# array A starting address goes to $s4
	li $s0, 25
	li $s1, 17	
	la $s4, A

	# Part 1
	# A[0] = x; A[1] = y;
	sw $s0, 0($s4)
	sw $s1, 4($s4)
	
	# Part 2
	# A[2] = x - y;
	sub $t0, $s0, $s1
	sw $t0, 8($s4)
	
	# Part 3
	# z = A[0] + A[2]
	lw $t0, 0($s4)
	lw $t1, 8($s4)
	add $s2, $t0, $t1
	
	# Part 4
	# w = x - A[2]
	lw $t2, 8($s4)
	sub $s3, $s0, $t2
	
	# Part 5
	# A[3] = z + (w - A[0])
	lw $t3, 0($s4)
	sub $t4, $s3, $t3
	add $t4, $s2, $t4
	sw $t4, 12($s4)
	
	
	
