#ifndef TUNALLOCATOR_H
#define TUNALLOCATOR_H

#include <iostream>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>


class TunAllocator
{

    char tun_name_[IFNAMSIZ];
public:
    TunAllocator(char *name);
    int TunAlloc(int flags);
    int TunSet(char* addr, char* netmask);
};

#endif // TUNALLOCATOR_H
