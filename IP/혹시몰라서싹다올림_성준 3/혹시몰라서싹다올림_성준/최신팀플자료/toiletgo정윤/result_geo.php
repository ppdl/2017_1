<!DOCUMENT html>
<html>
<head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no" />
	<title>검색결과</title>
	<link rel="stylesheet" type="text/css" href="css/slide-menu.css" />
	<link rel="stylesheet" type="text/css" href="css/default.css" />
	<style>
		article {
			padding-left: 20px;
			padding-bottom: 20px;
		}
	</style>
</head>
<body>
	<div id="header" class="reveal-header">
		<a href="index.html"><img id="logo" src="img/로고.png" /></a>
	</div>
	<div id="search-wrap">
		<form method="post" action="result.php">
			<input type="search" id="search" name="addr" required/>
			<input type="image" id="submit" src="img/search.png" width= "40" height="40" name="coord"  />
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
	<section class="result">
		<div id="map" style="width: 100%; max-width: 900px;height:50%;"></div>
		<!--<article>
			<p>검색결과: 연세대학교 제 1공학관</p>
			<p> 평점: </p>
			<a href="result_detail.html">상세페이지</a>
		</article>-->
	</section>
	<footer>
		<p>&copy; 급하니<span id="test"></span></p>
	</footer>
	<?php ?>
	<script type="text/javascript" language="javascript" src="js/jquery-1.11.0.min.js"></script>
	<script type="text/javascript" language="javascript" src="js/slide-menu.js"></script>
	<script type="text/javascript" src="//apis.daum.net/maps/maps3.js?apikey=d879aa969a5178ca44654675cdb43d21&libraries=services"></script>
	<script type="text/javascript" language="javascript" src="js/result.js"></script>
	<script type="text/javascript" language="javascript">
		
		if(navigator.geolocation) {
			navigator.geolocation.getCurrentPosition(success, fail); // success 함수와 fail 함수는 result.js 파일에 들어있다.
		} else {
			document.getElementById('map').textContent = "지원X";
		}
		
		var map = document.getElementById('map').firstChild;
		document.getElementById('test').textContent = 'dd';//map.getCenter().latitude;
	</script>
</body>
</html>