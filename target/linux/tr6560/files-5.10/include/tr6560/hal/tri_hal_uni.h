/*
 */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifndef __TRI_HAL_UNI_H__
#define __TRI_HAL_UNI_H__

#define TRI_HAL_TPID_NUM 3

/* 以太端口类型 */
enum tri_hal_uni_type_e {
	TRI_HAL_UNI_TYPE_FE_E = 0, /* FE */
	TRI_HAL_UNI_TYPE_GE_E, /* GE */
	TRI_HAL_UNI_TYPE_10GE_E, /* 10GE */
};

/* 以太端口的连接状态 */
enum tri_hal_uni_link_sta_e {
	TRI_HAL_UNI_LINK_DN, /* LINK DOWN状态 */
	TRI_HAL_UNI_LINK_UP, /* LINK UP状态 */
};

enum tri_hal_endian_e {
	TRI_HAL_BIG_ENDIAN_E = 0, /* 大端模式 */
	TRI_HAL_LITTLE_ENDIAN_E, /* 小端模式 */
};

enum tri_hal_uni_inout_e {
	TRI_HAL_UNI_IGR_TAG_ACT_E = 0, /* 表示入口方向 */
	TRI_HAL_UNI_EGR_TAG_ACT_E, /* 表示出口方向 */
};

enum tri_hal_uni_tag_type_e {
	TRI_HAL_UNI_TAG_ACT_E = 0, /* tag 动作 */
	TRI_HAL_UNI_PRI_TAG_ACT_E, /* pri tag 动作 */
	TRI_HAL_UNI_UNTAG_ACT_E, /* untag  动作 */
};

/* TAG 编辑 */
enum tri_hal_uni_tag_act_e {
	TRI_HAL_UNI_TAG_NO_ACT_E = 0, /* 无动作**/
	TRI_HAL_UNI_TAG_ADD_E, /* 添加一层TAG */
	TRI_HAL_UNI_TAG_DEL_E, /* 删除一层TAG */
	TRI_HAL_UNI_SVLAN_REP_E, /* 外层TAG替换成默认VLAN */
	TRI_HAL_UNI_TAG_HYBRID_E, /* 按HYBRID模式删除TAG */
	TRI_HAL_UNI_DTAG_DEL_E, /* 只删除默认TAG */
	TRI_HAL_UNI_TAG_DROP_E, /* 丢弃报文 */
	TRI_HAL_UNI_TAG_ACT_NUM_E,
};

/* 以太端口工作模式 */
enum tri_hal_port_eth_work_mode_e {
	TRI_HAL_PORT_ETH_AUTO_NEG_E, /* 自动协商 */

	TRI_HAL_PORT_ETH_HALF_10M_E, /* 半双工10M */
	TRI_HAL_PORT_ETH_HALF_100M_E, /* 半双工100M */
	TRI_HAL_PORT_ETH_HALF_1000M_E, /* 半双工1000M */

	TRI_HAL_PORT_ETH_DUP_10M_E, /* 全双工10M */
	TRI_HAL_PORT_ETH_DUP_100M_E, /* 全双工100M */
	TRI_HAL_PORT_ETH_DUP_1000M_E, /* 全双工1000M */
	TRI_HAL_PORT_ETH_TEST_E, /* 测试模式 */

	TRI_HAL_PORT_ETH_HALF_2500M_E, /* 半双工2.5G */
	TRI_HAL_PORT_ETH_DUP_2500M_E, /* 全双工2.5G */

	TRI_HAL_PORT_ETH_HALF_5000M_E, /* 半双工5G */
	TRI_HAL_PORT_ETH_DUP_5000M_E, /* 全双工5G */

	TRI_HAL_PORT_ETH_HALF_10000M_E, /* 半双工10000M */
	TRI_HAL_PORT_ETH_DUP_10000M_E, /* 全双工10000M */

	TRI_HAL_PORT_ETH_WORK_MODE_NUM_E
};

/* 以太端口环回模式 */
enum tri_hal_port_eth_loop_mode_e {
	TRI_HAL_PORT_ETH_NO_LOOP_E = 0, /* 正常模式 */
	TRI_HAL_PORT_ETH_IN_LOOP_E, /* MAC内环回模式 */
	TRI_HAL_PORT_ETH_OUT_LOOP_E, /* MAC外环回模式 */
	TRI_HAL_PORT_ETH_PHY_IN_LOOP_E, /* PHY内环回模式 */
	TRI_HAL_PORT_ETH_PHY_OUT_LOOP_E, /* PHY外环回模式 */
	TRI_HAL_PORT_ETH_LOOP_MODE_NUM_E
};

