#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
int __exit = 1;

void tcp_send(int argc ,char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

   sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        printf("sock() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        printf("connect() error!");
    char buf[512];
    memset(buf, 0, 512);
    printf("Start Sending\n");
    sprintf(buf, "do you have any question");
    do{
        write(sock, buf, 512);
        usleep(1000000);
    }while(__exit);

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1)
        printf("read() error!");

    printf("Message from server: %s\n", message);
    close(sock);

}

void sig_handler(int signum) {
    printf("Got Signal Num : %d\n", signum);
    __exit = 0;
}

int main(int argc ,char *argv[]){
    printf("Usage: revice or send");
    __exit = 1;
    signal(SIGPIPE, sig_handler);
    signal(SIGINT, sig_handler);
    if(argc == 3) {
        tcp_send(argc ,argv);
    }
    else {
        printf("ip and port\n");
    }
    return 0;
}
