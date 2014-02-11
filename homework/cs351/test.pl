#!/usr/bin/perl

## Turns off buffering
$| = 1;


my $output = `ls -a`;


print "Content-type: text/html\n\n";
print $output;