/* 报文的入队优先级选择 */
enum tri_hal_port_pq_pri_e {
	TRI_HAL_PORT_PQ_PRI_SPRI_E = 0, /* 外层tag pri */
	TRI_HAL_PORT_PQ_PRI_DSCP_MAP_E, /* DSCP映射pri */
	TRI_HAL_PORT_PQ_PRI_DEF_PRI_E, /* 端口默认pri */
	TRI_HAL_PORT_PQ_PRI_NUM_E
};

/* PHY的供应商类型 */
enum tri_hal_phy_type_e {
	TRI_PHY_INNER_E = 0,
	TRI_PHY_EXT_E = 1,
	TRI_PHY_TYPE_NUM
};

enum tri_hal_phy_reg_act_e {
	TRI_PHY_ACT_NONE = 0, /* 无动作 */
	TRI_PHY_ACT_WRITE_E, /* 写寄存器 */
	TRI_PHY_ACT_READ_E /* 读取寄存器 */
};

#ifdef __KERNEL__
#define tri_hal_trace() printk("FUNC: %s, LINE: %d\n", __FUNCTION__, __LINE__)
#define tri_hal_trace2(a, b, c, d) printk("%s : %d===> %d, %d, %d, %d\n", \
					 __FUNCTION__, __LINE__, a, b, c, d)
#else
#define tri_hal_trace() printf("FUNC: %s, LINE: %d\n", __FUNCTION__, __LINE__)
#define tri_hal_trace2(a, b, c, d) printf("%s : %d===> %d, %d, %d, %d\n", \
					 __FUNCTION__, __LINE__, a, b, c, d)
#endif

#define TRI_HAL_MAC_BYTE_NUM 6
#define TRI_HAL_SMAC_FILTER_LIST_NUM 8
#define TRI_HAL_IPV4_ADDR_LEN 4
#define TRI_HAL_IPV6_ADDR_LEN 16
#define TRI_HAL_PORT_NAME_LEN 64


#define TRI_HAL_UINT32_INVALID 0xFFFFFFFF
#define TRI_HAL_IFC_RESERVED   0 /* 预留配置vlan广播时使用 */

#define TRI_HAL_PORT_MASK_ETH0  (0x1U << TRI_HAL_PORT_ETH0_E)
#define TRI_HAL_PORT_MASK_ETH1  (0x1U << TRI_HAL_PORT_ETH1_E)
#define TRI_HAL_PORT_MASK_ETH2  (0x1U << TRI_HAL_PORT_ETH2_E)
#define TRI_HAL_PORT_MASK_ETH3  (0x1U << TRI_HAL_PORT_ETH3_E)
#define TRI_HAL_PORT_MASK_ETH4  (0x1U << TRI_HAL_PORT_ETH4_E)
#define TRI_HAL_PORT_MASK_ETH5  (0x1U << TRI_HAL_PORT_ETH5_E)
#define TRI_HAL_PORT_MASK_RGMII (0x1U << TRI_HAL_PORT_RGMII_E)
#define TRI_HAL_PORT_MASK_WAN   (0x1U << TRI_HAL_PORT_WAN_E)
#define TRI_HAL_PORT_MASK_PLC   (0x1U << TRI_HAL_PORT_PLC_E)
#define TRI_HAL_PORT_MASK_PRBS  (0x1U << TRI_HAL_PORT_PRBS_E)
#define TRI_HAL_PORT_MASK_CPU0  (0x1U << TRI_HAL_PORT_CPU0_E)
#define TRI_HAL_PORT_MASK_CPU1  (0x1U << TRI_HAL_PORT_CPU1_E)
#define TRI_HAL_PORT_MASK_CPU2  (0x1U << TRI_HAL_PORT_CPU2_E)
#define TRI_HAL_PORT_MASK_CPU3  (0x1U << TRI_HAL_PORT_CPU3_E)

