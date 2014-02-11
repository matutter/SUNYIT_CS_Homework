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

  					var res = $("#hw3form").serialize()
  					
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
		    			<table class="table table-condensed">
		    				<tbody>
				    		<th><label for="input1">Information</label></th>
				    		<tr>
				    			<td><strong>Name</strong></td>
				    			<td>
				    				<input value="mat" name="fname" type="text" id="fname" class="form-control">
	            					<input value="utter" name="fname" type="text" id="lname" class="form-control">
	            				</td>
			    			</tr>
			    			<tr>
			    				<td>
			    					<strong>Species</strong>
			    				</td>
			    				<td>
									<input type="radio" name="type" value="human" checked>Human 
					            	<input type="radio" name="type" value="alien">Alien
			    				</td>
			    			</tr>
			    			<tr>
				    			<td>
				    				<strong>Status</strong>
				    			</td>
				    			<td>
				    				<input type="checkbox" name="health" value="alive">Alive
									<input type="checkbox" name="health" value="dead">Dead 
								    <input type="checkbox" name="health" value="alive&dead" checked>Other
				    			</td>
			    			</tr>
			    			<tr>
			    				<td>
			    					<strong>Comment</strong>
			    				</td>	
			    				<td>
				    				<textarea name="comment" class="form-control" rows="4" cols="50">I love text areas SOOO much!</textarea>
			    				</td>
			    			<tr>
			    			<tr>
			    				<td>
			            		<button id="hw3btn" class="btn btn-default">Submit</button>
			    				</td>
			    				<td>
				            		<res1></res1>			    					
			    				</td>
			    			</tr>
	    					</tbody>
	    					</table>

            		</div></form>';
     		print '</div>';
			print '</div>';
		} 
print '<div class="col-sm-6"><res2></res2><div>';