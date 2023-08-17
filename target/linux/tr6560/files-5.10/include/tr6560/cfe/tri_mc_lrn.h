/*
 */

#ifndef __TRI_MC_LRN_H__
#define __TRI_MC_LRN_H__

/* 过滤模式 */
#define TRI_MC_LRN_REMOVE_GRP 0
#define TRI_MC_LRN_IN_ADD 1
#define TRI_MC_LRN_IN_CLEAR 2
#define TRI_MC_LRN_EX_ADD 3
#define TRI_MC_LRN_EX_CLEAR 4

/* WAN模式 */
#define TRI_MC_LRN_WAN_UNKWN 0
#define TRI_MC_LRN_WAN_BRIDGED 1
#define TRI_MC_LRN_WAN_ROUTED 2

#define TRI_MC_LRN_IP_GROUP_NUM 32

#define TRI_MC_LRN_EXT_PORT_MAX 2
#define TRI_MC_LRN_EXT_PORT_BASE 16

#define TRI_MC_LRN_DATA_DIP_MIN 0xE0000100 /* 224.0.1.0 */
#define TRI_MC_LRN_DATA_DIP_MAX 0xEFFFFFFF /* 239.255.255.255 */

#ifdef CONFIG_ARCH_YYXXXXB
#define TRI_MC_LRN_VPORT_BASE 12
#endif

#define tri_mc_lrn_dump_field(field, fmt, arg...) do { \
		tri_printk(KERN_CONT "\n%-16s= " fmt " ", field, ##arg); \
	} while (0)

union tri_mc_ip_u {
	struct in_addr v4;
	struct in6_addr v6;
};

enum tri_mc_type_e {
	TRI_MC_IPV4_E = 0,
	TRI_MC_IPV6_E = 1,
};

struct tri_mc_lrn_tagact_s {
	enum tri_hal_act_e tag_act;       /* TAG动作选择 */
	enum tri_hal_bool_e svlan_rep_en; /* 外层VLAN动作 */
	enum tri_hal_bool_e cvlan_rep_en; /* 内层VLAN动作 */
	tri_uint32 svlan;                 /* 外层自定义VLAN值 */
	tri_uint32 cvlan;                 /* 内层自定义VLAN值 */
};

struct tri_mc_lrn_cfg_s {
	tri_uchar8 enable;
	tri_uchar8 debug;
};

/* 报文信息 */
struct tri_mc_lrn_pkt_info_s {
	enum tri_mc_type_e type;
	union tri_mc_ip_u src;
	union tri_mc_ip_u grp;
	struct net_device *dev;
	struct net_device *igr_dev;
	tri_uchar8 smac[TRI_MAC_LEN]; /* smac */
	tri_uchar8 dmac[TRI_MAC_LEN]; /* dmac */
};

struct tri_mc_lrn_sub_node_s {
	struct tri_list_head sub_list;
	union tri_mc_ip_u src;
};

/* 记录ATP平台配置的(*,G)或(S,G)表项 */
struct tri_mc_lrn_node_s {
	struct tri_list_head list;
	enum tri_mc_type_e type;
	tri_int32 mode;
	union tri_mc_ip_u grp;
	struct net_bridge_port *prt;
	tri_uint32 port;
	tri_int32 wan_ops;
	tri_int32 wan_ppp;
	struct tri_list_head sub_hlist;
	struct tri_list_head sub_slist;
	struct tri_mc_lrn_tagact_s tagact;
};

/* 记录学习到的(S,G)表项 */
struct tri_mc_lrn_ip_group_s {
	tri_uint32 valid;
	enum tri_mc_type_e type;           /* 组播IP类型: 0-IPV4, 1-IPV6 */
	tri_uint32 dir;                    /* 组播流方向: 0-上行, 1-下行 */
	union tri_mc_ip_u src;             /* 组播源IP */
	union tri_mc_ip_u grp;             /* 组播组IP */
	tri_uint32 ttl_dec;                /* TTL是否减一 */
	tri_uint32 pppoe_rep;              /* pppoe编辑 */
	tri_uint32 smac_rep;               /* smac替换标识 */
	tri_uint32 dmac_rep;               /* dmac替换标识 */
	tri_uchar8 smac[TRI_MAC_LEN];       /* 需要替换的smac */
	tri_uchar8 dmac[TRI_MAC_LEN];       /* 需要替换的dmac */
	tri_uint32 cnt_en;                 /* 组播统计使能 */
	tri_uint32 portmap;                /* 组播节目出端口 */
	tri_uint32 refcnt;                 /* 引用计数 */
};

struct tri_mc_lrn_mng_s {
	struct tri_list_head list;
	tri_uchar8 enable;
	struct tri_cfe_hook_s hook;
	tri_uchar8 debug;
	tri_spinlock_t lrn_lock;
};

struct tri_mc_lrn_cnt_s {
	tri_uint32 disable_cnt;
	tri_uint32 prt_err_cnt;
	tri_uint32 node_null_cnt;
	tri_uint32 binding_cnt;
	tri_uint32 acc_null_cnt;
	tri_uint32 dup_cnt;
	tri_uint32 full_cnt;
	tri_uint32 grp_act_err_cnt;
	tri_uint32 usr_act_err_cnt;
	tri_uint32 hw_err_cnt;
	tri_uint32 grp_err_cnt;
	tri_uint32 usr_err_cnt;
};

struct tri_mc_lrn_cmd_s {
	tri_int32 mode;
	tri_uint32 src[4];
	tri_uint32 grp[4];
	tri_char8 ifname[TRI_HW_INTF_NAME_MAXLEN];
	tri_int32 wan_ops;
	tri_int32 wan_ppp;
};

struct tri_mc_lrn_cmd_s_v4 {
    tri_int32 mode;
	tri_uint32 src;
	tri_uint32 grp;
    tri_char8 ifname[TRI_HW_INTF_NAME_MAXLEN];
    tri_int32 wan_ops;
    tri_int32 wan_ppp;
};

struct tri_mc_lrn_ext_port_record_s {
	tri_int32 valid;
	tri_uchar8 ifname[TRI_HW_INTF_NAME_MAXLEN];
};

struct tri_mc_lrn_add_data_s {
	tri_int32 mode;                  /* include 0 or exclude 1 */
	union {
		struct in_addr *v4;
		struct in6_addr *v6;
	} src;                          /* 组播源IP，可以为空 */
	union {
		struct in_addr *v4;
		struct in6_addr *v6;
	} grp;                          /* 组播组IP，不能为空 */
	struct net_bridge_port *prt;    /* 桥出口 不能为空 */
	tri_int32 wan_ops;               /* 指示桥或者路由模式 */
	tri_int32 wan_ppp;               /* 指示wan连接为pppoe模式 */
};


/* IGMP组播接口 */
tri_int32 tri_mc_igmp_entry_add(struct tri_mc_lrn_add_data_s *data);
tri_int32 tri_mc_igmp_entry_del(tri_int32 mode, struct in_addr *src,
			      struct in_addr *grp, struct net_bridge_port *prt);

/* MLD组播接口 */
tri_int32 tri_mc_mld_entry_add(struct tri_mc_lrn_add_data_s *data);
tri_int32 tri_mc_mld_entry_del(tri_int32 mode, struct in6_addr *src,
			     struct in6_addr *grp, struct net_bridge_port *prt);
tri_int32 tri_mc_lrn_entry(struct sk_buff *skb, tri_void *hook);
tri_int32 tri_mc_lrn_wifi_tx(struct tri_hal_pie_cb_s *cb, struct sk_buff *skb);

#endif /* __TRI_MC_LRN_H__ */
