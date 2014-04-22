#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
my $c = CGI->new;
print_head();

$init = 1;
$increm = 1;
$rows = 2;
$cols = 3;
$text;

if($c->param('form1') > 0) #form1 submitted
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
	my $bar_data;
	my $max, $max;
	if(checkDef() eq 1) {
		$text = $cols . "x" . $rows;
		@matrix;
		($bar_data,$min,$max,$x,$y,@matrix) = assemble($init, $increm, $rows, $cols);
		makeTable($x,$y);
		print "<br><img src=\"hw8_graph.pl?min=$min&max=$max&cols=$cols&$bar_data\"><br>";
		#print $bar_data;
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
		if($c->param('form1') > 1)
		{
			$def = 1;
			$cols = $c->param('form1');
		}
	}
	if($rows < 1 || $cols < 1) {
		$def = 0;
	}
	return $def;
}

sub makeTable {
	print '
	<form class="no" action="" method="post">
		<div class="formhead">
			Thats a nice '.$text.' table
			<button class="btn btn-default pull-right">Clear</button>
			<button name="form1" value="'.$cols.'" type="submit" class="btn btn-default pull-right">Back</button>
		</div>
	<input style="display:none;" readonly value="'.$init.'::'.$increm.'::'.$rows.'" name="form1dat">
	</form>';
	print '<table class="table mytable">';
	my $i=0;
	#my @matrix = $_[2];
	for my $x (1..$_[0]) {
		print "<tr>";
		for my $y (1..$_[1]) {
			print "<td>";
				print $matrix[$y][$x]; 
			print "</td>";
		}
		print "</tr>";
	}
	print '</table>';
}
sub assemble {
	my $colsX = $_[2];
	my $rowsY = $_[3];
	my $i= $_[0];
	my $step = $_[1];
	my @mx;
	my @cols;
	my @linear_data;
	my $ bar_count = 0;
	my $max = 0;
	for my $x (1..$colsX) {
		my @row;
		for my $y (1..$rowsY) {
			$mx[$y][$x] = $i;
			if($i > $max) {
				$max = $i;
			}
			@linear_data[$bar_count++] = $i;
			$i += $step;
		}
	#	push(@cols,@row);
	}
	#print @linear_data;
	my $bars = join("&",@linear_data);
	my $min = min(@linear_data);
	return ($bars,$min,$max,$colsX,$rowsY,@mx);
}
sub min {
    splice(@_, ($_[0] > $_[1]) ? 0 : 1, 1);
    return ($#_ == 0) ? $_[0] : min(@_);
}
sub form1 {

print '
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
	<input style="display:none;" readonly value="'.$init.'::'.$increm.'::'.$rows.'" name="form1dat">
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
	position:relative;
	bottom:0px;
	width:100%;
}
</style>
<script>
</script>
<div class="panel panel-default footer">
  <div class="panel-body">
    Assignment 8
  </div>
  <div class="panel-footer">
	<ul>
		make forms that do this
		<li>1. form1: a) initial b) incremus c) number of rows</li>
		<li>2. form2: a) number of cols</li>
		<li>3. fill table</li>
		<li>4. allow cols to change</li>
		<li>5. store values in a 2d array</li>
		<li>6. Make a graph image using perl DG</li>
	</ul>
  </div>
</div>
<br>
';
}