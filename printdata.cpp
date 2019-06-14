#include <iostream>
#include <iomanip>
#include "printdata.h"





void PrintByHex(u_int8_t *data, int data_len)
{
    std::cout<<std::setfill('0');
    std::cout<<std::hex;

    std::cout<<"------------------------------------------------"<<"\n";

    for(int i=0; i<data_len; i++)
    {
        if (i !=0 && i % MAX_OF_LINE==0)
            std::cout<<"\n";
        std::cout<<std::setw(2)<<static_cast<int>(data[i])<<" ";

    }
    std::cout<<std::dec;
    std::cout<<"\n------------------------------------------------"<<"\n";
    std::cout<<"\n\n\n";
}

void PrintByHex(std::vector<uint8_t> arr)
{
    int count = 0;
    std::cout<<std::setfill('0');
    std::cout<<std::hex;
    std::cout<<"------------------------------------------------"<<"\n";
    for(auto i : arr)
    {
        if (count !=0 && count % MAX_OF_LINE==0)
            std::cout<<"\n";
        std::cout<<std::setw(2)<<static_cast<int>(i)<<" ";
    }

    std::cout<<std::dec;
    std::cout<<"\n------------------------------------------------"<<"\n";
    std::cout<<"\n\n\n";
}
