/*
 */

#ifndef __TRI_LINUX_H__
#define __TRI_LINUX_H__

#include <linux/string.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/random.h>
#include <linux/delay.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/socket.h>
#include <linux/netlink.h>
#include <linux/netdevice.h>
#include <linux/igmp.h>
#include <linux/udp.h>
#include <linux/etherdevice.h>
#include <linux/inetdevice.h>
#include <linux/jiffies.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/thread_info.h>
#include <linux/slab.h>
#include <linux/jhash.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/dma-mapping.h>
#include <linux/netfilter.h>
#include <linux/ppp_defs.h>
#include <linux/spinlock.h>
#include <linux/skbuff.h>
#include <tr6560/net/triams_exskbuff.h>
#include <linux/if_ether.h>
#include <linux/if_pppox.h>
#include <linux/dma-mapping.h>
#include <linux/kthread.h>
#include <linux/kernel_stat.h>
#include <linux/version.h>
#include <linux/if_arp.h>
#include <linux/netfilter_ipv6.h>
#include <linux/netfilter_bridge.h>
#include <linux/crc16.h>
#include <asm/atomic.h>
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <asm/delay.h>
#include <asm/io.h>
#include <net/sock.h>
#include <net/genetlink.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/netfilter/ipv4/nf_conntrack_ipv4.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_conntrack_acct.h>
#include <net/route.h>
#include <net/neighbour.h>
#include <../net/bridge/br_private.h>
#if (LINUX_VERSION_CODE > KERNEL_VERSION(3, 8, 0))
#include <net/ip_tunnels.h>
#else
#include <net/ipip.h>
#endif
#include <net/inet_ecn.h>
/* ipsec */
#include <linux/crypto.h>
#include <linux/scatterlist.h>
#include <crypto/algapi.h>
#include <crypto/cryptd.h>
#include <crypto/sha.h>
#include <linux/bitops.h>
#include <crypto/internal/hash.h>
#include <generated/autoconf.h>
#include <linux/kallsyms.h>

#endif /* __TRI_LINUX_H__ */
