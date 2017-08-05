.data
	nl : .asciiz "\m"
	hr : .asciiz "-------------\n"
	prompt: .asciiz "n = "
	_result: .asciiz "F("
	result_: .asciiz ") = "
.text
.main:
	la $a0, prompt
	li $v0, 4
	syscall
	#숫자 입력 ($t0)
	li $v0, 5
	syscall
	add $t0, $v0, $zero
	addi $sp, $sp, -4
	sw $t0, ($sp)
	
	li $v0, 4
	la $a0, hr
	syscall
	
	add $a0, $t0, $zero
	jal FIB
	add $v1, $v0, $zero
	
	la $a0, _result
	li $v0, 4
	syscall
	lw $a0, ($sp)
	addi $sp, $sp, 4
	li $v0, 1
	syscall
	la $a0, result_
	li $v0, 4
	syscall
		
	add $a0, $v1, $zero
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall

FIB:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $s0, 4($sp)
	sw $s1, 0($sp)
	
	add $s0, $a0, $zero
	
	addi $t1, $zero, 1
	beq $s0, $zero, ZERO
	beq $s0, $t1, ONE
	
	addi $a0, $s0, -1
	
	# F(n-1)
	jal FIB
	add $s1, $zero, $v0
	addi $a0, $s0, -2
	# F(n-2)
	jal FIB	
	
	# F(n-1) + F(n-2)
	add $v0, $v0, $s1
EXIT:
	lw $s1, 0($sp)
	lw $s0, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra

ONE:
	li $v0, 1
	j EXIT
ZERO:
	li $v0, 0
	j EXIT
