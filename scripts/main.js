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

$(document).ready(function(){
	var last = "cs249"
	var link = ""
	var fname= ""
	$('.download, #back, #console').hide()
	loadPage(last)

	$('.files').on('click','a',function(){
		link = $(this).attr('link')
		fname = $(this).text()
		$('#title').html(fname)
		$('.download').show()
		$.get(link, function(s){
			$('#code').text(s) //load as text not a file
		})
	})

	$('.major-nav li').click(function(){
		$('#files').empty()
		$(this).addClass('active').siblings().removeClass('active')
		last = $(this).attr('id')
		loadPage(last)
	})

	$('.download').click(function(){
		var pom = document.createElement('a')
		pom.setAttribute('href', link)
		pom.setAttribute('download', fname)
		pom.click()
	})

	$('#manage, #back').click(function(){
		$('#main, #back, #manage, #console').toggle()
	})
	$(document).scroll(function(){
		if($(this).scrollTop() != 0)
			$('.sub-nav').slideUp()
	})
	$('.nav-bot').click(function(){
		$('.sub-nav').slideToggle()
	})
})
