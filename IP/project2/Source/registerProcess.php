<?php
$doc = new DOMDocument('1.0', 'UTF-8');
$doc->load('account.xml');
$doc->formatOutput = true;

$id = $doc->createElement('id', $_POST['ID']);
$password = $doc->createElement('password', $_POST['PWD']);
$birthday = $doc->createElement('birthday', $_POST['BDAY']);
$phone = $doc->createElement('phone', $_POST['PHONE']);
$email = $doc->createElement('email', $_POST['EMAIL']);
$visit = $doc->createElement('visit', 0);

$newAccount = $doc->createElement("account");
$newAccount -> appendChild($id);
$newAccount -> appendChild($password);
$newAccount -> appendChild($birthday);
$newAccount -> appendChild($phone);
$newAccount -> appendChild($email);
$newAccount -> appendChild($visit);

$database = $doc->getElementsByTagName("database")[0];
$database->appendChild($newAccount);

$doc->save('account.xml');

header('Location: login.php');
?>