
/**
 * Sample for UNIX domain socket
 * Two-way communication between process server and client:
 * 1) Client connect and say hello to server
 * 2) Server receive client message and display
 * 3) Server say hello back to client
 * 4) Client receive server message and display
 * 5) Done.
 */

#include <unistd.h> // for fork()
#include <stdio.h> // for printf
#include <stdlib.h> // for exit()
#include <sys/socket.h>
#include <sys/un.h> // socket in Unix

// for print error message
#include <string.h>
#include <errno.h>

//#define SERVER_SOCK_PATH "/tmp/unix_sock.server"
#define CLIENT_SOCK_PATH "/tmp/unix_sock.client"
#define SERVER_SOCK_PATH "unix_sock.server"
//#define CLIENT_SOCK_PATH "unix_sock.client"

#define SERVER_MSG "HELLO FROM SERVER"
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

    // create two processes of client and server
//    pid_t pid = fork();


    //---------- SERVER PROCESS
//    if (pid != 0)
//    {
        // maximum number of client connections in queue
        int backlog = 10;

        /****************************************************/
        /* Open the server socket with the SOCK_STREAM type */
        /****************************************************/
        int server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if (server_sock == -1)
        {
            printf("SERVER: Error when opening server socket.\n");
            exit(1);
        }

        /*************************************/
        /* Bind to an address on file system */
        /*************************************/
        // similar to other IPC methods, domain socket needs to bind to a file system
        // so that client know the address of the server to connect to
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, SERVER_SOCK_PATH);
        int len = sizeof(server_addr);

        // unlink the file before bind, unless it can't bind
        unlink(SERVER_SOCK_PATH);

        rc = bind(server_sock, (struct sockaddr *)&server_addr, len);
        if (rc == -1)
        {
            printf("SERVER: Server bind error: %s\n", strerror(errno));
            close(server_sock);
            exit(1);
        }

        /***************************************/
        /* Listen and accept client connection */
        /***************************************/
        // set the server in the "listen" mode and maximum pending connected clients in queue
        rc = listen(server_sock, backlog);
        if (rc == -1)
        {
            printf("SERVER: Listen error: %s\n", strerror(errno));
            close(server_sock);
            exit(1);
        }

        printf("SERVER: Socket listening...\n");
        int client_fd = accept(server_sock, (struct sockaddr *) &client_addr, (socklen_t*)&len);
        if (client_fd == -1)
        {
            printf("SERVER: Accept error: %s\n", strerror(errno));
            close(server_sock);
            close(client_fd);
            exit(1);
        }
        printf("SERVER: Connected to client at: %s\n", client_addr.sun_path);
        printf("SERVER: Wating for message...\n");

        /********************/
        /* Listen to client */
        /********************/
        memset(buf, 0, 256);
        int byte_recv = recv(client_fd, buf, sizeof(buf), 0);
        if (byte_recv == -1)
        {
            printf("SERVER: Error when receiving message: %s\n", strerror(errno));
            close(server_sock);
            close(client_fd);
            exit(1);
        }
        else
            printf("SERVER: Server received message: %s.\n", buf);

        /**********************/
        /* Response to client */
        /**********************/
        printf("SERVER: Respond to the client...\n");
        memset(buf, 0, 256);
        strcpy(buf, SERVER_MSG);
        rc = send(client_fd, buf, strlen(buf), 0);
        if (rc == -1)
        {
            printf("SERVER: Error when sending message to client.\n");
            close(server_sock);
            close(client_fd);
            exit(1);
        }
        printf("SERVER: Done!\n");

        close(server_sock);
        close(client_fd);
        remove(SERVER_SOCK_PATH);
 //   }

    return 0;
}


















/*
#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>

//#define SOCKET_FILE "/var/www/html/myserver.sock"
#define SOCKET_FILE "/tmp/myserver.sock"
#define BUF_SIZE    64 * 1024

int main() {
  struct sockaddr_un server_address = {AF_UNIX, SOCKET_FILE};

	printf("socket is starting\n");
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	printf("socket completed\n");
  if (sock <= 0) {
      perror("socket creation failed");
      return 1;
  }

	printf("unlink is starting\n");
  unlink(SOCKET_FILE);

	printf("bind is starting\n");
  if (bind(sock, (const struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
      perror("bind failed");
      close(sock);
      return 1;
  }

  for (;;) {
    struct sockaddr_un client_address;
    int i, numBytes, len = sizeof(struct sockaddr_un);
    char buf[BUF_SIZE];
	printf("recvfrom is starting\n");
    numBytes = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr *) &client_address, &len);
    if (numBytes == -1) puts("recvfrom failed");

    printf("Server received %d bytes from %s\n", numBytes, client_address.sun_path);

    for (i = 0; i < numBytes; i++)
      buf[i] = toupper((unsigned char) buf[i]);

    if (sendto(sock, buf, numBytes, 0, (struct sockaddr *) &client_address, len) != numBytes)
      puts("sendto failed");
  }

}
*/
