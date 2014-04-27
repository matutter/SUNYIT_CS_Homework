#!/usr/bin/perl
$KEY = "::";
$endl = "<br>";
$| = 1;
use CGI qw();
my $c = CGI->new;



if( $c->param("logout") eq "now" )
{
	$cook = $c->cookie(
		-name => 'USER',
		-value => $c->param("uname"),
		-expires => '-10m'
	);
	print $c->header(-cookie=>$cook);
	print'
	<div class="user">
		<form name="login" method="post" action="">
			<input type="text" name="uname">
			<button type="submit">login</button>
		</form>
	</div>';
}
elsif($c->param("uname"))
{
	$cook = $c->cookie(
		-name => 'USER',
		-value => $c->param("uname"),
		-expires => '+10m'
	);
	print $c->header(-cookie=>$cook); 

	print '<div class="user">
		<form method="post">
				Logged in as: '. $c->param("uname") .'	
				<button name="logout" value="now">logout</button>
			</form>
	</div>';
}
elsif(	$c->cookie('USER')  )
{
	print "Content-type: text/html\n\n";
	print '<div class="user">
			<form method="post">
				Logged in as: '. $c->cookie('USER') .'
				<button name="logout" value="now">logout</button>
			</form>
	</div>';
}
else
{
	print "Content-type: text/html\n\n";
	print'
	<div class="user">
		<form name="login" method="post" action="">
			<input type="text" name="uname">
			<button type="submit">login</button>
		</form>
	</div>';
}






print
'
<style>
.user
{
	width:100%;
	height:40px;
	background-color:#222;
	color:#e7e7e7;
}
</style>
';