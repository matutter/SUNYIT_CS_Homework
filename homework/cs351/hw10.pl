#!/usr/bin/perl
#############################
#		PARTS 1 AND 2 		#
#############################
my $QKEY = "::";
$| = 1;
use CGI qw();
use strict;
use warnings;
use Data::Dumper;
my $c = CGI->new;
my @global_q;
my @global_a;
my $dir = "hw10_files/";
my $file = "exam1.file";
my $path = $dir.$file;
print "Content-type: text/html\n\n";


style();
if($c->param("review") eq "save")
{
	print 
	'
	<h3>Complete</h3>
	<p class="jumbo">
		The Exam is complete.<br>
		Click <a href="">Here</a> to continue.<br>
		Or <a href="hw10_files/exam1.file">View Raw<a>
	</p>
	';
}
elsif($c->param("form2"))
{
	if($c->param("form2") eq "cancel")
	{
		print_form1();
		return;
	}
	my @data = $c->param();
	pop @data;
	for(0 ... scalar @data)
	{
		if( $_ % 2 eq 1)
		{
			push @global_a, $c->param(@data[$_]);
		}
		elsif( $_ % 2 eq 0 )
		{
			push @global_q, $c->param(@data[$_]);
		}
	}
	save_file();
	print_review();
}
elsif($c->param("tr") || $c->param("text"))
{
	print_form2();
}
else
{
	print_form1();
}

sub save_file
{


	unless ( open FILE, '>'.$path ) {
		print "failed to write to $path";
	}

	foreach(0 ... scalar @global_q - 1)
	{
		print FILE @global_q[$_];
		print FILE "::";
		print FILE @global_a[$_];
		print FILE "\n";
	}

	close FILE;
}


sub print_review()
{
#	my @questions = @global_q;
#	my @answers = @global_a;

#################################
## START PART 2
#################################
	my @questions;
	my @answers;

	open(MYFILE, $path);
	while (<MYFILE>)
	{
		chomp;
		my @line = split( $QKEY , $_ );
		push @questions, @line[0];
		push @answers, @line[1]
	}
	close (MYFILE); 

#################################
## END PART 2
#################################
print '
<h3>Review</h3>
<form method="post" action="" name="review">
<p>
<table>
<thead>
<tr>
<td>
#
</td>
<td><strong>
Question</strong>
</td>
<td><strong>
Answer</strong>
</td>
</tr>
</thead>
<tbody>
';
	foreach(0 ... scalar @questions - 1)
	{
		print '<tr><td class="short">';
		print $_.'</td><td>'. @questions[$_] . "</td><td>" . @answers[$_] . "<br>";
		print '</td></tr>';

	}
print '
</tbody>
</table>
<br>
	<button name="review" value="save">Save Exam</button>
	<button name="review" value="cancel" class="red">Cancel</button>
</p>
</form>
';

}




sub print_form2 {

print '
<h3>Enter the Questions below</h3>
<form method="post" action="" name="form2">
<p>
';

my $question = $c->param("tf");
foreach(1 ... $question) {
	my $other = $_ % 2;
	print
	'
	<q'.$other.'>
	<label><strong>T/F Question '.$_.'.</strong></label><br>
		<input name="tf'.$_.'" type="text" value="TorF'.$_.'"></input><br>
		<input type="radio" checked name="q'.$_.'" value="True">True<br>
		<input type="radio" name="q'.$_.'" value="False">False 
		<ln></ln>
	</q'.$other.'>
	';
}
$question = $c->param("text");
foreach(1 ... $question) {
	my $other = $_ % 2;
	print
	'
	<ln class="blue"></ln>
	<q'.$other.'>
	<label><strong>Short Answer Question '.$_.'.</strong></label><br>
		<input name="text'.$_.'" type="text" value="Question '.$_.'"><br>
		<label>ANS:<input style="font-size:1.0em;" type="text" name="tq'.$_.'" value="answer"><br>
	</q'.$other.'>
	';
}
print '
	<button name="form2" value="create">Create Exam</button>
	<button name="form2" value="cancel" class="red">Cancel</button>
</p>
</form>
';
}

sub print_form1 {
print
'
<h3>Enter the amount of Exam questions</h3>
<form method="post" action="" name="form1">
<p>
<label><strong>T/F Questions</strong></label><br>
	<input name="tf" type="number" max="20" min="1" value="1"><br>
<label><strong>Short Answer Questions</strong></label><br>
	<input name="text" type="number" max="20" min="1" value="1">
	<br>
	<button name="form1" type="submit">Submit</button>
</p>
</form>
';
}

sub style
{
print
'
<style>
h3
{
	background-color:#979797;
	border: solid 3px #333;
	color: #333;
	border-radius: 3px;
	border-bottom-right-radius: 0px;
	border-bottom-left-radius:0px;
	border-bottom-width: 0px;
	padding: 3px;
	margin: 0px;
	width: 80%;
}
p
{
	background-color:#e7e7e7;
	border: solid 3px #333;
	color: #333;
	border-radius: 3px;
	border-top-right-radius: 0px;
	border-top-left-radius:0px;
	border-top-width: 0px;
	padding: 3px;
	margin: 0px;
	width: 80%;
	min-height: 200px;
}
input, label, button
{
	font-size: 2.0em;
	text-align: center;
}
button
{
	background-color: #4f8e23;
	color:white;
	border-radius: 8px;
}
ln
{
	width: 100%;
	height: 2px;
	background-color: red;
	display: block;
}
q1, q0
{
	display: block;
}
q1
{
	background-color: #f3f3f3;
}
q0
{
	background-color: #FFF;
}
.red
{
	background-color:#8e234f;
}
.blue
{
	background-color:#234f8e;
}
table
{
	width:100%;
	font-size:1.1em;
}
td
{
	width:50%;
}
tr:nth-child(even)
{
	background-color:#fff;
}
table td
{
	width:10px !important;
}
.jumbo
{
	text-align:center;
	font-size:2.1em;
}
</style>';	
}