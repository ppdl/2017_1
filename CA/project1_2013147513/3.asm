.data
	nl : .asciiz "\m"
	hr : .asciiz "-------------\n"
	promptx: .asciiz "Input x: "
	prompty: .asciiz "Input y: "
	result: .asciiz "Result: "
.text
.main:
	la $a0, promptx
	li $v0, 4
	syscall
	#첫번째 숫자 입력(x = $t0)
	li $v0, 5
	syscall	
	add $t0, $zero, $v0

	la $a0, prompty
	li $v0, 4
	syscall	
	#두번째 숫자 입력(y = $t1)
	li $v0, 5
	syscall
	add $t1, $zero, $v0
	
	li $v0, 4
	la $a0, hr
	syscall
	
	# EQUATION parameters
	# $a1 : x, $a2 : y, $v1 : result
	add $a1, $zero, $t0
	add $a2, $zero, $t1
	li $v1, 0
	jal EQUATION
	
	la $a0, result
	li $v0, 4
	syscall
	li $v0, 1
	add $a0, $zero, $v1
	syscall
	
	li $v0, 10
	syscall
	
# 2x^2 + 4xy + 3y^2 - 4
#$a1 : x, $a2 : y, $v1 : result
EQUATION:
	#initiatalize
	li $v1, 0
	
	# 2x^2
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal SQUARE
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	li $t1, 2
	mul $t0, $v0, $t1
	add $v1, $t0, $zero #2x^2
	
	# 4xy
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal MULTIPLY
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	li $t1, 4
	mul $t0, $v0, $t1
	add $v1, $v1, $t0 #2x^2 + 4xy
	
	# 3y^2
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	sw $a1, 0($sp)
	add $a1, $a2, $zero
	jal SQUARE
	lw $a1, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	li $t1, 3
	mul $t0, $v0, $t1
	add $v1, $v1, $t0 # 2x^2 + 4xy + 3y^2
	
	subi $v1, $v1, 7 # 2x&2 + 4xy + 3y^2 -7
	
	
#output $v0 = $a1 * $a2
MULTIPLY:
	mul $v0, $a1, $a2
	jr $ra

#output $v0 = $a1 * $a1
SQUARE:
	mul $v0, $a1, $a1
	jr $ra
	
