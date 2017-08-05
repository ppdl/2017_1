<?php
	// mysql 및 디비 커넥트
	$sqlcon = mysqli_connect("localhost", "u2013147561", "2013147561", "d2013147561");

	$sent_id = $_POST['id'];
	$sent_password = $_POST['pwd'];
	
	//받은 아이디에 해당하는 row를 얻어오는 쿼리문이다.
	$q = "select * from user where id = \"$sent_id\"";
	if(!$q) {
		echo "<script>alert(\"요청하신 쿼리를 가져오는데 실패했습니다. 로그인 페이지로 돌아갑니다.\");</script>";
		?><script>location.href="login.php";</script><?php
	}

	//받은 아이디에 해당하는 row를 얻어온다.(여기까지는 있는지 없는지 모름)
	$result = mysqli_query($sqlcon, $q) or die("리졀트 레코드 가져오는데 실패했음.");
	if(!$result) {
		echo "<script>alert(\"요청하신 쿼리결과 셋을 가져오는데 실패했습니다. 로그인 페이지로 돌아갑니다.\");</script>";
		?><script>location.href="login.php";</script><?php
	}
	
	//여기서 이제 result_set을 배열로 만드는데, 만약 데이터가 없으면 result셋이 없으므로 
	//아래의 에러처리문이 발동해서 비회원으로 판단, 회원가입페이지로 보낸다.
	$rows = mysqli_fetch_array($result);
	if(!$rows) {
		echo "<script>alert(\"회원이 아닙니다. 회원가입을 하세요. 회원가입 페이지로 이동합니다.\");</script>";
		?><script>location.href="register.php";</script><?php
	}
	
	//모든 예외처리를 통과하여, 이제 검사를 한다.(사실 아이디는 검사할 필요가 없다.)
	if(strcmp($rows['id'], $sent_id) == 0) {
		//비밀번호도 검사한다. 아이디를 알고 비밀번호를 틀리면 회원인 것으로 판단, 
		//에러메세지를 출력하고 다시 한번 로그인 페이지로 보낸다.
		if(strcmp($rows['pwd'], $sent_password) == 0){
			session_start();
			$_SESSION['id'] = $sent_id;
			//이 밑에를 추가
			
			$q = "update user set visit_cnt = visit_cnt+1 where id = \"$sent_id\"";
			$result = mysqli_query($sqlcon, $q);

			$_SESSION['visit_cnt'] = $rows['visit_cnt']+1;
			echo "<script>alert(\"로그인 성공!!\");</script>";
			?><script>location.href="index.php";</script><?php
		}
		else{
			echo "<script>alert(\"패스워드가 틀렸습니다. 로그인 페이지로 돌아갑니다.\");</script>";
			//틀리면 로그인페이지로 돌아감
			?><script>location.href="login.php";</script><?php
		}
	}
	else{
		echo "<script>alert(\"아이디가 틀렸습니다. 로그인 페이지로 돌아갑니다.\");</script>";
		//틀리면 로그인페이지로 돌아감.
		?><script>location.href="login.php";</script><?php
	}
?>