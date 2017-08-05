<?php
	session_start();
	require 'naverOAuth.php';

	$nid_ClientID = 'ohwnLHK2JIsECNGfSEAv';
	$nid_ClientSecret = 'Cp5EHzTxv_';
	$nid_RedirectURL = 	'http://127.0.0.1/toiletGo/php/nick.php';

	$request = new OAuthRequest( $nid_ClientID, $nid_ClientSecret, $nid_RedirectURL );
	$request -> call_accesstoken();
	$request -> get_user_profile();

	if($_SESSION['nick'] == true) {
    	header("location:http://localhost/toiletGo");
    	exit();		
	} 
	else {
		header("location:http://127.0.0.1/toiletGo/php/nickInput.php");	
		exit();
	}
?>

