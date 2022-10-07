/**
 * @file client.c
 * @author tigermini
 * @brief 基于udp的 unix domain socket 客户端
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#define REMOTE_PATH "uds_udp_sock.server"
#define BUF_SIZE 256
#define DATA "hello tiger,i am client"

int main(int argc, char *argv[])
{
    int client_socket, ret;
    struct sockaddr_un remote;
    char buf[BUF_SIZE];

    memset(&remote, 0, sizeof(remote));
    memset(buf, 0, BUF_SIZE);

    client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        printf("socket create error\n");
        return -1;
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, REMOTE_PATH);
    strcpy(buf, DATA);

    ret = sendto(client_socket, buf, strlen(buf), 0, (struct sockaddr *)&remote, sizeof(remote));
    if (ret == -1) {
        printf("socket sendto error\n");
        close(client_socket);
        return -1;
    } else {
        printf("DATA SEND SUCCESS\n");
    }

    close(client_socket);

    return 0;
}
