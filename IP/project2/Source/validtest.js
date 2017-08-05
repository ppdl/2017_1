var valid_ID;
var valid_PWD;
var valid_PWDcheck;
var valid_BDAY;
var valid_PHONE;
var valid_EMAIL;
var count = 0;

// enable submit button if all validation is satisfied
function checkall(){
	if(valid_ID && valid_PWD && valid_PWDcheck && valid_BDAY && valid_PHONE && valid_EMAIL){
		document.getElementById("btn").disabled = false;
	}
	else{
		document.getElementById("btn").disabled = true;	
	}
}

// ID validation
// 1) check ID is already exist or not in isExist() function
// 2) if not exist, call checkid() function to check the condition of
// 	  specification
function isExist(){
	var str = document.getElementById("ID").value;

	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
	    if (this.readyState == 4 && this.status == 200) {
	        checkIsExist(this);
	    }
	};
	xhttp.open("GET", "account.xml", true);
	xhttp.send();

	function checkIsExist(xml) {
		var xmlDoc = xml.responseXML;
		var ids = xmlDoc.getElementsByTagName("id");
		
		// check all account.xml file's <id> node
		for(i = 0; i<ids.length; i++){
			if(ids[i].childNodes[0].nodeValue == str){
				valid_ID = false;
				document.getElementById("idcheck").innerHTML = "존재하는 아이디입니다!";
				document.getElementById("idcheck").style.color = "red";
				return;
			}
		}
	}
	checkid(str);
}

function checkid(str){
	// if textbox loses focus without input, do not print message
	if(str == ""){
		document.getElementById("idcheck").innerHTML = "";
		return;
	}

	// valid test
	if(str.length >= 6 && str.length <= 10){
		if(str.match(/[^\w]/g) == null && str.match(/[A-Z]/g) != null && str.match(/[0-9]/g) != null)
			valid_ID = true;
	}
	else
		valid_ID = false;

	if(valid_ID == true){
		document.getElementById("idcheck").innerHTML = "사용가능한 아이이디입니다.";
		document.getElementById("idcheck").style.color = "blue";
	} else{
		document.getElementById("idcheck").innerHTML = "유효하지않은 아이디입니다!";
		document.getElementById("idcheck").style.color = "red";
	}
}

// check password if input satisfies given condition.
function checkpwd(){
	var str = document.getElementById("PWD").value;
	// character counter. Count how many specific characters have come out.
	var ascii = new Array(128).fill(0);

	// if lose focus with no input, do not print message
	if(str == ""){
		document.getElementById("passwordcheck").innerHTML = "";
		return;
	}
	// least password length: 4
	if(str.length < 4 || str.length >10){
		valid_PWD = false;
	}
	// check 3 or more consecutive same number of character
	else if(str.match(/([a-z\d])\1\1/g) != null){
		valid_PWD = false;
	}
	// check specification condition
	else{
		// find 3 or more identical characeters
		for(i=0; i<str.length; i++){
			var index = str[i].charCodeAt(0);
			ascii[index] ++;
			if(ascii[index] >= 3){
				valid_PWD = false;
				break;
			}
		}
		// check 3 or more consecutive number or character
		// compare neighboring characters' ascii code. if it's difference is 1 or -1, that are consecutive.
		if(valid_PWD != false){
			for(i=0; i<str.length - 2; i++){
				if((str[i].charCodeAt(0) - str[i+1].charCodeAt(0) == 1 && str[i+1].charCodeAt(0) - str[i+2].charCodeAt(0) == 1) || (str[i].charCodeAt(0) - str[i+1].charCodeAt(0) == -1) && str[i+1].charCodeAt(0) - str[i+2].charCodeAt(0) == -1){
					valid_PWD = false;
					break;
				}
				valid_PWD = true;
			}
		}
	}

	if(valid_PWD == true){
		document.getElementById("passwordcheck").innerHTML = "사용가능한 비밀번호입니다.";
		document.getElementById("passwordcheck").style.color = "blue";
	} else{
		if(str.length > 10)
			document.getElementById("passwordcheck").innerHTML = "조금 짧은 비밀번호로 설정해 주세요!";
		else			
			document.getElementById("passwordcheck").innerHTML = "더 복잡한 비밀번호로 설정해 주세요!";

		document.getElementById("passwordcheck").style.color = "red";
	}
}

// make sure that user enter the same password.
// verify that str1 and str2 are equal 
function pwdcheck(){
	var str1 = document.getElementById("PWDcheck").value;
	var str2 = document.getElementById("PWD").value;

	if(str1 == str2){
		valid_PWDcheck = true;
		document.getElementById("checkpassword").innerHTML = "비밀번호 확인.";
		document.getElementById("checkpassword").style.color = "blue";
	} else{
		valid_PWDcheck = false;
		document.getElementById("checkpassword").innerHTML = "비밀번호 가 일치하지 않습니다.";
		document.getElementById("checkpassword").style.color = "red";
	}
}

// check birthday
// check for a valid day-month pair
function checkbdy(){
	var str = document.getElementById("BDAY").value;
	// if lose focus with no input, do not print message
	if(str == ""){
		document.getElementById("birthcheck").innerHTML = "";
		return;
	}
	// check if the input has length 6
	if(str.match(/\d{6}/g) == null) valid_BDAY = false;
	else {
		
		var year = str[0] + str[1];
		var month = parseInt(str[2] + str[3]);
		var day = str[4] + str[5];
		valid_BDAY = true;

		// month-day validation
		switch(month){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if(day > 31) valid_BDAY = false;
				else valid_BDAY = true;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if(day > 30) valid_BDAY = false;
				else valid_BDAY = true;
				break;
			case 2:
				if(day > 29) valid_BDAY = false;
				else valid_BDAY = true;
				break;
			default:
				valid_BDAY = false;
				break;
		}
	}

	if(valid_BDAY== true){
		document.getElementById("birthcheck").innerHTML = "유효한 생년월일입니다.";
		document.getElementById("birthcheck").style.color = "blue";
	} else{
		document.getElementById("birthcheck").innerHTML = "유효하지않은 생년월일입니다!";
		document.getElementById("birthcheck").style.color = "red";
	}
}

// check for a valid phone input
function checkphone(){
	var str = document.getElementById("PHONE").value;
	// if lose focus with no input, do not print message
	if(str == ""){
		document.getElementById("phonecheck").innerHTML = "";
		return;
	}

	if(str.match(/^01[016789]-\d{4}-\d{4}$/g) == null) valid_PHONE = false;
	else valid_PHONE = true;

	if(valid_PHONE== true){
		document.getElementById("phonecheck").innerHTML = "유효한 번호입니다.";
		document.getElementById("phonecheck").style.color = "blue";
	} else{
		document.getElementById("phonecheck").innerHTML = "유효하지않은 번호입니다!";
		document.getElementById("phonecheck").style.color = "red";
	}
}

// check for a valid email input
function checkemail(){
	var str = document.getElementById("EMAIL").value;
	// if lose focus without input, do not print message
	if(str == ""){
		document.getElementById("emailcheck").innerHTML = "";
		return;
	}
	if(str.match(/.+@\w+\.\w+/g) == null) valid_EMAIL = false;
	else valid_EMAIL = true;

	if(valid_EMAIL== true){
		document.getElementById("emailcheck").innerHTML = "유효한 이메일입니다.";
		document.getElementById("emailcheck").style.color = "blue";
	} else{
		document.getElementById("emailcheck").innerHTML = "유효하지않은 이메일입니다!";
		document.getElementById("emailcheck").style.color = "red";
	}
}