 var fs = require('fs')
 var path = process.argv[2];
 var buffer = fs.readFileSync(path);
 var strBuffer = buffer.toString();
 var newlines = strBuffer.split('\n'); 
 console.log(newlines.length-1);