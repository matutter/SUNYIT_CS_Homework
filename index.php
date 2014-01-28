<?php
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN""http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="icon" href="../images/favicon.ico">
<link rel="stylesheet" href="//netdna.bootstrapcdn.com/font-awesome/4.0.0/css/font-awesome.css">
<link rel="stylesheet" href="../css/bootstrap.min.css"/>
<link rel="stylesheet" href="../css/main.css"/>
<!--[if 1t IE 7]>
<script type="text/javascript" src="js/DD_belatedPNG_0.0.7a-min.js">
<![endif]-->
<script src="../scripts/jquery-1.11.0.min.js"></script>
<script src="../scripts/bootstrap.min.js"></script>
<script src="../scripts/main.js"></script>

<title>utterm@sunyit.edu</title>
</head>
<body>

 <nav class="navbar navbar-inverse" role="navigation">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#"><img src="../images/utterm.png"></a>
        </div>
	        <div class="navbar-collapse collapse">
	          <ul class="nav nav-tabs">
				<li class="active" id="cs249"><a href="#">CS249</a></li>
				<li id="cs350"><a href="#">CS350</a></li>
				<li id="cs350"><a href="#">CS350</a></li>
				<li id="other"><a href="#">Other</a></li>
			</ul>
	        </div><!--/.navbar-collapse -->
      </div>
    </nav>

<div class="col-sm-10 col-sm-offset-1">
	<div class="panel panel-default ">
	  <div class="panel-heading"><h3>Homework</h3></div>
	  <div class="panel-body">
	    
	  </div>
	</div>
</div>

<div class="well well-lg">...</div>

</body>
<script>
$(document).ready(function(){
	loadPage("cs249")
	$('nav li').click(function(){
		if($(this).index() == 0) return;
		$('.panel-body').empty()
		$(this).addClass('active').siblings().removeClass('active')
		$('.collapse').removeClass('in')
		$('#collapse'+$(this).index()).addClass('in')
		loadPage($(this).attr('id'))
	})
})

</script>
</html>