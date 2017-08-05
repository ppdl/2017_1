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
  <script type="text/javascript" src="managementCheck.js"></script>
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

   th, td {
    padding: 3px;
    text-align: left;
    }
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
      <a class="navbar-brand" href="index.html"><img src="logo1.png" alt="car icon" width="25" height="25"></a>
    </div>
    <div class="collapse navbar-collapse" id="myNavbar">
      <ul class="nav navbar-nav">
        <!--
        <li><a href="index.html" style="color:#223d93; font-weight:bold">HOME</a></li>
        -->
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
        <li><a href="login.php" style="color:#223d93; font-weight:bold"><span class="glyphicon glyphicon-log-in"></span> Login</a></li>
      </ul>
    </div>
    <hr>
  </div>
</nav>
<div class="container" style="left:30vw; width:70vw; padding:30px;">
  <form id="management" method="POST" action="manager.php">
  <table>
	<tr>
      <td>아이디: </td>
      <td><input id="ID" name="ID" type="text" onblur="isExist();checkall()" autofocus></td>
      <td><span id="idcheck"></span></td>

    </tr>
    <tr>
		  <td>변경 비밀번호: </td>
      <td><input id="PWD" name="PWD" type="password" onblur="checkpwd();checkall()"></td>
      <td><span id="passwordcheck"></span></td>
    </tr>
    <tr>
      <td>비밀번호 확인: </td>
      <td><input id="PWDcheck" name="PWDcheck" type="password" onblur="pwdcheck();checkall()"></td>
      <td><span id="checkpassword"></span></td>
    </tr>
    <tr>
      <td></td>
      <td><input id = "btn" type="submit" value="변경" disabled="true"></td>
    </tr>
    </table>
	</form>
</div>

<script>
  $('#IDlist').html("hello");
  $.ajax({
    url: './visitCounter.php',
    dataType: 'json',
    success: function(data){
      $('#IDlist').html("bye");
    }
  })
</script>


<footer class="container-fluid text-center" style="text-align:left;">
  <p><b>Yonsei University. Internet Programming&copy;</b></p>
  <span style="font-size:.85em;">CONTACT: 1599-1855, 02) 2123-5712</span>
</footer>

</body>
</html>