#define TRI_HAL_PORT_MASK_CID0  (0x1U << TRI_HAL_PORT_CID0_E)
#define TRI_HAL_PORT_MASK_CID1  (0x1U << TRI_HAL_PORT_CID1_E)
#define TRI_HAL_PORT_MASK_CID2  (0x1U << TRI_HAL_PORT_CID2_E)
#define TRI_HAL_PORT_MASK_CID3  (0x1U << TRI_HAL_PORT_CID3_E)
#define TRI_HAL_PORT_MASK_CID4  (0x1U << TRI_HAL_PORT_CID4_E)
#define TRI_HAL_PORT_MASK_CID5  (0x1U << TRI_HAL_PORT_CID5_E)
#define TRI_HAL_PORT_MASK_CID6  (0x1U << TRI_HAL_PORT_CID6_E)
#define TRI_HAL_PORT_MASK_CID7  (0x1U << TRI_HAL_PORT_CID7_E)
#define TRI_HAL_PORT_MASK_CID8  (0x1U << TRI_HAL_PORT_CID8_E)
#define TRI_HAL_PORT_MASK_CID9  (0x1U << TRI_HAL_PORT_CID9_E)
#define TRI_HAL_PORT_MASK_CID10 (0x1U << TRI_HAL_PORT_CID10_E)
#define TRI_HAL_PORT_MASK_CID11 (0x1U << TRI_HAL_PORT_CID11_E)
#define TRI_HAL_PORT_MASK_CID12 (0x1U << TRI_HAL_PORT_CID12_E)
#define TRI_HAL_PORT_MASK_CID13 (0x1U << TRI_HAL_PORT_CID13_E)
#define TRI_HAL_PORT_MASK_CID14 (0x1U << TRI_HAL_PORT_CID14_E)
#define TRI_HAL_PORT_MASK_CID15 (0x1U << TRI_HAL_PORT_CID15_E)

#define TRI_HAL_PORT_MASK_UNI (TRI_HAL_PORT_MASK_ETH0 |  \
			      TRI_HAL_PORT_MASK_ETH1 |  \
			      TRI_HAL_PORT_MASK_ETH2 |  \
			      TRI_HAL_PORT_MASK_ETH3)
#define tri_hal_uni_port_trans(x) ((x)-TRI_HAL_PORT_ETH0_E)
#define tri_hal_uni_cpu_trans(x) ((x)-TRI_HAL_PORT_CPU0_E)

enum tri_hal_bool_e {
	TRI_HAL_FALSE_E = 0, /* FALSE */
	TRI_HAL_TRUE_E /* TRUE */
};

enum tri_hal_port_e {
	/* 业务端口 */
	TRI_HAL_PORT_ETH0_E = 0, /* ETH端口0 */
	TRI_HAL_PORT_ETH1_E, /* ETH端口1 */
	TRI_HAL_PORT_ETH2_E, /* ETH端口2 */
	TRI_HAL_PORT_ETH3_E, /* ETH端口3 */
	TRI_HAL_PORT_ETH4_E, /* ETH端口4 */
	TRI_HAL_PORT_ETH5_E, /* ETH端口5 */
	TRI_HAL_PORT_ETH_MAX_E, /* ETH最大端口6 */
	TRI_HAL_PORT_RGMII_E = 8, /* RGMII */
	TRI_HAL_PORT_WAN_E = 9, /* WAN */
	TRI_HAL_PORT_PLC_E = 10, /* PLC端口 */
	TRI_HAL_PORT_PRBS_E = 11, /* PRBS端口 */
	TRI_HAL_PORT_CPU0_E = 12, /* CPU端口0 */
	TRI_HAL_PORT_CPU1_E, /* CPU端口1 */
	TRI_HAL_PORT_CPU2_E, /* CPU端口2 */
	TRI_HAL_PORT_CPU3_E, /* CPU端口3 */
	/* PLC 端口 */
	TRI_HAL_PORT_CID0_E = 16, /* PLC端口0 */
	TRI_HAL_PORT_CID1_E, /* PLC端口1 */
	TRI_HAL_PORT_CID2_E, /* PLC端口2 */
	TRI_HAL_PORT_CID3_E, /* PLC端口3 */
	TRI_HAL_PORT_CID4_E, /* PLC端口4 */
	TRI_HAL_PORT_CID5_E, /* PLC端口5 */
	TRI_HAL_PORT_CID6_E, /* PLC端口6 */
	TRI_HAL_PORT_CID7_E, /* PLC端口7 */
	TRI_HAL_PORT_CID8_E, /* PLC端口8 */
	TRI_HAL_PORT_CID9_E, /* PLC端口9 */
	TRI_HAL_PORT_CID10_E, /* PLC端口10 */
	TRI_HAL_PORT_CID11_E, /* PLC端口11 */
	TRI_HAL_PORT_CID12_E, /* PLC端口12 */
	TRI_HAL_PORT_CID13_E, /* PLC端口13 */
	TRI_HAL_PORT_CID14_E, /* PLC端口14 */
	TRI_HAL_PORT_CID15_E, /* PLC端口15 */
	TRI_HAL_PORT_NUM_E, /* 32-63是qos给上行16个用户和下行16个用户分配的 */
};

