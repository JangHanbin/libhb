#ifndef PACKETPARSER_H
#define PACKETPARSER_H


#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>

bool RecvPacketFromPcap(pcap_t* pcd, uint8_t** buf, int& data_len);
bool RecvPacketFromRaw(int raw_fd, uint8_t* buf, int size_of_buf, int& captured_length , int flag);
bool EtherParse(u_int8_t** data, int& data_len, int type);
bool IpParse(u_int8_t** data, int& data_len, int type);
uint8_t* IpParse(uint8_t *data, int& data_len, int type);
bool TcpDataParse(u_int8_t** data, int& data_len);

#endif // PACKETPARSER_H
