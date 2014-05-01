function loadPage(s) {
	var part = s.split('&')
	$.ajax({
		type: "POST",
		url: "scripts/fileReader.php",
		data: {loadPage:part[0]},
		success: function(res) {
			//alert(res)
			//$('#files').prepend("<ul>")
			res = res.split(',')
			if(res.length < 1) {
				$('#files').prepend("No files")
				return;
			}
			$(res).each(function(i){
				$('#files').append('<li link="homework/'+s+'/'+res[i]+'">'+res[i]+'</li>')	
			})
			//oadCode(part[1], $('#code'))
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

function loadCode(link, target) {
//	alert( "file " + link )
	$.ajax({
	    type: "POST",
	    url: "scripts/codeformat.php",
	    data: {"loadCodeFile":link},
	    success: function(res){
	    	target.html( res )
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
	if(window.location.hash) {
		var hash = window.location.hash.substring(1);
		loadPage(hash)
		$('#'+hash).addClass('active').siblings().removeClass('active')
	}
	else
		loadPage(last)

	$('.files').on('click','li',function(){
		link = $(this).attr('link')
		fname = $(this).text()
		$('#title').fadeOut("fast",function(){
			$(this).html(fname).fadeIn("fast")
		})
		$('.download').show()
		$.get(link, function(s){
			loadCode(link, $('#code'))
		})
	})

	$('.major-nav li').click(function(){
		$('#files').empty()
		$(this).addClass('active').siblings().removeClass('active')
		last = $(this).attr('id')
		loadPage(last)
	})

	$('#manage, #back').click(function(){
		$('#main, #back, #manage, #console').toggle()
	})
	$(document).scroll(function(){
		if($(this).scrollTop() != 0)
			$('.sub-nav').slideUp()
	})

	$('nav #login').click(function(){ 
		if($(this).attr('id') == 'logout') logOut()
			else $('.login').slideToggle('fast')
	})
	$('form a#login').click(function(){ tryToLogin(); })


})