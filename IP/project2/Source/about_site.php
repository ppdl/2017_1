<?php session_start();?>

<!DOCTYPE html>
<?xml version="1.0" encoding="utf-8"?>
<html lang="en">
<head>
  <title>Bootstrap Example</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <link rel="stylesheet" href="login.css" type="text/css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
  <style>
    /* Remove the navbar's default margin-bottom and rounded borders */ 
    .navbar {
      margin-bottom: 0;
      border-radius: 0;
    }
    
    /* Add a gray background color and some padding to the footer */
    footer {
      background-color: #f2f2f2;
      padding: 25px;
    }
    a.navbar-brand img{
      animation: transformLogo;
      animation-duration: 2s;
      animation-iteration-count: infinite;
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
   div.aboutsite{
    height:500px;
    background-image:url('eco1.jpg');
    background-repeat: repeat;
   }
   div.aboutsite div{
      position: absolute;
      width: 350px;
      padding:70px 30px;
      margin: 0px 5px 40px;
      font-size:1.3em;
      box-shadow: 3px 3px 0px black;
      border-radius:10px;
      text-align: center;
      font-weight:bold;
      font-style:italic;
    }


   @keyframes navHover{
    from{}
    to{background:#223d93; color:white;}
   }

  /* Hide the carousel text when the screen is less than 600 pixels wide */
  @media (max-width: 600px) {
    .carousel-caption {
      display: none; 
    }
  }
  @media screen and (max-width: 600px){      
      div.aboutsite div:nth-child(1){
        background:linear-gradient(to right,#f58b84,white);
        z-index:1;
        position:relative;
        top:30px;
        left:30px;
      }
      div.aboutsite div:nth-child(2){
        background:linear-gradient(to right,#b16faf,white);
        z-index:2;
        position:relative;
        top:-50px;
        left:30px
      }
      div.aboutsite div:nth-child(3){
        background:linear-gradient(to right,#2d80c4,white);
        z-index:3;
        position:relative;
        top:-150px;
        left:30px;
      }
    }

  @media screen and (min-width: 601px) and (max-width:960px){      
      div.aboutsite div:nth-child(1){
        background:linear-gradient(to right,#f58b84,white);
        z-index:1;
        position:relative;
        top:30px;
        left:50px;
      }
      div.aboutsite div:nth-child(2){
        background:linear-gradient(to right,#b16faf,white);
        z-index:2;
        top:200px;
        left:150px
      }
      div.aboutsite div:nth-child(3){
        background:linear-gradient(to right,#2d80c4,white);
        z-index:3;
        top:350px;
        left:50px;
      }
    }

@media screen and (min-width:961px){
      div.aboutsite div:nth-child(1){
        background:linear-gradient(to right,#f58b84,white);
        z-index:1;
        position:relative;
        top:30px;
        left:50px;
      }
      div.aboutsite div:nth-child(2){
        background:linear-gradient(to right,#b16faf,white);
        z-index:2;
        top:200px;
        left:150px
      }
      div.aboutsite div:nth-child(3){
        background:linear-gradient(to right,#2d80c4,white);
        z-index:3;
        top:350px;
        left:250px;
      }
    }    
  @keyframes transformLogo{100%{transform: rotateY(360deg);}
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
  </div>
</nav>
<div class="aboutsite">
  <div>우리는 <br>친환경 자동차만을 취급합니다.</div>
  <div>배출가스, 미세먼지, 대기오염 이제 좀 줄여야 하지 않을까요?</div>
  <div>친환경 자동차, 우리의 아이들을 위한 선택입니다.</div>
</div>


<footer class="container-fluid text-center" style="text-align:left;">
  <p><b>Yonsei University. Internet Programming&copy;</b></p>
  <span style="font-size:.85em;">CONTACT: 1599-1855, 02) 2123-5712</span>
</footer>

</body>
</html>
