/*
 */

#ifndef __TRI_NETDEF_H__
#define __TRI_NETDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* Network order conversion, system only support little-endian */
#ifndef tri_ntoll
#define tri_ntoll(data)	((tri_ulong64)(((tri_ulong64)(data) >> 56) | \
	((tri_ulong64)(data) << 56) | \
	(((tri_ulong64)(data) >> 40) & 0x000000000000ff00LL) | \
	(((tri_ulong64)(data) << 40) & 0x00ff000000000000LL) | \
	(((tri_ulong64)(data) >> 24) & 0x0000000000ff0000LL) | \
	(((tri_ulong64)(data) << 24) & 0x0000ff0000000000LL) | \
	(((tri_ulong64)(data) >> 8) & 0x00000000ff000000LL) | \
	(((tri_ulong64)(data) << 8) & 0x000000ff00000000LL)))
#endif

#ifndef tri_ntohl
#define tri_ntohl(data)	((tri_uint32)(((tri_uint32)(data) >> 24) | \
	((tri_uint32)(data) << 24) | \
	(((tri_uint32)(data) >> 8) & 0x0000ff00) | \
	(((tri_uint32)(data) << 8) & 0x00ff0000)))
#endif

#ifndef tri_htonl
#define tri_htonl(data)	((tri_uint32)(((tri_uint32)(data) >> 24) | \
	((tri_uint32)(data) << 24) | \
	(((tri_uint32)(data) >> 8) & 0x0000ff00) | \
	(((tri_uint32)(data) << 8) & 0x00ff0000)))
#endif

#ifndef tri_ntohs
#define tri_ntohs(data)	((tri_ushort16)(((tri_ushort16)(data) >> 8) | \
	((tri_ushort16)(data) << 8)))
#endif

#ifndef tri_htons
#define tri_htons(data)	((tri_ushort16) (((tri_ushort16)(data) >> 8) | \
	((tri_ushort16)(data) << 8)))
#endif

#define tri_ushort(byte0, byte1)	((TRI_BITMASK_LOW08 & (tri_uint32)(byte0)) | \
	((TRI_BITMASK_LOW08 & (tri_uint32)(byte1)) << 0x8))

#define tri_uint(byte0, byte1, byte2, byte3) \
	((TRI_BITMASK_LOW08 & (tri_uint32)(byte0)) | \
	((TRI_BITMASK_LOW08 & (tri_uint32)(byte1)) << 0x8) | \
	((TRI_BITMASK_LOW08 & (tri_uint32)(byte2)) << (0x8 * 2)) | \
	((TRI_BITMASK_LOW08 & (tri_uint32)(byte3)) << (0x8 * 3)))

/* PRI(3bits) | CFI(1bit) | TAG(12bits) | Ether-Type(2bytes) | DATA | */
#define TRI_VLAN_PRI_MAX              0x7
#define TRI_VLAN_PRI_INVALID          0xFF

#define tri_get_vlan_vid(tag)         ((tag) & 0x0FFF)
#define tri_get_vlan_pri(tag)         (((tag) & 0xE000) >> 13)
#define tri_get_vlan_tag(pri, vid) \
		(((((tri_ushort16)(pri)) & 0x7) << 13) | ((vid) & 0x0FFF))

#define TRI_INADDR_ANY       0x00000000
#define TRI_INADDR_NONE      0xFFFFFFFFUL
#define TRI_INVALID_SOCKET   0xFFFFFFFFUL

#define TRI_MTU              1500
#define TRI_MAC_MTU          2000

#define TRI_MAC_LEN          6   /* mac address length */
#define TRI_ETH_HLEN         14  /* Total octets in header */
#define TRI_VLAN_HLEN        4
#define TRI_VLAN_MASK        0xEFFF
#define TRI_VLAN_DEF_TPID    0x8100
#define TRI_VLAN_DEF_TPID1   0x88a8
#define TRI_IPVERSION        4
#define TRI_IPV6ERSION       6
#define TRI_IPV4_LEN         4
#define TRI_IPV6_LEN         16
#define TRI_PPP_LEN          8

