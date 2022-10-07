/**
 * @file server.c
 * @author tigermini
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

#define SOCK_PATH "uds_udp_sock.server"
#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    /* 用于同一主机通信的结构体 */
    struct sockaddr_un server_sockaddr, peer_sock;
    char buf[BUF_SIZE];
    int server_sock, ret;
    int bytes_rec = 0;
    unsigned int len;

    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    memset(buf, 0, BUF_SIZE);

    server_sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_sock == -1) {
        printf("socket create error\n");
        return -1;
    }

    /* 设置family为AF_UNIX，先解除path的link来保证path绑定成功 */
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SOCK_PATH);
    len = sizeof(server_sockaddr);
    unlink(SOCK_PATH);
    ret = bind(server_sock, (struct sockaddr *)&server_sockaddr, len);
    if (ret == -1) {
        printf("socket bind error\n");
        close(server_sock);
        return -1;
    }

    printf("waiting to recvform...\n");
    bytes_rec = recvfrom(server_sock, buf, BUF_SIZE, 0, (struct sockaddr *)&peer_sock, &len);
    if (bytes_rec == -1) {
        printf("socket recvfrom error\n");
        close(server_sock);
        return -1;
    } else {
        printf("DATA RECEIVED = %s\n", buf);
    }

    close(server_sock);
    /* 删除bind产生的socket文件 */
    unlink(SOCK_PATH);

    return 0;
}
