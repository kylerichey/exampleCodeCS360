var lslib = require('./lslib.js')
var dirname = process.argv[2];
var ext = process.argv[3];

lslib(dirname,ext,function(err,files){
	files.forEach(function (file) {
			console.log(file);
	})	;
});
