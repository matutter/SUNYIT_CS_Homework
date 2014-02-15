#!/usr/bin/perl

## Turns off buffering
$| = 1; #why?
use strict;
use warnings FATAL => 'all';
use CGI qw();

my $c = CGI->new;

my @origins = ('United States','Utica','Planet','Space');
my @powers = ('flying','laser eyes','bullet proof','ice breath','fire breath','hammer');

print "Content-type: text/html\n\n";
print '<div class="col-sm-12 style="overflow:hidden;">';
	print '<div style="white-space:pre">';
		print '<div class="page-header"> <h4>Hw3 Mat Utter <small class="pull-right">'.localtime.'</small> </h4> </div>';


		if ('POST' eq $c->request_method && $c->param('data')) {
			my $res = $c->param('data');
			$res=~ s/\+/ /g;
			$res=~ s/\%5B\%5D|D5%B5%//g;
		   	my @chunks = split /\&/, $res;

		   	my %bits;
		   	print "You said that your\n";
		   	foreach(@chunks){
		   		my @part = split /\=/, $_ ;
		   		if(defined($bits{$part[0]})) {
		   			$bits{$part[0]}	.= " ";
		   		}
		   		$bits{$part[0]} .= $part[1];		   		
		   	}
		   	if(defined($bits{"health"}) ) {
		   		if($bits{"health"} eq "alive dead") {
	   				$bits{"health"} = "Zombie!!!";	
		   		}
		   	}
		   	#print in no particular order		   	
		   	print "$_ is $bits{$_}\n" for (keys %bits);

		   	#print with natural sort
		   	##not written yet

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
  					if(	$(document.activeElement).val() == "translate")
  						res = res.split("").reverse().join("")
					else if( $(document.activeElement).val() == "clear") {
						$("input,select,textarea").val("").prop("checked", false)
						return
					}
					
					if(posts > 5) { $("res1").empty().append("Stop making requests please..."); return; }
					
					$.ajax({
						type:"POST",
						url:"homework/cs351/hw3.pl",
						dataType: "html",
						data: { data: res },
						success: function(res) {
							$("res1,res2").empty()
							$("res2").append(res)
							++posts
							//$("res1").append("<strong>I MADE that POST ["+(++posts)+"]\n</strong>");
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
				    				<input value="mat" name="Fistname" type="text" id="fname" class="form-control">
	            					<input value="utter" name="LastName" type="text" id="lname" class="form-control">
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
				    				<input type="checkbox" name="health[]" value="alive" checked>Alive
									<input type="checkbox" name="health[]" value="dead">Dead
				    			</td>
			    			</tr>
			    			<tr>
			    				<td>
			    					<strong>Origin</strong>
			    				</td>
			    				<td>
			    					<select name="origin">';
			    					foreach(@origins){
			    						print '<option value="'. $_ .'">'. $_ .'</option>';
			    					}
			    			print	'</select>
			    				</td>
			    			</tr>
			    			<tr>
			    				<td>
			    					<strong>Super Powers</strong>
			    				</td>
			    				<td>
			    					<select multiple name="power" class="form-control">';
			    					my $i=0;
									foreach(@powers){
										$i++;
										if($i eq 1 || $i eq 2) {
											print '<option selected value="'. $_ .'">'. $_ .'</option>';											
										}
										else {
											print '<option value="'. $_ .'">'. $_ .'</option>';
										}
			    					}
			    			print '	</select>
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
			    				<button id="translate" class="btn btn-default" name="submit" value="translate">Alien Submit</button>
			            		<button id="hw3btn" class="btn btn-default" name="submit" value="normal">Normal Submit</button>
			            		<button class="btn btn-danger" name="clear" value="clear">Clear Form</button>
			    				</td>
			    				<td>
				            		<res1 class="container"></res1>			    					
			    				</td>
			    			</tr>
	    					</tbody>
	    					</table>

            		</div></form>';
     		print '</div>';
			print '</div>';
		} 
print '<div class="col-sm-6"><res2></res2><div>';