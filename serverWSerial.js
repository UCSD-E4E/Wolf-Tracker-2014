//server.js
var http = require('http');
var fs = require('fs');

//set up the serial port
var SerialPort = require("serialport").SerialPort;
var serialport = new SerialPort("/dev/ttyO1", {
    baudrate: 57600
});

//opens the serial port for us to use
serialport.on('open', function(){
});

function sendToArduino(data){
    for(var i = 0; i < data.length; i++){
        serialport.write(data.charAt(i));
    }
    serialport.write('\n');
}

//create the server
http.createServer(function(req,res){
  if(req.method == 'POST'){
    var body = '';
    req.on('data',function(data){
      body += data;
    });
    req.on('end',function(){
      var OBJ = JSON.parse(body);
      var stringData =  "L:" + OBJ.leftStick.toFixed(2) + "|" +
                        "R:" + OBJ.rightStick.toFixed(2) + ";";
      sendToArduino(stringData);

    });
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('post recieved');
  } else {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('Hello Node.js\n');
  }
}).listen(8124, "127.0.0.1");
console.log('Server running at http://127.0.0.1:8124/');