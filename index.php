<?php
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
<nav class="navbar navbar-inverse" role="navigation">
	<div class="navbar-brand"> <img src="images/utterm.png"> </div>
</nav>

<div class="col-sm-2 nav-side">
	<ul class="nav nav-pills nav-stacked">
		<li class="active" id="cs249"><a href="#">CS249</a></li>
		<li id="cs351"><a href="#">CS351</a></li>
		<li id="cs445"><a href="#">CS445</a></li>
		<li id="other"><a href="#">Other</a></li>
		<br>
		<br>
		<br>
		<br>
		<br>
		<br>
		<br><br><br><br><br><br><br><br><br><br>
	</ul>
</div>

<div class="col-sm-offset-1 col-sm-8">
	<div class="panel panel-default ">
		<div class="panel-heading"><h3>Homework</h3></div>
		<div class="panel-body">
			<div id="files" class="col-sm-3"></div>
			<div id="code" class="col-sm-9 code"></div>
		</div>
	</div>
</div>

<!--<div class="well well-lg">...</div> -->

</body>
<script>
$(document).ready(function(){
	var last = "cs249"

	loadPage(last)

	$('.panel-body').on('click','a',function(){
		var link = $(this).attr('link')
		$("#code").load(link, function(res) {
		    $("#code").append(res.replace(/\r\n/gi, "<br>"))
		})
	})

	$('.nav li').click(function(){
		$('#files').empty()
		$(this).addClass('active').siblings().removeClass('active')
		last = $(this).attr('id')

		loadPage($(this).attr('id'))
	})
})

</script>
<!--<link rel="stylesheet" href="//netdna.bootstrapcdn.com/font-awesome/4.0.0/css/font-awesome.css">-->
</html>