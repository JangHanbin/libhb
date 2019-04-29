#include "tunallocator.h"

TunAllocator::TunAllocator(char* name)
{
    strncpy(tun_name_, name, IFNAMSIZ);
}

int TunAllocator::TunAlloc(int flags)
{

    struct ifreq ifr;
    int fd, err;
    char *clonedev = const_cast<char * >("/dev/net/tun");

    /* Arguments taken by the function:
     *
     * char *dev: the name of an interface (or '\0'). MUST have enough
     *   space to hold the interface name if '\0' is passed
     * int flags: interface flags (eg, IFF_TUN etc.)
     */



    /* open the clone device */
    if( (fd = open(clonedev, O_RDWR)) < 0 ) {
        return fd;
    }
    /* preparation of the struct ifr, of type "struct ifreq" */
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = static_cast<short>(flags);   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */

    if (*tun_name_) {
        /* if a device name was specified, put it in the structure; otherwise,
        * the kernel will try to allocate the "next" device of the
        * specified type */
        strncpy(ifr.ifr_name, tun_name_, IFNAMSIZ);
    }
    /* try to create the device */
    if( (err = ioctl(fd, TUNSETIFF, static_cast<void * >(&ifr))) < 0 ) {
        close(fd);
        perror("CREATE DEVICE ERR : ");
        return err;
    }

    /* if the operation was successful, write back the name of the
     * interface to the variable "dev", so the caller can know
     * it. Note that the caller MUST reserve space in *dev (see calling
     * code below) */

    strcpy(tun_name_, ifr.ifr_name);
    /* this is the special file descriptor that the caller will use to talk
     * with the virtual interface */
    return fd;
}

int TunAllocator::TunSet(char *addr, char *netmask)
{

    struct ifreq ifr;
    struct sockaddr_in ip_addr;

    /************************************SET IP ADDR & FLAGS & RUNNING************************************/
    strncpy(ifr.ifr_name,tun_name_,IFNAMSIZ); //set interface Name
    memset(&ip_addr,0,sizeof(struct sockaddr)); //init ip_addr

    ip_addr.sin_family=AF_INET;
    ip_addr.sin_addr.s_addr=inet_addr(addr); //convert Dotted Decimal Notation to network byte
    ip_addr.sin_port=0;

    memcpy(&ifr.ifr_addr,&ip_addr,sizeof(struct sockaddr));
    int sock_fd = socket(AF_INET,SOCK_DGRAM,0);

    if(ioctl(sock_fd,SIOCSIFADDR,&ifr)<0)
    {
        perror("SIOCSIFADDR occured an error : ");
        exit(1);
    }

    //I delete SIOCG~ if there is an problem check this

    ifr.ifr_flags|=IFF_BROADCAST | IFF_LOOPBACK | IFF_PROMISC | IFF_DYNAMIC |
            IFF_ALLMULTI | IFF_MULTICAST | IFF_UP | IFF_RUNNING | IFF_BROADCAST ;

    if(ioctl(sock_fd,SIOCSIFFLAGS,&ifr)< 0) //UP & running
    {
        perror("SIOCSIFFLAGS occured an error : ");
        exit(1);
    }
    /************************************SET IP ADDR & FLAGS & RUNNING************************************/


    /************************************SET DEST ADDR************************************/
    ip_addr.sin_family=AF_INET;
    ip_addr.sin_addr.s_addr=INADDR_ANY; //convert Dotted Decimal Notation to network byte
    ip_addr.sin_port=0;

    memcpy(&ifr.ifr_addr,&ip_addr,sizeof(struct sockaddr));

    if (ioctl(sock_fd, SIOCSIFDSTADDR, &ifr) < 0)
    {
        perror("SIOCSIFDSTADDR occured an error : ");
        exit(1);
    }
    /************************************SET DEST ADDR************************************/


    /************************************SET NETMASK************************************/
    memset(&ip_addr,0,sizeof(struct sockaddr));
    ip_addr.sin_family=AF_INET;
    ip_addr.sin_addr.s_addr=inet_addr(netmask); //network prifix set /24
    ip_addr.sin_port=0;

    memcpy(&ifr.ifr_addr,&ip_addr,sizeof(struct sockaddr));

    if (ioctl(sock_fd, SIOCSIFNETMASK, &ifr) < 0)
    {
        perror("SIOCSIFNETMASK occured an error : ");
        exit(1);
    }
    /************************************SET NETMASK************************************/
    return 0;




}
