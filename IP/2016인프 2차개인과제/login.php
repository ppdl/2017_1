<html>
<head>
  <title>Login to my web page</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
</head>
<!--http://www.w3schools.com/bootstrap/tryit.asp?filename=trybs_form_basic&stacked=h이용-->
<body>

<div class="container">
  <h2>Login to play in my web page!</h2>
  <form method = "post" action = "login_ok.php">
    <div class="form-group">
      <label for="text">ID:</label>
      <input type="text" class="form-control" name="id" placeholder="Enter ID" required />
    </div>
    <div class="form-group">
      <label for="pwd">Password:</label>
      <input type="password" class="form-control" name="pwd" placeholder="Enter password" required />
    </div>
    <button type="submit" class="btn btn-default">Login</button>
  </form>
    
  <form method = "post" action = "register.php">
    <button type="submit" class="btn btn-default">New Account!</button>
  </form>
</div>

</body>
</html>