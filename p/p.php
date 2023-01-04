<?php

//this is also required
//chmod o+w unix_sock.server

system("/var/www/html/b.out");


/*
//not working

echo "unlink is starting\n";
//$file = "/var/www/html/myclient.sock";
$file = "/tmp/unix_sock.client";
unlink($file);

echo "socket_create is starting\n";
$socket = socket_create(AF_UNIX, SOCK_DGRAM, 0);

echo "socket_bind is starting\n";
if (socket_bind($socket, $file) === false) {
  echo "bind failed";
}

//$file2="/var/www/html/myserver.sock";
$file2="unix_sock.server";

echo "socket_sendto is starting to $file2\n";
if(socket_sendto($socket, "Hello world!", 12, 0, $file2, 0)===false){
  echo "sendto failed";
}

echo "socket_recvfrom is starting\n";
if (socket_recvfrom($socket, $buf, 64 * 1024, 0, $source) === false) {
  echo "recv_from failed";
}
echo "received: [" . $buf . "]   from: [" . $source . "]\n";
*/

?>
