<?php
define('PUBLIC_PATH',dirname(realpath(__FILE__)) . "/");
define('BASE_PATH',dirname(PUBLIC_PATH));
define('HW_PATH',BASE_PATH . "/homework/");
//echo BASE_PATH . "/";
if($_POST && isset($_POST["loadCodeFile"]) )
{
	$fd = 	BASE_PATH . "/" . $_POST["loadCodeFile"];	

	$handle = @fopen($fd, "r");
	$line_nums = "";
	$line_code = "";
	$ln = 0;
	$url = 'http://'.$_SERVER['HTTP_HOST'];
	$link = "<div class=\"col-sm-1 code-title\">link:</div><div class=\"col-sm-11 code-title\"><a href=\"". $url . "/" . $_POST["loadCodeFile"] ."\">" . $_POST["loadCodeFile"] . "</a></div>";

	if ($handle) {
	    while (($buffer = fgets($handle, 4096)) !== false) {
	        $line_code .= $buffer . "";
	        $line_nums .= ++$ln.".\n";
	    }
	    if (!feof($handle)) {
	        echo "Error: unexpected fgets() fail\n";
	    }
	    fclose($handle);

	    echo  $link . "<div class=\"col-sm-1 line-nums shadow\">" . $line_nums . "</div><div class=\"col-sm-11 line-code\">" . $line_code . "</div>";

	}

}