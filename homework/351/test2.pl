#!/usr/bin/perl
$KEY = "::";
$endl = "<br>";
$| = 1;
use CGI qw();
my $c = CGI->new;

print "Content-type: text/html\n\n";

print
'
<form method="post" action="">
	<input name="var" type="text" value="testit">
	<button>try post</button>
</form>
<form method="get" action="">
	<input name="var" type="text" value="testit">
	<button>try get</button>
</form>
';

my $num = 1;
my $bold = 0;
print "<table>";
foreach( %ENV )
{
	if($num % 2)
	{
		$num++;
		$bold++;
		print "<tr><td><strong>" . $_ . "</strong></td>";
	}
	else
	{
		print "<td>" . $_ . "</td></tr>";
		$num--;
	}
}
print "</table>";
foreach( %contents )
{
	print $_ . "<br>";
}