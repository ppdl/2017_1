.data 
#변수명 지정같은 것. 주소값을 labeling해주는 것임. asciiz는 ascii코드를 의미하고, zero는 끝에 null을 붙인다는 뜻
out_string: .asciiz "Hello, World!\n"
out_string2: .asciiz "Goodbye, Cruel World!\n"

.text
.main: 
   li $v0, 4 #load immediate:값을 바로 가져온다.
   la $a0, out_string #load address: 주소값을 가져온다
   syscall #레지스터 v0에 있는값을 바탕으로 무엇을 할지 결정을 함. mips syscall 검색해서 어떻게 쓰는지 알아보기
   la $a0, out_string2
   syscall
   
   li $v0, 10
   syscall #v0에 10이 들어간 후 syscall하면 c에서 return 0 같은 역할을 한다