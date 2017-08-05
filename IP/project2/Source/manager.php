<?php
session_start();

if(!isset($_SESSION['user_id']) || $_SESSION['user_id'] != 'admin'){
	?><script>
	alert("권한이 없습니다.");
	window.location = "login.html";
	<?php
}

$doc = simplexml_load_file('account.xml') or die("Error: Cannot create objedt");

foreach($doc->children() as $account){
	if($account->id == $_POST['ID']){
		$account->password = $_POST['PWD'];
		$doc->asXml('account.xml');
		?>
		<script>
		  alert("정상적으로 변경되었습니다.");
		  window.location = "index.php";
		</script><?php
		break;
	}
}
?>
