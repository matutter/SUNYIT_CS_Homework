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
my $test_dir = "hw10_files/taken";
my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime();
my $time = localtime();
   $time =~ s/[^a-zA-Z0-9]/_/g; 
my $file = "exam1.file";
my $path = $dir.$sec;
my $name = "none";
my $edit_param = "";
my $mode = "on";
#print "Content-type: text/html\n\n";


if( $c->param("update") )
{
	my $exam = $c->param("update");
	my @data = $c->param();
	pop @data;
	#print "$exam Changes Saved <br>";

	my %corrections = ();
	foreach( @data )
	{
		#print $_ . " " . $c->param($_) . "<br>";
		%corrections->{$_} = $c->param($_);
	}

	my $i = 0;
	open(MYFILE, $test_dir."/".$exam);
	my $new_grade = 0;
	my @update_lines;
	while (<MYFILE>)
	{
		chomp;
		my ($p1, $p2, $p3, $p4, $p5, $p6 ) = split("::",$_);
		

		if( defined %corrections->{"ch".$i}  )
		{
			$p4 = %corrections->{"ch".$i};
		}
		if( defined %corrections->{"co".$i}  )
		{
			$p5 = %corrections->{"co".$i};
		}
		if( defined %corrections->{"gr".$i}  )
		{
			$p6 = %corrections->{"gr".$i};
		}
		if($p1 eq "name\\grade")
		{
			$p3 =  $new_grade;
			push @update_lines, $p1 ."::" . $p2 ."::" . $p3 ."::" . $p4 . "\n";
		}
		else
		{
			$new_grade = $new_grade + $p6;
			push @update_lines, $p1 ."::" .  $p2."::" .  $p3."::" .  $p4 ."::" . $p5 ."::" . $p6 . "\n";
		}
		$i++;
	}
	close(MYFILE);
	open(MYFILE, ">".$test_dir."/".$exam);	
	foreach( @update_lines )
	{
		print MYFILE $_;
	}
	print "Content-type: text/html\n\n";
	print "<META HTTP-EQUIV=refresh CONTENT=\"0;url=?\">\n";
}



if( $c->param("instr") eq "on" )
{
	$mode = "off";
}


#do this if the user is logged in and clicks log out
if( $c->param("logout") eq "now" )
{
	my $cook = $c->cookie(
		-name => 'USER',
		-value => $c->param("uname"),
		-expires => '-30m'
	);
	print $c->header(-cookie=>$cook);
	print'
	<div class="user">
		<form name="login" method="post" action="">
			<input class="sml" type="text" name="uname">
			<button class="btn" type="submit">login</button>
			<a class="right" href="?instr='.$mode.'"> Turn Instructor Mode '.$mode.'</a>
		</form>
	</div>';
}
# do this if the user logs in 
elsif($c->param("uname"))
{
	my $cook = $c->cookie(
		-name => 'USER',
		-value => $c->param("uname"),
		-expires => '30m'
	);
	print $c->header(-cookie=>$cook); 
	$name =  $c->param("uname");
	print '<div class="user">
		<form method="post">
				Logged in as: '. $c->param("uname") .'	
				<button class="btn" name="logout" value="now">logout</button>
				<a class="right" href="?instr='.$mode.'"> Turn Instructor Mode '.$mode.'</a>
			</form>
	</div>';
}
# do this if the user cookie is set but has expired
elsif(	$c->cookie('USER') ne "-expires" )
{
	$name =  $c->cookie('USER');
	print "Content-type: text/html\n\n";
	print '<div class="user">
			<form method="post">
				Logged in as: '. $name .'
				<button class="btn" name="logout" value="now">logout</button>
				<a class="right" href="?instr='.$mode.'"> Turn Instructor Mode '.$mode.'</a>
			</form>
	</div>';
}
# do this if not logged in yet
else
{
	print "Content-type: text/html\n\n";
	print'<div class="user">
		<form name="login" method="post" action="">
			<input class="sml" type="text" name="uname">
			<button class="btn" type="submit">login</button>
			<a class="right" href="?instr='.$mode.'"> Turn Instructor Mode '.$mode.'</a>
		</form>
	</div>';
}
# send the user agent style sheets
style();

