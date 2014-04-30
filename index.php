<?php
session_start();
if(isset($_SESSION["status"])) {
if($_SESSION["status"] == "auth") {
	echo "<script> var log = 1; </script>";
}
else
	echo "<script> var log = 0; </script>";
} else echo "<script> var log = 0; </script>";
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN""http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="icon" href="images/favicon.ico">

<link rel="stylesheet" href="css/bootstrap.min.css"/>
<link rel="stylesheet" href="css/main.css"/>
<!--[if 1t IE 7]>
<script type="text/javascript" src="js/DD_belatedPNG_0.0.7a-min.js">
<![endif]-->
<script src="scripts/jquery-1.11.0.min.js"></script>
<script src="scripts/bootstrap.min.js"></script>
<script src="scripts/main.js"></script>

<script src="https://google-code-prettify.googlecode.com/svn/loader/run_prettify.js"></script>

<title>utterm@sunyit.edu</title>
<!--<author style="background-color:#cb4032; text-align:center; text-transform:uppercase; width:100%;"><a style="color:black; text-decoration:none; width:100%;" href="homework">for cs351 just view all assignments here </a></author>-->
</head>
<body>

<a class="sr-only" href="#content">Skip to main content</a>

<div id="no-js" style="width:100%; background-color:efefef; height:800px; position:fixed; top:52px;left:0px; z-index:999;" >
<script>$('#no-js').hide();</script>
Sorry! You need to run Javascript to view this page.
</div>

<header class="navbar navbar-static-top bs-docs-nav" role="banner">
	<div class="">
		<div class="navbar-header">
			<button class="navbar-toggle" type="button" data-toggle="collapse" data-target=".bs-navbar-collapse">
			<span class="sr-only">Toggle navigation</span>
			<span class="icon-bar"></span>
			<span class="icon-bar"></span>
			<span class="icon-bar"></span>
			</button>
			<a href="" class="navbar-brand display-name"></a>
		</div>
		<nav class="collapse navbar-collapse bs-navbar-collapse" role="navigation">
			<ul class="nav navbar-nav major-nav">
				<li class="active" id="cs249"><a href="#cs249">CS249</a></li>
				<li id="cs351"><a href="#cs351">CS351</a></li>
				<li id="cs445"><a href="#cs445">CS445</a></li>
				<li id="other"><a href="#other">Other</a></li>
			</ul>
			<ul class="nav navbar-nav navbar-right">
				<li><a href="http://www.github.com/matutter">See my Git</a></li>
			</ul>
		</nav>
	</div>
</header>
<div class="nav-bot">
	<div class="page-heading">
		<h3 id="title">Homework</h3>
	</div>
</div>
<div class="col-sm-12" id="main">
	<div class="">
		<div class="col-sm-3">
			
		<div id="files" class="files">
		</div>
			<blockquote style="margin-left:-15px;">
			<table class="table">
			<th colspan="2">Email</th>
			<tr><td colspan="2">utterm@sunyit.edu</td></tr>
			<tr><td colspan="2">matutter4@gmail.com</td></tr>
			<th colspan="2"><strong>Tutoring Hours</strong> <tiny>ends 5/8</tiny></th>
			<tr><td>mon:</td><td> 12-4p</td></tr>
			<tr><td>tue:</td><td> 10-12a</td></tr>
			<tr><td>wed:</td><td> 12-4p</td></tr>
			<tr><td>thr:</td><td> 10-12a</td></tr>
			</table>
			</blockquote>
		</div>
		<div id="code" class="col-sm-9 code " style="white-space:pre; tab-size:2;"><div class="col-sm-12 code-title">View Raw:</div>
<empty>Nothing loaded</empty>
		</div>
	</div>
</div>

<div>
<!--<div class="well well-lg">...</div> -->
<script>
	
$(document).ready(function() {
	initUser(log);
})

</script>

</body>
<script src="scripts/jquery-ui-1.10.4.custom.min.js"></script>
<!--<link rel="stylesheet" href="//netdna.bootstrapcdn.com/font-awesome/4.0.0/css/font-awesome.css">-->
</html>
