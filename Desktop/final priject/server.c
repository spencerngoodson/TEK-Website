#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 11000

int main() {
    //Creating a socket
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_fd < 0) {
        printf("Failed to create socket\n");
        return -1;
    }

    //Binding the socket to a socket address
    struct sockaddr_in sockaddr = {0};
    sockaddr.sin_family = AF_INET;

    if (inet_aton(SERVER_IP, &(sockaddr.sin_addr)) < 0) {
        printf("Failed to convert IP\n");
        return -1;
    }

    sockaddr.sin_port = htons(PORT);

    if (bind(server_sock_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        printf("Failed to bind the socket\n");
        return -1;
    }

    //Listen
    if (listen(server_sock_fd, 10) < 0) {
        printf("Failed to listen\n");
        return -1;
    }

    printf("Server is now listening...\n");

    //Accept
    int client_sock_fd = accept(server_sock_fd, NULL, NULL);
    if (client_sock_fd < 0) {
        printf("Failed to accept connection\n");
        return -1;
    }

    printf("Accepted a new connection...\n");

    //Receive file (whats different from github template socket code)
    char buf[1024];
    FILE *fp = fopen("received.txt", "wb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return -1;
    }

    int len;
    while ((len = recv(client_sock_fd, buf, sizeof(buf), 0)) > 0) {
        fwrite(buf, 1, len, fp);
    }

    printf("File received successfully\n");

    fclose(fp);
    close(client_sock_fd);
    close(server_sock_fd);

    return 0;
}