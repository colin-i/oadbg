


function begin(){
	//chrome.browserAction.onClicked.addListener(() => {
	chrome.action.onClicked.addListener(connect);
}

function check_response(){//response
	//if(response)begin();
	//else{
	chrome.tabs.query({active: true, currentWindow: true}, tabs => {//lastFocusedWindow
		if(tabs.length>0){
			const queryString = tabs[0].url.split('?')[1];//self.location.search;
			console.log(queryString);
			const urlParams = new URLSearchParams(queryString);
			console.log(urlParams);
			const is_broadway = urlParams.keys().next().value;
			console.log(is_broadway);
	
			let port;
			if(is_broadway=="1")port = chrome.runtime.connectNative('oadbgb');
			else port = chrome.runtime.connectNative('oadbg');
	
			//chrome.runtime.lastError is nullified after default print error
			//console.error= function (arg) { is not working
			//if(port.name){ is always ""
			//port.onDisconnect is not called if the application is missing
			//the only solution left is to call a third checker
	
			port.onDisconnect.addListener(function() {
			  console.log("Disconnected");
			  begin();
			});
			port.onMessage.addListener(function(msg) {
			  console.log('in');
			  console.log(msg);
			});
			//port.postMessage({text:is_broadway});
			//chrome.action.onClicked.addListener(() => {
			//  console.log('out');
			port.postMessage({text:"ping"});
			//});
		}else begin();
	});
}
function check_error(error){
	const s=`${error}`;
	console.error(s);
	begin();
}

function connect(){
	chrome.action.onClicked.removeListener(connect);
	const promise=chrome.runtime.sendNativeMessage("oadbge", { text:"1" });//,{text:""},check_response
	promise.then(check_response,check_error);
}
begin();



//On startup, connect to the "ping_pong" app.
//let port = browser.runtime.connectNative("ping_pong");

//Listen for messages from the app.
//port.onMessage.addListener((response) => {
//  console.log(`Received: ${response}`);
//});

//port.onDisconnect.addListener((msg)=>{
//	console.log("browser.runtime.lastError : " + JSON.stringify(browser.runtime.lastError));
//	console.log("Ondisconnect Argument : " + JSON.stringify(msg));
//});

//On a click on the browser action, send the app a message.
//browser.browserAction.onClicked.addListener(() => {
//  console.log("Sending:  ping");
//  port.postMessage("ping");
//});
