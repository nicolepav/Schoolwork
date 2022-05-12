# Extra Credit, CS 51, Nicole Pavlovich

.text

	main: 
	# x in $s0, y in $s1
	li $s0, 30
	li $s1, 27
	
	# Use two add instructions with the $zero register to do this
	add $a0, $s0, $zero
	add $a1, $s1, $zero
	
	# int z ($s2) = bigger(x, y)
	jal leaf_bigger
	add $s2, $v0, $zero
	
	# int w ($s3) = smaller(x, y)
	jal leaf_smaller
	add $s3, $v0, $zero
	
	# you will need to jump below the two  procedures and end the program
	j EndProgram


	leaf_bigger:
		slt $t0, $a1, $a0	# if a1 < a0 set t0 to 1
		bne $t0, $zero, LBElse	# if t1 is not 0, a0 is larger, branch to else	
		add $v0, $a1, $zero	# otherwise return a1 which is larger
		jr $ra
		
		LBElse:
			# return a0 instead because it is larger
			add $v0, $a0, $zero
			jr $ra
			
	leaf_smaller:
		slt $t0, $a1, $a0	# if a1 < a0 set t0 to 1
		beq $t0, $zero, LSElse	# if t0 equals 0, branch to else
		add $v0, $a1, $zero	# otherwise, return a1 because it is smaller
		jr $ra
		
		LSElse:
			# Return a0 because it is smaller 
			add $v0, $a0, $zero
			jr $ra

	EndProgram:
	# the end
