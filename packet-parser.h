#ifndef PACKETPARSER_H
#define PACKETPARSER_H


#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

bool RecvPacket(pcap_t* pcd, uint8_t** buf, int& data_len);
bool EtherParse(u_int8_t** data, int& data_len, int type);
bool IpParse(u_int8_t** data, int& data_len, int type);
bool TcpDataParse(u_int8_t** data, int& data_len);

#endif // PACKETPARSER_H
