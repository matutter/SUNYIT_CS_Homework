function loadPage(s) {
	//alert(s)
	$.ajax({
		type: "POST",
		url: "scripts/fileReader.php",
		data: {loadPage:s},
		success: function(res) {
			//alert(res)
			$('#files').prepend("<ul>")
			res = res.split(',')
			if(res.length < 1) {
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
	    url: "scripts/settings.php",
	    data: {init:"start"},
	    success: function(res){
	    	$('.display-name').text(res.dn)
	    	$('.alt-msg .email').text(res.em)
	    	$('.alt-msg p').html(res.st)
	    	if(res.sb == 0) { 
	    		$('.sub-nav').hide();
				$('#sb').text("Off")
	    	}
	    	$('#dn').attr('value',res.dn)
	    	$('#em').attr('value',res.em)
	    	$('#st').attr('value',res.st)
		}
	})
}

function tryToLogin() {
	$.ajax({
	    type: "POST",
	    url: "scripts/settings.php",
	    data: {login:JSON.stringify($('form#login').serialize())},
	    success: function(res){
	    	if(res == 1) {
	    		$('.mask').remove()
	    		$('.login').slideToggle('fast')
	    		$('.console input, .console button').prop('disabled', false)
	    		$('nav #login').text('Logout').attr('id',"logout")
	    	}
	    	else $('.login').effect('shake')
	    }
	})
}

function logOut() {
	$.ajax({
	    type: "POST",
	    url: "scripts/settings.php",
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
			if(link.match('.pl|.cgi')) {
				$('#code').html(s)
				$('.download').addClass('disabled')
			}
			else {
				$('#code').html(s.SyntaxHighlight()) //load as text not a file
				$('.download').removeClass('disabled')
			}
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
		/*if (fname.match('.pl')) { 
			//alert("Cannot download server side scripts")
			return
		}*/ // to stop attempting to download things without URIDATA
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
		if($(this).attr('id') == 'logout') logOut()
			else $('.login').slideToggle('fast')
	})
	$('form a#login').click(function(){ tryToLogin(); })


})
String.prototype.SyntaxHighlight = function() {
	//return this.replace(/\</g,"&lt;").replace(/\>/g,"&gt;").replace(/\(/g,'(<pr>').replace(/\)/g,'</pr>)')
	return this.replace(/\</g,"&lt;").replace(/\>/g,"&gt;")
	//s = this;
	//return s
}
