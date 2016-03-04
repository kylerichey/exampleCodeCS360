var fs = require('fs');
var path = require('path');

module.exports =function(dirname, ext, callback){
	var extension = "." + ext;
	fs.readdir(dirname, function(error, data) {
		if(error) {
			callback(err, null);
		}
		else {
			var results = [];
			data.forEach(function (file) {				
				if(path.extname(file) == extension) {				
					results.push(file)
				}
			});		
			callback(null, results);		
		}
	});

};