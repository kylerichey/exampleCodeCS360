var fs = require('fs');
var path = process.argv[2];

file =fs.readFile(path,  function callback(error, data){
	
	strData = data.toString();
	var numLines = strData.split('\n').length -1;
	console.log(numLines);
});


