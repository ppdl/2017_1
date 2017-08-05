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
		<a href="home.html"><img id="logo" src="img/로고.png" /></a>
	</div>
	<div id="search-wrap">
		<form method="post" action="result.php">
			<input type="search" name="addr" required/>
			<input type="image" src="img/search.png" width= "40" height="40" name="coord"  />
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
		<div id="map" style="width: 100%; max-width: 900px; height: 50%;"></div>
		<!--<article>
			<p>검색결과: 연세대학교 제 1공학관</p>
			<p> 평점: </p>
			<a href="result_detail.html">상세페이지</a>
		</article>-->
	</section>
	<footer>
		<p>&copy; 급하니<span id="test"></span></p>
	</footer>
	<script type="text/javascript" language="javascript" src="js/jquery-1.11.0.min.js"></script>
	<script type="text/javascript" language="javascript" src="js/slide-menu.js"></script>
	<script type="text/javascript" src="//apis.daum.net/maps/maps3.js?apikey=d879aa969a5178ca44654675cdb43d21&libraries=services"></script>
	<script type="text/javascript" language="javascript" src="js/result.js"></script>
	<script type="text/javascript" language="javascript">
		var addr = '<?php echo $_POST["addr"]; ?>'; // 맞는 코드(addr에 목적지 전달됨)
		// 주소-좌표 변환 객체를 생성합니다 - 다음의 라이브러리 사용
		var geocoder = new daum.maps.services.Geocoder();

		geocoder.addr2coord(addr, function(status, result) {
			var coords=null;
			// 정상적으로 검색이 완료됐으면
			if (status === daum.maps.services.Status.OK) {
				coords = new daum.maps.LatLng(result.addr[0].lat, result.addr[0].lng);
				makeMap(coords); // result.js 파일에 들어있는 함수
			} else { // 없으면 keywordSearch - 다음 라이브러리 사용
				var places = new daum.maps.services.Places();

				var callback = function(status, result) {
					if (status === daum.maps.services.Status.OK) {
						coords = new daum.maps.LatLng(result.places[0].latitude, result.places[0].longitude);
						makeMap(coords); // 이 함수는 result.js 파일에 들어있다.
					} else {
						document.getElementById('map').textContent = "찾을 수 없습니다.";
					}
				};
				places.keywordSearch(addr, callback);
			}
		});
	</script>
</body>
</html>