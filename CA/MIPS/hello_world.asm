.data 
#������ �������� ��. �ּҰ��� labeling���ִ� ����. asciiz�� ascii�ڵ带 �ǹ��ϰ�, zero�� ���� null�� ���δٴ� ��
out_string: .asciiz "Hello, World!\n"
out_string2: .asciiz "Goodbye, Cruel World!\n"

.text
.main: 
   li $v0, 4 #load immediate:���� �ٷ� �����´�.
   la $a0, out_string #load address: �ּҰ��� �����´�
   syscall #�������� v0�� �ִ°��� �������� ������ ���� ������ ��. mips syscall �˻��ؼ� ��� ������ �˾ƺ���
   la $a0, out_string2
   syscall
   
   li $v0, 10
   syscall #v0�� 10�� �� �� syscall�ϸ� c���� return 0 ���� ������ �Ѵ