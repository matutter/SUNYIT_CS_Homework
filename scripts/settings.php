<?php
  /*****************\\
 // secret passwords \\
//     don't share    \\
\\____________________//
*///				\\\*

	$ini = file_get_contents('user.ini', true);
	$ini = preg_replace("/#.*#/i","",$ini);
	$ini = explode("\r\n", $ini);
	$username = $ini[0];
	$password = $ini[1];
	$init = array(
		"sb" => $ini[2],	//0 to hide banner, 1 to show
		"dn" => $ini[3],	//display name
		"em" => $ini[4],	//Email
		"st" => $ini[5],	//Subtext underneath email
	);

if( $_POST && isset($_POST["login"]) ) {
	$res = str_replace("uname=","",$_POST["login"]);
	$res = str_replace("&pword=","",$res);
	$res = str_replace("\"","",$res);
	$res = explode("&", $res);
	
	if($res[0]==$username && $res[0]==$password)
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

	echo json_encode($init);
}
//echo "I should be secret";