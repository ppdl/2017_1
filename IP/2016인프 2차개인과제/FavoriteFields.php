<?php session_start() ?>
<?php
//만약 로그인이 되어있지 않으면, 바로 경고를 보내고 로그인 창으로 보냅니다.
if(!isset($_SESSION["id"])){
echo "<script>alert(\"You are not in login status!! Please Login!!\");</script>";
echo "<meta http-equiv='refresh' content = '0; url=http://165.132.122.160/~u2013147561/login.php'>";
exit;
}
if($_SESSION['id'] != "") echo $_SESSION['id']."님 ".$_SESSION['visit_cnt']."회 째 방문을 환영합니다. ";
else echo "로그인 상태가 아닙니다. 사이트하단에 로그인 버튼을 이용해주세요.";
?>
<html lang="en">
	<head>
		<meta charset = "utf-8">
		<title>My favorite Fields.(Additional)</title>
		<style type = "text/css">

			body
			{
				font-family: "Ubuntu";
				font-size: 12px;
				text-shadow: 1px 1px 1px DimGrey;
			}
			<!--구글 웹 폰트를 다운받아서 하였습니다!-->
			
			p
			{ margin:0.9em 0em; }
			.multi_columns
			{
				/* setting the number of columns to 2 */
				-webkit-column-count: 2; 
				-moz-column-count: 2; 
				-o-column-count: 2;
				column-count: 2;
				/* setting the space between columns to 30px */
				-webkit-column-gap: 30px;
				-moz-column-gap: 30px; 
				-o-column-gap: 30px; 
				column-gap: 30px;
				/* adding a 1px black line between each column */
				-webkit-column-rule: 1px outset black; 
				-moz-column-rule: 1px outset black; 
				-o-column-rule: 1px outset black; 
				column-rule: 1px outset black;
			}
			<!--2중컬럼을 선언한 것입니다. 교과서의 소스코드를 이용하였습니다.-->
			
			img
			{
				position: relative;
				-webkit-animation: movingImage linear 10s 1s 2 alternate;
				-moz-animation: movingImage linear 10s 1s 2 alternate;
				animation: movingImage linear 10s 1s 2 alternate;
			}
			@-webkit-keyframes movingImage
			{
				0%	{opacity: 0; left: 50px; top: 0px;}
				25%	{opacity: 1; left: 0px; top: 50px;}
				50%	{opacity: 0; left: 50px; top: 100px;}
				75%	{opacity: 1; left: 100px; top: 50px;}
				100%{opacity: 0; left: 50px; top: 0px;}
			}
			@-moz-keyframes movingImage
			{
				0%	{opacity: 0; left: 50px; top: 0px;}
				25%	{opacity: 1; left: 0px; top: 50px;}
				50%	{opacity: 0; left: 50px; top: 100px;}
				75%	{opacity: 1; left: 100px; top: 50px;}
				100%{opacity: 0; left: 50px; top: 0px;}
			}
			@keyframes movingImage
			{
				0%	{opacity: 0; left: 50px; top: 0px;}
				25%	{opacity: 1; left: 0px; top: 50px;}
				50%	{opacity: 0; left: 50px; top: 100px;}
				75%	{opacity: 1; left: 100px; top: 50px;}
				100%{opacity: 0; left: 50px; top: 0px;}
			}
			<!-- 네 블럭은 animation속성을 위한 것입니다. 교재의 소스코드를 이용하였습니다.-->
			
		</style>
		<link href='https://fonts.googleapis.com/css?family=Ubuntu' rel='stylesheet' type='text/css'>
		
		
	</head>
	
	<body>
	
		<header>
			<h1>My favorite Fields.</h1>
		</header>
		<!--이 문서의 논리적 구조를 위하여 footer를 사용했습니다. -->
		
		<div class = "multi_columns">
			<p>제 전공은 컴퓨터과학입니다. 제가 전역을 한 후, 특히나 관심있는 분야는 자율주행차, 무인차 분야입니다. 요즘은 
			사물인터넷(IoT: Internet of Things) 시대입니다. 사물 간 네트워크 연결로 정보를 주고받는 사물인터넷은 
			그동안 스마트홈이나 헬스케어 분야에서 두각을 나타냈는데요. 최근에는 자동차 업계에서도 이에 관한 기술 개발에 박차를 가하고 있습니다.
			자동차의 사물인터넷이 가질 수 있는 궁극의 목표는 자율주행입니다. 그리고 자율주행을 가능하게 하는 것이 
			‘커넥티드(Connected)’ 기술입니다. 이때, 커넥티드 카의 핵심요소는 '차량네트워크' 및 '클라우드'입니다.
			특히, 클라우드 구축과 함께 수집된 데이터를 고도의 연산을 통해 분석해 실시간으로 지능화된 서비스를 내려줄 수 있는 데이터
			분석기술이 중요할 것 같습니다.</p>
			<p>
			‘완벽한 자율주행’이란 주변 자동차, 도로 등 인프라를 포함한 사물과의 정보교환(V2X, Vehicle to Everything)을 
			통해 안전한 자율주행 환경을 제공하는 것을 말합니다. 앞서 살펴본 커넥티드카가 완벽히 구현된 것을 말합니다. 
			‘스마트 트래픽(Smart Traffic)’ 역시 같은 맥락으로, 차량의 위치와 교통 상황, 다른 차량의 목적지 등을 분석해 
			최적화된 이동구간을 안내하는 것을 말합니다. 시간, 에너지 손실, 환경 오염 등 사회적 비용을 줄일 수 있습니다. 
			</p> 
			<p>
			‘모빌리티 허브(Mobility Hub)’는 자동차가 곧 달리는 고성능 컴퓨터로, 모든 사물과의 연결 주체가 되는 것을 의미합니다.
			자동차가 단순히 이동수단이 아닌 움직이는 생활공간이 되는 것입니다. 현재, 스마트폰의 애플리케이션을 차의 모니터를 통해 실행하고 조작하는 것에서 나아가 스마트폰의 기능을 자동차로
			가져오고자 합니다. 또한, 자동차 내부에서 집에 있는 IT, 가전 기기들을 원격 제어할 수 있게 됩니다. 
			</p> 
			<p>제 취미가 자동차인 만큼 제가 컴퓨터과학을 전공하면서 배우는 IT가 이러한 분야와 합쳐지는게 굉장히 흥미롭습니다.
			최근, 엘론 머스크 CEO가 "테슬라 모델3"이라는 자동차를 출시했는데요, 이는 아주 특별한 자동차 입니다.
			<a href = "https://www.teslamotors.com/">이 링크</a>에서 확인할 수 있듯이(데스크톱 및 랩톱 환경에서 동영상이 지원됩니다.)
			자동차가 점점 가전 내지는 디바이스 레벨이 되어가는 모습을 보여주게 됩니다.
			</p>
		</div>
		<!--다중 컬럼디자인을 적용하였습니다.-->
		
		<p>(쉬어가는 사진) 다음 사진은 원주 구룡사에서 찍은 하늘입니다.</p>
		<p>
			<img src = "background_2.JPG" width = "300" height = "200" alt = "sky">
		</p>
		<!--animation 이미지소스 사용하였습니다.-->
		
		<footer>
			<em>my Email : chihun206@naver.com / phoneNum : +82 10 6709 5679</em>
		
			
		</footer>
		<!--페이지의 논리적 구조를 위해 footer를 사용하였습니다.-->
		
	</body>
</html>
