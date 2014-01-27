function loadPage(s) {
	//alert(s)
	$.ajax({
		type: "POST",
		url: "scripts/main.php",
		data: {loadPage:s},
		success: function(res) {

			res = res.split(',')
			if(res.length < 2) return;
			$(res).each(function(i){
				$('.panel-body').append('<li><a href="../homework/'+s+'/'+res[i]+'">'+res[i]+'</a></li>')	
			})
		}
	})
}