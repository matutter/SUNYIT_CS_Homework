#!/usr/bin/perl
$KEY = "::";
$endl = "<br>";
$| = 1;
use CGI qw();
my $c = CGI->new;

print "Content-type: text/html\n\n";

foreach( %ENV )
{
	print $_ . "<br>";
}