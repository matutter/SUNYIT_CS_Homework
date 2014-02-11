#!/usr/bin/perl

## Turns off buffering
$| = 1;


my $output = `ls -a`;
print $output;