<?php session_start();?>

<?php
$sent_id = $_POST['id'];
$sent_pw = $_POST['password'];
$valid = false;
$visit;

$doc = simplexml_load_file('account.xml');
foreach($doc->account as $account){
	if($account->id == $sent_id && $account->password == $sent_pw){
		$valid = true;
		$account->visit++;
		$visit = $account->visit;
		$doc->asXML('account.xml');

		// if login success, +1 to visit number
		$file = "counter.txt";
		$json = json_decode(file_get_contents($file), true);

		$json['visited'] = $json['visited'] + 1;
		if($json['date'] === date("F j, Y")){
			$json['today'] = $json['today'] + 1;
		} else{
			$json['today'] = 1;
			$json['date'] = date("F j, Y");
		}

		file_put_contents($file, json_encode($json));
		//header('Location: index.php');
		break;
	}
}
if($valid){
	$_SESSION['user_id'] = $sent_id;
	echo '<script>window.alert("'.$visit.'번째 방문을 환영합니다.")</script>';
	echo '<script>location.href="index.php";</script>';
	exit();
}
else{
	echo '<script>window.alert("잘못된 로그인 정보");</script>';
	echo '<script>location.href="login.php";</script>';
	exit();
}
?>




