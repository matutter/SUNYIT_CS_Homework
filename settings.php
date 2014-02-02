<?php
  /*****************\\
 // secret passwords \\
//     don't share    \\
\\____________________//
*///				\\\*

$username = "mat";
$password = "mat";

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
	$init = array(
		"sb" => "0",									//0 to hide banner, 1 to show
		"dn" => "Mat Utter",							//display name
		"em" => "utterm@sunyit.edu",					//Email
		"st" => "See my <a href=\"\">Github</a>",				//Subtext underneath email
		"li" => "http://www.github.com/matutter",		//the Href of a <li></li> in the subtext
	);
	echo json_encode($init);
}
//echo "I should be secret";