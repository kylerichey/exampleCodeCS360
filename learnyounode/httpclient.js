var https = require('https');
var url = process.argv[2];

https.get(url, function(request,resp){
	request.setEncoding("utf8");
	request.on("data", function(data){
		console.log(data);		
	});		
});