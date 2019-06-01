#ifndef CALCHECKSUM_H
#define CALCHECKSUM_H
#include <iostream>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <cstring>



#pragma pack(push,1)

struct Pseudoheader{
    uint32_t srcIP;
    uint32_t destIP;
    uint8_t reserved{0};
    uint8_t protocol;
    uint16_t TCPLen;
};


#pragma pack(pop)

#define CARRY 65536
uint16_t calculate(uint16_t* data, int dataLen);
uint16_t in_cksum(uint16_t* data, int data_len);
uint16_t calTCPChecksum(uint8_t* data, int dataLen);   // need to data pointer at IP Header
uint16_t calIPChecksum(uint8_t* data);                  // need to data pointer at IP Header
uint16_t calICMPChecksum(uint8_t* data, int dataLen);   // need to data pointer at IP Header
uint16_t calUDPChecksum(uint8_t* data, int dataLen);   // need to data pointer at IP Header
#endif // CALCHECKSUM_H
