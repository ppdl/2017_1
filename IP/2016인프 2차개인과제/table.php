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
	<title>표 기반으로 들었던 강의평가 및 소개</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
	<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
	<!--위쪽 네 줄은 표를 위한, 부트스트랩기반으로, 바로 아래에 있습니다.-->
	
	<style type = "text/css">
		#cover
		{
			position: relative;
			margin: 0 auto;
		}
	
		#cover img
		{
			position: absolute;
			left: 0;
			-webkit-transition: opacity 4s ease-in-out;
			transition: opacity 4s ease-in-out;
		}
	
		#cover img.top:hover
		{opacity: 0;}
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
<!--http://www.w3schools.com/bootstrap/tryit.asp?filename=trybs_table_contextual&stacked=h-->
<!--이 홈페이지의 부트스트랩표를 기반으로 만들었습니다.-->
<body>

	<div class="container">
	<div id="box_1"><h2>수강과목 평점매기기.</h2></div>
	<p class = "floated">들었던 과목 중, 괜찮았던 과목만 여기다가 매기고 평가해보는 시간을 갖겠다.</p>            
		<table class="table"><!--table속성을 부트스트랩 기반으로 이용하였습니다.-->
			<thead>
				<tr>
					<th>과목이름</th>
					<th>학정번호</th>
					<th>교수님</th>
					<th>좋았던 점</th>
				</tr>
			</thead>
			<tbody>
				<tr class="success">
					<td>공학기초설계</td>
					<td>ENG1107</td>
					<td>한요섭 교수님</td>
					<td>대학생활의 꽃인 "조모임"을 처음으로 경험하게 해주셨다.
					다만 학점은 원하는대로 안 나왔다 ㅠㅠ</td>
				</tr>
				<tr class="danger">
					<td>컴퓨터프로그래밍</td>
					<td>CSI2100</td>
					<td>Bernd Burgsteller교수님</td>
					<td>태어나서 처음으로 C언어를 배웠다. 이때는 개념이 제대로 박혀있지 않아 어려웠으나,
					지금 생각해보면, 내 프로그래밍적 사고를 조금 길러준 것 같다.</td>
				</tr>
				<tr class="info">
					<td>객체지향프로그래밍</td>
					<td>CSI2102</td>
					<td>김선주 교수님, 김재경 교수님</td>
					<td>이 과목은 1학년 2학기에 입대 전이라고 던지고 놀다가 D나와서, 이번에 정신차리고
					복학해서 재수강을 하는 과목이다. 그런데, 1학년때는 C++을 했고, 2학년인 지금은 
					JAVA언어를 한다. 그런데, 김재경 교수님께서 JAVA언어를 상세히 설명해주시고, 과제도 난이도가 쉬운 순에서
					어려운 순으로 단계별로 내주셔서 어렵다가도 단계별로 풀어내려 애를 쓰다보면, 어느새 실력이 늘어
					있는 마법같은 일이 벌어진다.(실제로 어려운 과제를 풀어낸 내 모습을 볼 때마다 감탄을 금치 못한다.)
					</td>
				</tr>
				<tr class="success">
					<td>디자인과 문화</td>
					<td>UCE1108</td>
					<td>김혜란 교수님</td>
					<td>예상과 다르게 디자인을 하는 건 거의 없고, 암기수업이다.
					별로 재미가 없는 경향이 없지않아 있고, 대신에 전시회 다녀오고 보고서 쓰라고 과제내주신 것은 좋았다.</td>
				</tr>
				<tr class="danger">
					<td>인터넷프로그래밍</td>
					<td>CSI2109</td>
					<td>이경호 교수님</td>
					<td>태어나서 처음으로 나만의 웹페이지를 만들 기회를 주셔서 너무 감사하다.
					진도의 양은 많지만, 이경호교수님 너무 잘생기셨고(진심) 너무 고상하신 것 같으심.
					의외로 자바스크립트 언어가 내가 알고있는 자바언어하고 비슷하게 기능해서(둘은 전혀 관련없다고 들은...)
					너무 신기했다. 그리고 뭔가 내가 문서편집기계가 되는 것 같은 느낌이 들었고,
					Sementic웹을 조사하면서 어렴풋이나마 그 개념이 조금 생기는 것 같다.</td>
				</tr>
			</tbody>
		</table>
	</div>
	
		돌발질문!! : 최근에 나온 두 하이브리드 자동차 입니다. 누가 좋나요?(아이오닉 or Niro); 마우스를 올려주세요!
		<div id = "cover">
			<img class = "bottom" src = "ioniq.PNG" width = "300" height = "200" alt = "아이오닉이 좋나요?">
			<img class = "top" src = "niro.PNG" width = "300" height = "200" alt = "아니면 니로가 좋나요?">
		</div>
	<!--교재에 있는 소스코드를 이용하였습니다. transition-->
	
	<br><br><br><br><br><br><br><br><br><br><br><br>
	
	

</body>
</html>
