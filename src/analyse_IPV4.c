#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>
#include "../include/analyse_udp.h"
#include "../include/analyse_tcp.h"

void ipv4_info(const struct ip *ip_hd)
{
    printf("\nANALYSE IPv4\n\n");
    printf("\tVersion : IPv%u\n", ip_hd->ip_v);
    printf("\tHeader length : %u bytes\n", ip_hd->ip_hl * 4);
    printf("\tType of service : %u\n", ip_hd->ip_tos);
    printf("\tTotal length : %u bytes\n", ntohs(ip_hd->ip_len));
    printf("\tIdentification : %u\n", ntohs(ip_hd->ip_id));
    printf("\tFragment offset field : %u\n", ip_hd->ip_off);
    printf("\tTime to live : %u\n", ip_hd->ip_ttl);
    printf("\tType of following protocol : %u\n", ip_hd->ip_p);
}

void ipv4_packet(const u_char *packet)
{
    const struct ip *ip_hd;
    ip_hd = (struct ip *)(packet);
    ipv4_info(ip_hd);
    switch (ip_hd->ip_p)
    {
    case 6:
        tcp_packet(packet+sizeof(struct ip));
        break;
    case 17:
        udp_packet(packet+sizeof(struct ip));
        break;
    default:
        printf("Type non encore traité\n");
        break;
    }
}