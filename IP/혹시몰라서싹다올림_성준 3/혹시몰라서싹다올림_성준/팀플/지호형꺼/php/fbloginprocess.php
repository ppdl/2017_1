<?php

session_start();  

$fbuserid = $_POST[userid];  
$fbusername = $_POST[username];  
$fbaccess = $_POST[fbaccesstoken];
$_SESSION['nick'] = true;

$host = 'localhost';
$user = 'root';
$pw = 'apmsetup';
$dbName = 'toiletgo';
$mysqli = new mysqli($host, $user, $pw, $dbName);

$curDate = date("Y-n-j");
$query = "SELECT * FROM member where memberid='".$fbuserid."'";  
$result = $mysqli->query($query);
$result_count = $result->num_rows;

if($result_count<1) {  
    //facebook으로 로그인한 아이디가 DB에 없을 경우.
    $query2 = "INSERT INTO member VALUES ('', '".$fbuserid."', '".iconv("utf-8","euc-kr", $fbusername)."', 0, 0, '".$curDate."')";

    $result2 = $mysqli->query($query2);  
      
    $query = "SELECT * FROM member where memberid='".$fbuserid."'";  
    $result = $mysqli->query($query);
    $_SESSION['nick'] = false;
}  

$row = mysqli_fetch_assoc($result);

if($row['lastDate' != $curDate]) {
	$query3 = "UPDATE member set visite = visite + 1 Where memberid='".$fbuserid."'";
	$result2 = $mysqli->query($query3);
}

$_SESSION['no'] = $row['no'];  
$_SESSION['id'] = $row['memberid'];  
//$_SESSION['name'] = iconv("euc-kr","utf-8", $row['name']);  
$_SESSION['name'] = $row['name'];
$_SESSION['score'] = $row['score'];  
$_SESSION['sta'] = true;  
$_SESSION['facebook'] = true;
$_SESSION['fbtoken'] = $fbaccess;
?>