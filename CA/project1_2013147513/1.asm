.data
	out_string: .asciiz "[Converting Alphabet Lower-Upper Case]\n"
	out_string_end:
.text
.main:
	#���� ���� �Է�
	li $v0, 4
	la $a0, out_string
	syscall
	
	#$t0 = ���ڿ��� ����
	la $a1, out_string_end
	la $a2, out_string
	sub $t0, $a1, $a2
	
LOOP:
	lb $t1, ($a0)	
	blt $t1, 65, SKIP
	bgt $t1, 122, SKIP
	
	blt $t1, 91, UPPERTOLOWER
	
	#91��~ 96���� ���ĺ��� �ƴϹǷ�
	blt $t1, 97, SKIP
	
	#�ҹ��� -> �빮��
	subi $t1, $t1, 32
	sb $t1, ($a0)
	j SKIP
	
	#�빮�� -> �ҹ���
UPPERTOLOWER:
	addi $t1, $t1, 32
	sb $t1, ($a0)
SKIP:
	addi $a0, $a0, 1
	subi $t0, $t0, 1
	bgtz $t0, LOOP
	
	li $v0, 4
	la $a0, out_string
	syscall
	
	li $v0, 10
	syscall
