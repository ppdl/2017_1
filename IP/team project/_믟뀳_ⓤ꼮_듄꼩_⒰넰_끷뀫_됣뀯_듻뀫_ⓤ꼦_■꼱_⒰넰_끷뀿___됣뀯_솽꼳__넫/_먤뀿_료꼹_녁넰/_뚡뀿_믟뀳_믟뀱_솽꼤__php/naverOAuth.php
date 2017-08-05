<?php
   	define( 'NAVER_OAUTH_AUTHORIZE_URL', 'https://nid.naver.com/oauth2.0/authorize' );
	define( 'NAVER_OAUTH_TOKEN_URL', 'https://nid.naver.com/oauth2.0/token' );
	define( 'NAVER_GET_USERINFO_URL', 'https://apis.naver.com/nidlogin/nid/getUserProfile.xml');
	class OAuthRequest{
		private $client_id;
		private $client_secret;
		private $redirect_url;
		private $state;
		private $session;
		private $authorize_url = NAVER_OAUTH_AUTHORIZE_URL;
		private $accesstoken_url = NAVER_OAUTH_TOKEN_URL;
		private $code;
		private $tokenArr; 
		private $userInfo;

		function __construct( $client_id, $client_secret, $redirect_url) {
			$this -> client_id = $client_id;
			$this -> client_secret = $client_secret;
			$this -> redirect_url = $redirect_url;
			if(!isset($_SESSION)) {
				session_start();
			}
		}
		private function generate_state(){
			$mt = microtime();
			$rand = mt_rand();
			$this -> state = md5( $mt . $rand );
			$_SESSION['sta'] = true;
		}
		public function set_state(){
			$this -> generate_state();
			$_SESSION['state'] = $this -> state;
		}
		private function get_code(){
			$this -> code = $_GET['code'];
		}
		private function get_state(){
			$this -> state = $_SESSION['state'];
			return $this -> state;
		}
		public function request_auth(){
			header('Location: '. $this -> get_request_url() );
		}
		public function get_request_url(){
			return $this -> authorize_url . '?response_type=code&client_id=' . $this -> client_id . '&state=' . $this -> state . '&redirect_url=' . urlencode($this -> redirect_url); 
		}
		public function get_accesstoken_url(){
			return $this -> accesstoken_url . '?grant_type=authorization_code&client_id=' . $this -> client_id . '&client_secret=' . $this -> client_secret . '&code=' . $this -> code . '&state= ' . $this -> state;
		}
		public function call_accesstoken(){
			$this -> get_code();
			$this -> get_state();

			$ch = curl_init();
			curl_setopt($ch, CURLOPT_URL, $this -> get_accesstoken_url() );
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, true );
			curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false );
			curl_setopt($ch, CURLOPT_COOKIE, '' );
			curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 300);
			$g = curl_exec($ch);
			curl_close($ch);
			$data = json_decode($g, true);
			$this -> tokenArr = array(
				 'Authorization: '.$data['token_type'].' '.$data['access_token']
			);
		}
		public function get_user_profile(){
			$ch = curl_init();
			curl_setopt($ch, CURLOPT_URL, NAVER_GET_USERINFO_URL );
			curl_setopt($ch, CURLOPT_HTTPHEADER, $this -> tokenArr );
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, true );
			curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false );
			curl_setopt($ch, CURLOPT_COOKIE, '' );
			curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 300);
			$g = curl_exec($ch);
			curl_close($ch);
			$xml = simplexml_load_string($g);
			$this -> userInfo = array(
				'userID' => (string)$xml -> response -> email ,
				'nickname' => (string)$xml -> response -> nickname,
				'age' => (string)$xml -> response -> age,
				'birth' => (string)$xml -> response -> birthday,
				'gender' => (string)$xml -> response -> gender,
				'profImg' => (string)$xml -> response -> profile_image
			);
			if(isset($_SESSION['sta']) && !isset($_SESSION['facebook'])) {
				$fbuserid = $this -> userInfo['userID'];  
				$fbusername = $this -> userInfo['nickname'];  
				$fbaccess = NULL;
				$host = 'localhost';
				$user = 'root';
				$pw = 'apmsetup';
				$dbName = 'toiletgo';
				$mysqli = new mysqli($host, $user, $pw, $dbName);

				$curDate = date("Y-n-j");
				$query = "SELECT * FROM member where memberid='".$fbuserid."'";  
				$result = $mysqli->query($query);  
				  
				$result_count = $result->num_rows; 
				$_SESSION['nick'] = true;

				if($result_count<1) {  
				    //facebook으로 로그인한 아이디가 DB에 없을 경우.  
				    $query2 = "INSERT INTO member VALUES ('', '".$fbuserid."', '".iconv("utf-8","euc-kr", $fbusername)."', 0, 0, '".$curDate."')";

				    $result2 = $mysqli->query($query2);  
				      
				    $query = "SELECT * FROM member where memberid='".$fbuserid."'";  
				    $result = $mysqli->query($query);
				    $_SESSION['nick'] = false;
				}  

				$row = mysqli_fetch_assoc($result);

				if($row['lastDate' != $curDate]) {
					$query3 = "UPDATE member set visite = visite + 1 Where memberid='".$fbuserid."'";
					$result2 = $mysqli->query($query3);
				}

				$_SESSION['no'] = $row['no'];  
				$_SESSION['id'] = $row['memberid'];  
				//$_SESSION['name'] = iconv("euc-kr","utf-8", $row['name']);  
				$_SESSION['name'] = $row['name'];
				$_SESSION['score'] = $row['score'];  
				$_SESSION['facebook'] = true;  
				$_SESSION['fbtoken'] = $fbaccess; 
			}
		}
		public function get_userInfo(){
			return $this -> userInfo;
		}
		public function get_userID(){
			return $this -> userInfo['userID'];
		}
		public function get_nickname(){
			return $this -> userInfo['nickname'];
		}
		public function get_age(){
			return $this -> userInfo['age'];
		}
		public function get_birth(){
			return $this -> userInfo['birth'];
		}
		public function get_gender(){
			return $this -> userInfo['gender'];
		}
		public function get_profImg(){
			return $this -> userInfo['profImg'];
		}
	}
?>