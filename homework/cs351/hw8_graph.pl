#!/usr/bin/perl
$| = 1;
use CGI qw();
my $c = CGI->new;
use GD::Simple;

my $size = 500;
my $offset = 30;
my $img = GD::Simple->new($size+$offset,$size);
my $blue = $img->colorAllocate( 0, 0, 255);
my $black= $img->colorAllocate( 0, 0, 0 );
my $white= $img->colorAllocate( 255, 255, 255 );
if ($c->param()) {

	print $c->header("image/png");
	$img->filledRectangle( 0, 0, $size, $size, $white );
	#$img->filledRectangle( 0, 0, $size, $size, $black );
	my $i = 0;

	#my $bars = 400 / $c->param() - 2*$c->param();
	my $count = $c->param() - 1;
	my @data = $c->param();
	@data = @data[3 .. $count];
	$count = @data;
	my $bars = $size / $count - 2;
	my $height	= $c->param("max");
	my $floor 	= $c->param("min");
	my $cols	= $c->param("cols");

	my $x1=0;
	my $y1=$size;
	my $x2=$bars;
	my $y2=$size;
	my $scale = $size / $height;
	my $highest_point = 0;
	my $base = $size - $floor * $scale + (1 * $scale);
	

	#@data = reverse( @data );
	foreach(@data) {

		$y1 =  $_ ;
		$y1 = $y1 * $scale;
		$y1 = sprintf "%.0f",$y1;

		my $color = $y1/$size * 255;
		$color = sprintf "%.0f", $color;
		my $temp = $img->colorAllocate( 255, 255 - $color, 255 - $color );

		if($highest_point < $y1)
		{
			$highest_point = $y1;
		}

		$img->filledRectangle( $x1 , $size - $y1, $x2, $y2, $temp );
		#$img->moveTo($x1 + $bars/2 - 3,$size - $y1 + 15);
	    #$img->string( $_ );

		$x1 = $x1 + $bars + 2;
		$x2 = $x2 + $bars + 2;
	}
	
	$x1=0;
	$y1=$size;
	$x2=$bars;
	$y2=$size;
	my $step = 0;
	my $val = @data[0];
	my $p1=0, $p2;
	foreach(@data) {
		if($step == $cols)
		{
			$step = 0;
			#$img->moveTo($x1 - ($bars*$cols)/2 ,$size - $y1 + 15);
			$img->moveTo($p1+$bars,$size - $y1 + 5);
		    $img->string( sprintf "%.0f",$val );

			$img->filledRectangle( $p1, 500-$_*$scale, $p1, 500, $blue );
			$p1 = $x1-1;
		}
		else
		{
			$step++;
			$val = running_avg($step,$val,$_);
		}

		$y1 =  $_ ;
		$y1 = $y1 * $scale;
		$y1 = sprintf "%.0f",$y1;

		$x1 = $x1 + $bars + 2;
		$x2 = $x2 + $bars + 2;
	}

	$img->filledRectangle( 0, $base, 500, $base-1, $blue );
	$img->moveTo(30,20);
    $img->string("Bars: ".$count);
	$img->moveTo(30,30);
    $img->string("min/max: ".$floor."/".$height);
	$img->moveTo(30,40);
    $img->string("Scale: ".$scale);
   	$img->moveTo(30,50);
    $img->string("High Point: ".$highest_point);
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

sub running_avg
{
	my $count=$_[0], $old=$_[1], $new=$_[2];
	$old = $old - $avg/$count;
	$new = $old + $new/$count;
	return $new;
}
#	my $bars = join("&",$c->param());
#	print "<img src=\"hw8_graph.pl?$bars\"><br>";