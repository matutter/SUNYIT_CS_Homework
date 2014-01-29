function loadPage(s) {
	//alert(s)
	$.ajax({
		type: "POST",
		url: "scripts/main.php",
		data: {loadPage:s},
		success: function(res) {
			$('#files').prepend("<ul>")
			res = res.split(',')
			if(res.length < 2) {
				$('#files').prepend("No files")
				return;
			}
			$(res).each(function(i){
				$('#files').append('<li><a link="homework/'+s+'/'+res[i]+'">'+res[i]+'</a></li>')	
			})
			$('#files').append("</ul>")
		}
	})
}