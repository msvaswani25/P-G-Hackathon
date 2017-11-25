$(function() {
	$('#btnGetUser').click(function(){
    $.ajax({
        url: '/get/user',
		data: $('form').serialize(),
    }).then(function(data) {
			$('.user_id')='ID: '+(data.id);
			$('.user_name')='Name: '+(data.name);
			$('.user_age')='Age: '+(data.age);
			$('.user_total_score')='Over All Score: '+(data.totalScore);
			$('.user_daily_score')='Daily Score: '(data.scores);			
    });
	});
});



