<?php
	@header('P3P: CP="NOI CURa ADMa DEVa TAIa OUR DELa BUS IND PHY ONL UNI COM NAV INT DEM PRE"');
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
	<script type="text/javascript" src="http://connect.facebook.net/ko_KR/all.js"></script> 
	<script type="text/javascript"></script>
	<script>
		var sessionId = '<?php echo session_id()?>'; 
	    var fbacceesstoken = '<?php echo $_SESSION['fbtoken']?>';  
	    var currentusername = '<?php echo $_SESSION['name']?>';  
	    var userid = '<?php echo $_SESSION['id'] ?>';
	    var score = '<?php echo $_SESSION['score'] ?>';
	    var sta = '<?php echo $_SESSION['facebook'] ?>';
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
	<script>
	function statusChangeCallback(response) {
	    console.log('statusChangeCallback');
	    console.log(response);
	    // response 객체는 현재 로그인 상태를 나타내는 정보를 보여준다. 
	    // 앱에서 현재의 로그인 상태에 따라 동작하면 된다.
	    // FB.getLoginStatus().의 레퍼런스에서 더 자세한 내용이 참조 가능하다.
	    if (response.status === 'connected') {
	      // 페이스북을 통해서 로그인이 되어있다.
	      testAPI();
	    } else if (response.status === 'not_authorized') {
	      // 페이스북에는 로그인 했으나, 앱에는 로그인이 되어있지 않다.
	      document.getElementById('status').innerHTML = 'Please log ' +
	        'into this app.';
	    } else {
	      // 페이스북에 로그인이 되어있지 않다. 따라서, 앱에 로그인이 되어있는지 여부가 불확실하다.
	      document.getElementById('status').innerHTML = 'Please log ' +
	        'into Facebook.';
	    }
  	}

	  // 이 함수는 누군가가 로그인 버튼에 대한 처리가 끝났을 때 호출된다.
	  // onlogin 핸들러를 아래와 같이 첨부하면 된다.
	function checkLoginState() {
	    FB.getLoginStatus(function(response) {
	      statusChangeCallback(response);
	    });
	}

  /*********************************************************************************/



	window.fbAsyncInit = function() {  
	    FB.init({appId: '759307620878577', status: true, cookie: true,xfbml: true});  
	    
	    // FB.init({
	    //   appId      : '759307620878577',
	    //   xfbml      : true,
	    //   version    : 'v2.5'
	    // });

	 //    FB.Event.subscribe('auth.login', function(response) {
	 //    	document.location.reload();
		// });

	 //    FB.Event.subscribe('auth.logout', function(response) {
	 //    	document.location.reload();
		// });
	};  
	      
	(function(d){  
	   var js, id = 'facebook-jssdk', ref = d.getElementsByTagName('script')[0];  
	   if (d.getElementById(id)) {return;}  
	   js = d.createElement('script'); js.id = id; js.async = true;  
	   // js.src = "//connect.facebook.net/en_US/all.js";  
	   ref.parentNode.insertBefore(js, ref);  
	 }(document));   

	  // (function(d, s, id){
	  //    var js, fjs = d.getElementsByTagName(s)[0];
	  //    if (d.getElementById(id)) {return;}
	  //    js = d.createElement(s); js.id = id;
	  //    //js.src = "//connect.facebook.net/en_US/sdk.js";
	  //    fjs.parentNode.insertBefore(js, fjs);
	  //  }(document, 'script', 'facebook-jssdk'));


	function facebooklogin() {  
    //페이스북 로그인 버튼을 눌렀을 때의 루틴.  
        FB.login(function(response) {  

            var fbname;  
            var accessToken = response.authResponse.accessToken;  
            FB.api('/me', function(user) {  

                fbname = user.name;
                //response.authResponse.userID
                $.post("./php/fbloginprocess.php", { "userid": user.id, "username": fbname, "fbaccesstoken": accessToken},
                function (responsephp) {

                    //댓글을 처리한 다음 해당 웹페이지를 갱신 시키기 위해 호출.  
                    location.replace('./index.php');
                });
            });   
        }, {scope: 'public_profile,email'}); 
    }

	</script>


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

        <li onclick="facebooklogin()" style="cursor: pointer;"><a href="#">
        	<script type="text/javascript">
        		if(!sta)
        			document.write('login');
        	</script>
        </a>
        </li>
        <li style="cursor: pointer;"><a href="php/logout.php">
        	<script type="text/javascript">
				if(sta)
        			document.write(userid);</script>
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
