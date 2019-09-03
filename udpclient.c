
//cli.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// #include <sys/socket.h>
// #include <netinet/in.h>

#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int sockCli = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockCli == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(10001);//端口号
    addrSer.sin_addr.s_addr = inet_addr(argv[1]);//服务器地址

    socklen_t addrlen = sizeof(struct sockaddr);

    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        printf("Cli:>");
        scanf("%s",sendbuf);
        sendto(sockCli, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrSer, addrlen);

        recvfrom(sockCli, recvbuf, 256, 0, (struct sockaddr*)&addrSer, &addrlen);
        printf("Cli:>%s\n", recvbuf);
    }
    close(sockCli);
    return 0;
}
