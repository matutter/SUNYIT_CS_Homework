<?php
define('PUBLIC_PATH',dirname(realpath(__FILE__)) . "/");
define('BASE_PATH',dirname(PUBLIC_PATH));
define('HW_PATH',BASE_PATH . "//homework/");
$res = "";
if($_POST && isset($_POST["loadPage"]))
{
	$log_directory = HW_PATH . $_POST["loadPage"];
	if (is_dir($log_directory)) {
		if ($handle = opendir($log_directory)) {
			while(($file = readdir($handle)) !== FALSE)
				if($file == "." || $file == ".." || $file == ".gitignore"); else
				$res .= $file.",";
			closedir($handle);
		}
		$res = rtrim($res,",");
	    echo $res;
	}
	else
		echo $log_directory . " not found.";
}
//echo $_SERVER['SERVER_SOFTWARE'];  // <-- is the OS the server runs on