<?php
	session_start();

	$nick = $_POST[user_name];
	$fbuserid = $_SESSION['id'];

	$host = 'localhost';
	$user = 'root';
	$pw = 'apmsetup';
	$dbName = 'toiletgo';
	
	$mysqli = new mysqli($host, $user, $pw, $dbName);

	$query3 = "UPDATE member set name = '$nick' Where memberid='".$fbuserid."'";
	$result2 = $mysqli->query($query3);

	header("location:http://127.0.0.1/toiletGo/");	
	exit();
?>