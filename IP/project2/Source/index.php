<?php 
session_start();
?>

<!DOCTYPE html>
<?xml version="1.0" encoding="utf-8"?>
<html lang="en">
<head>
  <title>youngjae</title>
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
  div.pic{
    float:left;
    width:40%;
    height:10%;
    transition: width 2s, height 2s;
  }
  div.pic:hover{
    width: 50%;
    height:20%;
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
        <?php if($_SESSION['user_id'] == 'admin'){?>
        <li><a href="management.php" style="color:#d43a3a; font-weight:bold">MANAGEMENT</a></li>
        <?php }?>
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

<div id="myCarousel" class="carousel slide" data-ride="carousel">
    <!-- Indicators -->
    <ol class="carousel-indicators">
      <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
      <li data-target="#myCarousel" data-slide-to="1"></li>
    </ol>

    <!-- Wrapper for slides -->
    <div class="carousel-inner" role="listbox">
      <div class="item active">
        <a href="#"><img src="ct200h_1.jpg" alt="Image" width="100" height="30"></a>
        <div class="carousel-caption">
          <h3>40,000,000원~</h3>
        </div>      
      </div>

      <div class="item">
        <a href="#"><img src="ioniq1.jpg" alt="Image"></a>
        <div class="carousel-caption">
          <h4 style="text-decoration:line-through; color:red">21,900,000원</h4>
          <h3>21,890,000원~</h3>
        </div>
      </div>
    </div>

    <!-- Left and right controls -->
    <a class="left carousel-control" href="#myCarousel" role="button" data-slide="prev">
      <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
      <span class="sr-only">Previous</span>
    </a>
    <a class="right carousel-control" href="#myCarousel" role="button" data-slide="next">
      <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
      <span class="sr-only">Next</span>
    </a>
</div>
  
<div class="container text-center">    
  <h3 style="line-height:1.5em; font-family:'Macondo', cursive; font-size:1.2em; font-weight:bold; font-style:italic; text-shadow:10px 12px 3px blue">ECO WORLD</h3><br>
  <div class="row">
      <div style="width: 80%; height:300px; margin:auto; overflow:hidden">
        <div class="pic">
          <img src="hybrid2.jpg" class="img-responsive" style="width:100%" alt="Image">
        </div>
        <div class="pic"> 
          <img src="hybrid1.jpg" class="img-responsive" style="width:100%" alt="Image">
        </div>
      </div>
  </div>
</div><br>

<footer class="container-fluid text-center" style="text-align:left">
  <p><b>Yonsei University. Internet Programming&copy;</b></p>
  <span style="font-size:.85em;">CONTACT: 1599-1855, 02) 2123-5712</span>
</footer>

</body>

<?php
if(!isset($_SESSION['user_id'])){
  ?><script>
      alert("로그인이 필요합니다.");
      window.location = "login.php";
    </script><?php
}
?>

</html>
