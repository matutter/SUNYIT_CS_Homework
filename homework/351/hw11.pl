#!/usr/bin/perl
$QKEY = "::";
$| = 1;
use CGI;
use strict;
use warnings;
use Data::Dumper;
#use CGI::Imagemap;
my $c = CGI->new;
#use Imagemap;
#my $map = new CGI::Imagemap;


print "Content-type: text/html\n\n";

#$map->setmap(@map);
#$action = $map->action($x,$y);

my $path; # = %ENV->{"SERVER_NAME"} . %ENV->{"SCRIPT_NAME"};
#my @parts = split("/",$path);
#pop @parts;
#print @parts;
#$path = join("/",@parts) . "/tree.jpg";

$path = "tree.jpg";
print "<a href=\"$path\">" . $path . "<a><br>";

print $c->start_form,
$c->image_button
(
	-name=>'stupid',
	-src=>$path,
	-width=>480,
	-height=>180
),
$c->end_form;

					#XL    YT    XR   YB
my @lr = ( 332, 123, 410, 163);
my @br = ( 177, 31, 300, 170);
if($c->param())
{
	my $x = $c->param("stupid.x");
	my $y = $c->param("stupid.y");
	#print "<br> x: $x <br> y: $y <br>";
	#print "$x >= " . @lr[0] . " && $x <= " . @lr[2];
	if( $x >= @lr[0] && $x <= @lr[2] && $y >= @lr[1] && $y <= @lr[3])
	{
		print "little rock";
	}
	elsif( $x >= @br[0] && $x <= @br[2] && $y >= @br[1] && $y <= @br[3])
	{
		print "big rock";
	}
	else
	{
		print "nothing";	
	}

}

print
'<br>
<style>
.mapTest
{
	width:480;
	height:180;
	background: url(tree.jpg);
	background-size: 480px 180px;
	z-index:2;
}
.map-box
{
	border:3px solid rgba(255,0,0,0.1);
	display:block;
	position:absolute;
}
.map-box:hover
{
	border:3px solid red;
}
</style>

<a href="">
<img src="tree.jpg" height="180" width="480" ismap usemap="#rocks">
</a>
<map name="rocks">
<area shape=cirlce coords="177, 31, 300, 170"  href="?rock1=t" >
<area shape=cirlce coords="332, 123, 410, 163" href="?rock2=t" >
<area shape=default href="?nothing=t">
</map>
<br>
';
if($c->param())
{
	if($c->param("rock1"))
	{
		print "big rock";
	}
	elsif($c->param("rock2"))
	{
		print "small rock";
	}
	else
	{
		print "nothing";
	}
}

print
'
<br><br>alternative client side<br>
<div class="mapTest">
<a href="?rock1=t" class="map-box" style="height:150px;width:120px;margin-top:20px;margin-left:170px;"></a>
<a href="?rock2=t" class="map-box" style="height:50px;width:80px;margin-top:110px;margin-left:320px;"></a>
</div>
';