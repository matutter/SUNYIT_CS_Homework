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

function initUser(l) {
	if(l) {
		$('.mask').remove()
		$('.console input, .console button').prop('disabled', false)
		$('nav #login').text('Logout').attr('id',"logout")
	}
	$.ajax({
	    type: "POST",
	    dataType: "json",
	    url: "settings.php",
	    data: {init:"start"},
	    success: function(res){
	    	$('.display-name').text(res.dn)
	    	$('.alt-msg .email').text(res.em)
	    	$('.alt-msg p').html(res.st)
	    	$('.alt-msg a').attr('href',res.li)
	    	if(res.sb == 0) { 
	    		$('.sub-nav').hide();
				$('#sb').text("Off")
	    	}
	    	$('#dn').attr('value',res.dn)
	    	$('#em').attr('value',res.em)
	    	$('#st').attr('value',res.st)
	    	$('#li').attr('value',res.li)
		}
	})
}

function tryToLogin() {
	$.ajax({
	    type: "POST",
	    url: "settings.php",
	    data: {login:JSON.stringify($('form#login').serialize())},
	    success: function(res){
	    	if(res == 1) {
	    		$('.mask').remove()
	    		$('.login').slideToggle('fast')
	    		$('.console input, .console button').prop('disabled', false)
				$('nav #login').text('Logout').attr('id',"logout")
	    	}
	    }
	})
}

function logOut() {
	$.ajax({
	    type: "POST",
	    url: "settings.php",
	    data: {out:1},
	    success: function(res){
	    	location.reload();
	    }
	})
}


$(document).ready(function(){
	var last = "cs249"
	var link = ""
	var fname= ""
	$('.download, #back, #console, .login').hide()
	$('.console input, .console button').prop('disabled', true)
	//initUser()
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
	$('nav #login').click(function(){ 
		if($(this).attr('id') == 'logout') logOut();
		$('.login').slideToggle('fast')
	})
	$('form a#login').click(function(){ tryToLogin(); })


})
