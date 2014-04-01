#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
my $c = CGI->new;

my $myfile = "text.file2";
my $firstLine = 1;
my $lastLine = $firstLine+1;
my $next = "checked";
my $back = "";


if($c->param()) {
	$myfile = $c->param('file');
	$firstLine = $c->param('line');
	if ('next' eq $c->param('dir')) {
		$firstLine++;
		$next = "checked";
		$back = "";
	}
	elsif ($firstLine != 1) {
		$firstLine--;
		$next = "";
		$back = "checked";
	}

	$lastLine = $firstLine+1;
}

$mystuff;
if(-e( $myfile )) {
	open my $info, $myfile or die "Could not open $myfile: $!";
	my $slength = 0;
	my $maxLength = -s $myfile;
	while( my $line = <$info>)  {
		$slength+=length($line);
		if($slength >= $maxLength) {
			$firstLine--;
			$next = "";
			$back = "checked";
			break;
		}
		#print $maxLength . "-" . $slength . "    L";
		if ($firstLine eq $.) {
	    	$stuff = "[" . $. ."]  " . $line . '<br>';    
		}
	    last if $. == $lastLine;
	}
	close $info;
}

print_head();


sub print_head {
print "Content-type: text/html\n\n";
print '
<link href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css"rel="stylesheet">
<style>

</style>
<script>

</script>
best viewed <a href="homework/cs351/hw6.pl"> here </a> <br>
<div class="col-sm-6">
	<form method="post" action="">
		<input  name="line" type="number" value="'.$firstLine.'"> <br>
		<input  name="file" type="text" value="'.$myfile.'"> <br>
		<input type="radio" name="dir" '.$back.' value="back">back<br>
		<input type="radio" name="dir" '.$next.' value="next">next<br>
		<button>See Next Line</button>		<br>
	</form>
';
print $stuff;

print '
</div>
<div class="col-sm-6">';
listDir();
print '</div>';
}

sub listDir {
    opendir (RUNNING, ".") or die $!;
    print "<ul>";
    while(my $name = readdir(RUNNING)) {
    	print "<li>" .$name. "</li>";
    }
    print "</ul>";
}