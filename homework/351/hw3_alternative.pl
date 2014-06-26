#!/usr/bin/perl
#hw3 non dynamic version
$| = 1; 
use strict;
use warnings FATAL => 'all';
use CGI qw();


my $q = new CGI;

print $q->header;
print $q->start_html(-title => 'A web form');

print $q->start_form;

print $q->start_form(
-name    => 'main_form',
-method  => 'POST',
-enctype => &CGI::URL_ENCODED,
-onsubmit => 'return javascript:validation_function()',
#-action => 'emot for self',
);

print $q->textfield(
-name      => 'text1',
-value     => 'default value',
-size      => 20,
-maxlength => 30,
);

print $q->textarea(
-name  => 'textarea1',
-value => 'default value',
-cols  => 60,
-rows  => 3,
);

my @values = ('value1', 'value2', 'value3');
print $q->popup_menu(
-name    => 'popup1',
-values  => \@values,
-default => 'value2'
);


   my @select_val = ('value1', 'value2', 'value3');
   my %labels = (
        'value1' => 'Choice 1',
        'value2' => 'Choice 2',
        'value3' => 'Choice 3',
    );

    print $q->popup_menu(
        -name => 'popup1',
        -values     => \@select_val,
        -default    => 'value2',
        -labels     => \%labels,
        -attributes => {
            'value1' => {
                'style' => 'color: red'
            }
        },
    );

    print $q->popup_menu(
        -name       => 'popup2',
        -values     => [keys %labels],
        -default    => 'value2',
        -labels     => \%labels,
        -attributes => {'value1' => {'style' => 'color: red'}},
    );

      print $q->checkbox_group(
        -name     => 'check1',
        -values   => ['one', 'two', 'three', 'four'],
        -defaults => ['one', 'two'],
        -columns  => 2,
        -rows     => 2,
    );

 print $q->radio_group(
        -name    => 'radio1',
        -values  => ['one', 'two', 'three', 'four'],
        -default => 'one',
        -columns => 2,
        -rows    => 2,
    );
 print $q->button(
        -name     => 'submit_form',
        -value    => 'Click here!',
        -method   => 'POST',
        -action   => 'self',
        #-onsubmit => 'javascript: validate_form()',
    );


print $q->end_form;


print "<br><br>";

my $text1_value = $q->param('text1');
my @checked_boxes = $q->param('check1');
print $q->param('text1');









