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
		<title>Manifest Format</title>
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
			div
			{
				border-width: 10px;
				width: 60px;
				padding: 20px 20px;
			}
			<!--div에 속성을 따로 부여하였습니다-->
			
			
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
		
		
		<header>
			<h1>What is Manifest Format?</h1>
			<h2>Intro</h2>
			<p>This specification defines a JSON-based manifest file that provides developers with a centralized
			place to put metadata associated with a web application. This metadata includes, but is not limited
			to, the web application's name, links to icons, as well as the preferred URL to open when a user 
			launches the web application. The manifest also allows developers to declare a default orientation
			for their web application, as well as providing the ability to set the display mode for the 
			application (e.g., in fullscreen). Additionally, the manifest allows a developer to "scope" a web 
			application to a URL. This restricts the URLs to which the manifest is applied and provides a means 
			to "deep link" into a web application from other applications. Using this metadata, user agents
			can provide developers with means to create user experiences that are more comparable to that of
			a native application. To associate documents of a web application with a manifest, 
			this specification defines the manifest link type as a declarative means for a document to
			be associated with a manifest.
			</p>
		</header>
		
		<section id = "1">
			<h2>Basic Concept</h2>
			<article>
				<p>To obtain a manifest, the user agent must run the steps for obtaining a manifest.
				The appropriate time to obtain the manifest is left up to implementations. A user agent may opt
				to delay fetching a manifest until after the document and its other resources have been
				fully loaded (i.e., to not delay the availability of content and scripts required by the
				document). A manifest is obtained and applied regardless of the media attribute of the link 
				element matches the environment or not.
				</p>
				
				<p>The steps for obtaining a manifest are given by the following algorithm. The algorithm,
				if successful, returns a processed manifest and the manifest URL; otherwise, it terminates 
				prematurely and returns nothing. In the case of nothing being returned, the user agent must
				ignore the manifest declaration. In running these steps, a user agent must not delay the load
				event.
				</p>
				<ol>
					<li>From the Document of the top-level browsing context, let manifest link be the first link element in tree order whose rel attribute contains the token manifest.</li>
					<li>If manifest link is null, terminate this algorithm.</li>
					<li>If manifest link's href attribute's value is the empty string, then abort these steps.</li>
					<li>Let manifest URL be the result of parsing the value of the href attribute, relative to the element's base URL. If parsing fails, then abort these steps.</li>
					<li>Let request be a new [FETCH] request, whose URL is manifest URL, and whose context is "manifest".</li>
					<li>If the manifest link's crossOrigin attribute's value is 'use-credentials', then set request's credentials to 'include'.</li>
					<li>Await the result of performing a fetch with request, letting response be the result.</li>
					<li>If response is a network error, terminate this algorithm.</li>
					<li>Let manifest be the result of running the steps for processing a manifest with response's body as the text, manifest URL, and the URL that represents the address of the top-level browsing context.</li>
					<li>Return manifest and manifest URL.</li>
				</ol>
				
				<p>NOTE that,
					Authors are encouraged to use the HTTP cache directives to explicitly cache the manifest.
					For example, the following response would cause a cached manifest to be used 30 days
					from the time the response is sent:

					HTTP/1.1 200 OK
					Cache-Control: max-age=2592000
					Content-Type: application/manifest+json
				</p>
				<figure>
					<img src = "Manifest_1.PNG" width = "350" height = "350" alt = "Manifest">
					<figcaption>
						<em>example code(Resource : Link below...)</em>
					</figcaption>
				</figure>
				<h2>Basic diagram is here.</h2>
				<figure>
					<img src = "Manifest_2.PNG" width = "600" height = "600" alt = "Basic concept" >
					<figcaption>
						<em>Manifest Format basic diagram(Resource : Link below...)</em>
					</figcaption>
				</figure>
			</article>
		</section>
		
		<footer>
			<h2>Epilogue</h2>
			<p>&lt;요약하자면, Manifest format은 다음과 같습니다.&gt;</p><!--special character를 사용하였습니다. -->
			<ul>
				<li>Web App의 인스톨 정보 제공</li>
				<li>Name, Icon, Start URL, Orientation 등</li>
				<li>홈스크린 설치, 태스크 관리자 통합 가능</li>
				<li>Service Worker 오프라인 기능과 함께 Native와 같은 사용자 경험 제공</li>
			</ul>
			
				<p>If you want to know about this technology, click the link below</p>
				<p><a href = "https://www.w3.org/TR/appmanifest/">More details....</a></p>
		</footer>
	</body>
</html>