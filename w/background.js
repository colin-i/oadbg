


function begin(){
	//chrome.browserAction.onClicked.addListener(() => {
	chrome.action.onClicked.addListener(connect);
}

function connect(){
	chrome.action.onClicked.removeListener(connect);
	chrome.tabs.query({active: true, currentWindow: true}, tabs => {//lastFocusedWindow
		const queryString = tabs[0].url.split('?')[1];//self.location.search;
		console.log(queryString);
		const urlParams = new URLSearchParams(queryString);
		console.log(urlParams);
		const is_broadway = urlParams.keys().next().value;
		console.log(is_broadway);

		let port;
		if(is_broadway=="1")port = chrome.runtime.connectNative('oadbgb');
		else port = chrome.runtime.connectNative('oadbg');

		port.onMessage.addListener(function(msg) {
		  console.log('in');
		  console.log(msg);
		});
		port.onDisconnect.addListener(function() {
		  console.log("Disconnected");
		  begin();
		});
		//port.postMessage({text:is_broadway});
		//chrome.action.onClicked.addListener(() => {
		//  console.log('out');
		port.postMessage({text:"ping"});
		//});
	});
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
