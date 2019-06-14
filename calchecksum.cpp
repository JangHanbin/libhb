#include <iostream>
#include <cstring>
#include "calchecksum.h"
#include "printdata.h"




uint16_t calTCPChecksum(uint8_t *data,int dataLen)
{
    //make Pseudo Header
    struct Pseudoheader pseudoheader; //saved by network byte order

    //init Pseudoheader
    struct iphdr *iph=(struct iphdr*)data;
    struct tcphdr *tcph=(struct tcphdr*)(data+iph->ihl*4);

    memcpy(&pseudoheader.srcIP,&iph->saddr,sizeof(pseudoheader.srcIP));
    memcpy(&pseudoheader.destIP,&iph->daddr,sizeof(pseudoheader.destIP));
    pseudoheader.protocol=iph->protocol;
    pseudoheader.TCPLen=htons(dataLen-(iph->ihl*4));

    //Cal pseudoChecksum
    uint16_t pseudoResult=calculate((uint16_t*)&pseudoheader,sizeof(pseudoheader));

    //Cal TCP Segement Checksum
    tcph->check=0; //set Checksum field 0
    uint16_t tcpHeaderResult=calculate((uint16_t*)tcph,ntohs(pseudoheader.TCPLen));


    uint16_t checksum;
    int tempCheck;

    if((tempCheck=pseudoResult+tcpHeaderResult)>CARRY)
        checksum=(tempCheck-CARRY) +1;
    else
        checksum=tempCheck;


    checksum=ntohs(checksum^0xffff); //xor checksum
    tcph->check=checksum;

    return checksum;
}

uint16_t calICMPChecksum(uint8_t *data,int dataLen)
{

    //init Pseudoheader
    struct iphdr *iph=(struct iphdr*)data;
    struct icmp *icmph=(struct icmp*)(data+iph->ihl*4);

    //Cal ICMP Segement Checksum
    icmph->icmp_cksum=0; //set Checksum field 0
    uint16_t checksum=calculate((uint16_t*)icmph,(dataLen-(iph->ihl*4)));

    checksum=ntohs(checksum^0xffff); //xor checksum
    icmph->icmp_cksum=checksum;

    return checksum;
}

uint16_t calUDPChecksum(uint8_t *data, int dataLen)
{
    //make Pseudo Header
    struct Pseudoheader pseudoheader; //save to network byte order

    //init Pseudoheader
    struct iphdr *iph=(struct iphdr*)data;
    struct udphdr *udph=(struct udphdr*)(data+iph->ihl*4);
    memcpy(&pseudoheader.srcIP,&iph->saddr,sizeof(pseudoheader.srcIP));
    memcpy(&pseudoheader.destIP,&iph->daddr,sizeof(pseudoheader.destIP));
    pseudoheader.protocol=iph->protocol;
    pseudoheader.TCPLen=htons(dataLen-(iph->ihl*4));

    //Cal pseudoChecksum
    uint16_t pseudoResult=calculate((uint16_t*)&pseudoheader,sizeof(pseudoheader));

    //Cal TCP Segement Checksum
    udph->check=0; //set Checksum field 0
    uint16_t tcpHeaderResult=calculate((uint16_t*)udph,ntohs(pseudoheader.TCPLen));


    uint16_t checksum;
    int tempCheck;

    if((tempCheck=pseudoResult+tcpHeaderResult)>CARRY)
        checksum=(tempCheck-CARRY) +1;
    else
        checksum=tempCheck;


    checksum=ntohs(checksum^0xffff); //xor checksum
    udph->check=checksum;

    return checksum;
}

uint16_t calculate(uint16_t* data, int dataLen)
{
    uint16_t result;
    int tempChecksum=0;
    int length;
    bool flag=false;
    if((dataLen%2)==0)
        length=dataLen/2;
    else
    {
        length=(dataLen/2)+1;
        flag=true;
    }

    for (int i = 0; i < length; ++i) // cal 2byte unit
    {

        if(i==length-1&&flag) //last num is odd num
            tempChecksum+=ntohs(data[i]&0x00ff);
        else
            tempChecksum+=ntohs(data[i]);

        if(tempChecksum>CARRY)
                tempChecksum=(tempChecksum-CARRY)+1;

    }

    result=static_cast<uint16_t>(tempChecksum);
    return result;
}

uint16_t in_cksum(uint16_t* data, int data_len)
{
    uint16_t answer;
    uint32_t sum = 0;
    uint16_t odd_byte = 0;

    while( data_len > 1 )
    {
        sum += *data++;
        data_len -= 2;

    }/* WHILE */


    /* mop up an odd byte, if necessary */
    if( data_len == 1 )
    {
        *( u_char* )( &odd_byte ) = *( u_char* )data;
        sum += odd_byte;

    }/* IF */

    sum = ( sum >> 16 ) + ( sum & 0xffff );    /* add hi 16 to low 16 */
    sum += ( sum >> 16 );                    /* add carry */
    answer = ~sum;                            /* ones-complement, truncate*/

    return ( answer );

}

uint16_t calIPChecksum(uint8_t* data)
{
    struct iphdr* iph=(struct iphdr*)data;
    iph->check=0;//set Checksum field 0

    uint16_t checksum=calculate((uint16_t*)iph,iph->ihl*4);
    iph->check=htons(checksum^0xffff);//xor checksum

    return checksum;
}
