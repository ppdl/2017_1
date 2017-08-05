.data
	prompt1: .asciiz "First integer: "
	prompt2: .asciiz "Secont integer: "
	nl: .asciiz "\n"
	hr: .asciiz "-----------------\n"
	mult_result: .asciiz "Multi result: "
	div_result: .asciiz "Div result: \n"
	div_quot: .asciiz "Quotient: " 
	div_rem: .asciiz "Remainder: "
	error: .asciiz "Division error\ndivide by 0!\n"
.text
.main:
	la $a0, prompt1
	li $v0, 4
	syscall
	#ù��° ���� �Է�($t1)
	li $v0, 5
	syscall	
	add $t1, $zero, $v0
	
	la $a0, prompt2
	li $v0, 4
	syscall
	#�ι�° ���� �Է�($t2)
	li $v0, 5
	syscall
	add $t2, $zero, $v0
	
	li $v0, 4
	la $a0, hr
	syscall
	
	# MYMULT parameters
	# $a0 * $a1 = $a2
	add $a0, $zero, $t1
	add $a1, $zero, $t2
	add $a2, $zero, $zero
	jal MYMULT
	
	#���	
	la $a0, mult_result
	li $v0, 4
	syscall
	
	li $v0, 1
	add $a0, $zero, $a3
	syscall
	li $v0, 4
	la $a0, nl
	syscall
	la $a0, hr
	syscall
	
	# MYDIV parameters
	# $a0 / $a1, �� : $a2, ������ : $a3
	add $a1, $zero, $t2
	add $a2, $zero, $zero
	add $a3, $zero, $t1
	jal MYDIV
	
	#���
	la $a0, div_result
	li $v0, 4
	syscall
	la $a0, div_quot
	syscall
	li $v0, 1
	add $a0, $zero, $a2
	syscall
	li $v0, 4
	la $a0, nl
	syscall
	la $a0, div_rem
	li $v0, 4
	syscall
	li $v0, 1
	add $a0, $zero, $a3
	syscall	
	li $v0, 10
	syscall
	
MYMULT:	
	# $a0�� ���� $a1����ŭ ���� -> $a0 * $a1
	ble $a1, 0, EXIT
	add $a3, $a3, $a0
	subi $a1, $a1, 1
	j MYMULT
EXIT:
	jr $ra
MYDIV:	
	# �������� ��($a3)�� ���� 0���� ũ�ų� �������� $a3���� ������ ��($a1)�� ��� ��,  
	# �� Ƚ�� = ��($a2), ������ = ������($a3)
	beq $a1, 0, ERROR #0���� ������ ���
	sub $a3, $a3, $a1
	addi $a2, $a2, 1
	bgez $a3, MYDIV
	subi $a2, $a2, 1
	add $a3, $a3, $a1
	jr $ra
ERROR:
	li $v0, 4
	la $a0, error
	syscall
	
	li $v0, 10
	syscall
	
		
	