#edit exam as instructor
if( $c->param("instr") eq "on" )
{
	print "<ln2 class=\"purple\"> Instructor Mode On: Selecting Past Exams Enters Grading Mode </ln2>";
	$edit_param = "&instr=on";
}
# do this if the user tries to look at old exams
if( $c->param("oldexams") )
{
	oldexams($c->param("oldexams"));
	sub oldexams {
		my @parts = split( "__" , $_[0] );
		my $exam = @parts[1];
		my $user = @parts[0];

		open ( MYFILE, $test_dir."/".$_[0] ) || die "ERROR Unable to open test: $!\n";
		my $last;
		while (<MYFILE>) {$last = $_}
		close MYFILE;
		my ($p1,$p2,$p3,$p4) = split("::",$last);

		print
		'<div class="pfix">
		User: '. $user .'<br>
		Test: '. $exam .'<br>
		Grade: '. $p3 .'<br>';


		my $grade;
		if( $c->param("instr") eq "on" )
		{
			print '<form name="update" method="post" action="">';
		}
		print "<table> <tbody> 
		<tr>
		<td><strong>Question</strong></td>
		<td><strong>Answer Given</strong></td>
		<td><strong>Expected Answer</strong></td>
		<td><strong> Instructor Changes </strong></td>
		<td><strong> Instructor Comments </strong></td>
		<td><strong> Points </strong></td>
		</tr>
		";



		#print $p4;
		my $i=0;
		open(MYFILE, $test_dir."/".$_[0]);
		while (<MYFILE>)
		{
			chomp;
			my $q = "";
			my $g = "";
			my $a = "";
			my $chng = "";
			my $cmnt = "";
			my $pnts = "";
			($q,$g,$a,$chng,$cmnt,$pnts) = split( $QKEY , $_ );
			if($chng eq "0") { $chng = ""; }
			if($cmnt eq "0") { $cmnt = ""; }

			if( $c->param("instr") eq "on" && !( $a eq "True" or $a eq "False" ) && !($a eq $g))
			{
				$chng = "<input name=\"ch$i\" type=\"text\" value=\"$chng\">";
				$cmnt = "<input name=\"co$i\" type=\"text\" value=\"$cmnt\">";
				$pnts = "<input name=\"gr$i\" type=\"number\" max=\"$p4\" min=\"0\" value=\"$pnts\">";
			}

			if( $q eq "name\\grade" )
			{
				$grade = $a;
			}
			else
			{
				if($g ne $a)
				{
					print "<tr class=\"red\" >";
				}
				else
				{
					print "<tr class=\"blue\">";	
				}
				print "<td>$q</td><td>$g</td><td>$a</td><td>$chng</td><td>$cmnt</td><td>$pnts</td>";
				print "</tr>";
			}
			$i++;
		}
		close (MYFILE);
		print "</tbody>  </table>";
		if( $c->param("instr") eq "on" )
		{
			print '
			<button name="update" value="'.$_[0].'" type="submit">Submit Changes</button>
			</form>';
		}
		print '
		<a class="btn2 red" href="?">Cancel</a>
		</div>';
	}

}
# do this is the user just finished a test and 
# wants to see the results
elsif( $c->param("grade") )
{
	my @answers;
	my @questions;
	my @real_answers;
	my @real_questions;

	my @data = $c->param();
	my $test = $c->param(@data[-1]);
	pop @data; 
	foreach( @data )
	{
		push @answers, $c->param( $_ );
		push @questions, $_;
	}
	open(MYFILE, $dir."/".$test);
	my %real = ();
	my $count = 0;
	while (<MYFILE>)
	{
		chomp;
		my @line = split( $QKEY , $_ );
		$count++;
		%real->{@line[0]} = @line[1];
		push @real_questions, @line[0];
		push @real_answers, @line[1];
	}
	close (MYFILE);

	print '<h3> Test Results Are </h3>
		<div class="pfix">
	';

	unless ( open FILE, '>'. $test_dir."/".$name."__".$test ) {
		print "failed to write to" . $test_dir."/".$name ;
	}
	my $grade = scalar @real_answers;
	my $correct = 0;
	for(0 ... scalar @answers - 1)
	{
		if( %real->{@questions[$_]} eq @answers[$_] )
		{
			print '<ln2 class="blue">yes</ln2>';
			print FILE @questions[$_] . '::' . @answers[$_] . '::' . @answers[$_] . "\n";
			$correct++;
		}
		else
		{
			print '<ln2 class="red">WRONG!';
			print " Expected \"" . %real->{@questions[$_]} . "\"</ln2>";	
			print FILE @questions[$_] . '::' . @answers[$_] . '::' . %real->{@questions[$_]} . "\n";
		}
		print "<h4>" . @questions[$_] ."</h4>". @answers[$_];
		%real->{@questions[$_]} = 0;

		$count--;
	}
	if( $count > 0 )
	{
		print "<ln2 class=\"red\">$count more unanswered</ln2>";
	}
	$grade = (100/$grade) * $correct;
	print FILE "name\\grade"."::".$name."::".$grade;
	close (FILE);
	print '
	<br>
	<strong>Final Grade: '.$grade.'%</strong>
	<br>
	<a href="?"> All Done Goodbye </a>
	</div>';


}
# do this is a user tries to take a test
# redirect to old tests if the test is already done
elsif($c->param("take"))
{

	##take##
	opendir (DIR, $test_dir) or die $!;
	while (my $file = readdir(DIR)) {
		next if ($file =~ m/^\./);
		my ($user,$test) = split("__",$file);
		if ($name eq $user && $test eq $c->param("take")) {
			#print "ALREADY TAKEN!!!<br>
			#Sorry You cant take this twice <a href=\"?\">Click Here</a>";
			close(DIR);
			oldexams($file);
			return
		}

	}
	close(DIR);
	print_take($c->param("take"));
}
# a form to make new exams
elsif($c->param("new") eq "makeexam")
{
	print_form1();
}
# a form to take an exam
elsif($c->param("new") eq "takeexam")
{
	print_choose();
}
# a page for reviewing a test that was just made
elsif($c->param("review") eq "save")
{
	print'
	<h3>Complete </h3>
	<p class="jumbo">
		The Exam is complete.<br>
		Click <a href="?">Here</a> to continue.<br>
		Or <a href="'.$c->param("path").'">View Raw<a>
	</p>';
}
# the form that presents the user with fields to create an exam
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
	save_file($path);
	#print $c->param("path");
	print_review($path);
}
# if the user submitted the amount of types of questions do this
elsif($c->param("tr") || $c->param("text"))
{
	print_form2();
}
# first page
else
{
	print_intro();
}




