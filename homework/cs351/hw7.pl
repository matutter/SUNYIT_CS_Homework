#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
#use CGI::Cookie;
my $c = CGI->new;
my $myfile = "text.file2";
my $firstLine = 1;
my $lastLine = $firstLine+1;
my $next = "checked";
my $back = "";
my @j;
#print "Content-type: text/html\n\n";

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
	$cook = $c->cookie(
		-name => 'PAGE',
		-value => $firstLine,
		-expires => '+6m'
	);
	print $c->header(-cookie=>$cook); 
	$lastLine = $firstLine+1;
}
else
{
    $firstLine = $c->cookie('PAGE');
}
$mystuff;
if(-e( $myfile )) {
	open my $info, $myfile or die "Could not open $myfile: $!";
	#my $slength = 0;
	#my $maxLength = -s $myfile;
	my $last;
	while( my $line = <$info>)  {
		#$slength+=length($line);
		#if($slength >= $maxLength) {
		#	$firstLine--;
		#	$next = "";
		#	$back = "checked";
		#	break;
		#}
		#print $maxLength . "-" . $slength . "    L";
		#if ($firstLine eq $.) {
	    #	$stuff = "[" . $. ."]  " . $line . '<br>';    
		#}
	    #last if $. == $lastLine;
	    @j = jadd(jparse($.,$line), @j);
	    $last = $.;
	}
	close $info;
	if($last < $firstLine) {
		$firstLine = $last;
		$next = "";
		$back = "checked";
	}
	###################################
	# CS CREDIT GETTING IT OUTA A HASH
	$stuff = jname( @j , $firstLine );
}

print_head();


sub print_head {
#print "Content-type: text/html\n\n";
print $c->header('text/html');
print '
<link href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css"rel="stylesheet">
<style>

</style>
<script>

</script>
</header>
<html>
<br>
best viewed <a href="homework/cs351/hw6.pl"> here </a> <br>
<div class="col-sm-4">
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
<div class="col-sm-4">';
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
############################################
# CS CREDIT STUFF BELOW
# explanation: I created a version of 
# JSON encoding (javascript object notation)
# it doesn't handle nested objects but
# thats fine... one level deep, makes it 
# binary expressive literal object notation
# 1 name paired with 1 value...
# sounds like belon(y), but it can be
# effectively used like a PERL hash
# which is delicious for breakfast..
# hash an belogna... YUM
############################################
#returns a value given a name
sub jname {
	my $r = " ";
	foreach(@_) {
		my $s = $_;
		$s =~ s/[^\w]/$r/g;
		my @p = split($r,$s);
		if(@p[2] eq $_[-1]) {
			return $b . @p[5] . $b;
		}
	}
}
#serialize object
sub jstringify {
	my $s = join ",",@_; 
	return "{".$s."}";
}
#add an element to front or back (A,B)= AB (B,A) = BA
sub jadd {
	return @_;
}
#convert a name and value pair into an object elem
sub jparse {
	if(defined($_[1])) {
		return "{\"".$_[0]."\":\"".$_[1]."\"}";		
	}
	else
	{
		my @c = split(" ", $_[0]);
		return "{\"".@c[0]."\":\"".@c[1]."\"}";		
	}
}