<?php
	@header('P3P: CP="NOI CURa ADMa DEVa TAIa OUR DELa BUS IND PHY ONL UNI COM NAV INT DEM PRE"');
	session_start();
//수정 해야 하는 부분 
	$mem= $_POST['member_no']? $_POST['member_no']:2;
	$part = $_GET['part']? $_GET['part']:1;
?>

<!DOCUMENT html>
<html>
<head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no" />
	<title>쾌변 고!</title>
	<link rel="stylesheet" type="text/css" href="css/slide-menu.css" />
	<link rel="stylesheet" type="text/css" href="css/default.css" />


	<script> 
	    var fbacceesstoken = '<?php echo $_SESSION['fbtoken']?>';  
	    var currentusername = '<?php echo $_SESSION['name']?>';  
	    var userid = '<?php echo $_SESSION['id'] ?>';
	    var score = '<?php echo $_SESSION['score'] ?>';
	    var sta = '<?php echo $_SESSION['sta'] ?>';
	 
	/*   if(!sta) {
	    	location.href="login.php";
	    } */
	</script>
</head>
<body>
	<div id="header" class="reveal-header">
		<a href="home.html"><img id="logo" src="img/로고.png" /></a>
	</div>
	<div id="search-wrap">
		<input type="search" />
		<input type="image" id="gps" src="img/gps.png" width= "40" height="40"/>
	</div>
	<div id="mobile-nav"></div>
	<nav class="reveal-nav">
      <ul class="menu">
        <li><a href="login.html">Login</a></li>
        <li><a href="#">Services</a></li>
        <li><a href="#">About</a></li>
        <li><a href="#">PC version</a></li>
	  </ul>
	</nav>
	
	<form action="create.php" method="post" enctype="multipart/form-data">
	
	<?php
		if($part ==1){	//part 가 1 이면 건물이름부터 써야댐 
			echo "<div id='building'>";
			echo "<label>건물이름:  ";
			echo '<input type="text" name="building_name" required />';
			echo "</label>";
			echo '</div>';

			echo "<div style='display:none;'>";
			echo '<input type="number" name="long" value="'.$_GET['lng'].'" />';
			echo '<input type="number" name="lati" value="'.$_GET['lat'].'" />';
			echo "</div>";
		}
		else if($part ==2){	//part가 2면 빌딩정보도 포스트로 보내야댐 
			echo "<div style='display:none;'>";
			echo '<input type="number" name="building_no" value="'.$_GET['building_no'].'">';
			echo "</div>";
		}
	?>

	<?php
		if($part == 1 || $part == 2){	//part가 1,2면 화장실 이름도 써야댐 
			echo "<div id='toilet'>";
			echo "<label>화장실이름: ";
			echo '<input type="text" name="toilet_name" required />';
			echo "</label>";
			echo '</div>';
		}
		else {	//part가 3이면 화장실 정보도 포스트로 보냄 
			echo "<div style='display:none;'>";
			echo '<input type="number" name="toilet_no" value="'.$_GET['toilet_no'].'">';
			echo "</div>";
		}
	?>
	<div style="display: none;"> <!--보이지 않지만 포스트로 보내야하는 내용 -->
		<input type="number" name="member_no" value=<?php echo '"'.$mem.'"'; ?> />
		<input type="number" name="part" value=<?php echo '"'.$part.'"'; ?> />
		<input type="text" name="sub" value="ok" />

	</div>

	<div id="form-wrap">
		<textarea type="content" name="cont" rows="15" required style="width: 100%;"></textarea>
		<label>평점: 1 <input type="range" name="rating" min= "1" max = "5" /> 5
		</label>
		
		<input type="file" name="image" />
		<br>

		<input type="submit" value="쓰기!">
	</div>
	</form>

	<footer>
		<p>&copy; 급하니</p>
	</footer>
	<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
	<script src="js/slide-menu.js"></script>


	
</body>
</html>
