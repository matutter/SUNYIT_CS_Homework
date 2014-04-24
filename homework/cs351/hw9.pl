#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI qw();
use strict;
use warnings;
use Data::Dumper;
my $c = CGI->new;

print "Content-type: text/html\n\n";

my $directory = 'hw9_files';

my @file_list;
my $size;
my $file_size 	= 0;
my $largest 	= 0;
my $i 			= 0;
my $choices		= "";
my %size_hash 	= ();
my %select_hash = ();
opendir (DIR, $directory) or die $!;
while (my $file = readdir(DIR)) {
	next if ($file =~ m/^\./);
	$size = -s $directory ."/". $file;
	$i++;
	%size_hash->{$file} = $size;
	%select_hash->{$file} = 0;
#	if($file_size < $size) {
#		$file_size = $size;
#		$largest = $i;
#	}
	push @file_list, $file;
}


if($c->param()) {
	my @old_choice;

	if($c->param("newfile"))
	{
		if( $c->param("name")  &&  $c->param("msg") ) {
			create_file($c->param("name"),$c->param("msg"));
		}
		$choices =  $c->param("newfile"); 
		@old_choice = split( "&", $choices );
	}
	elsif( $c->param("delete") )
	{
		#my @deletes = split( "&",$c->param("delete") );
		my @deletes = join("&",$c->param("select"));
		my $temp = join("&",@file_list);
		@old_choice = @deletes;
		#print @deletes;
		foreach(@deletes)
		{
			%select_hash->{$_} = 0;
			$temp =~ s/$_//;
			#print $_ . "<br>";
			unlink $directory . "/" . $_;
		}
		$temp =~ s/&+/&/g;
		@file_list = split("&",$temp);

	}
	else
	{
		$choices = join("&",$c->param("select"));
		if($c->param("largest")) {
			#@old_choice = split( "&", $c->param("largest") );
			@old_choice = split( "&", $choices );
		}
	}
	foreach(@old_choice) {
		%select_hash->{$_} = 1;
	}
}

if($i != 0) {

	print '<div style="position:absolute; height:350px; left:0px; top:25px; width:33%; background-color:#e7e7e7; display:inline-block;"">';
	print '<form name="form1" id="form1" action="" method="post">';

	print_buttons($choices);
	print "<br>";
	print_select(@file_list,$choices,$largest);
	print '</form>';
	my $hyperlink = largest_file($choices);
	print_hyperlink( $hyperlink );
	print '
		</div>
		<div style="position:absolute; height:350px; left:200px; top:25px; width:33%; background-color:#e7e797; display:inline-block;">';
	print '
	<form name="form2" method="post" action="">
		<button name="newfile" value="'.$choices.'">Add File</button>
		<input name="name" placeholder="file name" value="new1.file">
		<textarea name="msg" style=" margin:2%; width:96%; height:200px;" >New file text!!!</textarea>
	</form>
	';
	print '</div>';
}

sub create_file {
	#print "making: " . $_[0] . ":" . $_[1];
	
	if( length $_[1] > 100 ) { return }

	my $file = $directory . "/" . $_[0];

	unless ( open FILE, '>'.$file ) {
		print $file;
	}
	print FILE "asdasd";
	close FILE;

	if( !exists %size_hash->{ $_[0] }   )
	{
		%size_hash->{$_[0]} = length $_[1];
		%select_hash->{$_[0]} = 0;
		push @file_list, $_[0];
	}
}

sub	print_hyperlink {	
	print '<a href="'.$directory."/".$_[0].'">' . $_[0] . '</a><br>' ;
	my $file = "";
	open(MYFILE, $directory."/".$_[0]);
	while (<MYFILE>)
	{
		chomp;
		#print "$_\n";
		$file = $file . $_ . "\n";
	}
	close (MYFILE); 

	print '<pre><textarea style=" margin:2%; width:96%; height:190px;">'.$file.'</textarea></pre>';
}

sub largest_file {
	my @choice_list = split("&",@_[0]);
	my $lrg_name;
	my $lrg_num = 0;
	foreach( @choice_list ) {
		#print %size_hash->{$_} . "<BR>";
		if(%size_hash->{$_} > $lrg_num ) {
			$lrg_num = %size_hash->{$_};
			$lrg_name = $_;
		}
	}
	return $lrg_name;
}

sub print_buttons {
	print '		
		<button name="delete" value="'.$_[0].'">Delete</button>
		<button form="form1" name="largest" value="'.$_[0].'" type="submit" >Largest</button>
	';
}

sub print_select {
	my $i = 0;
	my @files = @_;
	my @choices = split( "&", @_[-2] );
	pop @files;
	pop @files;

	print '<select style=" margin:2%; width:96%; " multiple form="form1" name="select">';
	foreach(@files) {
		if( $_ eq "" ) {
			#my $noop;
		}
		elsif( %select_hash->{$_}  ) {
			print '<option selected value="'.$_.'">'.$_.'</option>';
		}
		else {
			print '<option value="'.$_.'">'.$_.'</option>';
		}
	}
	print '</select>';
}

sub indexOf {
my	@elems = @_		;
	pop @elems		;
my	$key = $_[-1]	;
foreach(@elems) {
	print $_ . " " . $key;
	if($_ == $key) {
		return 1;
	}
}
return 0;
}

#compare files
#sleect with file file_list
#allow multiple selects
#out of all selected one a biggest should be found when a button is clicked
#biggest file is displayed with a hyperlink
# that hyperlink shows the file in a text area
#select never clears