#!/usr/bin/perl
$KEY = "::";
$endl = "<br>";
$| = 1;
use CGI qw();
my $c = CGI->new;

print "Content-type: text/html\n\n";


use CGI::PathInfo;

$path_info = CGI::PathInfo->new;
($form_field_value) = $path_info->param('some_field_name');

print $form . $endl;
