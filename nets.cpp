#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>

void u_log(const char *fmt, ...)
{
    int n;
    va_list arg_list;
    va_start(arg_list, fmt);
    n = vprintf(fmt, arg_list);
    printf("\n");
    va_end(arg_list);
}

void tcp_recieve(int argc ,char *argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello world!";

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        printf("sock() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(10001);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        printf("bind() error");

    if (listen(serv_sock, 5) == -1)
        printf("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    printf("Starting Server");
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    printf("Starting Recieve");
    if (clnt_sock == -1)
        printf("accept() error");
    char buf[1024 * 2];
    for(;;){
        int len = read(clnt_sock, buf, 1024 * 2);
        printf("rc : %d\n", len);
    }

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

}

const int tryCnt = 5;

void udp_svr(char *sport) {
    int udp_s;
    struct addrinfo hints;
    struct addrinfo *rslt;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int ret;
    for(int i = 0; i < tryCnt; i++) {
        ret = getaddrinfo(NULL, sport, &hints, &rslt);
        if(ret == 0) {
            printf("get addrinfo success\n");
            break;
        }
        if(rslt) {
            printf("get addrinfo failed\n");
            freeaddrinfo(rslt);
        }
    }

    if(!rslt) {
        printf("get addrinfo Faile after try 5\n");
        return ;
    }

    struct addrinfo *p = rslt;
    while(p) {
        udp_s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(udp_s == -1) {
            printf("Create socket Failed\n");
            p = p->ai_next;
            continue;
        }
        ret = bind(udp_s, p->ai_addr, p->ai_addrlen);
        if(ret == -1) {
            printf("Bind socket Failed\n");
            close(udp_s);
            p= p->ai_next;
            continue;
        }
        break;
    }
    freeaddrinfo(rslt);
    char buf[32];
    struct sockaddr_in remote;
    memset(&remote, 0, sizeof(struct sockaddr_in));
    socklen_t addrlen = sizeof(struct sockaddr);
    while(1) {
        memset(buf, 0, 32);
        int cnt = read(udp_s, buf, 32);
        //int cnt = recvfrom(udp_s, buf, 16, 0, (struct sockaddr *)&remote, &addrlen);
        printf("read cnt : %d\n", cnt);
        printf("sync char :%x , %x\n", buf[0], buf[15]);
        //printf("Read From IP : %s\n", inet_ntoa(remote.sin_addr));
    }
    close(udp_s);
}

void udp_cli(char *ip, char *port) {
    int udp_s;
    struct addrinfo hints;
    struct addrinfo *rslt = NULL;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int ret;
    printf("ip : %s and port : %s\n", ip, port);
    for(int i = 0; i < tryCnt; i++) {
        ret = getaddrinfo(ip, port, &hints, &rslt);
        if(ret == 0) {
            printf("get addrinfo success\n");
            break;
        }
        if(rslt) {
            printf("get addrinfo failed\n");
            freeaddrinfo(rslt);
        }
    }

    if(!rslt) {
        printf("get addrinfo Faile after try 5\n");
        return ;
    }

    struct addrinfo *p = rslt;
    while(p) {
        udp_s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(udp_s == -1) {
            printf("Create socket Failed\n");
            p = p->ai_next;
            continue;
        }
        break;
    }
    char buf[32];
    int count = 0;
    if(!p) {
        printf("get addr error \n");
        return;
    }

    // struct sockaddr_in svr;
    // svr.sin_family = AF_INET;
    // svr.sin_port = htons(port);//server port
    // svr.sin_addr.s_addr = inet_addr(ip);//server ip addr

    //socklen_t addrlen = sizeof(struct sockaddr);

    while(1) {
        memset(buf, 0, 32);
        buf[0] = count % 256;
        buf[15] = count % 256 + 1;
        int cnt = sendto(udp_s, buf, 16, 0, p->ai_addr, (socklen_t)p->ai_addrlen);
        if(count > 10000) {
            count = 0;
        }
        if(count % 10 == 0) {
            usleep(1000);
        }
        count++;
    }
    freeaddrinfo(rslt);
    close(udp_s);
}

void setUnBlock(int sock){
    int flags, res;

    flags = fcntl(sock, F_GETFL);
    if (flags == -1) {
        u_log("error : cannot get socket flags!\n");
        exit(1);
    }

    flags |= O_NONBLOCK;
    res    = fcntl(sock, F_SETFL, flags);
    if (res == -1) {
        u_log("error : cannot set socket flags!\n");
        exit(1);
    }
}

void manageSvr() {
    int sockfd = 0;
    int sockcli = 0;
    int epollfd = 0;
    int err = 0;
    struct addrinfo hints;
    struct addrinfo *prslt = NULL;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    for(int i = 0; i < 5; i++) {
        u_log("Try to get addr info");
        err = getaddrinfo(NULL, "31415", &hints, &prslt);
        if(!err) {
            break;
        }
        if(!prslt) {
            freeaddrinfo(prslt);
        }
    }
    if(!prslt) {
        u_log("Get Addrinfo Error ,Exit");
        return;
    }
    struct addrinfo *p = prslt;
    while(p) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(sockfd == -1) {
            u_log("socket error : %d", errno);
            p = p->ai_next;
        }
         else
            break;
    }
    if(sockfd == -1) {
        u_log("socket error, Exit");
        freeaddrinfo(prslt);
        return;
    }
    err = bind(sockfd, p->ai_addr, p->ai_addrlen);
    if(err == -1) {
        u_log("bind error %d, Exit", errno);
        freeaddrinfo(prslt);
        close(sockfd);
        return;
    }
    if(listen(sockfd, 10) == -1){
        u_log("listen error %d, Exit", errno);
        freeaddrinfo(prslt);
        close(sockfd);
        return;
    }
    setUnBlock(sockfd);

    struct epoll_event event, event_array[1024];
    epollfd = epoll_create(1024);
    event.events = EPOLLIN | EPOLLOUT | EPOLLET;
    event.data.fd = sockfd;
    err = epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event);
    if(err == -1) {
        u_log("Add socket to epoll error : %d ,exit", errno);
        return;
    }
    do {
        int hsize = epoll_wait(epollfd, event_array, 1024, -1);
        if(hsize == -1) {
            u_log("epoll wait error : %d", errno);
            break;
        }
        for(int i = 0; i < hsize; i++) {
            struct epoll_event *pevt = event_array + i;
            uint32_t evt = pevt->events;
            if( ( evt & EPOLLERR) || (evt & EPOLLHUP) || !(evt & EPOLLIN)) {
                u_log("socket fd error i : %d, err: %d", i, errno);
                close(event_array[i].data.fd);
                continue;
            }
            else if(sockfd == pevt->data.fd) {
                while (1) {
                    struct sockaddr client_addr;
                    int addrlen = sizeof(struct sockaddr);
                    sockcli = accept(sockfd, &client_addr, (socklen_t *)&addrlen);
                    if (sockcli == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        } else {
                            perror("error : cannot accept new socket!\n");
                            continue;
                        }
                    }
                    setUnBlock(sockcli);

                    event.data.fd = sockcli;
                    event.events  = EPOLLET | EPOLLIN;
                    int res = epoll_ctl(epollfd, EPOLL_CTL_ADD, sockcli, &event);
                    if (res == -1) {
                        u_log("error : cannot add to epoll");
                        exit(1);
                    }
                }
            }
        }
    } while(1);

}


int main(int argc ,char *argv[]){
    printf("Usage: revice or send\n");
    //tcp_recieve(argc, argv);
    assert(argc != 1);

    int type = atoi(argv[1]);
    if(type == 1)
        udp_svr(argv[2]);
    else if(type == 2)
        udp_cli(argv[2], argv[3]);
    else if(type == 3) {
        u_log("TCP Watch");
    }
    return 0;
}
