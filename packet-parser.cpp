#include "packet-parser.h"
#include <iostream>

bool EtherParse(u_int8_t **data, int &data_len, int type)
{
    std::cout<<"Faile?"<<std::endl;
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

}

bool TcpDataParse(u_int8_t **data, int &data_len)
{

}
