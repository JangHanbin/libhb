#ifndef TUNALLOCATOR_H
#define TUNALLOCATOR_H

#include <net/if.h>


class TunAllocator
{

    char tun_name_[IFNAMSIZ];
public:
    TunAllocator(const char *name);
    int TunAlloc(int flags);
    int TunSet(const char* addr, const char* netmask);
};

#endif // TUNALLOCATOR_H
