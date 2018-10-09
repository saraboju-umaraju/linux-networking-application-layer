struct in_addr {
    __be32  s_addr;
};

struct sockaddr_in {
  __kernel_sa_family_t  sin_family; /* Address family       */
  __be16        sin_port;   /* Port number          */
  struct in_addr    sin_addr;   /* Internet address     */

  /* Pad to size of `struct sockaddr'. */
  unsigned char     __pad[__SOCK_SIZE__ - sizeof(short int) -
            sizeof(unsigned short int) - sizeof(struct in_addr)];
};

struct sockaddr {
    sa_family_t sa_family;  /* address family, AF_xxx   */
    char        sa_data[14];    /* 14 bytes of protocol address */
};

struct ifreq
  {
# define IFHWADDRLEN    6
# define IFNAMSIZ   IF_NAMESIZE
    union
      {
    char ifrn_name[IFNAMSIZ];   /* Interface name, e.g. "en0".  */
      } ifr_ifrn;

    union
      {
    struct sockaddr ifru_addr;
    struct sockaddr ifru_dstaddr;
    struct sockaddr ifru_broadaddr;
    struct sockaddr ifru_netmask;
    struct sockaddr ifru_hwaddr;
    short int ifru_flags;
    int ifru_ivalue;
    int ifru_mtu;
    struct ifmap ifru_map;
    char ifru_slave[IFNAMSIZ];  /* Just fits the size */
    char ifru_newname[IFNAMSIZ];
    __caddr_t ifru_data;
      } ifr_ifru;
  };
struct sockaddr_pkt {
    unsigned short spkt_family;
    unsigned char spkt_device[14];
    __be16 spkt_protocol;
};

struct sockaddr_ll {
    unsigned short  sll_family;
    __be16      sll_protocol;
    int     sll_ifindex;
    unsigned short  sll_hatype;
    unsigned char   sll_pkttype;
    unsigned char   sll_halen;
    unsigned char   sll_addr[8];
};

