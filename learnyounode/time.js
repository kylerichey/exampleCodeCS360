var net = require('net')
var port = Number(process.argv[2])


function pad(n) { return n < 10 ? '0' + n : n }


var server = net.createServer(function (socket) {
	  d = new Date();
  s = d.getFullYear() + "-"
    + pad(d.getMonth() + 1) + "-"
    + pad(d.getDate()) + " "
    + pad(d.getHours()) + ":"
    + pad(d.getMinutes()) + "\n";
  socket.end(s);
})
server.listen(port)
