#!/usr/bin/perl
## Turns off buffering
$| = 1;
use strict;
use CGI qw();
my $b = "<br>";
print "Content-type: text/html\n\n";
print "objective: make a JSON module for perl.<br>";

#print "{ \" name \" : \" value \" }";
my $s2 = "{ \" name \" : \" value \" }";
my $s = "name value";
print "'" .$s ."'  --->  ". $s2 . " = ". jparse($s) . $b;

my @j;
#@j[0] = jparse("name","value");
@j = jadd(jparse("hello","world"), @j);
@j = jadd(jparse("crate","number"), @j);
@j = jadd(jparse("emu2","3300"), @j);
print jstringify( @j );

$s = jname( @j , "crate" );
print $b . $s;

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