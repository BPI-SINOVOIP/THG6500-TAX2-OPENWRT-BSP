/*
 */

#ifndef __TRI_ETH_H__
#define __TRI_ETH_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef __TRACE__
#endif

#ifdef TRI_VERSION_DEBUG
#define tri_eth_printmemdes(dbglevel,src,len,fmt,arg...) \
	tri_memdes(TRI_KSOC_SDK_L2_ETH, dbglevel, src, len, (tri_uchar8 *)fmt, ##arg)
#define tri_eth_systrace(ret, arg1, arg2, arg3, arg4) \
	tri_systrace(TRI_KSOC_SDK_L2_ETH, ret, arg1, arg2, arg3, arg4)
#define tri_eth_debug(level, fmt, arg...) \
	tri_debug(TRI_KSOC_SDK_L2_ETH, level, fmt, ##arg)
#define tri_eth_print(level, fmt, arg...) \
	tri_print(TRI_KSOC_SDK_L2_ETH, level, fmt, ##arg)
#else
#define tri_eth_printmemdes(dbglevel, src, len, fmt, arg...)
#define tri_eth_systrace(ret, arg1, arg2, arg3, arg4)
#define tri_eth_debug(module, level, fmt, arg...)
#define tri_eth_print(module, dbglevel, fmt, arg...)
#endif

#ifdef __MACRO__
#endif

#define TRI_MDIO_BAUD_RATE_1M25        1
#define TRI_MDIO_BAUD_RATE_2P5M        0
#define TRI_MDIO_TIME                  100000000 /* apb freq: 100M */

#define TRI_MDIO_PHY_MAX_NUM           31
#define TRI_MDIO_REG_MAX_NUM           31

#define TRI_MDIO_XGE_SINGLE_WRITE_ADDR 0
#define TRI_MDIO_XGE_SINGLE_WRITE_DATA 1
#define TRI_MDIO_XGE_SINGLE_READ_DATA  2

#define tri_get_reg64(reg)   (*((tri_ulong64 *) & (reg)))

#define TRI_MAC_MTU_MAX                9600
#define TRI_MAC_MTU_MIN                1518
#define TRI_PHY_ETH_NUM                6
#define TRI_PHY_INNER_NUM              5

#define TRI_MAC_MTU                    2000

#ifdef __ENUM__
#endif

/* mdio接口序号 */
enum tri_mdio_idx_e {
	TRI_MDIO_IF0_E = 0, /* mdio 0: inner phy */
	TRI_MDIO_IF1_E,     /* mdio 1: extern phy */
};

/* mdio接口模式 */
enum tri_mdio_mode_e {
	TRI_MDIO_GE_MODE_E = 0,
	TRI_MDIO_10GE_MODE_E = 1,
	TRI_MDIO_MODE_NUM_E,
};

enum tri_mac_id_e {
	TRI_MAC_GE0_E = 0,
	TRI_MAC_GE1_E,
	TRI_MAC_GE2_E,
	TRI_MAC_GE3_E,
	TRI_MAC_GE4_E,
	TRI_MAC_GE5_E,
	TRI_MAC_GE_NUM_E,
};

/* MAC SPEE与寄存器手册完全对应 */
enum tri_mac_speed_e {
	TRI_MAC_SPEED_10M_E = 0, /* 0x0 10M */
	TRI_MAC_SPEED_100M_E,    /* 0x1 100M */
	TRI_MAC_SPEED_1000M_E,   /* 0x2 100M */
	TRI_MAC_SPEED_10000M_E,
};

/* MAC 双工 与寄存器手册完全对应 */
enum tri_mac_duplex_e {
	TRI_MAC_DUPLEX_HALF_E = 0, /* 半双工 */
	TRI_MAC_DUPLEX_FULL_E,     /* 全双工 */
};

/* MAC环回模式 */
enum tri_mac_loop_e {
	TRI_MAC_NO_LOOP_E,
	TRI_MAC_IN_LOOP_E,  /* MAC内环回模式 */
	TRI_MAC_OUT_LOOP_E, /* MAC外环回模式 */
};

/* 端口协商速率枚举定义 */
enum tri_eth_status_e {
	TRI_ETH_STATUS_DOWN_E       = 0,
	TRI_ETH_STATUS_10_HALF_E    = 1,
	TRI_ETH_STATUS_10_FULL_E    = 2,
	TRI_ETH_STATUS_100_HALF_E   = 3,
	TRI_ETH_STATUS_100_FULL_E   = 4,
	TRI_ETH_STATUS_1000_HALF_E  = 5,
	TRI_ETH_STATUS_1000_FULL_E  = 6,
	TRI_ETH_STATUS_2500_HALF_E  = 7,
	TRI_ETH_STATUS_2500_FULL_E  = 8,
	TRI_ETH_STATUS_5000_HALF_E  = 9,
	TRI_ETH_STATUS_5000_FULL_E  = 10,
	TRI_ETH_STATUS_10000_HALF_E = 11,
	TRI_ETH_STATUS_10000_FULL_E = 12,
	TRI_ETH_STATUS_AUTO_E,
	TRI_ETH_STATUS_NUM_E
};

#ifdef __STRUCT__
#endif

struct tri_mac_eee_time_s {
	tri_uint32 eee_wait_time;
	tri_uint32 eee_sleep_time;
	tri_uint32 eee_wakeup_time;
};

struct tri_mac_mtu_s {
	tri_uint32 macidex;
	tri_uint32 mtu;
};

struct tri_mac_cnt_s {
	tri_v_u32 rx_pkt_l;
	tri_v_u32 rx_pkt_h;
	tri_v_u32 rx_uc_pkt_l;
	tri_v_u32 rx_uc_pkt_h;
	tri_v_u32 rx_mc_pkt_l;
	tri_v_u32 rx_mc_pkt_h;
	tri_v_u32 rx_bc_pkt_l;
	tri_v_u32 rx_bc_pkt_h;
	tri_v_u32 rx_pause_pkt_l;
	tri_v_u32 rx_pause_pkt_h;
	tri_v_u32 rx_unk_ctrl_pkt_l;
	tri_v_u32 rx_unk_ctrl_pkt_h;
	tri_v_u32 rx_under_min_pkt_l;
	tri_v_u32 rx_under_min_pkt_h;
	tri_v_u32 rx_minto63_pkt_l;
	tri_v_u32 rx_minto63_pkt_h;
	tri_v_u32 rx_64_pkt_l;
	tri_v_u32 rx_64_pkt_h;
	tri_v_u32 rx_65to127_pkt_l;
	tri_v_u32 rx_65to127_pkt_h;
	tri_v_u32 rx_128to255_pkt_l;
	tri_v_u32 rx_128to255_pkt_h;
	tri_v_u32 rx_256to511_pkt_l;
	tri_v_u32 rx_256to511_pkt_h;
	tri_v_u32 rx_512to1023_pkt_l;
	tri_v_u32 rx_512to1023_pkt_h;
	tri_v_u32 rx_1024to1518_pkt_l;
	tri_v_u32 rx_1024to1518_pkt_h;
	tri_v_u32 rx_1519t2047_pkt_l;
	tri_v_u32 rx_1519t2047_pkt_h;
	tri_v_u32 rx_over_max_pkt_l;
	tri_v_u32 rx_over_max_pkt_h;
	tri_v_u32 rx_undersize_pkt_l;
	tri_v_u32 rx_undersize_pkt_h;
	tri_v_u32 rx_fragement_pkt_l;
	tri_v_u32 rx_fragement_pkt_h;
	tri_v_u32 rx_over_size_pkt_l;
	tri_v_u32 rx_over_size_pkt_h;
	tri_v_u32 rx_jabber_l;
	tri_v_u32 rx_jabber_h;
	tri_v_u32 rx_fcs_err_pkt_l;
	tri_v_u32 rx_fcs_err_pkt_h;
	tri_v_u32 rx_align_error_l;
	tri_v_u32 rx_align_error_h;
	tri_v_u32 rx_fifo_overrun_l;
	tri_v_u32 rx_fifo_overrun_h;
	tri_v_u32 ch_tag_err_l;
	tri_v_u32 ch_tag_err_h;
	tri_v_u32 rx_byte_ok_l;
	tri_v_u32 rx_byte_ok_h;
	tri_v_u32 rx_byte_err_l;
	tri_v_u32 rx_byte_err_h;

	tri_v_u32 tx_pkt_l;
	tri_v_u32 tx_pkt_h;
	tri_v_u32 tx_uc_pkt_l;
	tri_v_u32 tx_uc_pkt_h;
	tri_v_u32 tx_mc_pkt_l;
	tri_v_u32 tx_mc_pkt_h;
	tri_v_u32 tx_bc_pkt_l;
	tri_v_u32 tx_bc_pkt_h;
	tri_v_u32 tx_pause_pkt_l;
	tri_v_u32 tx_pause_pkt_h;
	tri_v_u32 tx_minto63_pkt_l;
	tri_v_u32 tx_minto63_pkt_h;
	tri_v_u32 tx_64_pkt_l;
	tri_v_u32 tx_64_pkt_h;
	tri_v_u32 tx_65to127_pkt_l;
	tri_v_u32 tx_65to127_pkt_h;
	tri_v_u32 tx_128to255_pkt_l;
	tri_v_u32 tx_128to255_pkt_h;
	tri_v_u32 tx_256to511_pkt_l;
	tri_v_u32 tx_256to511_pkt_h;
	tri_v_u32 tx_512to1023_pkt_l;
	tri_v_u32 tx_512to1023_pkt_h;
	tri_v_u32 tx_1024to1518_pkt_l;
	tri_v_u32 tx_1024to1518_pkt_h;
	tri_v_u32 tx_1519to2047_l;
	tri_v_u32 tx_1519to2047_h;
	tri_v_u32 tx_over_max_pkt_l;
	tri_v_u32 tx_over_max_pkt_h;
	tri_v_u32 tx_crc_err_pkt_l;
	tri_v_u32 tx_crc_err_pkt_h;
	tri_v_u32 tx_single_col_l;
	tri_v_u32 tx_single_col_h;
	tri_v_u32 tx_multi_col_l;
	tri_v_u32 tx_multi_col_h;
	tri_v_u32 tx_excess_col_l;
	tri_v_u32 tx_excess_col_h;
	tri_v_u32 tx_late_col_l;
	tri_v_u32 tx_late_col_h;
	tri_v_u32 tx_deferral_trans_l;
	tri_v_u32 tx_deferral_trans_h;
	tri_v_u32 tx_crs_lost_l;
	tri_v_u32 tx_crs_lost_h;
	tri_v_u32 tx_abort_pkt_l;
	tri_v_u32 tx_abort_pkt_h;
	tri_v_u32 tx_fifo_underrun_l;
	tri_v_u32 tx_fifo_underrun_h;
	tri_v_u32 tx_byte_ok_l;
	tri_v_u32 tx_byte_ok_h;
	tri_v_u32 tx_byte_err_l;
	tri_v_u32 tx_byte_err_h;
};

struct tri_mdio_op_cmd_s {
	tri_uint32 phy_id;    /* phy index */
	tri_uint32 reg_addr;  /* phy寄存器地址 */
	tri_ushort16 data;      /* phy寄存器数据 */
	tri_ushort16 resv;
};

struct tri_mdio_op_clause45_cmd_s {
	tri_uint32   phy_id;   /* phy index */
	tri_uint32   reg_addr; /* phy寄存器地址 */
	tri_uint32   mmi_addr; /* mmi寄存器地址 */
	tri_ushort16 data;     /* phy寄存器数据 */
	tri_ushort16 resv;
};

struct tri_mac_chan_en_cmd_s {
	tri_uint32 macid;
	tri_uint32 enable;
};

struct tri_mac_mtu_cmd_s {
	tri_uint32 macid;
	tri_uint32 mtu;
};

struct tri_mac_smac_cmd_s {
	tri_uint32 macid;
	tri_uchar8 smac[TRI_MAC_LEN];
	tri_ushort16 resv;
};

struct tri_mac_loopback_cmd_s {
	tri_uint32 macid;
	tri_uint32 loop_mode;
};

struct tri_mac_speed_duplex_cmd_s {
	tri_uint32 macid;
	tri_uint32 speed;
	tri_uint32 duplex;
};

struct tri_mac_eee_time_cmd_s {
	tri_uint32 macid;
	struct tri_mac_eee_time_s times;
};

struct tri_mac_eee_en_cmd_s {
	tri_uint32 macid;
	tri_uint32 enable;
};

struct tri_mac_status_cmd_s {
	tri_uint32 macid;
	tri_uint32 is_xge;
	tri_uint32 status;
};

struct tri_mac_cnt_cmd_s {
	tri_uint32 macid;
	tri_ulong64 pkts;
};

#ifdef __DECLARE__
#endif

/* mac */
tri_void tri_mac_clk_en(tri_uint32 macid);
tri_void tri_mac_clk_dis(tri_uint32 macid);
tri_void tri_mac_reset_n(tri_uint32 macid);
tri_void tri_mac_reset_en(tri_uint32 macid);
tri_void tri_mac_reset_dis(tri_uint32 macid);
tri_void tri_mac_enable(tri_uint32 macid);
tri_void tri_mac_disable(tri_uint32 macid);
tri_uint32 tri_mac_get_chan_en(tri_uint32 macid);
tri_uint32 tri_mac_set_mtu(tri_uint32 macid, tri_uint32 mtu);
tri_uint32 tri_mac_get_mtu(tri_uint32 macid, tri_uint32 *mtu);
tri_uint32 tri_mac_set_smac(tri_uint32 macid, tri_uchar8 *smac);
tri_uint32 tri_mac_get_smac(tri_uint32 macid, tri_uchar8 *smac);
tri_uint32 tri_mac_set_loopback(tri_uint32 macid, tri_uint32 mode);
tri_uint32 tri_mac_get_loopback(tri_uint32 macid, tri_uint32 *mode);
tri_uint32 tri_mac_set_speed_duplex(tri_uint32 macid,
				  tri_uint32 speed, tri_uint32 duplex);
tri_uint32 tri_mac_get_speed_duplex(tri_uint32 macid,
				  tri_uint32 *speed, tri_uint32 *duplex);
tri_uint32 tri_mac_set_eee_times(tri_uint32 macid,
			       struct tri_mac_eee_time_s *eee_time);
tri_uint32 tri_mac_get_eee_times(tri_uint32 macid,
			       struct tri_mac_eee_time_s *eee_time);
tri_uint32 tri_mac_set_eee_enable(tri_uint32 macid, tri_uint32 enable);
tri_uint32 tri_mac_get_eee_enable(tri_uint32 macid, tri_uint32 *enable);
tri_void tri_mac_proc_eee_enable(tri_uint32 macid, tri_uint32 status);
tri_uint32 tri_mac_get_txpkt(tri_uint32 macid, tri_ulong64 *data);
tri_uint32 tri_mac_get_rxpkt(tri_uint32 macid, tri_ulong64 *count);
tri_uint32 tri_mac_get_txlate(tri_uint32 macid, tri_ulong64 *late_col);
tri_uint32 tri_mac_get_fcs_err_pkt(tri_uint32 macid, tri_ulong64 *count);
tri_uint32 tri_mac_set_status(tri_uint32 macid,
			    tri_uint32 is_xge, tri_uint32 status);
tri_uint32 tri_mac_get_status(tri_uint32 macid, tri_uint32 *status);
tri_uint32 tri_mac_cfg_rgmii_chip(tri_uint32 macid, tri_uint32 status);
tri_int32 tri_mac_init(tri_void);
tri_void tri_mac_exit(tri_void);

/* mdio */
tri_uint32 tri_mdio_write_inner_clause45(tri_uint32 phy_addr, tri_uint32 reg_addr,
	tri_uint32 mmid, tri_ushort16 data);
tri_uint32 tri_mdio_read_inner_clause45(tri_uint32 phy_addr, tri_uint32 reg_addr,
	tri_uint32 mmid, tri_ushort16 *data);
tri_uint32 tri_mdio_read_inner_exreg(tri_uint32 phy_addr, tri_uint32 reg_addr,
	tri_ushort16 *data);
tri_uint32 tri_mdio_write_inner_exreg(tri_uint32 phy_addr, tri_uint32 reg_addr,
	tri_ushort16 data);
tri_uint32 tri_mdio_write_inner(tri_uint32 phy_addr,
			      tri_uint32 reg_addr, tri_ushort16 data);
tri_uint32 tri_mdio_read_inner(tri_uint32 phy_addr,
			     tri_uint32 reg_addr, tri_ushort16 *data);
tri_uint32 tri_mdio_write_extern(tri_uint32 phy_addr,
			       tri_uint32 reg_addr, tri_ushort16 data);
tri_uint32 tri_mdio_read_extern(tri_uint32 phy_addr,
			      tri_uint32 reg_addr, tri_ushort16 *data);
tri_uint32 tri_mdio_write_extern_clause45(tri_uint32 phy_addr,
					tri_uint32 reg_addr,
					tri_uint32 mmid,
					tri_ushort16 data);
tri_uint32 tri_mdio_read_extern_clause45(tri_uint32 phy_addr,
				       tri_uint32 reg_addr,
				       tri_uint32 mmid,
				       tri_ushort16 *data);
tri_uint32 tri_mdio_write_extern_pagereg(tri_uint32 phyid,
				       tri_ushort16 reg_addr,
				       tri_ushort16 data,
				       tri_ushort16 pagereg_addr,
				       tri_ushort16 pagereg_data,
				       tri_ushort16 pagereg_default);
tri_uint32 tri_mdio_read_extern_pagereg(tri_uint32 phyid,
				      tri_ushort16 reg_addr,
				      tri_ushort16 *data,
				      tri_ushort16 pagereg_addr,
				      tri_ushort16 pagereg_data,
				      tri_ushort16 pagereg_default);

tri_int32 tri_mdio_init(tri_void);
tri_void tri_mdio_exit(tri_void);

/* rgmii */
tri_int32 tri_rgmii_init(tri_void);
tri_void tri_rgmii_exit(tri_void);
tri_uint32 tri_rgmii_config(tri_uint32 macid, tri_uint32 status);

/* XGE */
tri_uint32 tri_xge_mac_cfg(tri_uint32 status);

/* phy */
tri_void tri_phy_ext_tri_init(tri_void);
tri_void tri_phy_inner_tri_init(tri_void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_ETH_H__ */