union tri_hal_port_u {
	struct {
		tri_uint32 eth0 : 1; /* bit0,ETH0 */
		tri_uint32 eth1 : 1; /* bit1,ETH1 */
		tri_uint32 eth2 : 1; /* bit2,ETH2 */
		tri_uint32 eth3 : 1; /* bit3,ETH3 */
		tri_uint32 eth4 : 1; /* bit4,ETH4 */
		tri_uint32 eth5 : 1; /* bit5,ETH5 */
		tri_uint32 res1 : 2; /* reserved */
		tri_uint32 rgmii : 1; /* bit8, RGMII */
		tri_uint32 wan : 1; /* bit9,WAN */
		tri_uint32 plc : 1; /* bit10, plc */
		tri_uint32 prbs0 : 1; /* bit11,PRBS0 */
		tri_uint32 cpu0 : 1; /* bit12,CPU0 */
		tri_uint32 cpu1 : 1; /* bit13,CPU1 */
		tri_uint32 cpu2 : 1; /* bit13,CPU1 */
		tri_uint32 cpu3 : 1; /* bit13,CPU1 */
		tri_uint32 res3 : 16; /* reserved */
	} bits;

	tri_uint32 value;
};

enum tri_hal_ip_version_e {
	TRI_HAL_IP_V4_E = 0, /* IP_V4版本 */
	TRI_HAL_IP_V6_E, /* IP_V6版本 */
};

enum tri_hal_forward_act_e {
	TRI_HAL_FWD_NORMAL_E = 0, /* 正常转发 ，IFC/OFC 共用 */
	TRI_HAL_FWD_DROP_E, /* 丢弃 ，IFC/OFC 共用 */
	TRI_HAL_FWD_CPU_E, /* 交CPU   ，IFC/OFC 共用 */
	TRI_HAL_FWD_CPU_FWD_E, /* 拷贝到CPU同时转发，IFC可用 */
	TRI_HAL_FWD_TOPOINT_E, /* 转发到指定端口，IFC/OFC 共用 */
	TRI_HAL_FWD_THRU_E, /* 透传，IFC可用 */
	TRI_HAL_FWD_NAPT_E = 7, /* NAPT   ，IFC可用 */
	TRI_HAL_FWD_BC_E = 9, /* 广播 ，IFC可用 */
	TRI_HAL_FWD_ROUTE_E = 10, /* L3路由转发，IFC可用 */
	TRI_HAL_FWD_POLICY_ROUTE_E = 11, /* 策略路由，IFC可用 */
};

/* 修改行为 */
enum tri_hal_act_e {
	TRI_HAL_NO_ACTION = 0, /* 无动作 */
	TRI_HAL_ADD1,          /* 添加一层 */
	TRI_HAL_DEL1,          /* 删除一层 */
	TRI_HAL_ADD2,          /* 添加二层 */
	TRI_HAL_DEL2,          /* 删除二层 */
	TRI_HAL_EDIT,          /* 编辑动作 */
};

struct tri_hal_mac_s {
	tri_uchar8 data[TRI_HAL_MAC_BYTE_NUM]; /* mac地址 */
	tri_uchar8 reserve[2];
};

struct tri_hal_ip_s {
	enum tri_hal_ip_version_e version; /* IP类型 */
	union {
		tri_uchar8 ipv4[TRI_HAL_IPV4_ADDR_LEN]; /* IPV4 地址 */
		tri_uchar8 ipv6[TRI_HAL_IPV6_ADDR_LEN]; /* IPV6 地址 */
	} data;
};

struct tri_hal_pkt_len_s {
	tri_ushort16 ipver; /* IP类型 */
	tri_ushort16 len;
};

