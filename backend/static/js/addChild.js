$(function(){
	$('#btnAddUser').click(function(){
		
		$.ajax({
			url: '/add/user',
			data: $('form').serialize(),
			type: 'POST',
			success: function(response){
				console.log(response);
			},
			error: function(error){
				console.log(error);
			}
		});
	});
});



