

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

var port = chrome.runtime.connectNative('ping_pong');
port.onMessage.addListener(function(msg) {
  console.log("Received" + msg);
});
port.onDisconnect.addListener(function() {
  console.log("Disconnected");
});

//chrome.browserAction.onClicked.addListener(() => {
chrome.action.onClicked.addListener(() => {
  console.log("Sending:  ping");
  port.postMessage({ text: "ping" });
});
