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
		<title>Service Worker</title>
		<link rel = "stylesheet" type="text/css" href="otherStyle.css">
		<style type = "text/css">
		
			div.background
			{
				background-image: url(sakura.PNG), url(WallPaper.jpg);
				background-position: bottom right, 5% center;
				background-origin: border-box; content-box;
				background-repeat: no-repeat; repeat;	
			}
			<!--multiple background를 설정하였습니다.-->
			div.content
			{
				padding: 20px 20px;
				border-width: 10px;
				color: white;
				font-size:150%;
			}
			#repeat
			{
				-webkit-border-image:url(background_1.JPG) 34% 34% repeat;
				-moz-border-image:url(background_1.JPG) 34% 34% repeat;
				-o-border-image:url(background_1.JPG) 34% 34% repeat;
				border-image:url(background_1.JPG) 34% 34% repeat;
			}
			<!--image border속성을 사용하셨습니다. 교재의 코드를 이용하였습니다.-->
			
		</style>
	</head>
	
	<body>
	
		<header>
			<h1>What is Service Worker?; Service Worker API</h1>
			<div id ="repeat"><h2>Intro</h2></div><!--image border속성을 이용하였습니다. 교재의 코드를 이용하였습니다.-->
			<p>ervice workers essentially act as proxy servers that sit between web applications,
			and the browser and network (when available). They are intended to (amongst other things)
			enable the creation of effective offline experiences, intercepting network requests and 
			taking appropriate action based on whether the network is available and updated assets
			reside on the server. They will also allow access to push notifications and background sync APIs.<br>
			A service worker is run in a worker context: it therefore has no DOM access, 
			and runs on a different thread to the main JavaScript that powers your app, so it is not blocking.
			It is designed to be fully async; as a consequence, APIs such as synchronous XHR and localStorage 
			can't be used inside a service worker. Service workers only run over HTTPS, for security reasons. 
			Having modified network requests wide open to man in the middle attacks would be really bad.<br>
			한마디로 요약하면, 웹 페이지와 독립적으로 오프라인/시스템 기능을 제공하는 이벤트 기반 Worker입니다. Service Worker는 1차적으로 오프라인
			의 문제를 해결하기 위한 시작점입니다. 물론, Service Worker가 커버하는 범위는 이보다 더 넓지만, Native Application의 동작흐름을 
			웹으로 가져오기 위한 가장 중요한 기능이라고 하겠습니다.
			</p>
		</header>
		
		<section id="1">
			<div class="background"><!--multi-background의 속성입니다.-->
			<div class="content">
				<h2>Basic Concept; Logic Based Offline Resource Management.</h2>
				<p>Application Cache의 경우 캐싱 처리를 정적인 분기 로직을 기반으로 동작시켜야 했으며, 
				대체적으로 개발자가 원하던 방식보다는 브라우저의 정책에 따라 리소스가 관리되는 문제가 존재하였습니다. 
				대표적인 문제점들은 다음과 같이 Application Cache is a douchebag에서 지적된 내용들입니다.
				</p>
				<ol>
					<li>온라인에 있을 때에도 파일들이 언제나 어플리케이션 캐시로부터 로딩된다.</li>
					<li>캐시된 데이터는 Manifest자체가 변경될 때만 업데이트 된다.</li>
					<li>어플리케이션 캐시는 선택 불가능한 추가적인 캐시(동작)이다.</li>
					<li>이 후의 Manifest를 캐시하지 않는다.</li>
					<li>캐싱되지 않는 리소스는 캐시된 페이지에서 로딩되지 않는다.</li>
				</ol>
				<p>서비스 워커는 이를 해결하기 위해 프로그램 가능(Programmable)한 오프라인 리소스의 근본적인 처리 방법을 제시합니다.
				브라우저에서 일어나는 요청(Request)들을 조건에 따른 콜백을 통해 직접 응답(Custom response)할 수 있는 기능을 제공하여
				직접 리소스를 관리할 수 있습니다. 따라서 캐시 로직은 직접 작성이 가능하며 언제든지 업데이트할 수 있습니다.
				</p>
				<figure>
					<img src = "serviceworker_cache_flow.png" alt = "service worker" width = "640" height = "300"/>
					<figcaption>
						<em>Basic diagram of Service Worker.</em>
					</figcaption>
				</figure>
			</div></div>
		</section>
		
		<footer>
			<h2>Epilogue</h2>
			<p>서비스 워커는 웹 어플리케이션의 근본적인 한계를 탈출하기 위한 내용을 담고 있습니다. 반대로 보자면 웹 어플리케이션 개발자 관점에서는
			다소 익숙하지 않은 형태의 많은 개발 형태를 예고하고 있습니다. 특히 서비스 워커는 시각적인 기능을 가지고 있지는 않습니다만, 
			이로 인해 가능해지는 많은 기능들이 네이티브 어플리케이션에서 많이 활용되는 기능들이므로 아마도 웹 어플리케이션 개발에 있어 큰 패러다임 
			변화를 이끌어낼 가능성이 있다고 보입니다. 따라서, 웹 어플리케이션의 오프라인 기능 지원이 시작되고 있는 지금 반드시 익숙해져야 하는 
			대표적인 기능이기도 합니다. 서비스 워커는 그 특성상 폴리필 라이브러리를 제공할 수 없습니다만, 현재 크롬이 서비스워커의 첫번째 네이티브
			구현을 포함하고 있습니다. 아직 캐시 API는 폴리필 형태로 제공하고 있습니다만, 대체적인 기능은 현재도 사용이 가능합니다. 
			Google I/O 2014에서 폴리머 데모로 소개된 Topeka는 로딩 타임의 제거를 위해 모든 리소스를 초기에 로딩하는 기능을 서비스 워커로
			구현하고 있습니다. 코드를 참조하시는 것만으로도 충분하게 기능을 확인해 볼 수 있을 것입니다.
			</p>
			
			<p><a href = "https://www.w3.org/TR/service-workers/">참고링크는 여기를 클릭해주세요.</a></p>
		</footer>
	</body>
</html>