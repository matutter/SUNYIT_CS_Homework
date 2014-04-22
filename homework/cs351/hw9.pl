#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
use strict;
use warnings;
my $c = CGI->new;

print "Content-type: text/html\n\n";

my $directory = 'hw9_files';

my @file_list;
my $file_size = 0;
my $size;
my $largest = 0;
my $i = 0;
opendir (DIR, $directory) or die $!;
while (my $file = readdir(DIR)) {
	next if ($file =~ m/^\./);
	$size = -s $directory ."/". $file;
	$i++;
	if($file_size < $size) {
		$file_size = $size;
		$largest = $i;
	}
	push @file_list, $file;
}

if($i != 0) {
	print '<form name="form1" id="form1" action="" method="post">';
	print_buttons();
	print "<br>";
	print_select(@file_list,$largest);


	print '</form>';
}


if($c->param()) {
	print $c->param("select");

}


sub print_buttons {
	print '
		<button form="form1" type="submit" >Largest</button>
	';
}


sub print_select {
	my $i = 0;
	my @files = @_;
	pop @files;
	print '<select multiple form="form1" name="select">';

	foreach(@files) {
		if(++$i == @_[-1]) {
			print '<option selected value="'.$_.'">'.$_.'</option>';
		}
		else {
			print '<option value="'.$_.'">'.$_.'</option>';
		}
	}
	print '</select>';
}

#compare files
#sleect with file file_list
#allow multiple selects
#out of all selected one a biggest should be found when a button is clicked
#biggest file is displayed with a hyperlink
# that hyperlink shows the file in a text area
#select never clears