var webSocketUrl = "wss://api.artik.cloud/v1.1/websocket?ack=true";
var device_id = "";
var device_token = "";
var LED_PIN = 22;

var WebSocket = require('ws');
var isWebSocketReady = false;
var ws = null;

var puts = require('sys').puts;

var led = require('pi-pins').connect(LED_PIN);
led.mode('out');

function getTimeMillis(){
	return parseInt(Date.now().toString());
}

function start() {
	//Create the WebSocket connection
	isWebSocketReady = false;
	ws = new WebSocket(webSocketUrl);
	ws.on('open', function() {
			console.log("WebSocket connection is open ....");
			register();
			});
	ws.on('message', function(data) {
			console.log("Received message: " + data + '\n');
			handleRcvMsg(data);
			});
	ws.on('close', function() {
			console.log("WebSocket connection is closed ....");
			exitClosePins();
			});
}

function register(){
	console.log("Registering device on the WebSocket connection");
	try{
		var registerMessage = 
			'{"type":"register", "sdid":"'+device_id+'", "Authorization":"bearer '+device_token+'", "cid":"'+getTimeMillis()+'"}';
		console.log('Sending register message ' + registerMessage + '\n');
		ws.send(registerMessage, {mask: true});
		isWebSocketReady = true;
	}
	catch (e) {
		console.error('Failed to register messages. Error in registering message: ' 
				+ e.toString());
	}    
}

function sendLampStateToArtikCloud(state) {
	try{
		ts = ', "ts": '+getTimeMillis();
		var data = {
			"LED": state 
		};
		var payload = '{"sdid":"'+device_id+'"'+ts+', "data": '+JSON.stringify(data)+', "cid":"'+getTimeMillis()+'"}';
		console.log('Sending payload ' + payload + '\n');
		ws.send(payload, {mask: true});
	} catch (e) {
		console.error('Error in sending a message: ' + e.toString() +'\n');
	}
}


function handleRcvMsg(msg){
	var msgObj = JSON.parse(msg);
	if (msgObj.type != "action") return; //Early return;

	var actions = msgObj.data.actions;
	var actionName = actions[0].name; 
	console.log("The received action is " + actionName);
	var newState;
	if (actionName.toLowerCase() == "seton") { 
		newState = 1; 
		console.log('LED Turned On');
		led.value(true);
		sendLampStateToArtikCloud(true);
	} else if (actionName.toLowerCase() == "setoff") { 
		newState = 0; 
		console.log('LED Truned Off');
		led.value(false);
		sendLampStateToArtikCloud(false);
	} else {
		console.log('Do nothing since receiving unrecognized action ' + actionName);
		return;
	} 
}

function exitClosePins() {
	console.log('Exit and destroy all pins!');
	process.exit();
}

start();

