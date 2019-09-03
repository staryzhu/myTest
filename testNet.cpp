#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

void captureRaw() {
    int sock = 0;
    int trycnt = 0;
    struct addrinfo hint;
    struct addrinfo *rslt = NULL;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    while (trycnt < 5) {
        int ret = getaddrinfo("www.baidu.com", "80", &hint, &rslt);
        if(ret != 0) continue;
        if(!ret && rslt) break;
        printf("getaddrinfo try count : %d\n", trycnt);
    }
    struct addrinfo *p = rslt;
    for(; p != NULL; p = p->ai_next) {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(sock == -1) {
            printf("create socket error : %d\n", errno);
            continue;
        }
        int ret = connect(sock, p->ai_addr, p->ai_addrlen);
        if(ret == -1) {
            close(sock);
            continue;
        }
        else {
            printf("Connect Success\n");
            break;
        }
    }
    freeaddrinfo(rslt);
    char buf[1024] = {0};
    do {
        write(sock, "nihao", 100);
        read(sock, buf, 100);
        printf("read out : %s\n", buf);
    } while(0);
    close(sock);
}

void srvall() {
    int socksvr;
    int ret;
    struct addrinfo hint;
    struct addrinfo *rslt = NULL;
    for(int i = 0; i < 5; i++) {
        rslt = NULL;
        memset(&hint, 0, sizeof(hint));
        hint.ai_family = AF_INET;
        hint.ai_socktype = SOCK_STREAM;
        ret = getaddrinfo(NULL, "9999", &hint, &rslt);
        if(ret == -1) {
            printf("getaddrinfo error : %d\n", errno);
            continue;
        }

        if(rslt) {
            printf("get addrinfo ok\n");
            break;
        }
    }

    struct addrinfo *p = rslt;
    for(; p != NULL; p = p->ai_next) {
       // printf("addrinfo : %d, ")
        socksvr = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(socksvr == -1) {
            printf("init socket server failed : %d\n", errno);
            continue;
        }
        ret = bind(socksvr, p->ai_addr, p->ai_addrlen);
        if(ret == -1) {
            printf("socksvr bind error : %d\n", errno);
            close(socksvr);
            continue;
        }
        else {
            printf("create socket and bind ok\n");
            break;
        }
    }
    freeaddrinfo(rslt);
    if(socksvr == -1) {
        printf("init error\n");
        return;
    }
    if(listen(socksvr, 5) == -1) {
        close(socksvr);
        printf("listen error : %d\n", errno);
    }
    struct sockaddr peer_addr;
    socklen_t len = sizeof(peer_addr);
    char buf[128] = {0};
    do {
        int peer = accept(socksvr, &peer_addr, &len);
        if(peer == -1) {
            printf("accept error : %d\n", errno);
            continue;
        }
        int size = read(peer, buf, 128);
        printf("read from : %s and size: %d\n", buf, size);
        close(peer);
    }while(1);
    close(socksvr);
    printf("Exit the Server \n");
}

int main() {
    // while(1) {
    //     captureRaw();
    //     usleep(10000000);
    // }
    srvall();
    return 0;
}
