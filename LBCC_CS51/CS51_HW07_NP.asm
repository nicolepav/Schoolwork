# Code for HW7, CS 51, Nicole Pavlovich

.data
	A: .space 28
	
.text
	li $t0, 15
	li $t1, 20
	li $t2, 35
	li $t3, 20
	li $t4, 45
	li $t5, 65
	li $t6, 20
	
	la $s0, A
	sw $t0, 0($s0)
	sw $t1, 4($s0)
	sw $t2, 8($s0)
	sw $t3, 12($s0)
	sw $t4, 16($s0)
	sw $t5, 20($s0)
	sw $t6, 24($s0)
	
	li $s1, 0 		# x in $s1
	li $s2, 20 		# y in $s2
	li $s3, 0		# z in $s3
	
	main:

	Loop: 	slti $t7, $s1, 7 		# while x < 7, 
		beq $t7, $zero, endwhile	# otherwise, end the loop	
		
		sll $t8, $s1, 2			# Load the value into t1
		add $t8, $s0, $t8		
		lw $t9, 0($t8)
		
		addi $s1, $s1, 1		# add one to x to increase counter
		
		bne $t9, $s2, Loop		# compare the array value to y, back to top if wrong	
		add $s3, $s3, 1			# add one to z if correct
		
		j Loop				# go back to top
		
	endwhile: 
	
	
	
	
	
	
	
	