#form for taking test
sub print_take
{
	my @questions;
	my @answers;

	print "<h3>Taking Exam ".$_[0]." </h3>";

	open(MYFILE, $dir."/".$_[0]);
	while (<MYFILE>)
	{
		chomp;
		my @line = split( $QKEY , $_ );
		push @questions, @line[0];
		push @answers, @line[1]
	}
	close (MYFILE);

	print "<div class=\"pfix\">";
	print '<form name="test" method="post" action="">';
	my $i = 0;
	foreach(@answers)
	{

		if($_ eq "True" or $_ eq "False")
		{
			print "<ln2 class=\"red\">$i</ln2>";
			print "<h4>@questions[$i]</h4>";
			print "<input type=\"radio\" name=\"@questions[$i]\" value=\"True\">True</input>";
			print "<br><input type=\"radio\" name=\"@questions[$i]\" value=\"False\">False</input>";
		}
		else
		{
			print "<ln2 class=\"blue\">$i</ln2>";
			print "<h4>@questions[$i]</h4>";
			print "<input type=\"text\" name=\"@questions[$i]\">"; 
		}
		$i++;
	}
	print '
	<br><button name="grade" value="'.$_[0].'">Submit Exam</button>
	<button name="test" value="cancel" class="red">Cancel</button>
	</form>
	</div>';
}

