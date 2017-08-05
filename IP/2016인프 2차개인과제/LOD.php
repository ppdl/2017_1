<?php session_start() ?>

<?php
if($_SESSION['id'] != "") echo $_SESSION['id']."님 ".$_SESSION['visit_cnt']."회 째 방문을 환영합니다. ";
?>

<html>
	<head>
		<meta charset = "utf-8">
		<title>Linked Open Data</title>
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
				border : 3px solid purple;
				padding : 5px 20px;
				text-align: left;<!--text align 사용-->
			}
			
			#round_1
			{
				border : 3px solid purple;
				padding : 5px 20px;
				background : white;
				width : 200px;
				text-align: left;
				border-radius: 45px;
				margin-bottom: 20px;
				box-shadow: -25px -25px 50px dimgrey;
			}
			<!--margin, padding, border속성을 사용하였습니다.-->
			<!--rounded corner속성을 적용하였습니다. -->
			<!--box shadow속성을 사용하였습니다.-->
			
			#box_1
			{
				width = 200px;
				height = 200px;
				background-color: plum;
				box-shadow: -25px -25px 50px dimgrey;
				margin-bottom: 20px;
			}<!--box shadow속성을 사용하였습니다.-->
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
		
			<div id="box_1"><h1>What is LOD(Linked Open Data)?</h1></div><!--박스속성을 이용하였습니다.-->
			<h2>Intro</h2>
			<p>LOD는 ‘링크드 데이터(Linked Data)’와 ‘공개 데이터(Open Data)’ 성격을 모두 갖는 데이터다. 즉, 링크드 데이터 
			구축 원칙에 맞게 만든 개방형 데이터다. 링크드 데이터 구축 원칙은 글로벌 웹표준 제정 기구인 월드와이드웹컨소시엄(W3C) 중심으로 발전되고 있다.
			4대 원칙은 아래와 같다.
			<ol>
				<li>통합 자원 식별자를 사용한다.(URI)</li>
				<li>URI는 HTTP프로토콜을 통해 접근할 수 있어야 한다.</li>
				<li>RDF나 스파클 같은 표준을 사용한다.</li>
				<li>풍부한 링크 정보가 있어야 한다.</li>
			</ol>
			<p>링크드 데이터의 가장 큰 특징은 ‘통합 자원 식별자’(Uniform Resource Identifier, URI)’를 사용한다는 점이다.
			흔히 알고 있는 ‘URL(Uniform Resource Locator)’과 비슷한 개념이다. URL이 특정 정보 자원의 종류와 위치를 가리킨다면,
			URI는 웹에 저장된 객체(식별자)를 가리킨다는 점에서 다르다. 지금의 웹은 문서 기반으로 연결돼 있다. URI를 활용하면 데이터를 중심으로
			웹을 연결할 수 있다. 예컨대 소나무에 대한 데이터를 수목원에서 만들었다 치자. 수목원은 소나무의 명칭과 뜻, 분포지역, 사진 등의 자료를 
			정리해 올리게 된다. 그런데 국립중앙도서관도 소나무와 관련된 책을 소장하고, 이를 데이터로 입력해 올려놓았다. 웹에 중복 자료가 생긴 것이다.
			예전에는 수목원 홈페이지 밑에 ‘참고자료 : (국립중앙도서관 홈페이지 주소)’ 식으로 관련 정보를 수동으로 표시하는 식으로 두 웹사이트 정보를
			연결하곤 했다. URI를 활용하면 각 기관에 있는 데이터를 곧바로 홈페이지에 연동해 보여줄 수 있다. 수목원에서는 기존 소나무 소개 페이지에 
			‘소나무와 관련된 책 정보’를 바로 연결할 수 있다. 서로 다른 데이터베이스에 저장된 정보이지만, 웹을 매개체로 필요한 데이터를 서로 가져와 
			쓸 수 있는 것이다.
			</p>
			<figure>
				<img src = "LOD_1.jpg" width = "600" height = "450" alt = "링크드 데이터 예시">
				<figcaption>
					<em>Example diagram of Linked Open Data in national case.</em>
				</figcaption>
			</figure>
		</header>
		
		<section id = "1">
			<h2>Concept 1: Web as a DB storage.</h2>
			<article>
				<p>LOD가 공공데이터 분야에서 활용되면 같은 데이터를 여러 번 만들지 않아도 된다. 웹 자체를 거대한 DB로 활용해, 누구나 LOD에 접근할 수 있기 때문이다. 공공기관은 새로운 데이터를 만들 때 이미 나와 있는 LOD를 활용해 구축 시간과 노력을 줄일 수 있다. 또한 다른 기관 데이터를 참고하면서 데이터 품질에 대해 논의하고 기관·개인·정부끼리 자연스레 협업할 수도 있다. 이는 LOD가 가진 가장 큰 장점이기도 하다.
				LOD를 기반으로 서비스를 만들면 사용자에게도 좋다. LOD를 이용해 검색 서비스를 만들었다고 가정하자. 사용자는 특정 키워드와 관련된 결과물만 받는 데 그치지 않고, 해당 키워드와 연관된 정보도 함께 얻을 수 있다. 실제로 한국 특허청은 이러한 검색 서비스를 구축할 수 있게 지원하고 있다. 한국 특허청은 미국, 일본, 중국, 유럽과 협약을 맺어 산업재산권 데이터를 공유하고 있다. 누군가가 산업재산권 정보를 검색하는 서비스를 만들 때 해외에도 비슷한 정보가 있는지 비교할 수 있다면 더 유용할 것이다. 특허청은 이러한 활용성을 고려해 협약을 맺은 다른 나라 산업재산권 데이터도 LOD로 접근할 수 있도록 구축했다.
				LOD를 많이 쓰는 대표적인 곳은 도서관이다. 전세계 도서관은 보통 마크(MARC) 체제를 기반으로 도서 정보 데이터베이스를 만든다. 여러 도서 정보를 한번에 입력하는 데 쓰는 글로벌 표준 규격이다. MARC는 기계가 읽을 수 있는 형식으로 데이터를 변환한다. 이 데이터는 책의 표제, 저자명, 판 사항, 발행 사항, 형태 사항, 주제, 주기 등에 대한 정보를 담고 있다. 이러한 공통된 데이터 규격이 있기 때문에 전세계 도서관은 같은 기준으로 데이터를 찾거나 저장할 수 있다.
				하지만 이들 데이터를 더욱 ‘똑똑히’ 연결하는 방법이 있다. RDF(Resource Description Framework)를 활용하면 된다. RDF는 W3C가 제안한 표준 규격으로, 웹의 자원 정보를 표현하는 데 쓴다. 서로 다른 메타데이터간 뜻이나 구조 등을 기계가 읽을 수 있는 언어로 표현한 것이다. 메타데이터끼리 정보를 효율적으로 교환할 수 있도록 고안됐다.
				도서관 데이터를 RDF로 저장하면 도서관 뿐 아니라 더 많은 기관과 데이터를 주고받거나 관리하기 쉬워진다. 국립중앙도서관은 MARC와 더불어 RDF로 LOD를 만드는 작업을 진행하고 있다.
				</p>
				<figure>
					<img src = "RISS.PNG" width = "500" height = "450" alt = "Riss">
					<figcaption>
						<em>Example of RISS(국내 논문 검색사이트)</em>
					</figcaption>
				</figure>
				<h2>Concept 2: Explaination</h2>
				<p>LOD는 데이터베이스(DB) 지식이 어느 정도 있는 사람이 구축하거나 사용할 수 있다. 관련 용어도 미리 숙지해야 한다. 일단 RDF를 알아야 한다. RDF는 앞서 설명했듯, 메타데이터를 입력할 수 있는 구조다.’트리플’에도 익숙해져야 한다. 트리플은 RDF 메타데이터 모델을 표현하는 용어다. 주어-술어-목적어 (subject-predicate-object) 형식으로 메타데이터를 표현하는 데서 유래한 말이다.
				개발자가 LOD에 접근하거나 서비스를 구축하려면 ‘SPARQL(스파클)’이라는 언어를 이해해야 한다. 스파클은 SQL와 유사한 쿼리 언어다. 이 언어를 이용하면 RDF 형식에 맞게 데이터를 불러오고 저장할 수 있다.
				LOD는 데이터에 접근할 수 있는 주소를 하나씩 부여한다. 개발자는 ‘PREFIX’라는 선언문과 함께 LOD 주소를 입력해야 한다. 가령 특허청 LOD 주소나 중앙도서관 LOD 주소처럼 원하는 데이터 저장소를 주소로 입력하면 해당 데이터에 접근할 수 있는 권한이 생긴다. LOD를 구축한 공공기관은 각 데이터 필드명과 각 필드에 어떤 데이터가 담겨 있는지 공개했다. 개발자는 이러한 자료를 기반으로 원하는 데이터의 이름을 알 수 있다.
				</p>
				<figure>
					<img src = "SparkleQuery.jpg" width = "500" height = "400" alt = "Sparkle Query">
					<figcaption>
						<em>산업재산권 LOD 홈페이지</em>
					</figcaption>
				</figure>
			</article>
		</section>
		
		<footer>
			<h2>Epilogue</h2>
			<p>LOD는 거저 구축되는 게 아니다. 비용과 시간을 투자해야 하고, 전문 개발자도 투입돼야 한다. 그럼에도 많은 공공기기관이 LOD에 관심을 가져야 하는 이유는 명확하다. LOD가 공공데이터 품질을 높여주기 때문이다.
			LOD의 중요성을 앞장서 주창하는 곳은 W3C다. 팀 버너스 리는 개방형 데이터의 수준을 5단계로 나누어 품질을 정의하고 있다. 각 단계별 데이터는 다음과 같다.
			1단계는 포맷을 고려하지 않은 데이터다. 표를 스캔해서 PDF나 HWP 파일로 올린 경우가 1단계 수준의 공공데이터다. 2단계는 표를 이미지가 아닌 구조화된 데이터로 제공하는 형태다. 엑셀 파일로 표를 제공하는 경우가 이에 해당한다. 3단계는 비독점 포맷을 사용한 데이터다. 엑셀 파일 대신 CSV 파일로 데이터를 공개한 경우 3단계 데이터라고 말할 수 있다. 4단계는 개체를 가리킬 수 있도록 URI를 제공하는 경우다. 마지막 5단계는 다른 데이터끼리 연결할 수 있는 데이터를 말한다. 팀 버너스 리는 이처럼 가장 높은 수준의 데이터로 LOD를 꼽았다. 많은 공공기관들이 데이터 품질을 이야기할 때 이 5단계 기준을 참고한다.
			</p>
			<figure>
				<img src = "five_opendata.jpg" width = "500" height = "400" alt = "Five Open Data">
				<figcaption>
					<em>5 stages of open data declared by 팀 버너스 리</em>
				</figcaption>
			</figure>
			<p>한국정보화진흥원이 발간한 ‘2014 링크드 오픈 데이터 국내 구축 사례집’에 따르면 “국내 정보관리기관이나 일반적인 웹사이트에서 공개한 데이터는 위 기준에서 별 1개 ~ 3개 수준의 데이터”라고 한다. 한국정보화진흥원은 “이러한 수준에서는 새로운 애플리케이션 혹은 서비스, 비즈니스 모델 창출을 위해서는 기초 데이터의 가공과 정제 등에 많은 노력을 기울여야 한다”라고 설명했다. 또한 “단순히 개방된 형태의 데이터보다는 링크드 데이터로 개방된 데이터의 가치 창출이 기업, 개인, 정부 등이 상호 지속적인 연결고리를 가지며 고 부가가치 창출이 가능하다”라며 LOD에 투자하는 이유를 서술했다.
			한국 공공기관이 LOD를 구축한 사례는 2014년 기준으로 10여건에 불과하다. LOD는 이제 막 국내에서 움직임이 싹트는 단계라고 볼 수 있다. LOD가 제대로 구축되려면 무엇보다 데이터 양 자체가 많아야 하며, 이를 연결할 수 있는 요소도 많아야 한다. 국내에선 현재 공공데이터 양 자체가 많지 않아 LOD를 활용하는 사례가 적은 것으로 보인다. 해외에선 ‘디비피디아’가 LOD의 좋은 활용 사례로 꼽힌다. 디비피디아는 위키피디아에 있는 정보를 RDF로 변환해 모아둔 저장소다. 디비피디아에 있는 정보를 활용하면 개인 웹사이트에 위키피디아 정보를 바로 보여줄 수 있다.
			</p>
			
			<div id="round_1"><p><a href = "http://terms.naver.com/entry.nhn?docId=2454603&cid=42346&categoryId=42346">
				자세한 정보는 여기를 클릭하세요.</a>
			</p></div><!--round box를 적용하였습니다.-->
		</footer>
	</body>
</html>