/* 端口号 */
struct tri_hal_port_s {
	enum tri_hal_port_e port; /* HAL层业务端口 */
	tri_uint32 phy_port; /* 该业务端口对应芯片物理端口 */
};

struct tri_hal_vlan_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 vlan; /* 端口vlan，或者vlan bc */
	tri_uint32 ifc_id; /* 内部使用 */
};

enum tri_hal_ifc_label_e {
	TRI_HAL_STAT_LABEL_E = 0, /* 统计相关表项 */
	TRI_HAL_QOS_LABEL_E = 1, /* Qos相关表项 */
	TRI_HAL_TAG_LABEL_E = 2, /* ifc只作tag动作的流 */
	TRI_HAL_QOS_ARP_DOS_LABEL_E = 3, /* ARP限速用ifc table id固定为3 */
	TRI_HAL_PRI_LABEL_E = 4, /* pri切换优先级 */
	TRI_HAL_FWD_LABEL_E = 5, /* ifc直接控制转发关系label */

};

enum tri_hal_ifc_label_state_e {
	TRI_HAL_TAG_ACT_LABEL_E = 0, /* 用于TAG动作和IFC ID 输出到后续环节 */
	TRI_HAL_QOS_CAR_LABEL_E = 1, /* 流量控制，做CAR */
	TRI_HAL_MARK_PRI_LABEL_E = 2, /* 上下行入队优先级标记 */
	TRI_HAL_STAT_CNT_LABEL_E = 3, /* 统计 */
	TRI_HAL_DEFAULT_FWD_LABEL_E = 4, /* 默认label，转发过滤也放在这里 */
	TRI_HAL_RSV_0_LABEL_E = 7, /* 保留0 */
	TRI_HAL_UPMAP_xxx1_LABEL_E = 5, /* 兼龋鯝RL，UPMAP 和 N:1使用 */
	TRI_HAL_RSV_1_LABEL_E = 6, /* 保留1 */

};

typedef tri_uint32(*tri_kernel_hal_hook)(tri_void *arg, tri_uint32 type);

/* hal层回调函数注册接口 */
tri_uint32 tri_kernel_hal_hook_register(tri_kernel_hal_hook hook);

/* hal层回调函数注销接口 */
tri_uint32 tri_kernel_hal_hook_unregister(tri_void);

/* phy寄存器类型 */
enum tri_hal_phy_reg_type_e {
	TRI_PHY_REG_BASE_E = 0, /* 基本寄存器 */
	TRI_PHY_REG_EXTEND_E /* 扩展寄存器 */
};

/* 端口link状态回调函数原型 */
typedef unsigned int (*tri_kernel_hal_uni_eth_linkstatus_hook)(
	tri_char8 *ethname,
	enum tri_hal_port_e port,
	enum tri_hal_uni_link_sta_e linkstatus);

struct tri_hal_port_transform_record_s {
	enum tri_hal_port_e transform_port; /* 转换后端口 */
};

struct tri_hal_port_transform_s {
	enum tri_hal_port_e
	tran_port[TRI_HAL_PORT_CPU3_E + 1]; /* 转换后端口 */
};

struct tri_hal_port_tpid_s {
	tri_ushort16 ctpid[TRI_HAL_TPID_NUM]; /* 内层TPID */
	tri_ushort16 stpid[TRI_HAL_TPID_NUM]; /* 外层TPID */
};

struct tri_hal_tag_s {
	tri_uint32 tpid; /* TPID */
	tri_uint32 priority; /* 优先级 */
	tri_uint32 vlan; /* vlan */
	enum tri_hal_endian_e cfi; /* cfi */
};

struct tri_hal_port_tag_act_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_uni_inout_e dir; /* 方向：入口、出口 */
	enum tri_hal_uni_tag_type_e tagtype; /* 类型：untag、pritag、tag */
	enum tri_hal_uni_tag_act_e tagact; /* 该类型报文的动作 */
};

/* 待删除 */
struct tri_hal_port_filter_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 igr_vlanfilter_en; /* 入口vlan过滤使能 */
	tri_uint32 egr_vlanfilter_en; /* 出口vlan过滤使能 */
};

struct tri_hal_port_tag_s {
	enum tri_hal_port_e port; /* 端口 */
	struct tri_hal_tag_s default_tag; /* 该端口缺省default tag */
};

