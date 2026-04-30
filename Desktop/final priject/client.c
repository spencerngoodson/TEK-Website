#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 11000

int main() {
    //Create a socket
    int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock_fd < 0) {
        printf("Failed to create client socket\n");
        return -1;
    }

    //Connect to server
    struct sockaddr_in server_sock_addr = {0};
    server_sock_addr.sin_family = AF_INET;

    if (inet_aton(SERVER_IP, &(server_sock_addr.sin_addr)) < 0) {
        printf("Failed to convert server IP\n");
        return -1;
    }

    server_sock_addr.sin_port = htons(PORT);

    if (connect(client_sock_fd, (struct sockaddr*)&server_sock_addr, sizeof(server_sock_addr)) < 0) {
        printf("Failed to connect to server\n");
        return -1;
    }

    printf("Connected to server...\n");



    //Send file (whats different from github template socket code)
    FILE *fp = fopen("test.txt", "rb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return -1;
    }

    char buf[1024];
    int len;

    while ((len = fread(buf, 1, sizeof(buf), fp)) > 0) {
        send(client_sock_fd, buf, len, 0);
    }

    printf("File sent successfully\n");

    fclose(fp);
    close(client_sock_fd);

    return 0;
}