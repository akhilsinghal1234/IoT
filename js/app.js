$(document).ready(function(){
	$.ajax({
		url: "display1.php",
                dataType: 'json',
		success: function(data) {
			var id = [];
			var temp = [];
                        var humidity = [];

			for(var i in data) {
				id.push("Day " + data[i][0]);
                                //console.log(id[i]);
				temp.push(data[i][1]);
                                humidity.push(data[i][2]);
                                //console.log(temp[i]);
			}

			var chartdata = {
				labels: id,
				datasets : [
					{
						label: 'Temperature',
						backgroundColor: 'rgba(0,255,0, 0.7)',
						borderColor: 'rgba(0,255,0, 1)',
						hoverBackgroundColor: 'rgba(200, 200, 200, 1)',
						hoverBorderColor: 'rgba(200, 200, 200, 1)',
						data: temp
					}
				]
			};

			var ctx = $("#mycanvas");

			var barGraph = new Chart(ctx, {
				type: 'bar',
				data: chartdata
			});
		}
//		error: function(data) {
//		}
	});
});