<?php
//register.php파일로부터 form의 post방식으로 다섯개의 변수를 받아옵니다.
$sent_ID = $_POST['id'];
$sent_password = $_POST['pwd'];
$sent_birth = $_POST['birth'];
$sent_phoneNum = $_POST['phoneNum'];
$sent_address = $_POST['addr'];
//그리고 이 start변수는 처음 회원가입 하는 사람은 
$start = 0;

//디비커넥트
$connect = mysqli_connect('localhost','u2013147561','2013147561', "d2013147561");
if($connect) echo "DB Connection success";
else echo "DB Connection fail";
echo "<br>";
//쿼리문 작성
$q = "insert into user (id, pwd, birth, phoneNum, addr, visit_cnt) values ('$sent_ID', '$sent_password', '$sent_birth', '$sent_phoneNum', '$sent_address', '$start')";

//쿼리문 실행
$test = mysqli_query($connect, $q);
if($test) {
	//성공하면 창에도 성공했다고 뜨고, 성공했으므로 로그인페이지로 유도한다.
	echo "Register success";
	echo "<script>alert(\"Success!! We will go to login page.\");</script>";
	?><script>location.href="login.php";</script><?php
	mysqli_close($connect);
}
//실패하면 회원가입 실패가 창에 출력되며 종료된다.
else echo "Register fail";

mysqli_close($connect);
?>