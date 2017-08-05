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
		<title>내 사이트의 특장점/비교</title>
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
			
			
			.flexbox 
			{
				width: 1100px;
				height: 600px;
				display: -webkit-box;
				display: box;
				-webkit-box-orient: horizontal;
				box-orient: horizontal;
			}
			.flexbox > div 
			{
				-webkit-transition: 1s ease-out;
				transition: 1s ease-out;
				-webkit-border-radius: 10px;
				border-radius: 10px;
				border: 2px solid black;
				width: 250px;
				margin: 10px -10px 10px 0px;	
				padding: 20px 20px 20px 20px;	
				box-shadow: 10px 10px 10px dimgrey;
			}
			.flexbox > div:nth-child(1){ background-color: lightgrey; }
			.flexbox > div:nth-child(2){ background-color: lightgrey; }
			.flexbox > div:nth-child(3){ background-color: lightgrey; }
			.flexbox > div:nth-child(4){ background-color: lightgrey; }
			.flexbox > div:hover { width: 200px; color: white; font-weight: bold; }
			.flexbox > div:nth-child(1):hover { background-color: royalblue; }
			.flexbox > div:nth-child(2):hover { background-color: white; }
			.flexbox > div:nth-child(3):hover { background-color: royalblue; }
			.flexbox > div:nth-child(4):hover { background-color: white; }
			<!-- 위의 세 블락은, flexbox를 위한 부분입니다. 교재의 소스코드를 이용하였습니다.-->
			
			p	{overflow: hidden; font-family: tahoma, helvetica, sans-serif;	 font-size: 12pt; color: gray;}
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
		<!--반응형 웹의 기능입니다. -->
		<!--http://www.w3schools.com/html/tryit.asp?filename=tryrwd_simple-->
		<!--다음 링크에서 가져왔습니다.-->
		
		
		<h1>Why my web page is strong than other's?</h1>
		<p>In my web page, there is abbreviated data. In general, many websites just write
		their web pages information. But I don't want to that. So, I make "Summary" and use "detail"
		element.</p>
		
		<h2>이 웹페이지에 대한 장점(다른 사이트와 비교했을 시) 및 정리.</h2>
		<div class = "flexbox"><!--flexbox를 사용한 부분입니다. div에서 class를 적용했습니다.-->
			<div>
				<p>이 웹페이지는 우선적으로 굉장히 눈에 잘 들어오는 색깔과 글씨체로 구성하였습니다. Paragraph의 내용, 즉, 우리가 주로 읽는 주제별 내용들의
				글씨 색은 주로 눈이 편안하게 강렬하지 않은 무채색 계열 중, 회색을 골랐습니다. 이는 페이지의 배경색인 dimm gray색보다 조금 더 두드러지는 정도이며,
				웹 사이트의 구성을 굉장히 간결하게 해주는 효과를 누리게 해줍니다.
				</p>
			</div>
			<div>
				<p>제 프로젝트의 index.html 페이지에 가시면, 지도를 삽입하였습니다. 저를 어떻게 표현할까 하다가, 제가 주로 있는 위치조차도 지도서비스를 이용하여
				표현하였습니다. 이를 토대로, 굳이 네이버지도에서 제 위치를 찾지 않으셔도, 바로 알 수 있게 해놓았습니다.(프로젝트 표준에 주신 pdf파일 하단부 링크를
				사용하여 찾아보니, iframe속성은 대신 사용할 수 없다고 나와있어서 이미지 속성을 사용하였습니다. 이는 표준에 어긋나지 않습니다.)
				</p>
			</div>
			<div>
				<p>저는 또한, 다른 웹페이지들에서 흔히 찾아볼 수 없었던(물론 어떤 웹사이트에는 있지만), details 속성을 이용하여 표현하고자 하는 정보의 제목만
				나타내며, 간단한 소개 및, 링크로 연결해주는 부분을 숨겼습니다. 이를 통해, 이 웹페이지를 찾는 방문자가 조금 더 재미있게, 이 웹사이트를 이용하도록
				하였습니다.
				</p>
			</div>
			<div>
				<p>그리고 매 웹페이지마다 맺음 말(내지는 Epilogue)을 넣어서, 자세한 사항에 대한 링크가 연결되도록 도움을 주었으며,
				이 또한 하단에 넣었습니다. 또한 이 웹페이지의 소스코드는, 타 웹페이지와 다르게, 소스코드가 굉장히 간결하게 정리되어있습니다.
				이를 통해, 다른 사람들이 이 웹 사이트를 기반으로 쉽게 자신의 웹사이트를 꾸미도록 이식성을 제공했다는 점에서도 이 웹사이트가
				다른 사이트보다 조금 더 장점을 가진다고 하겠습니다.
				</p>
			</div>
		</div>
		
	</body>
</html>