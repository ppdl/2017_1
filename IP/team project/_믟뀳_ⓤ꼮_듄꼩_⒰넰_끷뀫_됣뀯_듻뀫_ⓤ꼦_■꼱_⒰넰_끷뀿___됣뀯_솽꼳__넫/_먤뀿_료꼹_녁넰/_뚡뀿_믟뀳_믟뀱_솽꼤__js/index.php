<?php
	session_start();
?>

<!DOCUMENT html>
<html>

<head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no" />
	<title>쾌변 고!</title>
	<link rel="stylesheet" type="text/css" href="css/slide-menu.css" />
	<script type="text/javascript" src="js/jquery-1.7.1.min.js" charset="utf-8"></script>
	<script type="text/javascript" src="https://static.nid.naver.com/js/naverLogin_implicit-1.0.2.js"></script>
	<script type="text/javascript" src="./jquery-1.11.3.min.js"></script>
	<script type="text/javascript" charset="utf-8" src="oauth/jquery.cookie.js"></script>
    <script type="text/javascript" charset="utf-8" src="oauth/naverLogin.js"></script>
	<script type="text/javascript"></script>
	<script> 
	    var fbacceesstoken = '<?php echo $_SESSION['fbtoken']?>';  
	    var currentusername = '<?php echo $_SESSION['name']?>';  
	    var userid = '<?php echo $_SESSION['id'] ?>';
	    var score = '<?php echo $_SESSION['score'] ?>';
	    var sta = '<?php echo $_SESSION['sta'] ?>';
	    	
	</script>

	<style>
		html {
			margin: 0 0;
		}
		body {
			margin: 0px 0px;
			/*padding: 0 0;*/
		}
		div {
			margin: 0px 0px;
			padding: 0 0;
		}
		#header {
			width: 100%;
			height: 70px;
			background-color: rgb(0, 192, 221);
		}
		#header a {
			width: 175px;
			height: 70px;
			margin: 0 auto 0 auto;
			padding: 0 0;
			display: block;
		}
		#logo {
			width: 175px;
			height: 70px;
			margin: 0 auto 0 auto;
		}
		input[type=search] {
			width: 80%;
			height: 40px;
			border: 2px solid black;
			border-radius: 10px;
			font-size: 26px;
			padding: 2px 5px;
		}
		input[type=image] {
			margin-bottom: -11px;
		}
		#search-wrap {
			background-color: rgb(220, 220, 220);
			text-align: center;
			padding: 10px 0;
		}
		#content ul {
			width: 70%;
			margin: auto;
			padding: 10px 0;
		}
		#content ul, #content li {
			text-align: center;
			font-size: 20px;
			line-height: 35px;
			list-style-type: none;
		}
		#content li {
			border-top: 1px solid rgba(0,0,0,0.3);
			width: 100%;
			margin: auto;
		}
		footer {
			background-color: rgb(0, 192, 221);
			margin-bottom: 0;
			height: 70px;
		}
		footer p {
			color: white;
			font-size: 30px;
			margin: auto;
			padding-top: 10px;
			width: 150px;
		}
		@media all and (min-width: 768px) {
			div#content {
				width: 90%;
				margin: auto;
				height: 200px;
			}
			#content ul {
				float: left;
				width: 38%;
				margin: auto 5%;
			}
		}
	</style>
</head>
<body>

	<div id="header" class="reveal-header">
		<a href="home.html"><img id="logo" src="img/로고.png" /></a>
	</div>
	<div id="search-wrap">
		<input type="search" />
		<input type="image" id="gps" src="img/gps.png" width= "40" height="40"/>
	</div>
	<div id="mobile-nav"></div>

	<nav class="reveal-nav">
      <ul class="menu">
		<div id="status"></div>

		<li style="cursor: pointer;"><a href="login.php">
        	<script type="text/javascript">
        		if(!sta)
        			document.write('login');
        	</script>
        </a>
        </li>

        <li style="cursor: pointer;"><a href="php/logout.php">
        	<script type="text/javascript">
				if(sta)
        			document.write(userid);
        	</script>
        </a>
        </li>
        <li><a href="#">Services</a></li>
        <li><a href="#">About</a></li>
        <li><a href="#">PC version</a></li>

	  </ul>
	</nav>

	<div id="content" class="reveal-contents">
		<ul>게시글
			<li>title1</li>
			<li>title2</li>
			<li>title3</li>
			<li>title4</li>
		</ul>
		<ul>순위
			<li>1위</li>
			<li>2위</li>
			<li>3위</li>
			<li>4위</li>
		</ul>
	</div>
	<footer>
		<p>&copy; 급하니</p>
	</footer>
	<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
	<script src="js/slide-menu.js"></script>

</body>
</html>
