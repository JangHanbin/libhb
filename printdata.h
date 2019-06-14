#ifndef PRINTDATA_H
#define PRINTDATA_H

#include <stdint.h>
#include <vector>

#define MAX_OF_LINE 16
void PrintByHex(u_int8_t* data,int data_len );
void PrintByHex(std::vector<uint8_t> arr);

#endif // PRINTDATA_H
