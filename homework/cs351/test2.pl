#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
my $c = CGI->new;

print "Content-type: text/html\n\n";

my $queu = "this" . $QKEY . "is" .$QKEY. "a" .$QKEY. "queu";


print $queu ."<br>";

$queu = enqueu($queu, "YAY2!");

print $queu ."<br>";

$queu = dequeu($queu);

print $queu ."<br>";


while(qsize($queu)!=0){
	print qfront($queu);
	$queu = dequeu($queu);
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