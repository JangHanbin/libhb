#include "packet-parser.h"
#include <iostream>

bool EtherParse(u_int8_t **data, int &data_len, int type)
{
    struct ether_header *ep = reinterpret_cast<struct ether_header*>(*data);
    if(ntohs(ep->ether_type)==type)
    {
        *data=*data+sizeof(struct ether_header);
        data_len-=sizeof(struct ether_header);
        return true;
    }

    return false;

}

bool IpParse(u_int8_t **data, int &data_len, int type)
{
    struct iphdr *iph=reinterpret_cast<struct iphdr*>(*data);

    if(iph->protocol==type)
    {
        *data=*data+(iph->ihl*4);
        data_len-=(iph->ihl*4);
        return true;
    }


    return false;
}

uint8_t *IpParse(uint8_t *data, int &data_len, int type)
{
    struct iphdr *iph=reinterpret_cast<struct iphdr*>(data);

    if(iph->protocol==type)
    {
        data_len-=(iph->ihl*4);
        return data+(iph->ihl*4);
    }


    return nullptr;
}


bool TcpDataParse(u_int8_t **data, int &data_len)
{
    struct tcphdr* tcph = reinterpret_cast<struct tcphdr*>(*data);

    if((data_len - tcph->doff*4)<=0)
    {
        //there is no payload
        return false;
    }
    else
    {
        data_len-=(tcph->doff*4);
        *data=*data+(tcph->doff*4);
        return true;
    }
}

bool RecvPacketFromPcap(pcap_t *pcd, uint8_t **buf, int &data_len)
{
    const u_char *pkt_data;
    struct pcap_pkthdr *pkt_header;
    int value_of_next_ex;

    while(true)
    {
        value_of_next_ex=pcap_next_ex(pcd,&pkt_header,&pkt_data);        
        switch (value_of_next_ex)
        {
        case 1:
            *buf=reinterpret_cast<uint8_t*>(const_cast<u_char*>(pkt_data));
            data_len=static_cast<int>(pkt_header->caplen);
            return true;

        case 0:
            //cout<<"need a sec.. to packet capture"<<endl;
            continue;
        case -1:
            perror("pcap_next_ex function has an error!!");
            exit(1);

        case -2:
            perror("the packet have reached EOF!!");
            return false;
        default:
            return false;
        }
    }
}

bool RecvPacketFromRaw(int raw_fd, uint8_t *buf, int size_of_buf, int &captured_length,int flag )
{

//    captured_length = static_cast<int>(recv(raw_fd,buf,static_cast<size_t>(size_of_buf),flag));
    captured_length = ::recv(raw_fd,buf,size_of_buf,flag);
    if(captured_length<0)
        return false;

    return true;
}
