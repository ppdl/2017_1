var valid_ID;
var valid_PWD;
var valid_PWDcheck;
var count = 0;

function checkall(){
	if(valid_ID && valid_PWD && valid_PWDcheck){
		document.getElementById("btn").disabled = false;
	}
	else{
		document.getElementById("btn").disabled = true;	
	}
}

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
		
		for(i = 0; i<ids.length; i++){
			if(ids[i].childNodes[0].nodeValue == str){
				valid_ID = true;
				document.getElementById("idcheck").innerHTML = "존재하는 아이디입니다!";
				document.getElementById("idcheck").style.color = "blue";
				return;
			} else{
				valid_ID = false;
				document.getElementById("idcheck").innerHTML = "존재하지 않는 아이디입니다!";
				document.getElementById("idcheck").style.color = "red";
			}
		}
	}

	checkid(str);
}

function checkpwd(){
	var str = document.getElementById("PWD").value;
	// if lose focus with no input, do not print message
	if(str == ""){
		document.getElementById("passwordcheck").innerHTML = "";
		return;
	}
	//least password length: 4
	if(str.length < 4){
		valid_PWD = false;
	}
	//check 3 or more consecutive same number of character
	else if(str.match(/([a-z\d])\1\1/g) != null){
		valid_PWD = false;
	}
	//check 3 or more consecutive number or character
	else{
		//compare neighboring characters' ascii code. if it's difference is 1 or -1, that are consecutive.
		for(i=0; i<str.length - 2; i++){
			if((str[i].charCodeAt(0) - str[i+1].charCodeAt(0) == 1 && str[i+1].charCodeAt(0) - str[i+2].charCodeAt(0) == 1) || (str[i].charCodeAt(0) - str[i+1].charCodeAt(0) == -1) && str[i+1].charCodeAt(0) - str[i+2].charCodeAt(0) == -1){
				valid_PWD = false;
				break;
			}
			valid_PWD = true;
		}
	}
	if(valid_PWD == true){
		document.getElementById("passwordcheck").innerHTML = "사용가능한 비밀번호입니다.";
		document.getElementById("passwordcheck").style.color = "blue";
	} else{
		document.getElementById("passwordcheck").innerHTML = "더 복잡한 비밀번호로 설정해 주세요!";
		document.getElementById("passwordcheck").style.color = "red";
	}
}

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
