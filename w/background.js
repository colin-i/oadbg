
let pageport;

function begin(msg){
	pageport.onMessage.removeListener(begin);
	const is_broadway=msg.text;

	if(is_broadway)port = chrome.runtime.connectNative('oadbgb');
	else port = chrome.runtime.connectNative('oadbg');

	port.onDisconnect.addListener(function() {
	  console.log("Disconnected");
	});
	port.onMessage.addListener(function(msg) {
	  console.log('in');
	  console.log(msg);
	});
	port.postMessage({text:"ping"});

	pageport.onMessage.addListener(instructions);
	pageport.postMessage({});//send oadbg connected (or not but we unimplemented the extension action click so here is not a noob area)
}

// For long-lived connections:
chrome.runtime.onConnectExternal.addListener(function(p) {
	pageport=p;
	pageport.onMessage.addListener(begin);//recv arguments
});

function instructions(msg){
	console.log(msg.text);
}




//chrome.runtime.lastError is nullified after default print error
//console.error= function (arg) { is not working
//if(port.name){ is always ""
//port.onDisconnect is not called if the application is missing
//the only solution left is to call a third checker



//const promise=chrome.runtime.sendNativeMessage("oadbge", { });//,{text:""},check_response
//promise.then(check_response,check_error);



//function check_error(error){
//	const s=`${error}`;
//	console.error(s);
//}


//chrome.action.onClicked.addListener(connect);


//	chrome.tabs.query({active: true, currentWindow: true}, tabs => {//lastFocusedWindow: true
//		if(tabs.length>0){
//			const tab=tabs[0];



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




//,"scripting"
//chrome.scripting.executeScript({
//	target: { tabId: tab.id },
//	files: ["content-script.js"]
//});
//return;

//Refused to load the script because it violates the following Content Security Policy directive: "script-src 'self' ...
//ruffle.src="/dist/ruffle.js"

//document.addEventListener('oadbg-ready', dbgready);
//document.dispatchEvent(new CustomEvent('oadbg-ready', { }));

//player=document.getElementById("container").children[0];
//player is not having ruffle api in content script, only structure. tryed also through dispatchEvent

//Only the web page can initiate a connection. (page<->bgscript)

//loadedmetadata is not for the tag
//		setTimeout(() => {
//			console.log(player);
//			console.log(player.pause);
//			player.pause();
//		}, "10000");



//test.c
//int a=0; will crash chrome
//char a[]={2,0,0,0,'\"','\"'};
//write(fileno(stdout),&a,6);
//fwrite(&a,4,1,stdout);