struct tri_hal_port_hybrid_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 vid; /* 端口vlan */
	tri_uint32 remove_en; /* 出口时是否剥除vlan */
};

struct tri_hal_port_eth_workmode_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 enable; /* 端口使能 */
	enum tri_hal_port_eth_work_mode_e work_mode; /* 工作模式 */
};

struct tri_hal_port_eth_status_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_port_eth_work_mode_e work_mode; /* 工作模式 */
	enum tri_hal_uni_link_sta_e link; /* 上线指示，只读 */
	enum tri_hal_uni_type_e type; /* GE or FE，只读 */
};

struct tri_hal_port_eth_loop_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_port_eth_loop_mode_e loop_mode; /* 环回模式 */
};

/* 以太端口生成树状态 */
enum tri_hal_port_eth_stp_status_e {
	TRI_HAL_PORT_ETH_STP_FORWARD_E = 0, /* 转发 */
	TRI_HAL_PORT_ETH_STP_LEARN_E, /* 学习 */
	TRI_HAL_PORT_ETH_STP_LISTEN_E, /* 侦听 */
	TRI_HAL_PORT_ETH_STP_BLOCK_E, /* 阻塞 */
	TRI_HAL_PORT_ETH_STP_CLOSE_E, /* 关闭,丢弃 */
};

struct tri_hal_port_eth_stpstate_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_port_eth_stp_status_e state; /* stp 状态 */
};

struct tri_hal_port_mirror_s {
	union tri_hal_port_u igr_mask; /* 入口镜像使能，支持多选 */
	tri_uint32 igr_cid; /* 入口镜像源端口为plc时的cid */
	union tri_hal_port_u egr_mask; /* 出口镜像使能，支持多选 */
	tri_uint32 egr_cid; /* 出口镜像源端口为plc时的cid */

	/* 以下为镜像出口参数配置 */
	enum tri_hal_port_e
	dst_port; /* 目标端口，比如FE0 ，入端口和出端口的报文都镜像到目标端 */
	tri_uint32 dcid; /* 目标端口为plc时的cid */
	tri_uint32 dst_pq; /* 端口出队优先级 */
};

struct tri_hal_port_eth_flowctl_bm_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 enable; /* 端口流水线使能 */
	tri_uint32 high_thr; /* 端口流水线高位值 */
	tri_uint32 low_thr; /* 端口流水线低位值 */
};

struct tri_hal_port_eth_flowctl_car_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 enable; /* 入端口car 使能 */
	tri_uint32 cir; /* car参数，单位kbps */
};

struct tri_hal_port_mtu_s {
	tri_uint32 mtu; /* 端口mtu,默认2000 Bytes */
};

struct tri_hal_port_eth_pause_s {
	enum tri_hal_port_e port; /* 端口 */
	tri_uint32 pause_en; /* 端口pause 使能 */
};

struct tri_hal_port_8021x_auth_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_bool_e auth_en; /* 端口授权状态 0-关闭，1-开启 */
};

struct tri_hal_port_pq_pri_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_port_pq_pri_e sel; /* 端口报文的入队优先级选择 */
};

struct tri_hal_port_nni_s {
	union tri_hal_port_u nni; /* 上行端口，最多支持双上行 */
	tri_uint32 wan_en; /* 映射wan口队列使能 */
	enum tri_hal_port_e wan; /* 映射wan口队列的端口 */
};

/*
 * 以太端口PHY支持的自动协商能力集
 * 修改此能力集会触发重新自协商，
 * 如果在link上状态配置会出现一次up/down
 * 建议在phy link up前配置好
 */
struct tri_hal_eth_capability_s {
	enum tri_hal_port_e port; /* 端口 */
	enum tri_hal_bool_e half_10m_en; /* 10M半双工 */
	enum tri_hal_bool_e half_100m_en; /* 100M半双工 */
	enum tri_hal_bool_e half_1000m_en; /* 1000M半双工 */
	enum tri_hal_bool_e full_10m_en; /* 10M全双工 */
	enum tri_hal_bool_e full_100m_en; /* 100M全双工 */
	enum tri_hal_bool_e full_1000m_en; /* 1000M全双工 */
	enum tri_hal_bool_e full_2p5g_en; /* 2.5G全双工 */
	enum tri_hal_bool_e full_5g_en; /* 5G全双工 */
	enum tri_hal_bool_e full_10g_en; /* 10G全双工 */
};

