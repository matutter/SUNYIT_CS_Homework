#!/usr/bin/perl
$| = 1;
use CGI qw();
my $c = CGI->new;
use GD::Simple;

my $size = 500;

my $img = GD::Simple->new($size,$size);
my $blue = $img->colorAllocate( 0, 0, 255);
my $black= $img->colorAllocate( 0, 0, 0 );
my $white= $img->colorAllocate( 255, 255, 255 );
if ($c->param()) {

	print $c->header("image/png");
	$img->filledRectangle( 0, 0, $size, $size, $white );
	my $i = 0;

	#my $bars = 400 / $c->param() - 2*$c->param();
	my $count = $c->param() - 1;
	my @data = $c->param();
	@data = @data[1 .. $count];
	$count = @data;
	my $bars = $size / $count - 2;
	my $height = $c->param("max");

	my $x1=0;
	my $y1=$size;
	my $x2=$bars;
	my $y2=$size;
	my $scale = $size / $height;
	@data = reverse( @data );
	foreach(@data) {

		$y1 =  $_  ;
		$y1 = $y1 * $scale;
		$y1 = sprintf "%.0f",$y1;

		my $color = $y1/$size * 200 + 55;
		$color = sprintf "%.0f", $color;
		my $temp = $img->colorAllocate( 255, $color, $color );

		$img->filledRectangle( $x1, $y1, $x2, $y2, $temp );

		$x1 = $x1 + $bars + 2;
		$x2 = $x2 + $bars + 2;
	}
	$img->moveTo(30,20);
    $img->string("Bars: ".$count);
	$img->moveTo(30,30);
    $img->string("Max: ".$height);
	$img->moveTo(30,40);
    $img->string("Scale: ".$scale);
	print $img->png;
}
else
{
	print $c->header("image/png");
	$img->filledRectangle( 0, 0, 400, 400, $white );
	$img->moveTo(200,120);
    $img->string('NO DATA RECIEVED');
	print $img->png;
}

#	my $bars = join("&",$c->param());
#	print "<img src=\"hw8_graph.pl?$bars\"><br>";