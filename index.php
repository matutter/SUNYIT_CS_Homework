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
<title>utterm@sunyit.edu</title>
</head>
<body>

<a class="sr-only" href="#content">Skip to main content</a>

<div id="no-js" style="width:100%; background-color:efefef; height:800px; position:fixed; top:52px;left:0px; z-index:999;" >
<script>$('#no-js').hide();</script>
Sorry! You need to run Javascript to view this page.
</div>

<header class="navbar navbar-static-top bs-docs-nav" role="banner">
	<div class="container">
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
				<li class="active" id="cs249"><a href="#">CS249</a></li>
				<li id="cs351"><a href="#">CS351</a></li>
				<li id="cs445"><a href="#">CS445</a></li>
				<li id="other"><a href="#">Other</a></li>
			</ul>
			<ul class="nav navbar-nav navbar-right">
				<li><a href="#" id="manage">Manage</a></li>
				<li><a href="#" id="back">Back</a></li>
				<li><a href="#" id="login" tabindex="8">Login</a></li>
				<li><a href="#">Help</a></li>
			</ul>
		</nav>
	</div>
</header>
<div class="sub-nav">
	<div class="container">
	    <div class="bs-header" id="content">
		    <div class="container">
		    	<div class="col-sm-5">
		    		<div class="alt-msg">
				        <h1 class="email"></h1>
				        <p></p>
					</div>
			    </div>
			    <div class="col-sm-6">
			    	<!-- empty right side -->
			    </div>
		    </div>
	    </div>
	</div>
</div>
<div class="nav-bot"></div>
<div class="login">
	<div class="col-sm-12">
	<div class="container">
		<form class="navbar-form navbar-right" id="login" action="" >
			<div class="form-group">
				<input type="text" class="form-control" placeholder="Username" id="login" name="uname" tabindex="9">
			</div>
			<div class="form-group">
				<input type="password" class="form-control" placeholder="Password" id="login" name="pwd" tabindex="10">
			</div>
			<a class="btn btn-default" id="login" tabindex="11">Login</a>
		</form>
	</div>
	</div>
</div>
<div class="col-sm-12" id="main">
	<div class="container">
		<div class="page-heading">
			<h3 id="title">Homework</h3>
			<button class="btn btn-default download">GetSource</button>
		</div>
	</div>

	<div class="container">
		<div id="files" class="col-sm-3 files"></div>
		
		<div id="code" class="col-sm-9 code" style="white-space:pre; tab-size:4;"></div>
		
	</div>
</div>

<div class="col-sm-12 console" id="console">
	<div class="mask"></div>
	<div class="container">
		<!--<div class="col-sm-3">
			<div class="page-heading">
				<h3> Console </h3>
			</div>

			<input type="text" class="form-control" placeholder="SITNET ID">
			<input type="password" class="form-control" placeholder="Password">
		</div>-->
	
		<div class="col-sm-8 col-sm-offset-2">
			<table class="table">
				<thead>
					<th colspan="10">Class Settings</th>
					<th> <small class="pull-right">Add classes</small> </th>
				</thead>
				<tbody>
					<tr>
						<td colspan="0">
							<button class="btn btn-success">Add Class</button>				
						</td>
						<td colspan="10">
							<input type="text" class="form-control" placeholder="Course">
						</td>
					</tr>
				</tbody>
			</table>

			<table class="table">
				<thead>
					<th colspan="10">Management</th>
  					<th><small class="pull-right">Edit details and security</small></th>
				</thead>
				<tbody>
					<tr>
						<td colspan="0">Show Banner</td>
						<td colspan="10"><button type="button" class="btn btn-primary" data-toggle="button" id="sb">On</button></td>
					</tr>
					<tr>
						<td colspan="0">Display name</td>
						<td colspan="10"><input type="text" class="form-control" placeholder="display name" id="dn"></td>
					</tr>
					<tr>
						<td colspan="0">Email</td>
						<td colspan="10"><input type="text" class="form-control" placeholder="email" id="em"></td>
					</tr>
					<tr>
						<td colspan="0">Email sub-text</td>
						<td colspan="10"><input type="text" class="form-control" placeholder="sub-text" id="st"></td>
					</tr>				
				</tbody>
			</table>			
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
