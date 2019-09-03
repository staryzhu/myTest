//memberServer.c

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_CAST "224.0.2.99"

int memberSvr(int argc, char **argv)
{
    int server_socket;
    struct sockaddr_in address;

    server_socket=socket(AF_INET,SOCK_DGRAM,0);
    if(server_socket<0){
        perror("socket");
        return 0;
    }

    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_port=htons(5555);
    address.sin_addr.s_addr=inet_addr(MEMBER_CAST);

    while(1){
        char buf[200];
        printf("input your word:");
        scanf("%s",buf);
        if(sendto(server_socket,buf,sizeof(buf),0,(struct sockaddr*)&address,sizeof(address))<0){
            perror("sendto");
            return 0;
        }
    }

    return 0;
}


int memberCli(int argc, char **argv)
{
    struct ip_mreq mreq;
    int serveraddress_len;
    int client_socket;
    struct sockaddr_in serveraddress;

    //
    memset(&serveraddress,0,sizeof(serveraddress));
    serveraddress.sin_family=AF_INET;
    serveraddress.sin_port=htons(5555);
    serveraddress.sin_addr.s_addr=htonl(INADDR_ANY);

    if((client_socket=socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("client");
        return 0;
    }

    if(bind(client_socket,(struct sockaddr*)&serveraddress,sizeof(serveraddress))<0){
        printf("bind");
        return 0;
    }

    int opt=1;
    if(setsockopt(client_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))<0){
        printf("setsockopt1");
        return 0;
    }

    //add to member
    mreq.imr_multiaddr.s_addr=inet_addr(MEMBER_CAST);
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);

    if(setsockopt(client_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0){
        perror("setsockopt2");
        return 0;
    }

    //send member msg
    struct sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_port=htons(5555);
    address.sin_addr.s_addr=inet_addr(MEMBER_CAST);

    while(1){
        char buf[200];
        serveraddress_len=sizeof(serveraddress);
        if(recvfrom(client_socket,buf,200,0,(struct sockaddr*)&serveraddress,(socklen_t *)serveraddress_len)<0){
            perror("recvfrom");
        }
        printf("msg from server: %s\n",buf);

        printf("input your word:");
        scanf("%s",buf);
        if(sendto(client_socket,buf,sizeof(buf),0,(struct sockaddr*)&address,sizeof(address))<0){
            perror("sendto");
            return 0;
        }

        if(strcmp(buf,"quit")==0){
            if(setsockopt(client_socket,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq))<0){
                perror("setsokopt3");
            }
            close(client_socket);
            return 0;
        }
    }

    return 0;
}


int main(int argc, char *argv[]){
    if(argc > 1){
        printf("member Server\n");
        memberSvr(argc, argv);
    }
    else
    {
        printf("member Client\n");
        memberCli(argc, argv);
    }

    return 0;
}
