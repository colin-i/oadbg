<?php

//this is also required
//sudo chmod 777 unix_sock.server






//$exec = "echo z | /usr/bin/sudo -S /var/www/html/b.out";
//echo $exec;
echo system("/var/www/html/b.out");

//exec($exec,$out,$rcode);

?>

<?php
/*
echo "unlink is starting\n";
//$file = "/var/www/html/myclient.sock";
$file = "/tmp/myclient.sock";
unlink($file);

echo "socket_create is starting\n";
$socket = socket_create(AF_UNIX, SOCK_DGRAM, 0);

echo "socket_bind is starting\n";
if (socket_bind($socket, $file) === false) {
  echo "bind failed";
}

//$file2="/var/www/html/myserver.sock";
$file2="/tmp/myserver.sock";

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
