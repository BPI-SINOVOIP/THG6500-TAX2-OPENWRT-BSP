/*
 */

#ifndef __TRI_CFE_HOOK_H__
#define __TRI_CFE_HOOK_H__

/* 业务学习挂载点定义 */
enum tri_cfe_hook_pos_e {
	/* LINUX系统钩子函数节点 */
	TRI_CFE_HOOK_PREROUTING_BRIDGE_E = 0,
	TRI_CFE_HOOK_PREROUTING_INET_E = 1,
	TRI_CFE_HOOK_PREROUTING_INET6_E = 2,
	TRI_CFE_HOOK_LOCAL_IN_BRIDGE_E = 3,
	TRI_CFE_HOOK_LOCAL_IN_INET_E = 4,
	TRI_CFE_HOOK_LOCAL_IN_INET6_E = 5,
	TRI_CFE_HOOK_FORWARD_BRIDGE_E = 6,
	TRI_CFE_HOOK_FORWARD_INET_E = 7,
	TRI_CFE_HOOK_FORWARD_INET6_E = 8,
	TRI_CFE_HOOK_LOCAL_OUT_BRIDGE_E = 9,
	TRI_CFE_HOOK_LOCAL_OUT_INET_E = 10,
	TRI_CFE_HOOK_LOCAL_OUT_INET6_E = 11,
	TRI_CFE_HOOK_POSTROUTING_BRIDGE_E = 12,
	TRI_CFE_HOOK_POSTROUTING_INET_E = 13,
	TRI_CFE_HOOK_POSTROUTING_INET6_E = 14,
	/* 系统设备自身提供钩子函数节点 */
	/* 接收钩子 */
	TRI_CFE_HOOK_POST_ETH0_E = 20, /* 来自eth0报文 */
	TRI_CFE_HOOK_PRE_TOLINUX_E,    /* 交LINUX处理前 */
	TRI_CFE_HOOK_POST_TOLINUX_E,   /* 交LINUX之前 */
	/* 发送钩子 */
	TRI_CFE_HOOK_PRE_CPUTODEV_E = 30, /* CPU发送到指定设备入口 */
	TRI_CFE_HOOK_POST_CPUTODEV_E,     /* CPU发送到指定设备出口 */
	TRI_CFE_HOOK_POST_CPUTOWIFI_E,
	TRI_CFE_HOOK_POST_CPUTOWIFI_NOVIRT_E,
	TRI_CFE_HOOK_POST_CPUTOWIFI_NOIGR_E,
	TRI_CFE_HOOK_POST_CPUTOWIFI_UNKNOWN_E,

	/* 来自扩展设备到CPU */
	TRI_CFE_HOOK_EXTDEV_TO_CPU_E = 40,
	/* 来自扩展设备到CPU报文;ACC硬件加速后转CPU出口报文 */
	TRI_CFE_HOOK_EXTDEV_PRE_TYPE_EXT_WIFI_E,
	TRI_CFE_HOOK_EXTDEV_POST_TYPE_EXT_WIFI_E,
	TRI_CFE_HOOK_EXTDEV_PRE_TYPE_EXT_QOS_E,
	TRI_CFE_HOOK_EXTDEV_POST_TYPE_EXT_QOS_E,
	/* MUX设备 */
	TRI_CFE_HOOK_EXTDEV_MUX_E = 50,
	/* 来自LSW到扩展设备 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_E = 60,     /* 入口 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_L2MC_E,     /* 二层组播报文 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_L3MC_E,     /* 三层组播报文 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_UNKNOW_E,   /* 未知报文或者广播报文 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_NORMAL_E,   /* 单播报文 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_TODEV_E,    /* 出口 */
	TRI_CFE_HOOK_EXTDEV_FROM_LSW_TODEV_MC_E, /* 组播报文 */
	/* 来自扩展设备到LSW入口 */
	TRI_CFE_HOOK_EXTDEV_PRE_TO_LSW_E = 70,
	/* 来自扩展设备到LSW出口 */
	TRI_CFE_HOOK_EXTDEV_POST_TO_LSW_E,
	TRI_CFE_HOOK_EXTDEV_PRE_TO_TOLINUX_E,
	TRI_CFE_HOOK_EXTDEV_PRE_TO_TOWIFI_E,
	TRI_CFE_HOOK_EXTDEV_SSIDS_LOOPBACK1_E,
	TRI_CFE_HOOK_EXTDEV_SSIDS_LOOPBACK2_E,
	TRI_CFE_HOOK_POS_CNT_E,
};

/* 业务学习钩子函数 */
typedef tri_int32 (*tri_cfe_hook_method)(struct sk_buff *skb, tri_void *node);

struct tri_cfe_hook_s {
	struct tri_list_head list;
	tri_cfe_hook_method lrn;
};

tri_int32 tri_cfe_hook_init(tri_void);

tri_void tri_cfe_hook_uninit(tri_void);

tri_void tri_cfe_hook_lrn_del(struct tri_cfe_hook_s *node);

tri_void tri_cfe_hook_lrn_exec(struct sk_buff *skb, enum tri_cfe_hook_pos_e pos);

tri_int32 tri_cfe_hook_lrn_init(tri_void);

tri_void tri_cfe_hook_lrn_insert(enum tri_cfe_hook_pos_e pos,
			       struct tri_cfe_hook_s *node);

tri_void tri_cfe_hook_snooping(struct sk_buff *skb, enum tri_cfe_hook_pos_e pos);

#endif /* __TRI_CFE_HOOK_H__ */