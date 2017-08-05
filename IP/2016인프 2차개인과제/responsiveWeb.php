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
<html>
	<head>
		<meta charset = "utf-8">
		<title>Responsive Web Technology</title>
		<link rel = "stylesheet" type="text/css" href="otherStyle.css">
		<style type = "text/css">
			body {margin:0;}
			ul.topnav {
			list-style-type: none;
			margin: 0;
			padding: 0;
			overflow: hidden;
			background-color: #333;
			}

			ul.topnav li {float: left;}

			ul.topnav li a {
			display: inline-block;
			color: #f2f2f2;
			text-align: center;
			padding: 14px 16px;
			text-decoration: none;
			transition: 0.3s;
			font-size: 17px;
			}

			ul.topnav li a:hover {background-color: #111;}

			ul.topnav li.icon {display: none;}

			@media screen and (max-width:800px) {
			ul.topnav li:not(:first-child) {display: none;}
			ul.topnav li.icon {
				float: right;
				display: inline-block;
				}
			}

			@media screen and (max-width:800px) {
			ul.topnav.responsive {position: relative;}
			ul.topnav.responsive li.icon {
			position: absolute;
			right: 0;
			top: 0;
			}
			ul.topnav.responsive li {
				float: none;
				display: inline;
			}
			ul.topnav.responsive li a {
				display: block;
				text-align: left;
				}
			}
			<!--반응형 웹의 기능입니다. -->
			<!--http://www.w3schools.com/html/tryit.asp?filename=tryrwd_simple-->
			<!--다음 링크에서 가져왔습니다.-->
			img
			{
				margin : 10px;
				-webkit-transition: -webkit-transform 4s;
				-moz-transition: -moz-transform 4s;
				-o-transition: -o-transform 4s;
				transition: transform 4s;
			}
			img:hover
			{
				-webkit-transform: rotate(360deg) scale(2, 2);
				-moz-transform: rotate(360deg) scale(2, 2);
				-o-transform: rotate(360deg) scale(2, 2);
				transform: rotate(360deg) scale(2, 2);
			}
			<!--image transform을 이용하였습니다.-->

		</style>
	</head>
	<body>
		<ul class="topnav">
			<li><a class="active" href="index.php">Home</a></li>
			<li><a href="responsiveWeb.php">Responsive Web</a></li>
			<li><a href="serviceWorker.php">Service Workder</a></li>
			<li><a href="Manifest_Format.php">Manifest_Format</a></li>
			<li><a href="LOD.php">Linked Open Data</a></li>
			<li><a href="FavoriteFields.php">Favorites</a></li>
			<li><a href="table.php">Lecture</a></li>
			<li class="icon">
				<a href="javascript:void(0);" style="font-size:15px;" onclick="myFunction()">☰</a>
			</li>
		</ul>

		<script>
			function myFunction() {
				document.getElementsByClassName("topnav")[0].classList.toggle("responsive");
			}
		</script>
		<h1>What is Responsive Web Technology?</h1>
		
		<h2>Intro</h2>
		<p>Responsive Web technology is technology that is able to response to
		any devices according to size of display.<br>
		In former days, internet homepage was only with desktop access; 
		These days, smartphones, laptops, tablet, smartphone, not only with various mobile devices,
		access to the Internet. Display type and size in each Web technology 
		is needed because of different reaction!<br>
		PC에서는 잘 보이던 홈페이지가 모바일이나 태블릿을 접속했을 때 
		화면이 잘 보이지 않거나 깨져 보이는 경험을 해본 적이 있으십니까? 
		이러한 불편함을 없애주는 역할을 하는 것이 바로 '반응형 홈페이지'입니다.
		반응형 기술로 제작된 홈페이지는 언제 어디서는 다양한 모바일 기기로 웹사이트에 접속했을 때 
		자동적으로 웹사이트의 크기를 적절한 사이즈로 맞춰주기 때문에 홈페이지에 방문한 사용자들이 보기 수월하고 편리합니다.
		</p>
		
		<section id ="1">
			<h2>장점과 단점</h2>
			<article>
				<p>반응형 웹의 장점으로는, HTML 소스가 하나이므로, 컨텐츠가 어디서나 일치하고, 웹페이지당 하나의 URL만 관리하면 되는
				"SEO Optimization"가 있습니다. 또한, 어떠한 모바일 기기로 웹사이트에 접속해도 그 화면에 맞는 해상도로 전환되어,
				각 사이즈 표준에 맞추어 제작하는 수고를 덜 수도 있습니다. 동일한 디자인 컨셉으로 각각의 디바이스에 자연스럽게 어울려 디자인 통일성이
				좋다는 점도 장점으로 꼽힙니다. 또한 URL이 하나이므로, 검색과 노출에 유리하다는 장점도 갖습니다.<br>
				하지만, 반응형 웹으로 홈페이지를 제작하면 비용이 조금 더 올라가게 되고, 데스크탑용 화면 전체가 전송된다는 점에서,
				성능 이슈의 단점을 꼽을 수 있습니다. 하지만, 비용 대비 훨씬 효과적인 홈페이지 기술이므로, 최근 "웹 트렌드"로 선정되어,
				이에 맞춘 홈페이지를 만드는 추세입니다.
				</p>
		
				<h2>기본 개념</h2>
				<p>이 기술의 간단한 개념 및 방법은 다음과 같습니다. 첫 번째로, 웹 문서의 가변폭을 설정합니다.<br>
				<figure>
					<img src = "Max_Min.png" alt = "Maximum, minimum"/>
					<figcaption>
						<em>You should think about size of display.</em>
					</figcaption>
				</figure><br>
				<p>
				그 가변폭의 최대/최소값을 설정하며, 이번에는 미디어 쿼리를 설정해주어야 합니다. CSS3 미디어 쿼리는 화면 크기에 따라서
				각기 다른 CSS를 적용할 수 있는 어떤 경우를 제공합니다.
				</p>
				<figure>
					<img src = "MediaQuery.png" alt = "MediaQuery"/>
					<figcaption>
						<em>Media query; you can display various size in various devices.</em>
					</figcaption>
				</figure><br>
				<p>
				이번에는 모바일 뷰 포트를 설정해주어야 합니다.
				스마트폰 기기는 테블릿이나 데스크톱과 달리 독자적인 뷰 포트 처리 방식을 가지고 있습니다.
				테블릿과 데스크톱의 뷰 포트는 웹 문서의 너비와 무관하게 화면에 보이는 영역이 뷰 포트가 되고,
				데스크톱은 웹 브라우저의 창 크기를 조절함으로써 사용자가 뷰 포트의 크기를 직접 제어할 수도 있게 됩니다.
				한편 스마트폰의 경우 단말의 스크린 사이즈와 무관하게 웹 문서의 너비와 높이가 뷰 포트가 되고
				스마트폰 스크린에 웹 문서(뷰 포트)를 모두 출력하기 위해 스크린 사이즈보다 큰 문서는 자동으로 줌 아웃 처리를 합니다. 
				다시 말하면 뷰 포트를 스크린 크기에 맞게 강제로 축소하는 것입니다. 결과적으로 데스크톱에 대응하도록 만들어진 문서를
				스마트폰으로 열어 보면 통상 3~4배 이상 줌 아웃 되어 글씨를 알아 볼 수 없는 형태로 작게 표시합니다.
				</p>
				<figure>
					<img src = "safarinotthesame.jpg" alt = "Doesn't coincide between Desktop and smartphone."/>
					<figcaption>
						<em>Doesn't coincide between Desktop and smartphone.</em>
					</figcaption>
				</figure><br>
			</article>
		</section>
		
		<footer>
			<h2>맺음말</h2>
			<p>이러한 방법으로, 우리는 반응성 웹을 이용하여, User friendly한 웹을 만들 수 있습니다.</p>
			<p>조금 더 자세한 정보는 다음 링크를 참조하세요.</p>
			<ul>
				<li><a href = "http://readme.skplanet.com/?p=9739">SK-planet blog</a></li>
				<li><a href = "http://naradesign.net/wp/2012/05/30/1823/">Basic concept of media query</a></li>
				<li><a href = "http://blog.froont.com/9-basic-principles-of-responsive-web-design/">
						9 basic priciples of responsive web design.</a></li>
			</ul>
		
		</footer>
	</body>
</html>