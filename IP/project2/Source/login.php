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

   @keyframes navHover{
    from{}
    to{background:#223d93; color:white;}
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
        <li><a href="#" style="color:#223d93; font-weight:bold"><span class="glyphicon glyphicon-log-in"></span> Login</a></li>
      </ul>
    </div>
  </div>
</nav>

<form class="log" method="POST" action="login_check.php">
  <fieldset name="log1">
  <legend>LOGIN</legend>
  <div style="float:left">
    <label>&nbsp;&nbsp;ID  <input type="text" size="15" name='id' autofocus></label><br>
    <label>PW <input type="password" size="15" name='password'></label>
    </div>
  <input type="Submit" value="LOGIN" style="height:56px"><br>
  <div style="clear:left; margin-left:35px"><a href="register.php">Register</a></div>
  </fieldset>
</form>


<footer class="container-fluid text-center" style="text-align:left">
  <p><b>Yonsei University. Internet Programming&copy;</b></p>
  <span style="font-size:.85em;">CONTACT: 1599-1855, 02) 2123-5712</span>
</footer>

</body>
</html>