struct tri_hal_port_smac_s {
	enum tri_hal_port_e port;
	tri_uchar8 mac[TRI_HAL_MAC_BYTE_NUM];
};

struct tri_hal_port_map_s {
	tri_uint32 port_id;
	tri_uchar8 port_name[TRI_HAL_PORT_NAME_LEN]; /* 端口名 */
	tri_uint32 phy_id; /* 物理phy id */
	enum tri_hal_phy_type_e phy_type; /* phy型号类型 */
	tri_uint32 mac_id; /* phy对应的MAC索引 */
};

/* phy寄存器操作 */
struct tri_hal_phy_reg_info_s {
	enum tri_hal_phy_reg_act_e act; /* phy寄存器读写动作 */
	enum tri_hal_phy_reg_type_e type; /* phy寄存器类型选择 */
	tri_uint32 port; /* 需要读取的端口 */
	tri_ushort16 addr; /* 需要读/写的phy地址 */
	tri_ushort16 data; /* 需要读/写的内容 */
};

/* phy信息收集 */
struct tri_hal_port_phy_info_s {
	tri_uint32 port; /* 以太端口索引，从0开始 */
	tri_uint32 num; /* 需要收集的phy 寄存器数量 */
};

/* 获取HAL端口顺序转换配置 */
tri_uint32 tri_kernel_hal_eth_port_transform_get(
	struct tri_hal_port_transform_s *arg);

/* 配置HAL端口顺序转换 */
tri_uint32 tri_kernel_hal_eth_port_transform_set(
	struct tri_hal_port_transform_s *arg);

/* 配置tpid属性 */
tri_uint32 tri_kernel_hal_port_tpid_set(struct tri_hal_port_tpid_s *tpid);

/* 获取tpid属性 */
tri_uint32 tri_kernel_hal_port_tpid_get(struct tri_hal_port_tpid_s *tpid);

/* 配置端口default tag */
tri_uint32 tri_kernel_hal_port_deftag_set(struct tri_hal_port_tag_s *arg);

/* 获取端口default tag */
tri_uint32 tri_kernel_hal_port_deftag_get(struct tri_hal_port_tag_s *arg);

/* 配置端口tag报文动作行为 */
tri_uint32 tri_kernel_hal_port_tag_act_set(struct tri_hal_port_tag_act_s *arg);

/* 获取端口tag报文动作行为 */
tri_uint32 tri_kernel_hal_port_tag_act_get(struct tri_hal_port_tag_act_s *arg);

/* 配置端口hybrid模式行为 */
tri_uint32 tri_kernel_hal_port_hybrid_set(struct tri_hal_port_hybrid_s *arg);

/* 获取端口hybrid模式行为 */
tri_uint32 tri_kernel_hal_port_hybrid_get(struct tri_hal_port_hybrid_s *arg);

/* 配置端口工作模式、并使能端口 */
tri_uint32 tri_kernel_hal_port_eth_workmode_set(
	struct tri_hal_port_eth_workmode_s *arg);

/* 获取端口工作模式、并使能端口 */
tri_uint32 tri_kernel_hal_port_eth_workmode_get(
	struct tri_hal_port_eth_workmode_s *arg);

/* 获取端口工作模式、是否上线、GE模式等状态 */
tri_uint32 tri_kernel_hal_port_eth_status_get(
	struct tri_hal_port_eth_status_s *arg);

/* 配置端口环回模式 */
tri_uint32 tri_kernel_hal_port_eth_loop_set(struct tri_hal_port_eth_loop_s *arg);

/* 获取端口环回模式 */
tri_uint32 tri_kernel_hal_port_eth_loop_get(struct tri_hal_port_eth_loop_s *arg);

/* 配置端口生成树状态 */
tri_uint32 tri_kernel_hal_port_eth_stpstate_set(
	struct tri_hal_port_eth_stpstate_s *arg);

/* 获取端口生成树状态 */
tri_uint32 tri_kernel_hal_port_eth_stpstate_get(
	struct tri_hal_port_eth_stpstate_s *arg);

/* 端口使能 */
tri_uint32 tri_kernel_hal_port_add(enum tri_hal_port_e port);

tri_uint32 tri_kernel_hal_port_del(enum tri_hal_port_e port);

tri_uint32 tri_kernel_hal_port_pause_set(struct tri_hal_port_eth_pause_s *arg);