# form for choosing what exam to take
sub print_choose {
###################################

opendir (DIR, $dir) or die $!;
my $text = "";
while (my $file = readdir(DIR))
{
	next if ($file =~ m/^\./);
	$text = $text . "<li><a href=\"?take=$file\">" . $file . "</a></li><br>";
}

print "<h3>Choose An Exam To Take</h3>

<div class=\"pfix\">
$text
</div>
";

###########################
}

# first page
sub print_intro
{
print '
	<h3>Do something</h3>
	<div class="pfix">
		<div class="half">
			<a href="?new=makeexam">Make a test</a>
			<br> 
			<a href="?new=takeexam">Take a test</a>
		</div>
		<div class="half">
			<strong>Past Exams</strong><br>
	';

opendir (DIR, $test_dir) or die $!;
while (my $file = readdir(DIR)) {
	next if ($file =~ m/^\./);

	print "<a href=\"?oldexams=$file$edit_param\">".$file . "</a><br>";
}
close(DIR);

	print '
		</div>
	</div>';
}
#function to save a test file
sub save_file
{
	unless ( open FILE, '>'.$_[0]) {
		print "failed to write to $path";
	}
	foreach(0 ... scalar @global_q - 2)
	{
		my $q = @global_q[$_];
		my $a = @global_a[$_];
		$q =~ s/::/_/g;
		$a =~ s/::/_/g;
		print FILE $q;
		print FILE "::";
		print FILE $a;
		print FILE "\n";
	}
	close FILE;
}
#shows review key of the new exam
sub print_review()
{
#	my @questions = @global_q;
#	my @answers = @global_a;

#################################
## START 10 PART 2
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
## END 10 PART 2
#################################
print '
<h3>Review '.$_[0].'</h3>
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
	<input name="path" type="text" style="display:none;" value="'.$_[0].'"> <br>
	<button name="review" value="save">Continue</button>
	<button name="review" value="cancel" class="red">Cancel</button>
</p>
</form>';
}

# the form for creating the new questions
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
	<input name="path" type="text" style="display:none;" value="'.$path.'"> <br>
	<button name="form2" value="create">Create Exam</button>
	<button name="form2" value="cancel" class="red">Cancel</button>
</p>
</form>
';
}

# the form for getting the amount of questions on the test
sub print_form1 {
print '
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

# the style info
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
	border-top-width:0px;
	padding: 3px;
	margin: 0px;
	width: 100%;
}
p, .pfix
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
	width: 100%;
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
ln2
{
	width: 100%;
	background-color: red;
	display: block;
	color:white;
	font-weight:900;
	padding:2px;
}
h4
{
	margin:0px;
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
	background-color:#8e234f !important;
}
.blue
{
	background-color:#234f8e !important;
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
.user
{
	width:100%;
	height:40px;
	background-color:#222;
	color:#e7e7e7;
	padding-left:15px;
}
.btn
{
	font-size: 0.8em;
	margin:10px;
}
.sml
{
	margin:5px;
	height:30px;
	width: 200px;
	font-size: 0.8em;
}
.half
{
	vertical-align:top;
	width:49%;
	display:inline-block;
}
.right
{
	float: right;
	margin-right:15px;
	padding:10px;
	color:white;
}
.purple
{	
	background-color:#85769a;
}
td input
{
	font-size:0.8em;
	width:100%;
}
.btn2
{
	font-size: 2.0em;
	text-align: center;
	color:white;
	border-radius: 8px;
	padding:2px;
	text-decoration:none;
	display:inline-block;
	margin:2px;
}
</style>';	
}