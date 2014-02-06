#!/usr/bin/perl

## Turns off buffering
$| = 1; #why?

###########################################
# pushing onto stack by concatting with ::
# is Stack is null just return 2nd arg
sub mpush {
	if(!defined($_[1])) { print return $_[0]; }
	@stack = $_[1] . "::" . $_[0];	
	return @stack;
}
##########################################
# Return the first part of the string
#
sub mtop {
	@top = split( /::/, $_[0] );
	return @top[0];
}
##########################################
# Remove first thing, and then re assemble
# 
sub mpop {
	@pop = split( /::/, $_[0] );
	@s   = "";
	for (my $i = 1, my $j = 0; $i < @pop; $i++, $j++) {
		@s[$j] = @pop[$i];
	}
	return join "::", @s;
}

print "Content-type: text/html\n\n";
print '<div class="col-sm-12">';
	print '<div style="white-space:pre">';
		print '<div class="page-header"> <h4>Hw2 Mat Utter <small class="pull-right">'.localtime.'</small> </h4> </div>';

		$count = 0;
		print "<strong>Putting things on the stack:</strong>\n";
		for($count=0; $count<10;$count++)  {
			@word = "Thing[$count] ";
			print @word;
			@stack = mpush( @stack, @word );
		}

		print "\n\n<strong>Popping things off the stack:</strong>\n";

		for($count=0; $count<10;$count++)  {
			print mtop(@stack) . "\n";
			@stack = mpop(@stack);
		}

	print '</div>';
print '</div>';
