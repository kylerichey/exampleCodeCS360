var fs = require('fs');
var path = require('path');
var dirPath = process.argv[2];
var extentionFilter = RegExp('\\.' + process.argv[3] + '$');
var extArray = [];
file = fs.readdir(dirPath, function callback(error, data) 
{
	data.forEach(function (file)
	{
		var extName = path.extname(file)
		if(extentionFilter.test(extName))
		{
			//extArray += file;
			console.log(file);
		}
	});
	
	//console.log(extArray);
});