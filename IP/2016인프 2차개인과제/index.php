<?php session_start() ?>
<?php
//만약 로그인이 되어있지 않으면, 바로 경고를 보내고 로그인 창으로 보냅니다.
//과제 스펙의 로그인 경고기능 구현.
if(!isset($_SESSION["id"])){
echo "<script>alert(\"You are not in login status!! Please Login!!\");</script>";
echo "<meta http-equiv='refresh' content = '0; url=http://165.132.122.160/~u2013147561/login.php'>";
//로그인 창으로 보내줍니다.
exit;
}
if($_SESSION['id'] != "") echo $_SESSION['id']."님 ".$_SESSION['visit_cnt']."회 째 방문을 환영합니다. ";
//만약에 성공적으로 로그인을 하였다면, 세션아이디와 세션방문횟수 변수를 받아와서, 모든 웹페이지의 상단에 표시해줍니다.
else echo "로그인 상태가 아닙니다. 사이트하단에 로그인 버튼을 이용해주세요.";
?>

<html>
	<head>
		<meta charset = "utf-8">
		<title>Cutting-edge</title>
		<link rel = "stylesheet" type="text/css" href="myStyle.css">
		<!--external style sheet을 적용하였습니다. 아직 초보라서, 전체를 부트스트랩으로 가져오기 보다는 우선은
		제가 만들었습니다. 허접하지만 잘 봐주셨으면 감사하겠습니다.-->
		<style type = "text/css">
			.special	{color:teal;
						font-weight:bold;<!--font-weight사용-->
						font-size:15pt;
						font-family:tahoma, sans-serif;
						}
			<!--교재에 있길래, special class적용하였습니다.-->
			.background_image { position: absolute;
								top: 0px
								left: 730px;
								z-index = 0;
							   }
			.foreground_image { position: absolute;
								top: 1900px;
								left: 100px;
								z-index = 10;					
								}
							   
			.text			  { position: absolute;
								top:1900px;
								left:100px;
								z-index = 3;<!-- z-index -->
								font-size:10pt;
								font-family:tahoma, sans-serif;
								color:black;
							   }
			<!--포지셔닝도 하였으며, z-index는 여기서 쓰였습니다.-->
			span	{color: purple;
					 font-size:.6em;
					 height:2em;}
					 
			.sub	{position: relative;
					 bottom:-1ex
			<!--상대적 포지셔닝도 하였습니다!-->
					}
			body	{
					background-color: #EEEEEE;
					background-position: 50% 50%;
					background-repeat: no-repeat;
					 <!--Background img insert... background-image: url(filename.jpg);-->
					}
			div		{ text-align: left;<!-- text-align 속성 적용 -->
					  width : 50%;
					  position : relative;
					  left : 0%;
					  border-width: 6px;
					}
			.border_style { border-width:thin;
							border-style:dotted;
							border-color:gray;
						  }
			.floated {background-color: #FFFFFF;
					  font-size: 1.5em;
					  font-family: arial, helvetica, tahoma;
					  padding: .2em;
					  margin-left: .5em;
					  margin-bottom: .5em;
					  float: left;
					  text-align: left;
					  width: 60%;
					}
			#gradient {
				height: 50px;
				background: red; /* For browsers that do not support gradients */
				background: -webkit-linear-gradient(white, blue); /* For Safari 5.1 to 6.0 */
				background: -o-linear-gradient(white, blue); /* For Opera 11.1 to 12.0 */
				background: -moz-linear-gradient(white, blue); /* For Firefox 3.6 to 15 */
				background: linear-gradient(white, blue); /* Standard syntax (must be last) */
			}	<!--using the link http://www.w3schools.com/css/tryit.asp?filename=trycss3_gradient-linear-->
			<!-- embedded style sheet을 적용하였습니다. -->

		</style>
	</head>
	
	<body>
	
		<header>
			<h1>Cutting-edge Computer Science</h1>
			<div class = "border_style">
			<figure>
				<img src = "ProfilePicture_2.JPG" width = "200" height="133" alt = "Song Chi Heon">
			</figure>
			<!--이미지를 삽입하기위해, figure속성을 적용하였습니다.-->
			
			<h2>Introduce my self; <small>Song Chi Heon</small>
			<span class="sub">is undergraduate level student.</span></h2>
			<p>Hi, my name is Song Chi Heon. My english name is Phillip. You can call me Phillip.
			I'm second year student in Yonsei University, major in Computer Science. I have entered Yonsei at Feburary, 2013.
			I'm discharged from my military service January 19th, 2016. I had worked at Post office of Airforce Academy, position of soldier.
			I like car very much. My hobby is driving, listening musics and cooking. Also, I like JAVA programming 
			so much. And I will like Internet Programming too. And, if you wonder about my favorite field,
			<a href = "FavoriteFields.html">click this link.</a> Thank you!
			</p>
			</div>
		</header>
		<!--자기소개 부분이며, 문서의 논리적구조를 위해, header를 적용하였습니다.-->
		
		<section id ="1"><!--begin section 1-->
			<h2>&lt;In this web page, I introduce you to four Web Technologies.&gt;</h2><!--special character적용-->
			<nav>
				<ul class="special">
					<li>
						<details>
							<summary>Responsive Web Technology</summary>
							<p>소개 : 요즘처럼 인터넷에 접근하는 Device가 여러종류인 만큼, 각 Device의 Size에 맞춰서 웹에 접근할 필요가 있다.<br>
							이에, Device의 Display의 크기마다 자동적으로 최적화되는 기술을 반응형 웹 기술 이라고 한다.
							</p>
							<p class="special"><a href = "responsiveWeb.php">
							More details are here..</a></p>
						</details>
						<!--문서의 깔끔함을 위해서, details속성을 이용하였습니다. warning이 뜨긴 하지만, 
						error는 아니며, 이 기능이 구현되지 않아도 어느 사이트든 사용하는데 크게 지장이 없습니다.-->
					</li>
					<li>
						<details>
							<summary>Service Worker</summary>
							<p>소개 : 서비스워커는 웹페이지나 사용자와 interaction이 필요하지 않은 기능들을 위한 기회를 제공한다.<br>
							웹페이지와는 별개로 여러분의 브라우저에 의해 백그라운드에서 실행되는 스크립트 이다.
							</p>
							<p class="special"><a href = "serviceWorker.php">
								More details are here..</a>
							</p>
						</details>
					</li>
					<li>
						<details>
							<summary>Manifest Format</summary>
							<p>소개 : Manifest Format은 사이트에 meta data로 앱 이름, 아이콘 링크, URL 등을 넣어주는 기능이다.<br>
							Apple이 Meta-tag로 지원했던 기능이며, W3C에서 표준화 했다.
							</p>
							<p class="special"><a href ="Manifest_Format.php">
							More details are here..</a>
							</p>
						</details>
					</li>
					<li>
						<details>
							<summary>Linked Open Data</summary>
								<p>소개 : ‘공공데이터’는 공공기관이 다루는 데이터 중 누구나 자유롭게 활용하고 재설계 혹은 재생산할 수 있도록 개방한 데이터를 일컫는다.<br>
								미국, 영국, 한국 정부 등은 오랫동안 공공데이터를 확산하기 위한 다양한 노력을 기울여 왔다.<br>
								공공데이터 품질을 높이기 위한 노력 가운데 하나가 ‘링크드 오픈데이터’(Linked Open Data, LOD)다.
								</p>
								<p class="special"><a href = "LOD.php">
									More details are here..</a>
								</p>
						</details>
					</li>
				</ul>
			
			<!--advertisement-->
				<aside>
					<p style = "font-size: 12pt; color: deepskyblue;"><!--font-size사용--><!--in-line style sheet사용-->
						In this internet age, whether you are in field of computer science or not, 
						you should know about cutting-edge web-based technology.
					</p>
				</aside>
				<!-- aside속성을 사용하였습니다. -->
			</nav>
			<!-- nav속성을 사용하였습니다. -->
		</section>
		
		<!--여기서부터는 form타입을 사용하였습니다. 7개의 form-type이 사용되었으며, 표준이 아닌 건 없습니다.-->
		<section id = "2">
			<h2 class = "floated">You can submit to me about Your feedback</h2><!--float 속성을 이용하였습니다.-->
			<br><br><br>
			<p>
				Why my webpage is strong than other's? If you wonder, please click<a href = "compare.php"> Here!</a>
			</p>
			<form method = "post" autocomplete = "on">
				<p><label>1. Name:
					<input type = "text" id = "name" placeholder = "Name" required />
					</label>
				</p>
				
				
				<p>2. Your Favorite parts:(You can choice multiple options.)<br>
					<label>a. Design
						<input type = "checkbox" name = "favorite_parts" value = "Design">
					</label>
					<label>b. Contents
						<input type = "checkbox" name = "favorite_parts" value = "Design">
					</label>
					<label>c. Summary
						<input type = "checkbox" name = "favorite_parts" value = "Design">
					</label>
					<label>d. Profile
						<input type = "checkbox" name = "favorite_parts" value = "Design">
					</label>
					<label>e. Font
						<input type = "checkbox" name = "favorite_parts" value = "Design">
					</label>
				</p>
				
				<p><label>3. Please advise to me:<br>
					<textarea name = "comments" rows = "7" cols = "36">Your comments here...
					</textarea>
					</label>
				</p>
				
				<p>
					<label>4. Grade my website:
						<select name = "grading">
							<option selected>Excellent</option>
							<option>A+</option>
							<option>A0</option>
							<option>A-</option>
							<option>B+</option>
							<option>B0</option>
							<option>B-</option>
							<option>C+</option>
							<option>C0</option>
							<option>C-</option>
							<option>D0</option>
							<option>Awkward</option>
						</select>
					</label>
				</p>
				
				<p>
					<label>5. Date:
						<input type = "date" />
							e.g.) (yyyy-mm-dd)
					</label>
				</p>
				
				<p>
					<label>6. Tel:
						<input type = "tel" placeholder = "(###) ####-####"
						pattern = "\(\d{3}\)+\d{4}-\d{4}" required />
							e.g.) (010) 1234-5678
					</label>
				</p>
				
				<p>
					<label>7. Email:
						<input type = "email" placeholder = "domain@site.com" required />
					</label>
				</p>
				
				<p>
					<input type = "submit" value = "Submit">
					<input type = "reset" value = "Clear">
				</p>
			</form>
			
							
		</section>
		
		<section id = "3">
			<h2>How to find me in Yonsei University?</h2>
			<ul>
				<li>Yonsei-Samsung Library, Laptop reading room, 4th floor in Campus.<br>
					<img src = "map.PNG" width = "600" height = "450" alt = "map"><p></p><p></p>
				</li>
				
				<li>My contact
					<ol>
						<li>Phone Number : +82 10-6709-5679</li>
						<li>E-mail address : <a href = "mailto:chihun206@naver.com">chihun206@naver.com</a></li>
					</ol>
				</li>
			</ul>
		</section>
		
		<footer>
			
			<div id="gradient"><h2>Epilogue.</h2></div><!--gradient사용하였습니다-->
			<p>학교에 다니면서 인상깊은 던 과목들을 <a href = "table.php">링크에 첨부합니다.</a></p>
			<p><h3><a href = "login.php">로그인하러가기</a></h3></p>
			
			<p><img src = "logoYonsei.jpg" class = "background_image" 
				alt="logo of Yonsei, background" width = "300" height = "100"/><!--z-index 및 이미지 겹침이 사용된 곳 입니다.-->
			</p>
			<p><img src = "ioniq.PNG" class = "foreground_image" alt = "feature of ioniq" width = "300" height = "200" /></p>
			<p class = "text">Positioned Text</p>
			
		</footer>
	</body>
</html>