#define TRI_SKB_RESV_LEN     256
#define TRI_SKB_CB_LEN       64

#define TRI_AF_UNSPEC     0
#define TRI_AF_UNIX       1   /* Unix domain sockets */
#define TRI_AF_LOCAL      1   /* POSIX name for AF_UNIX */
#define TRI_AF_INET       2   /* Internet IP Protocol */
#define TRI_AF_AX25       3   /* Amateur Radio AX.25 */
#define TRI_AF_IPX        4   /* Novell IPX */
#define TRI_AF_APPLETALK  5   /* AppleTalk DDP */
#define TRI_AF_NETROM     6   /* Amateur Radio NET/ROM */
#define TRI_AF_BRIDGE     7   /* Multiprotocol bridge */
#define TRI_AF_ATMPVC     8   /* ATM PVCs */
#define TRI_AF_X25        9   /* Reserved for X.25 project */
#define TRI_AF_INET6      10  /* IP version 6 */
#define TRI_AF_ROSE       11  /* Amateur Radio X.25 PLP */
#define TRI_AF_DECNET     12  /* Reserved for DECnet project */
#define TRI_AF_NETBEUI    13  /* Reserved for 802.2LLC project */
#define TRI_AF_SECURITY   14  /* Security callback pseudo AF */
#define TRI_AF_KEY        15  /* PF_KEY key management API */
#define TRI_AF_NETLINK    16
#define TRI_AF_ROUTE      AF_NETLINK  /* Alias to emulate 4.4BSD */
#define TRI_AF_PACKET     17  /* Packet family */
#define TRI_AF_ASH        18  /* Ash */
#define TRI_AF_ECONET     19  /* Acorn Econet */
#define TRI_AF_ATMSVC     20  /* ATM SVCs */
#define TRI_AF_RDS        21  /* RDS sockets */
#define TRI_AF_SNA        22  /* Linux SNA Project (nutters!) */
#define TRI_AF_IRDA       23  /* IRDA sockets */
#define TRI_AF_PPPOX      24  /* PPPoX sockets */
#define TRI_AF_WANPIPE    25  /* Wanpipe API Sockets */
#define TRI_AF_LLC        26  /* Linux LLC */
#define TRI_AF_CAN        29  /* Controller Area Network */
#define TRI_AF_TIPC       30  /* TIPC sockets */
#define TRI_AF_BLUETOOTH  31  /* Bluetooth sockets */
#define TRI_AF_IUCV       32  /* IUCV sockets */
#define TRI_AF_RXRPC      33  /* RxRPC sockets */
#define TRI_AF_ISDN       34  /* mISDN sockets */
#define TRI_AF_PHONET     35  /* Phonet sockets */
#define TRI_AF_IEEE802154 36  /* IEEE802154 sockets */
#define TRI_AF_CAIF       37  /* CAIF sockets */
#define TRI_AF_ALG        38  /* Algorithm sockets */
#define TRI_AF_NFC        39  /* NFC sockets */
#define TRI_AF_VSOCK      40  /* vSockets */
#define TRI_AF_MAX        41  /* For now */

#define TRI_ETH_P_LOOP       0x0060  /* Ethernet Loopback packet */
#define TRI_ETH_P_PUP        0x0200  /* Xerox PUP packet */
#define TRI_ETH_P_PUPAT      0x0201  /* Xerox PUP Addr Trans packet */
#define TRI_ETH_P_IP         0x0800  /* Internet Protocol packet */
#define TRI_ETH_P_X25        0x0805  /* CCITT X.25 */
#define TRI_ETH_P_ARP        0x0806  /* Address Resolution packet */

