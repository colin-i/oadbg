
/**
 * Sample for UNIX domain socket
 * Two-way communication between process server and client:
 * 1) Client connect and say hello to server
 * 2) Server receive client message and display
 * 3) Server say hello back to client
 * 4) Client receive server message and display
 * 5) Done.
 */

#include <unistd.h> // for fork() unlink close
#include <stdio.h> // for printf
#include <stdlib.h> // for exit()
#include <sys/socket.h>
#include <sys/un.h> // socket in Unix

// for print error message
#include <string.h>
#include <errno.h>

#define CLIENT_SOCK_PATH "/tmp/unix_sock.client"
#define SERVER_SOCK_PATH "unix_sock.server"

#define CLIENT_MSG "HELLO FROM CLIENT"


int main(int argc, char **argv)
{
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    int rc;
    // for simplicity, we will assign a fixed size for buffer of the message
    char buf[256];


    //---------- CLIENT PROCESS
//    else
//    {
        /**************************************************/
        /* Open a client socket (same type as the server) */
        /**************************************************/
        int client_sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if (client_sock == -1)
        {
            printf("CLIENT: Socket error: %s\n", strerror(errno));
            exit(1);
        }

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
            printf("CLIENT: Client binding error. %s\n", strerror(errno));
            close(client_sock);
            exit(1);
        }

        /****************************************/
        /* Set server address and connect to it */
        /****************************************/
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, SERVER_SOCK_PATH);
        rc = connect(client_sock, (struct sockaddr*)&server_addr, len);
        if(rc == -1)
        {
            printf("CLIENT: Connect error. %s\n", strerror(errno));
            close(client_sock);
            exit(1);
        }
        printf("CLIENT: Connected to server.\n");

        /**************************/
        /* Send message to server */
        /**************************/
        memset(buf, 0, sizeof(buf));
        strcpy(buf, CLIENT_MSG);
        rc = send(client_sock, buf, sizeof(buf), 0);
        if (rc == -1)
        {
            printf("CLIENT: Send error. %s\n", strerror(errno));
            close(client_sock);
            exit(1);
        }
        printf("CLIENT: Sent a message to server.\n");

        /**************************************/
        /* Listen to the response from server */
        /**************************************/
        printf("CLIENT: Wait for respond from server...\n");
        memset(buf, 0, sizeof(buf));
        rc = recv(client_sock, buf, sizeof(buf), 0);
        if (rc == -1)
        {
            printf("CLIENT: Recv Error. %s\n", strerror(errno));
            close(client_sock);
            exit(1);
        }
        else
            printf("CLIENT: Message received: %s\n", buf);

        printf("CLIENT: Done!\n");

        close(client_sock);
        remove(CLIENT_SOCK_PATH);
//    }

    return 0;
}
