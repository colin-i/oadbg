
// include the PHP API itself
#include <php.h>
// then include the header of your extension
#include "php_helloworld.h"

// register our function to the PHP API
// so that PHP knows, which functions are in this module
zend_function_entry helloworld_php_functions[] = {
    PHP_FE(helloworld_php, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry helloworld_php_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_HELLOWORLD_EXTNAME,
    helloworld_php_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_HELLOWORLD_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(helloworld_php)




//#include <unistd.h> // for fork() unlink close
//#include <stdio.h> // for printf
//#include <stdlib.h> // for exit()
//#include <sys/socket.h>
#include <sys/un.h> // socket in Unix

// for print error message
//#include <string.h>
//#include <errno.h>

#define CLIENT_SOCK_PATH "/tmp/unix_sock.client"
#define SERVER_SOCK_PATH "unix_sock.server"

#define CLIENT_MSG "HELLO FROM CLIENT"




// Finally, we implement our "Hello World" function
// this function will be made available to PHP
// and prints to PHP stdout using printf
PHP_FUNCTION(helloworld_php) {

    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    int rc;
    char buf[256];
    /**************************************************/
    /* Open a client socket (same type as the server) */
    /**************************************************/
    int client_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_sock == -1)
    {
        php_printf("CLIENT: Socket error: %s\n", strerror(errno));
        exit(1);
    }
    php_printf("socket ok\n");

    /********************************************/
    /* Bind client to an address on file system */
    /********************************************/
    // Note: this binding could be skip if we want only send data to server without receiving
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, CLIENT_SOCK_PATH);
    int len = sizeof(client_addr);
    unlink (CLIENT_SOCK_PATH);
    rc = bind(client_sock, (struct sockaddr *)&client_addr, len);
    if (rc == -1)
    {
        php_printf("CLIENT: Client binding error. %s\n", strerror(errno));
        close(client_sock);
        exit(1);
    }
    php_printf("bind ok\n");

    /****************************************/
    /* Set server address and connect to it */
    /****************************************/
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SERVER_SOCK_PATH);
    rc = connect(client_sock, (struct sockaddr*)&server_addr, len);
    if(rc == -1)
    {
        php_printf("CLIENT: Connect error. %s\n", strerror(errno));
        close(client_sock);
        exit(1);
    }
    php_printf("CLIENT: Connected to server.\n");

    /**************************/
    /* Send message to server */
    /**************************/
    memset(buf, 0, sizeof(buf));
    strcpy(buf, CLIENT_MSG);
    rc = send(client_sock, buf, sizeof(buf), 0);
    if (rc == -1)
    {
        php_printf("CLIENT: Send error. %s\n", strerror(errno));
        close(client_sock);
        exit(1);
    }
    php_printf("CLIENT: Sent a message to server.\n");

    /**************************************/
    /* Listen to the response from server */
    /**************************************/
    printf("CLIENT: Wait for respond from server...\n");
    memset(buf, 0, sizeof(buf));
    rc = recv(client_sock, buf, sizeof(buf), 0);
    if (rc == -1)
    {
        php_printf("CLIENT: Recv Error. %s\n", strerror(errno));
        close(client_sock);
        exit(1);
    }
    php_printf("CLIENT: Message received: %s\n", buf);
    php_printf("CLIENT: Done!\n");
    close(client_sock);
    remove(CLIENT_SOCK_PATH);
}
