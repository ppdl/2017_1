<?php
	include "connect.php";
	$no = $_GET["review_no"];

	$q = "SELECT nickname,wdate,content,rcmd,image,toilet_name,review.numof_comment,review.rating,building_name FROM review JOIN member,toilet,building WHERE review_no = $no and review.member_no = member.member_no and review.toilet_no = toilet.toilet_no and toilet.building_no = building.building_no LIMIT 1";

	$res = mysql_query($q);
	$row = mysql_fetch_array($res);
	$gdate = $row['wdate'];
	$date = substr($gdate,0,4)."년".substr($gdate,5,2)."월".substr($gdate,8,2)."일 ".substr($gdate,11,2).':'.substr($gdate,14,2).':'.substr($gdate, 17,2);
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
	<style type="text/css">
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


	<div id="cont">
		<?php 
			$image = $row['image'];
			if(strlen($image)<3){
				$image = "default_thumb.jpg";
			}

			echo '<div class="row"> <div class="col-xs-6"> '.$row['nickname'].'</div>';
			echo '<div class="col-xs-6">'.$date.'</div> </div> <div class="row">';
			echo '<div class="col-xs-6"> <a href="'.$image.'" ><img src="'.$image.'"> </a> </div>';
			echo '<div class="col-xs-6">'.$row['building_name'].'</div>';
			echo '<div class="col-xs-6">'.$row['toilet_name'].'</div>';
			echo '<div class="col-xs-6">평점: '.$row['rating'].'</div></div>';
			echo '<div class="row"><div class="col-xs-12">'.$row['content'].'</div></div>';
			echo '<div class="row"><div class="col-xs-6"></div>';
			//추천 버튼 만들기 

			echo '<div class="col-xs-3">추천:  '.$row['rcmd'].'</div>';
			echo '<div class="col-xs-3">댓글: '.$row['numof_comment'].'</div></div>';

			//댓글 입력란
			echo '<div class="row"><form action="comment_create.php" method="post">';
			echo '<div style="display: none"><input type="number" name="review_no" value="'.$no.'" /> <input type="text" name="sub" value="ok" /> </div>';
			echo '<div class="col-xs-8"><input type="text" name="cmt" required style="width: 95%" /> </div>';
			echo '<div class="col-xs-4"> <input type="submit" value="댓글쓰기" /></form> </div></div>';
			

			$q2="SELECT content,comment.wdate,nickname FROM comment JOIN member WHERE review_no = $no and comment.member_no = member.member_no LIMIT ".$row["numof_comment"];
			$res2=mysql_query($q2);
			while($row2 = mysql_fetch_array($res2)) {

				$gdate2 = $row2['wdate'];
				$date2 = substr($gdate2,0,4)."년".substr($gdate2,5,2)."월".substr($gdate2,8,2)."일 ".substr($gdate2,11,2).':'.substr($gdate2,14,2).':'.substr($gdate2, 17,2);
				echo '<div class="row"><div class="col-xs-12"> '.$row2['content'].'</div>';
				echo '<div class="col-xs-6"> '.$row2['nickname'].'</div>';
				echo '<div class="col-xs-6"> '.$date2.'</div></div>';
			}
		?>

	</div>


	<footer>
		<p>&copy; 급하니</p>
	</footer>
	<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
	<script src="js/slide-menu.js"></script>

</body>
</html>

<?
		
?>