#!/usr/bin/perl
    use MIME::Types;
    use strict;
    use warnings;
    use CGI;
    use CGI::Carp qw(fatalsToBrowser); #qweasdretylarp
    my $q = new CGI;
    my $MIME = new MIME::Types;

    start_page();

    print join "\n", $MIME->listTypes();
  
    end_page();


sub end_page {
  print '<div class="col-sm-6"><res2></res2><div>';
}

sub start_page {
  print "Content-type: text/html\n\n";
  print '<div class="col-sm-12 style="overflow:hidden;">';
    print '<div style="white-space:pre">';
      print '<div class="page-header"> <h4>matesting<small class="pull-right">'.localtime.'</small> </h4> </div>';
}