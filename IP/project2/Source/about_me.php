<?php session_start();?>

<!DOCTYPE html>
<?xml version="1.0" encoding="utf-8"?>

<html lang="en">
<head>
  <title>Bootstrap Example</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <link href="https://fonts.googleapis.com/css?family=Macondo" rel="stylesheet">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
  <style>
    /* Remove the navbar's default margin-bottom and rounded borders */ 
    .navbar {
      margin-bottom: 0;
      border-radius: 0;
    }
    a.navbar-brand img{
      animation: transformLogo;
      animation-duration: 2s;
      animation-iteration-count: infinite;
    }
    /* Add a gray background color and some padding to the footer */
    footer {
      background-color: #f2f2f2;
      padding: 25px;
    }
    
  .carousel-inner img {
      width: 100%; /* Set width to 100% */
      margin: auto;
      min-height:200px;
  }
  ul.nav li a:hover{
    color:white;
    text-shadow: 0 0 10px white;
    animation: navHover;
    animation-duration: 1s;
    animation-direction: alternate;
    animation-iteration-count: infinite;
   }
   div.myinfo{
      border-left:5px solid #195ead;
      padding-left:10px;
      margin: 0px 5px 40px;
      font-size:1.3em;
      float:left;
    }
   @keyframes navHover{
    from{}
    to{background-color:#223d93; color:white;}
   }

   @keyframes transformLogo{100%{transform: rotateY(360deg);}
  /* Hide the carousel text when the screen is less than 600 pixels wide */
  @media (max-width: 600px) {
    .carousel-caption {
      display: none; 
    }
  }
  </style>
</head>
<body>
<nav class="navbar navbar-inverse" style="background-color:white; border:0px solid #35b9d6;">
  <div class="container-fluid">
    <div class="navbar-header">
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#myNavbar">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>                        
      </button>
      <a class="navbar-brand" href="index.php"><img src="logo1.png" alt="car icon" width="25" height="25"></a>
    </div>
    <div class="collapse navbar-collapse" id="myNavbar">
      <ul class="nav navbar-nav">
        <li><a href="index.php" style="color:#223d93; font-weight:bold">HOME</a></li>
        <li><a href="about_me.php" style="color:#223d93; font-weight:bold">ABOUT ME</a></li>
        <li><a href="about_site.php" style="color:#223d93; font-weight:bold">ABOUT SITE</a></li>
        <li><a href="contact_us.php" style="color:#223d93; font-weight:bold">CONTACT US</a></li>
        <li style="font-size: 5px"> Total visit: <?php
          $file = "counter.txt";
          $json = json_decode(file_get_contents($file), true);

          echo $json['visited'];?><br> Today visit: <?php
          echo $json['today'];?></li>
      </ul>

      <ul class="nav navbar-nav navbar-right">
        <li><?php
        if(!isset($_SESSION['user_id'])){
          ?><a href="login.php" style="color:#223d93; font-weight:bold">LOGIN</a><?php
        }   
        else{
          ?><a href="logout.php" style="color:#223d93; font-weight:bold">LOGOUT</a><?php
        }
        ?></li>
      </ul>
    </div>
    <hr>
    <div class="myinfo">인적사항<ul>        
          <li>1992년 12월 5일생</li>
          <li>연세대학교 컴퓨터과학과</li>
          <li>서문에 살고있음</li></ul>
      </div>
      <div class="myinfo">취미
        <ul>
          <li>인터넷 프로그래밍</li>
          <li>운영체제</li>
          <li>컴퓨터 그래픽스</li>
        </ul>
      </div>
      <div style="clear:left">
        <form action="#" method="post" autocomplete="on" style="font-weight:bold; font-size:.8em; margin-left:100px">사이트 어떄?<br>
          <label>이름<input type="text" size="20" autofocus></label>
          <label>(익명<input type="checkbox" name="anonymous" value="anonymous">)</label><br>
          <label>좋아요<input type="radio" name="isgood" value="good"></label> 
          <label>매우좋아요<input type="radio" name="isgood" value="verygood"></label> 
          <label>너무좋아요<input type="radio" name="isgood" value="veryverygood" required></label><br>
          <p><label>Comment:<br>
            <textarea name="tellme" rows="4" cols="50" placeholder="다른 하고싶은 말"></textarea>
          </label></p>
          <input type="submit" value="Submit">
          <input type="reset" value="Clear">
        </form>
      </div>
  </div>
</nav>


<footer class="container-fluid text-center" style="text-align:left">
  <p><b>Yonsei University. Internet Programming&copy;</b></p>
  <span style="font-size:.85em;">CONTACT: 1599-1855, 02) 2123-5712</span>
</footer>

</body>
</html>