tri_uint32 tri_kernel_hal_port_pause_get(struct tri_hal_port_eth_pause_s *arg);

/* 配置端口loop */
tri_uint32 tri_kernel_hal_port_mirror_set(struct tri_hal_port_mirror_s *arg);

/* 获取端口loop */
tri_uint32 tri_kernel_hal_port_mirror_get(struct tri_hal_port_mirror_s *arg);

/* 配置端口流控水线 */

tri_uint32 tri_kernel_hal_port_eth_pause_set(struct tri_hal_port_eth_pause_s *arg);

/* 获取端口流控水线 */
tri_uint32 tri_kernel_hal_port_eth_pause_get(struct tri_hal_port_eth_pause_s *arg);

/* 配置端口car参数、pause使能 */
tri_uint32 tri_kernel_hal_port_eth_ingress_car_set(
	struct tri_hal_port_eth_flowctl_car_s *arg);

/* 获取端口car参数、pause使能 */
tri_uint32 tri_kernel_hal_port_eth_ingress_car_get(
	struct tri_hal_port_eth_flowctl_car_s *arg);

/* 配置端口mtu使能 */
tri_uint32 tri_kernel_hal_port_mtu_set(struct tri_hal_port_mtu_s *arg);

/* 获取端口mtu使能 */
tri_uint32 tri_kernel_hal_port_mtu_get(struct tri_hal_port_mtu_s *arg);

/* 配置端口802.11 认证使能 */
tri_uint32 tri_kernel_hal_port_8021x_auth_set(
	struct tri_hal_port_8021x_auth_s *auth);

/* 获取端口802.11 认证使能状态 */
tri_uint32 tri_kernel_hal_port_8021x_auth_get(
	struct tri_hal_port_8021x_auth_s *auth);

/* 通过业务端口查询芯片对应的物理端口 */
tri_uint32 tri_kernel_hal_port_remap(struct tri_hal_port_s *arg);

/* 通过芯片对应的物理端口查询对应的业务端口 */
tri_uint32 tri_kernel_hal_port_remap_sdk(struct tri_hal_port_s *arg);

/* 端口link状态上报回调函数注册接口 */
tri_uint32 tri_kernel_hal_uni_eth_linkstatus_register_hook(
	tri_kernel_hal_uni_eth_linkstatus_hook hook);

/* 端口link状态上报回调函数注销接口 */
tri_uint32 tri_kernel_hal_uni_eth_linkstatus_unregister_hook(void);
/* 设置端口自协商能力 */
tri_uint32 tri_kernel_hal_port_capability_set(
	struct tri_hal_eth_capability_s *capability);

/* 获取端口自协商能力 */
tri_uint32 tri_kernel_hal_port_capability_get(
	struct tri_hal_eth_capability_s *capability);

/* 打印所有端口的自协商能力 */
tri_uint32 tri_kernel_hal_port_capability_dump(void);
/* 配置端口的MAC */
tri_uint32 tri_kernel_hal_port_smac_set(struct tri_hal_port_smac_s *mac);

/* 获取端口的MAC */
tri_uint32 tri_kernel_hal_port_smac_get(struct tri_hal_port_smac_s *mac);

/* 配置端口报文的入队优先级 */
tri_uint32 tri_kernel_hal_port_pq_pri_set(struct tri_hal_port_pq_pri_s *pri);

/* 获取端口报文的入队优先级 */
tri_uint32 tri_kernel_hal_port_pq_pri_get(struct tri_hal_port_pq_pri_s *pri);

/* 配置上行口和wan口 */
tri_uint32 tri_kernel_hal_port_nni_set(struct tri_hal_port_nni_s *nni);

/* 获取上行口和wan口 */
tri_uint32 tri_kernel_hal_port_nni_get(struct tri_hal_port_nni_s *nni);

/* 关闭所有PHY电源 */
tri_uint32 tri_kernel_hal_port_eth_phy_alldown(tri_void);

/* 配置端口map */
tri_uint32 tri_kernel_hal_port_map_set(struct tri_hal_port_map_s *map);

/* eth phy debug接口，用于读写内置、外置phy寄存器 */
tri_uint32 tri_kernel_hal_port_eth_phy_debug(
	struct tri_hal_phy_reg_info_s *reg_info);

#endif /* __TRI_HAL_UNI_H__ */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
