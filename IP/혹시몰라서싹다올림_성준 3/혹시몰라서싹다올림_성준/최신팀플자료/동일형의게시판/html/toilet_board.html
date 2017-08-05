<?php
	include "connect.php";
	$t_no = $_GET["toilet_no"];

	$q= "SELECT review_no,nickname,wdate,thumb,content,rating,rcmd,review.numof_comment FROM review JOIN member WHERE toilet_no = $t_no and member.member_no = review.member_no ORDER BY wdate DESC";
	$res = mysql_query($q);
?>

<!DOCUMENT html>
<html>
<head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no" />
	<title>쾌변 고!</title>
	<link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
	<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
	<link rel="stylesheet" type="text/css" href="css/slide-menu.css" />
	<link rel="stylesheet" type="text/css" href="css/default.css" />
	<link rel="stylesheet" type="text/css" href="css/home.css" />
	<style>
		button {
			background-color: none;
		}
		#cont {
			width: 98%;
			max-width: 520px;
			margin-left: auto;
			margin-right: auto;
		}
		#cont img{
			width: 98%;
			margin-left: auto;
			margin-right: auto;
		}
	</style>
</head>
<body>
	<div id="header" class="reveal-header">
		<a href="home.html"><img id="logo" src="img/로고.png" /></a>
	</div>
	<div id="search-wrap">
		<form method="post" action="result.php">
			<input type="search" name="addr" required="required"/>
			<input type="image" src="img/search.png" width= "40" height="40" />
			<img src="img/gps.png" id="gps" width="40" height="40" name="coord"  title="내 위치로 찾기"/>
		</form>
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
	
	<div class="row">
		<div class="col-xs-4"></div>
		<div class="col-xs-4"><a href=<?php echo '"'.'create_review.php?part=3&toilet_no='.$t_no.'"' ?>>리뷰쓰기</a></div>
		<div class="col-xs-4"></div>
	</div>

	<div id="cont">
		<?php
			while($row=mysql_fetch_array($res)) {
				$image = $row['thumb'];
				if(strlen($image)<3){
					$image = "default_thumb.jpg";
				}
				$gdate = $row['wdate'];
				$date = substr($gdate,0,4)."년".substr($gdate,5,2)."월".substr($gdate,8,2)."일 ".substr($gdate,11,2).':'.substr($gdate,14,2).':'.substr($gdate, 17,2);

				$cont;
				if (strlen($row['content'])>130) {
					$cont = mb_substr($row['content'],0,60,"UTF-8")."......";
				}
				else{
					$cont = $row['content'];
				}

				echo '<div id="one">';
				echo '<div class="row"><div class="col-xs-6">'.$row['nickname'].'</div>';
				echo '<div class ="col-xs-6">'.$date.'</div></div>';
				echo '<div class="row"><div class ="col-xs-6"><img src="'.$image.'" /></div>';
				echo '<a href="post.php?review_no='.$row['review_no'].'"><div class ="col-xs-6">'.$cont.'</div></a></div>';
				echo '<div class="row"><div class="col-xs-6">평점:'.$row['rating'].'</div>';
				echo '<div class ="col-xs-3">추천: '.$row['rcmd'].'</div>';
				echo '<a href="post.php?review_no='.$row['review_no'].'"><div class ="col-xs-3">댓글: '.$row['numof_comment'].'</div></a></div>';
				echo '</div>';
			}
		?>	
	</div>


	<footer>
		<p>&copy; 급하니</p>
	</footer>
	<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
	<script src="js/slide-menu.js"></script>
	<script type="text/javascript" language="javascript" src="js/gps.js"></script> <!-- 첫 시작화면에서만 쓰는 geolocation api 가능 여부 알려주는 함수들 모음 -->
</body>
</html>
