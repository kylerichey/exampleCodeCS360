var numArgs = process.argv.length;
var total =0;
for(var i =2; i< numArgs; i++)
{
	total += Number(process.argv[i]);
}

console.log(total);