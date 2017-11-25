$(function() {
	$('#btnGetUser').click(function(){
    $.ajax({
        url: '/get/user',
		data: $('form').serialize(),
    }).then(function(data) {
			$('.user_id').append(data.id);
			$('.user_name').append(data.name);
			$('.user_age').append(data.age);
			$('.user_total_score').append(data.totalScore);
			$('.user_daily_score').append(data.scores);
    });
	});
});



