#!/usr/bin/perl

## Turns off buffering
$| = 1;


#sub m_push() {
#	print "pushing $item";
#	return s;
#}


print "Content-type: text/html\n\n";

print '<div class="col-sm-8">';
	print '<div class="container">';
		print '<div class="page-header" <h1>Hw1 Mat Utter</h1> </div>';

#		@stack;
		$count = 0;
		for($count=0; $count<10;$count++)  {
			push @stack,"Hello World[$count]\n";
			
		}
		#for($count=0; $count<10;$count++) {
		#	print @stack[-1];
		#	pop @stack;
		#}
		foreach(@stack) {
			print @stack;
			pop @stack[-1];
		}
		##m_push("asd");


	print '</div>';
print '</div>';

#sub m_pop {
#
#	return s;
#}