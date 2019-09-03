//ser.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// #include <sys/socket.h>
// #include <netinet/in.h>

#include <arpa/inet.h>
#include <sys/socket.h>

//extern in_addr_t inet_addr(const char *cp);

int main()
{
    int sockSer = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockSer == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(10001);//端口号
    addrSer.sin_addr.s_addr = htonl(INADDR_ANY);//服务器地址

    socklen_t addrlen = sizeof(struct sockaddr);

    const int opt = 1;
    //set the broadcast type
    if(setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == -1)
    {
        perror("ReUsePort Error\n");
        return -1;
    }

    int ret = bind(sockSer, (struct sockaddr*)&addrSer, addrlen);
    if(ret == -1)
    {
        perror("bind.");
        exit(1);
    }

    struct sockaddr_in addrCli;

    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        recvfrom(sockSer, recvbuf, 256, 0, (struct sockaddr*)&addrCli, &addrlen);
        printf("Cli:>%s\n", recvbuf);
        printf("Ser:>");
        scanf("%s",sendbuf);
        sendto(sockSer, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, addrlen);
    }

    close(sockSer);
    return 0;
}


