<?php
$fbuserid = $_POST[userid];  
$fbusername = $_POST[username];  
$fbaccess = $_POST[fbaccesstoken];  
  
//echo $fbuserid;  
//echo "\n";  
//echo $fbusername;  
 echo "<script>alert(\"이렇게 띄우면 되자나\");</script>";

 $host = 'localhost';
 $user = 'root';
 $pw = 'apmsetup';
 $dbName = 'toiletgo';
 $mysqli = new mysqli($host, $user, $pw, $dbName);
  
$query = "SELECT * FROM member where memberid='".$fbuserid."'";  
$result = $mysqli->executeQuery($query);  
  
$result_count = $result->num_rows;  
  
if($result_count<1) {  
    //facebook으로 로그인한 아이디가 DB에 없을 경우.  

    $query2 = "INSERT INTO member VALUES ('', '".$fbuserid."', '".iconv("utf-8","euc-kr", $fbusername)."', NULL)";

    $result2 = $mysqli->executeQuery($query2);  
      
    $query = "SELECT * FROM memberid where userid='".$fbuserid."'";  
    $result = $mysqli->executeQuery($query);   
}  
session_start();  
  
$row = mysqli_fetch_assoc($result);  
$_SESSION['num'] = $row['num'];  
$_SESSION['id'] = $row['email'];  
//$_SESSION['name'] = iconv("euc-kr","utf-8", $row['name']);  
$_SESSION['name'] = $row['name'];  
$_SESSION['facebook'] = true;  
$_SESSION['fbtoken'] = $fbaccess; 
?>