/* G8BPQ AX.25 Ethernet Packet [ NOT AN OFFICIALLY REGISTERED ID ] */
#define TRI_ETH_P_BPQ        0x08FF
#define TRI_ETH_P_IEEEPUP    0x0a00  /* Xerox IEEE802.3 PUP packet */
#define TRI_ETH_P_IEEEPUPAT  0x0a01  /* Xerox IEEE802.3 PUP Addr Trans packet */
#define TRI_ETH_P_DEC        0x6000  /* DEC Assigned proto */
#define TRI_ETH_P_DNA_DL     0x6001  /* DEC DNA Dump/Load */
#define TRI_ETH_P_DNA_RC     0x6002  /* DEC DNA Remote Console */
#define TRI_ETH_P_DNA_RT     0x6003  /* DEC DNA Routing */
#define TRI_ETH_P_LAT        0x6004  /* DEC LAT */
#define TRI_ETH_P_DIAG       0x6005  /* DEC Diagnostics */
#define TRI_ETH_P_CUST       0x6006  /* DEC Customer use */
#define TRI_ETH_P_SCA        0x6007  /* DEC Systems Comms Arch */
#define TRI_ETH_P_RARP       0x8035  /* Reverse Addr Res packet */
#define TRI_ETH_P_ATALK      0x809B  /* Appletalk DDP */
#define TRI_ETH_P_AARP       0x80F3  /* Appletalk AARP */
#define TRI_ETH_P_8021Q      0x8100  /* 802.1Q VLAN Extended Header */
#define TRI_ETH_P_IPX        0x8137  /* IPX over DIX */
#define TRI_ETH_P_IPV4       0x0800  /* IPv4 */
#define TRI_ETH_P_IPV6       0x86DD  /* IPv6 over bluebook */
#define TRI_ETH_P_SLOW       0x8809  /* Slow Protocol. See 802.3ad 43B */
#define TRI_ETH_P_WCCP       0x883E  /* Web-cache coordination protocol */
#define TRI_ETH_P_PPP_DISC   0x8863  /* PPPoE discovery messages */
#define TRI_ETH_P_PPP_SES    0x8864  /* PPPoE session messages */
#define TRI_ETH_P_MPLS_UC    0x8847  /* MPLS Unicast traffic */
#define TRI_ETH_P_MPLS_MC    0x8848  /* MPLS Multicast traffic */
#define TRI_ETH_P_ATMMPOA    0x884c  /* MultiProtocol Over ATM */
#define TRI_ETH_P_ATMFATE    0x8884  /* Frame-based ATM Transport */
#define TRI_ETH_P_PPP_PRO_IP   0x0021
#define TRI_ETH_P_PPP_PRO_IPv6 0x0057
#define TRI_PPP_RESV_SESSIONID 0xFFFF /* reserved PPPoE session ID */

enum tri_ipproto_e {
	TRI_IPPROTO_IP_E = 0,      /* Dummy protocol for TCP */
	TRI_IPPROTO_ICMP_E = 1,    /* Internet Control Message Protocol */
	TRI_IPPROTO_IGMP_E = 2,    /* Internet Group Management Protocol */
	TRI_IPPROTO_IPIP_E = 4,    /* IPIP tunnels (older KA9Q tunnels use 94) */
	TRI_IPPROTO_TCP_E = 6,     /* Transmission Control Protocol */
	TRI_IPPROTO_EGP_E = 8,     /* Exterior Gateway Protocol */
	TRI_IPPROTO_PUP_E = 12,    /* PUP protocol */
	TRI_IPPROTO_UDP_E = 17,    /* User Datagram Protocol */
	TRI_IPPROTO_IDP_E = 22,    /* XNS IDP protocol */
	TRI_IPPROTO_DCCP_E = 33,   /* Datagram Congestion Control Protocol */
	TRI_IPPROTO_RSVP_E = 46,   /* RSVP protocol */
	TRI_IPPROTO_GRE_E = 47,    /* Cisco GRE tunnels (rfc 1701,1702) */
	TRI_IPPROTO_IPV6_E = 41,   /* IPv6-in-IPv4 tunnelling */
	TRI_IPPROTO_ESP_E = 50,    /* Encapsulation Security Payload protocol */
	TRI_IPPROTO_AH_E = 51,     /* Authentication Header protocol */
	TRI_IPPROTO_NEXTHDR_ICMP_E = 58,
	TRI_IPPROTO_BEETPH_E = 94, /* IP option pseudo header for BEET */
	TRI_IPPROTO_PIM_E = 103,      /* Protocol Independent Multicast */
	TRI_IPPROTO_COMP_E = 108,     /* Compression Header protocol */
	TRI_IPPROTO_ZERO_HOP_E = 114, /* any 0-hop protocol */
	TRI_IPPROTO_SCTP_E = 132,     /* Stream Control Transport Protocol */
	TRI_IPPROTO_UDPLITE_E = 136,  /* UDP-Lite (RFC 3828) */
	TRI_IPPROTO_RAW_E = 255,      /* Raw IP packets */
	TRI_IPPROTO_MAX_E,
};

