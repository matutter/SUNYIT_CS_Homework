#!/usr/bin/perl

## Turns off buffering
$| = 1; #why?
use strict;
use warnings FATAL => 'all';
use CGI qw();

my $c = CGI->new;

print "Content-type: text/html\n\n";
print '<div class="col-sm-12 style="overflow:hidden;">';
	print '<div style="white-space:pre">';
		print '<div class="page-header"> <h4>Hw3 Mat Utter <small class="pull-right">'.localtime.'</small> </h4> </div>';


		if ('POST' eq $c->request_method && $c->param('data')) {
			my $res = $c->param('data'); 
		   	print "I GOT that POST!\n";
		   	print $res;
		   	print "<br>";

		   	print "</div></div>";
		   	return;
		} else {

			print 
			'<script>
			$(document).ready(function(){
				var posts = 0;

				$( "form" ).on( "submit", function( event ) {
  					event.stopPropagation()
  					event.preventDefault()

  					var res = $("#input1").val()+"::"+$("#input1").attr("name")+","

					if(posts > 5) { $("res1").empty().append("Stop making requests please..."); return; }
					
					$.ajax({
						type:"POST",
						url:"homework/cs351/hw3.pl",
						dataType: "html",
						data: { data: res },
						success: function(res) {
							$("res1,res2").empty()
							$("res2").append(res)
							$("res1").append("<strong>I MADE that POST ["+(++posts)+"]\n</strong>");
						}

					})
				})
			})
			
			</script>';

			print '<div class="col-sm-6 style="overflow:hidden;">';
		    print "If you click submit I POST to myself.\nI show up on the side when posted to.\nRequests handled at timestamps.";
		    print	'<form id="hw3form" role="form" style="white-space:normal;">
			    		<div class="form-group">
	    					<label for="input1">text input</label>
	            			<input value="default" name="textbox!" type="text" id="input1" class="form-control">
		            		<button id="hw3btn" class="btn btn-default">Submit</button>
	            		<res1></res1></div>
            		</form>';
     		print '</div>';
			print '</div>';
		} 
print '<div class="col-sm-6"><res2></res2><div>';