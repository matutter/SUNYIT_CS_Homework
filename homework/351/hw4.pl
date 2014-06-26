#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
my $c = CGI->new;
print_head();
$text_sum = "";
$No=0;
$sum = 0;
if ($c->param() and $c->param('elems')>0) #post data
{
	my $res = $c->param('elems');
	$No = $res;
	#my $queu = split($QKEY, $c->param('sum')); #it comes in as a queu
	my $queu = $c->param('sum');
	while(qsize($queu)!=0) {
		$sum += qfront($queu);
		#print qfront($queu) . " " . "<br>";
		$text_sum .= " " . qfront($queu) . " ";
		$queu = dequeu($queu);
	}
	print ' <form action="" method="post" id="secretform">
				<input id="sum" name="sum" style="display:none;" value="'.$queu.'">
				<input id="sum" name="elems" style="display:none;" value="'.$res.'">
			</form>';
	start_page();
	print_default_body();
	end_page();
}
else
{
	start_page();
	print_page1();
	end_page();
}

sub print_head {
print "Content-type: text/html\n\n";
print "<style>
	box { width:102.75px;	cursor:pointer; position: relative;display: inline-block;	font-family: Impact, Charcoal, sans-serif;	background-color: #6e3276;	border-width: 12px;	border-style: dashed;	border-color: black;	height:auto;	text-align: center;	line-height: 100px;	font-size: 4em;}
	box:hover { background-color: #a049ac; }
	#holder{}
	holder { overflow-y:scroll; display: block;width: 500px;height: 126px;background-color: #333; color:#EEE; font-size:2em; }
	.button{	display: inline-block;	font-family: Impact, Charcoal, sans-serif;	height: 62px;	text-align: center;	width: 20.5%;	border-width: 0px;	background-color: #111;	color:white;	font-size: 2em; border-style:solid; border-width:4px; border-color:#244a96; }
	sum {	font-family: Impact, Charcoal, sans-serif;	display: block;	width: 500px;	height: 126px;	background-color: #aca049;	}
	box-container { width:500px; display:inline-block;}
	text { display:block; background-color:#111; color:#AAA; width:500px; text-align:center; padding-top:6px; padding-bottom:6px; }
	.added { background-color:#c0c0c0 ; width:2%; font-size:1em; display:inline-block; }
</style>";
print '<script>
	var i = 0;
	function sum() {
		document.getElementById("secretform").submit();
	}
	function back() {
		var s = location.href;
		window.location.assign(s.substring(0,s.indexOf("?")));
	}
	function add() {
		var target = event.target;
		var id = target.id
		var text = document.getElementById(id).textContent;
		document.getElementById("sum").value += text + "::";
		if((++i)==1)
			document.getElementById("holder").innerHTML+=text;
		else
			document.getElementById("holder").innerHTML+=\' + \'+text;		
	}
	function clearit() { document.getElementById("holder").innerHTML=""; }
</script>';
}
sub print_default_body {
	print_buttons();
	print_boxbuttons();
	print_panels();
}
sub print_buttons {
	print '<box-container>
	<button class="button" type="button" onclick="clearit()">Clear</button><button class="button" type="button" onclick="sum()">Add</button><button  class="button" type="button" onclick="back()"> Back </button>
	</box-container>
	
	<text> click "text-boxes" to add it to the buffer, click "Add" to put it in the queu, Also instead a third page I\'m just leaving things on this page.</text>';
}
sub print_boxbuttons {
	print '<box-container>';
	$No--;
	foreach(0..$No) {
		print '<box id="elem'.$No.'" type="button" onclick="add()">'.$No.'</box>';
		$No--;
	}
	print "</box-container><br>";
}
sub print_panels {
	my $thisText = $text_sum;
	my $space = " ";
	$thisText =~ s/:/$space/g;

	$sum = " = (".$sum.")";

	print '<holder id="holder"></holder>
	<br>
	<sum>'.$thisText.$sum.'</sum>';
}
sub print_page1 {
	print '
	<form action="" method="post">
		<strong>Add elements to the next page!<small>16 is the limit, for no reason</small></strong><br>
		Amount: <input type="number" name="elems" max="16"><br>
		<input type="submit" value="Do it">
	</form>';
}
sub start_page {
	print '<div class="col-sm-12 style="overflow:hidden;">';	
		print '<div class="page-header"> <h4>Hw4 Mat Utter <small class="pull-right">'.localtime.'</small> </h4> </div>';
}
sub end_page {
	print '<div class="col-sm-6"><res2></res2>';
}

sub enqueu {
	if(defined($_[1])) {  
		return $_[0] . $QKEY . $_[1];
	}
	else { return "err"; }
}
sub qback {
	my @back = split(/$QKEY/, $_[0]);
	return @back[-1];
}
sub qfront {
	my @front = split(/$QKEY/, $_[0]);
	return @front[0];
}
sub dequeu {
	my @pop = split(/$QKEY/,$_[0]);
	splice @pop, 0,1;

	return join $QKEY, @pop;
}
sub qsize {
	return scalar split(/$QKEY/,$_[0]);
}