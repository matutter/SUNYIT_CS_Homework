<?php
  /*****************\\
 // secret passwords \\
//     don't share    \\
\\____________________//
*///				\\\*
define('UserName',"mat");
define('PassWord',"mat");
define('ShowBanner',"0");
define('DisplayName',"Mat Utter");
define('Email',"utterm@sunyit.edu");
define('SubText','See my <a href="http://www.github.com/matutter">Github</a>');

if( $_POST && isset($_POST["login"]) ) {
	$res = str_replace("uname=","",$_POST["login"]);
	$res = str_replace("&pword=","",$res);
	$res = str_replace("\"","",$res);
	$res = explode("&", $res);
	
	if($res[0]==UserName && $res[0]==PassWord)
	{
		session_start();
		$_SESSION['status'] = 'auth';
		echo 1;
	}
	else
	{
		$_SESSION['status'] = 'NoAUTH';
		echo 0;
	}
}
if( $_POST && isset($_POST["out"]) ) {
	session_start();
	$_SESSION['auth'] == 0;
	session_destroy();
}

if($_POST && isset($_POST["init"])) {
	$init = array(
		"sb" => ShowBanner,	//0 to hide banner, 1 to show
		"dn" => DisplayName,	//display name
		"em" => Email,	//Email
		"st" => SubText,	//Subtext underneath email
	);
	echo json_encode($init);
}