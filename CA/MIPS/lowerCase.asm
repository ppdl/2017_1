#�빮�ڸ� �ҹ��ڷ� �ٲٱ�.

.data
	#���̺��� �ּҴ�, �޸𸮿� ���������� �����
	#out_string_end - out_string �ϸ� out_string�� ���̰� ����
	out_string: .asciiz "DON'T CONVERT QUOTE\n"
	out_string_end:

.text
.main:
	li $v0, 4
	la $a0, out_string
	syscall
	
	la $a1, out_string_end
	la $a2, out_string
	sub $t0, $a1, $a2 #t0 = a1�� �ּ� - a2�� �ּ� : string�� ����
	
LOOP:
	lb $t1, ($a0) #load byte : Ư�� �ּҿ� �ִ� byte���� ������. ��ȣ�� �� �ּ��� ����. dereference���� ���ε�
	
	blt $t1, 65, SKIP #A�� �ڵ尡 65, �װͺ��� ������ �ٲ��� ����
	bgt $t1, 90, SKIP #Z�� �ڵ尡 90, �װͺ��� ũ�� �ٲ��� ����
	
	addi $t1, $t1, 32 #add immediate: ����� ������ �� ����. +32�ϸ� �빮�� -> �ҹ���
	sb $t1, ($a0) #store byte, t1�� byte�� a0�� �ּҿ� ������ �ش�

SKIP:
	addi $a0, $a0, 1 #�ּ� ��ĭ �̵���. ascii character�� ũ��� 1����Ʈ �̹Ƿ�
	subi $t0, $t0, 1 #���� ���̸� 1�� �ٿ���
	bgtz $t0, LOOP
	
	li $v0, 4
	la $a0, out_string
	syscall
		
	li $v0, 10
	syscall
