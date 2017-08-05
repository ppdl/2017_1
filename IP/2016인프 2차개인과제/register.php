<html>
<head>
  <title>Making New Account</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
  <!--<script src="register.js"></script>-->
</head>
<!--http://www.w3schools.com/bootstrap/tryit.asp?filename=trybs_form_basic&stacked=h이용-->
<body>

<div class="container">
  <h2>Making New Account!!</h2>
  <form method = "post" action = "checkAndStore.php">
    <div class="form-group">
      <label for="text">ID:</label>
      <input type="text" class="form-control" name="id" placeholder="Enter ID" required />
    </div>
    <div class="form-group">
      <label for="pwd">Password:</label>
      <input type="password" class="form-control" name="pwd" placeholder="Enter password" required />
    </div>
    <div class="form-group">
      <label for="date">BirthDay:(입력예시 : 2016-06-13)</label>
      <input type="text" class="form-control" name="birth" placeholder="Your Birthday">
    </div>
    <div class="form-group">
      <label for="tel">PhoneNumber:</label>
      <input type="tel" class="form-control" name="phoneNum" placeholder="###-####-####"
        pattern = "\d{3}-\d{4}-\d{4}">
      <!--전화번호 패턴 제시-->
    </div>
    <div class="form-group">
      <label for="text">Address:</label>
      <input type="text" class="form-control" name="addr" placeholder="Your Address">
      <!--주소의 패턴제시-->
    </div>
     <button type="submit" class="btn btn-default">New account!</button>
  </form>
</div>

</body>
</html>