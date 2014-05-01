<?php
define('PUBLIC_PATH',dirname(realpath(__FILE__)) . "/");
define('BASE_PATH',dirname(PUBLIC_PATH));
define('HW_PATH',BASE_PATH . "//homework/");
$res= "";
$i 	= 0;
if($_POST && isset($_POST["loadPage"]))
{
	$log_directory = HW_PATH . $_POST["loadPage"];
	if (is_dir($log_directory)) {
		if ($handle = opendir($log_directory)) {
			while(($file = readdir($handle)) !== FALSE)
				if($file == "." || $file == ".." || preg_match("/\.git/",$file) || $file == ".htaccess" || !preg_match("/\./i",$file) || preg_match("/\.out/i",$file) ); else
				//$res .= $file.",";
			$res[$i++] = $file;
			closedir($handle);
		}
		sort($res);
		$res = implode(",",$res);
		$res = rtrim($res,",");
		if($i == 0)
		{
			echo "Empty";
		}
		else
		    echo $res;
	}
	else
		echo $log_directory . " not found.";
}
//echo $_SERVER['SERVER_SOFTWARE'];  // <-- is the OS the server runs on