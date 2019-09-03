#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAC_SIZE    18
#define IP_SIZE     16

// function declare
int get_ip_by_domain(const char *domain, char *ip); // 根据域名获取ip
int get_local_mac(const char *eth_inf, char *mac); // 获取本机mac
int get_local_ip(const char *eth_inf, char *ip); // 获取本机ip


char* getip(char *ip_buf)
{
    struct ifreq temp;
    struct sockaddr_in *myaddr;
    int fd = 0;
    int ret = -1;
    strcpy(temp.ifr_name, "eno1");
    if((fd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        return NULL;
    }
    ret = ioctl(fd, SIOCGIFADDR, &temp);
    close(fd);
    if(ret < 0)
        return NULL;
    myaddr = (struct sockaddr_in *)&(temp.ifr_addr);
    strcpy(ip_buf, inet_ntoa(myaddr->sin_addr));
    return ip_buf;
}

int ip2lnum(char *strIP){
    char *p = strIP;
    int flag = 0;
    int num = 0;
    if(strIP == NULL)
    {
        return -1;
    }
    while(*(p) != '\0'){
        if(*p == '.') flag++;
        else if(*p != '\0' && flag >= 0){
            //printf("the : %d\n", *p - '0');
            num = num * 10 + *p - '0';
        }
        p++;
    }
    return num % 256;//max number of the devices
}

int ip2l1num(char *strIP){
    char *p = strIP;
    int flag = 0;
    int num = 0;
    if(strIP == NULL)
    {
        return -1;
    }
    while(*(p++) != '\0'){
        if(*p == '.') flag++;
        else if(*p != '\0' && flag >= 0){
            printf("the : %d\n", *p - '0');
            num = num * 10 + *p - '0';
        }

    }
    return num;
}

int ip2num(char *strIP){
    char *p = strIP;
    int flag = 0;
    unsigned int reslt = 0;
    int num = 0;
    if(strIP == NULL)
    {
        return -1;
    }
    while(*(p) != '\0'){
        if(*p == '.') {
            reslt = (reslt << 8) | num;
            num = 0;
            printf("reslt : %d\n", reslt);
        }
        else{
            printf("the : %d\n", *p - '0');
            num = num * 10 + *p - '0';
        }
        ++p;
    }
    reslt = (reslt << 8) | num;
    return reslt;
}

char *id2ip(unsigned id, char * strIP){
    snprintf(strIP, 16, "%d.%d.%d.%d", (id >> 24) & 0xff, (id >> 16) & 0xff, (id >> 8) & 0xff, id & 0xff);
    return strIP;
}

/****** main test **********/
int main(void)
{
    char ip[IP_SIZE];
    char mac[MAC_SIZE];
    const char *test_domain = "www.baidu.com";
    const char *test_eth = "eth0";

    get_ip_by_domain(test_domain, ip);
    printf("%s ip: %s\n", test_domain, ip);

    get_local_mac(test_eth, mac);
    printf("local %s mac: %s\n", test_eth, mac);

    get_local_ip(test_eth, ip);
    printf("local %s ip: %s\n", test_eth, ip);
    printf("num ip to num  : %d \n", ip2num(ip));
    printf("lnum ip to lnum  : %d \n", ip2lnum(ip));

    getip(ip);
    int nip = ip2num(ip);
    printf("num ip to num  : %d \n", nip);
    printf("num to ip : %s\n", id2ip(nip, ip));
    printf("lnum ip to lnum  : %d \n", ip2lnum(ip));

    printf("local %s ip: %s\n", test_eth, ip);

    return 0;
}

// 根据域名获取ip
int get_ip_by_domain(const char *domain, char *ip)
{
    char **pptr;
    struct hostent *hptr;

    hptr = gethostbyname(domain);
    if(NULL == hptr)
    {
        printf("gethostbyname error for host:%s/n", domain);
        return -1;
    }

    for(pptr = hptr->h_addr_list ; *pptr != NULL; pptr++)
    {
        if (NULL != inet_ntop(hptr->h_addrtype, *pptr, ip, IP_SIZE) )
        {
            return 0; // 只获取第一个 ip
        }
    }

    return -1;
}

// 获取本机mac
int get_local_mac(const char *eth_inf, char *mac)
{
    struct ifreq ifr;
    int sd;

    bzero(&ifr, sizeof(struct ifreq));
    if( (sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("get %s mac address socket creat error\n", eth_inf);
        return -1;
    }

    strncpy(ifr.ifr_name, eth_inf, sizeof(ifr.ifr_name) - 1);

    if(ioctl(sd, SIOCGIFHWADDR, &ifr) < 0)
    {
        printf("get %s mac address error\n", eth_inf);
        close(sd);
        return -1;
    }

    snprintf(mac, MAC_SIZE, "%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned char)ifr.ifr_hwaddr.sa_data[0],
        (unsigned char)ifr.ifr_hwaddr.sa_data[1],
        (unsigned char)ifr.ifr_hwaddr.sa_data[2],
        (unsigned char)ifr.ifr_hwaddr.sa_data[3],
        (unsigned char)ifr.ifr_hwaddr.sa_data[4],
        (unsigned char)ifr.ifr_hwaddr.sa_data[5]);

    close(sd);

    return 0;
}


// 获取本机ip
int get_local_ip(const char *eth_inf, char *ip)
{
    int sd;
    struct sockaddr_in sin;
    struct ifreq ifr;

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sd)
    {
        printf("socket error: %s\n", strerror(errno));
        return -1;
    }

    strncpy(ifr.ifr_name, eth_inf, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;

    // if error: No such device
    if (ioctl(sd, SIOCGIFADDR, &ifr) < 0)
    {
        printf("ioctl error: %s\n", strerror(errno));
        close(sd);
        return -1;
    }

    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    snprintf(ip, IP_SIZE, "%s", inet_ntoa(sin.sin_addr));

    close(sd);
    return 0;
}
