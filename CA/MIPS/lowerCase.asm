#대문자를 소문자로 바꾸기.

.data
	#레이블의 주소는, 메모리에 순차적으로 저장됨
	#out_string_end - out_string 하면 out_string의 길이가 나옴
	out_string: .asciiz "DON'T CONVERT QUOTE\n"
	out_string_end:

.text
.main:
	li $v0, 4
	la $a0, out_string
	syscall
	
	la $a1, out_string_end
	la $a2, out_string
	sub $t0, $a1, $a2 #t0 = a1의 주소 - a2의 주소 : string의 길이
	
LOOP:
	lb $t1, ($a0) #load byte : 특정 주소에 있는 byte값을 가져옴. 괄호는 그 주소의 값임. dereference같은 뜻인듯
	
	blt $t1, 65, SKIP #A의 코드가 65, 그것보다 작으면 바꾸지 않음
	bgt $t1, 90, SKIP #Z의 코드가 90, 그것보다 크면 바꾸지 않음
	
	addi $t1, $t1, 32 #add immediate: 상수를 더해줄 수 있음. +32하면 대문자 -> 소문자
	sb $t1, ($a0) #store byte, t1의 byte를 a0의 주소에 저장해 준다

SKIP:
	addi $a0, $a0, 1 #주소 한칸 이동함. ascii character의 크기는 1바이트 이므로
	subi $t0, $t0, 1 #문장 길이를 1씩 줄여줌
	bgtz $t0, LOOP
	
	li $v0, 4
	la $a0, out_string
	syscall
		
	li $v0, 10
	syscall
