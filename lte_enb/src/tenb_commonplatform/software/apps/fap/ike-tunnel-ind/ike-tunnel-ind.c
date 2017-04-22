#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>

#define FROM_ID     (1<<16)
#define TENPIN_ID   26
#define DISCONN_IND 0x4806 /* SERIALISATION_ID_IKE_TUNNEL_DISCONNECT_IND */
#define CONNECT_IND 0x4805 /* SERIALISATION_ID_IKE_TUNNEL_CONNECT_IND */

#define POST_OFFICE_PORT 6000

#define USAGE() fprintf(stderr, "expected 2 or 3 args: [up|down] tunnelid [inner ipaddr]\n")

int main(int argc, char *argv[])
{
    uint32_t from=htonl(FROM_ID), to=htonl(TENPIN_ID);
    uint32_t serid, tid;
    int sock, rc,addr;
    char data[33];
    struct sockaddr_in sin;
    int size; /* 17 or 21 or 33 */
    struct in6_addr inaddr= {};
    uint8_t ipAddrType;

    /* we expect 2 arguments for tunnel-down indication
     * and 3 arguments for tunnel-up indication */
    if (argc < 3 || argc > 4) { USAGE(); return 1; }

    /* first arg is up/down indication */
    if (strcmp(argv[1], "up") == 0) {
        /* if first arg is up, tunnelid and inner ip addr follow */
        if (argc != 4) { USAGE(); return 1; }
        serid = htonl(CONNECT_IND);
        tid = htonl(atoi(argv[2]));
        if(inet_pton(AF_INET6,argv[3],&inaddr) == 1)
        {
             ipAddrType = 1;
             size = 33;
        }
        else
        {
            ipAddrType = 0;
            size = 21;
            addr = htonl(inet_addr(argv[3]));
            if (addr == INADDR_NONE) {
              fprintf(stderr, "invalid ip addr: %s\n", argv[3]);
              return 1;
            }
        }
    } else if (strcmp(argv[1], "down") == 0) {
        /* if first arg is down, only tunnel id follows */
        if (argc != 3) { USAGE(); return 1; }
        size = 16;
        serid = htonl(DISCONN_IND);
        tid = htonl(atoi(argv[2]));
    } else {
        USAGE();
        return 1;
    }

    /* compile the packet payload */
    memcpy(&data[0],  &from,  4);
    memcpy(&data[4],  &to,    4);
    memcpy(&data[8],  &serid, 4);
    memcpy(&data[12], &tid,   4);
    if (size == 33)
    {
        memcpy(&data[16], &ipAddrType, 1);
        memcpy(&data[17],&(inaddr.s6_addr32[0]),4);
        memcpy(&data[21],&(inaddr.s6_addr32[1]),4);
        memcpy(&data[25],&(inaddr.s6_addr32[2]),4);
        memcpy(&data[29],&(inaddr.s6_addr32[3]),4);
    }
    else
    {
        if(size == 21)
        {
            memcpy(&data[16], &ipAddrType, 1);
            memcpy(&data[17],&addr,4);
           
        }
    }


    /* send the payload to post office on localhost using udp */

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        fprintf(stderr, "could not create socket, errno=%d\n", errno);
        return 1;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(POST_OFFICE_PORT);
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);

    rc = sendto(sock, data, size, 0, (const void *) &sin, sizeof(sin));
    if (rc != size) {
        fprintf(stderr, "packet send failed, errno=%d\n", errno);
    	close(sock);
        return 1;
    }

    close(sock);

    return 0;
}

