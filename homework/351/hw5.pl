#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
my $c = CGI->new;
print_head();

$init = 0;
$increm = 0;
$rows = 2;
$cols = 3;
$text;

my $matrix;

$matrix[0][0] = 0;
$matrix[0][1] = 1;
$matrix[1][0] = 2;
$matrix[1][1] = 3;

@arr = ( [ qw/ 1 2 3 / ],
         [ qw/ 4 5 6 / ] );


if($c->param('form1') eq 1) #form1 submitted
{
	if(checkDef() eq 1) {
		form2();
	}
	else 
	{
		form1();	
	}
}
elsif($c->param('form2') eq 1) #form2 submitted
{
	my $size=2;

	if(checkDef() eq 1) {
		$text = $cols . "x" . $rows;
		makeTable($rows,$cols);
	}
	else 
	{
		form1();	
	}
}
else #first page
{
	form1();
}




sub checkDef {
	my $def = 1;
	if(!defined($c->param('init'))) {
		$def = 0;
	}
	if(!defined($c->param('increm'))) {
		$def = 0;
	}
	if(!defined($c->param('rows'))) {
		$def = 0;
	}
	$rows 	= $c->param('rows');
	$increm = $c->param('increm');
	$init 	= $c->param('init');

	if(defined($c->param('form1dat'))) { 
		my @res = split(/::/,$c->param('form1dat'));
		$init 	= @res[0];
		$increm = @res[1];
		$rows	= @res[2];
		$def = 1;
		if(!defined($c->param('cols'))) { 
			$def = 0;
		}
		$cols 	= $c->param('cols');
	}
	return $def;
}




sub makeTable {
print '
<form class="no" action="" method="post">
	<div class="formhead">
		Thats a nice '.$text.' table
		<button class="btn btn-default pull-right">Clear</button>
	</div>
</form>';
print '<table class="table mytable">';
for my $x (1..$_[0]) {
	print "<tr>";
	for my $y (1..$_[1]) {
		print "<td>";
		print $y . " " . $x . "<br>";
		print "</td>";
	}
	print "</tr>";
}
print '</table>';
}

sub form1 {

print ' best viewed at <a href="/homework/cs351/hw5.pl">here</a>
<div class="formwrap">
<form action="" method="post">
<div class="formhead">
	Step 1 <small>Init the table</small>
	<button name="form1" value="1" type="submit" class="btn btn-default pull-right">Next Step</button>
</div>
	<div class="input-group formwrap">
		<span class="input-group-addon addon-space">Initial Value</span>
		<input name="init" type="number" class="form-control" value="'.$init.'" placeholder="'.$init.'">
	</div>
	<div class="input-group formwrap">
		<span class="input-group-addon addon-space">Increment</span>
		<input name="increm" type="number" class="form-control" value="'.$increm.'" placeholder="'.$increm.'">
	</div>
	<div class="input-group formwrap">
		<span class="input-group-addon addon-space">Number of rows</span>
		<input name="rows" type="number" class="form-control" max="10" value="'.$rows.'" placeholder="'.$rows.'">
	</div>
</form>
</div>
';
}

sub form2 {

print '
<div class="formwrap">
<form action="" method="post">
<div class="formhead">
	Step 2 <small>Pick Columns</small>
	<button name="form2" value="1" type="submit" class="btn btn-default pull-right">Create Table</button>
</div>
	<div class="input-group formwrap">
		<span class="input-group-addon addon-space">Number of cols</span>
		<input name="cols" type="number" class="form-control" max="10" value="'.$cols.'" placeholder="'.$cols.'">
	</div>
	<input readonly value="'.$init.'::'.$increm.'::'.$rows.'" name="form1dat">
</form>
</div>
';
}


sub print_head {
print "Content-type: text/html\n\n";
print '
<link href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css"rel="stylesheet">
<style>

td:nth-child(even) {background: #BBB}
.no
{
	padding:0px;
	margin:0px;
	position:table-block;
}
.addon-space
{
	width:120px;
}
.formwrap
{
	position: relative;
	width: 500px !important;
}
.formhead
{
	width: 500px;
	background-color: #d43f3a;
	border-radius: 3px;
	padding:2px;
	font-size: 1.7em;
	font-weight: 700;
	margin-bottom: 3px;
	padding-left:5px;
}
.mytable
{
	width:500;
	text-align:center;
}
.footer
{
	position:absolute;
	bottom:0px;
	width:100%;
}
</style>
<script>
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
</script>

<br>
';
}