/* NextHeader field of IPv6 header */
enum tri_ipv6_nexthd_e {
	TRI_NEXTHDR_HOP_E       = 0,    /* Hop-by-hop option header. */
	TRI_NEXTHDR_TCP_E       = 6,    /* TCP segment. */
	TRI_NEXTHDR_UDP_E       = 17,   /* UDP message. */
	TRI_NEXTHDR_IPV6_E      = 41,   /* IPv6 in IPv6 */
	TRI_NEXTHDR_ROUTING_E   = 43,   /* Routing header. */
	TRI_NEXTHDR_FRAGMENT_E  = 44,   /* Fragmentation/reassembly header. */
	TRI_NEXTHDR_ESP_E       = 50,   /* Encapsulating security payload. */
	TRI_NEXTHDR_AUTH_E      = 51,   /* Authentication header. */
	TRI_NEXTHDR_ICMP_E      = 58,   /* ICMP for IPv6. */
	TRI_NEXTHDR_NONE_E      = 59,   /* No next header */
	TRI_NEXTHDR_DEST_E      = 60,   /* Destination options header. */
	TRI_NEXTHDR_MOBILITY_E  = 135,  /* Mobility header. */
	TRI_NEXTHDR_MAX_E       = 255,
};

#define tri_network_is_valid_mac_addr(addr) ((!(0x01 & (addr)[0])) && \
	(((addr)[0] | (addr)[1] | (addr)[2] | \
	(addr)[3] | (addr)[4] | (addr)[5])))

#define TRI_NET_DEVICE_TYPE_ROOT 0
#define TRI_NET_DEVICE_TYPE_WAN  1
#define TRI_NET_DEVICE_TYPE_LAN  2

#pragma pack(1)

struct tri_in6_addr_s {
	union {
		tri_uchar8   addr8[16];
		tri_ushort16 addr16[8];
		tri_uint32   addr32[4];
	};
};

/* network data structure */
struct tri_ethhdr_s {
	tri_uchar8   dest[TRI_MAC_LEN];   /* destination eth addr */
	tri_uchar8   source[TRI_MAC_LEN]; /* source ether addr */
	tri_ushort16 proto;              /* packet type ID field */
}; /* __attribute__((packed)) */

struct tri_pppoehdr_s {
	tri_uchar8   version : 4;
	tri_uchar8   type    : 4;
	tri_uchar8   code;
	tri_ushort16 sid;
	tri_ushort16 len;
	tri_ushort16 proto;
};

struct tri_vlanhdr_s {
	tri_ushort16 subtype;
	tri_ushort16 vlan;
};

struct tri_iphdr_s {
	tri_uchar8 ihl : 4,
		  version : 4;
	tri_uchar8 tos;
	tri_ushort16 tot_len;
	tri_ushort16 id;
	tri_ushort16 frag_off;
	tri_uchar8 ttl;
	tri_uchar8 protocol;
	tri_ushort16 check;
	tri_uint32 saddr;
	tri_uint32 daddr;
	/* The options start here */
};

