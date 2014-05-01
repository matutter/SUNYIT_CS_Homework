<?php
define('PUBLIC_PATH',dirname(realpath(__FILE__)) . "/");
define('BASE_PATH',dirname(PUBLIC_PATH));
define('HW_PATH',BASE_PATH . "/homework/");
//echo BASE_PATH . "/";
if($_POST && isset($_POST["loadCodeFile"]) )
{
	$fd = 	BASE_PATH . "/" . $_POST["loadCodeFile"];	

	$stupid_fang_fix = "";
	$handle = @fopen($fd, "r");
	$line_nums = "";
	$line_code = "";
	$ln = 0;
	$url = 'http://'.$_SERVER['HTTP_HOST'];
	if( strpos($url,"sunyit") !== false)
	{
		$stupid_fang_fix = "/~utterm";
	}
	$link = "<div class=\"col-sm-12 code-title\">View Raw: <a href=\"". $url . $stupid_fang_fix . "/" . $_POST["loadCodeFile"] ."\">" . $_POST["loadCodeFile"] . "</a> </div>";

	if ($handle) {
	    while (($buffer = fgets($handle, 4096)) !== false) {
	    	$buffer = str_replace("<", "&lt;", $buffer);
	        $line_code .= $buffer . "";
	        $line_nums .= ++$ln."\n";
	    }
	    if (!feof($handle)) {
	        echo "Error: unexpected fgets() fail\n";
	    }
	    fclose($handle);

	    $linum = "<div class=\"col-sm-1 line-nums shadow\">" . $line_nums . "</div>";
	    $body = "<div class=\"col-sm-11 line-code shadow\">" . $line_code . "</div>";
	    echo  $link . $linum . $body;

	}

}