struct tri_ipv6hdr_s {
	tri_uchar8   priority : 4,
		    version : 4;
	tri_uchar8   flow_lbl[3];

	tri_ushort16 payload_len;
	tri_uchar8   nexthdr;
	tri_uchar8   hop_limit;

	struct tri_in6_addr_s saddr;
	struct tri_in6_addr_s daddr;
};

struct tri_ipv6nxt_s {
	tri_uchar8 nexthdr;
	tri_uchar8 extlen;
	tri_uchar8 rsv[2];
};

struct tri_arphdr_s {
	tri_ushort16 hrd;              /* format of hardware address */
	tri_ushort16 pro;              /* format of protocol address */
	tri_uchar8   hln;              /* length of hardware address */
	tri_uchar8   pln;              /* length of protocol address */
	tri_ushort16 op;               /* ARP opcode (command) */
	tri_uchar8   smac[TRI_MAC_LEN]; /* source mac address */
	tri_uint32   sip;              /* source ip address */
	tri_uchar8   dmac[TRI_MAC_LEN]; /* destination mac address */
	tri_uint32   dip;              /* destination ip address */
};

struct tri_icmphdr_s {
	tri_uchar8   type;
	tri_uchar8   code;
	tri_ushort16 checksum;
	union {
		struct {
			tri_ushort16 id;
			tri_ushort16 sequence;
		};
		tri_uint32 gateway;
		struct {
			tri_ushort16 unused;
			tri_ushort16 mtu;
		};
	};
};

struct tri_udphdr_s {
	tri_ushort16 source;
	tri_ushort16 dest;
	tri_ushort16 len;
	tri_ushort16 check;
};

struct tri_tcphdr_s {
	tri_ushort16 source;
	tri_ushort16 dest;
	tri_uint32   seq;
	tri_uint32   ack_seq;
	union {
		struct {
			tri_uchar8 rsv0 : 4,
				  len : 4;
		};
		tri_uchar8 value1;
	};
	union {
		struct {
			tri_uchar8 fin : 1,
				  syn : 1,
				  rst : 1,
				  psh : 1,
				  ack : 1,
				  urg : 1,
				  rsv1 : 2;
		};
		tri_uchar8 value2;
	};
	tri_ushort16 window;
	tri_ushort16 check;
	tri_ushort16 urg_ptr;
};

struct tri_tcpopt_s {
	tri_uchar8 type;
	tri_uchar8 len;
	tri_ushort16 data;
};

#pragma pack()

struct tri_pseudohdr_s {
	tri_uint32 sip;
	tri_uint32 dip;
	tri_uchar8 pad;
	tri_uchar8 proto;
	tri_ushort16 len;
};

struct tri_in_addr_s {
	tri_uint32 addr;
};

struct tri_sockaddr_s {
	tri_ushort16 sa_family;   /* address family AF_xxx */
	tri_uchar8   sa_data[14]; /* 14 byte protocol address */
};

struct tri_sockaddr_in_s {
	tri_ushort16  sin_family;  /* address family */
	tri_ushort16  sin_port;    /* port number */
	struct tri_in_addr_s sin_addr;    /* IP address */
	/* padding 0 to maintain and struct sockaddr the same size */
	tri_uchar8    sin_zero[8];
};

struct tri_ipv4_s {
	tri_uint32 v4;
};

struct tri_ipv6_s {
	tri_uchar8 v6[16]; /* 16 byte ipv6 address */
};

union tri_ip_addr_u {
	struct tri_ipv4_s v4;
	struct tri_ipv6_s v6;
};

/* IP VERSION */
enum tri_ip_ver_e {
	TRI_NOIP_E,
	TRI_IPV4_E,
	TRI_IPV6_E,
	TRI_IP_VER_CNT_E
};

struct tri_ip_addr_s {
	union tri_ip_addr_u ip;
	enum tri_ip_ver_e ver;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_NETDEF_H__ */
