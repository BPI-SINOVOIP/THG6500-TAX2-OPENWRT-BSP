/*
 */

#ifndef __TRI_PHY_TRI_H__
#define __TRI_PHY_TRI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef __MACRO__
#endif

#define TRI_PHY_ED_REG              0xb
#define TRI_PHY_ED_STATUS_REG       0xc
#define TRI_PHY_PW_REG              0x1095
#define TRI_PHY_EEE_REG             0x10c2
#define TRI_PHY_ED_ENABLE           0x100
#define TRI_PHY_ED_DISABLE          0x0
#define TRI_PHY_PW_DISABLE          0x1
#define TRI_PHY_PW_ENABLE           0x0
#define TRI_PHY_EYE_REG             0x4FFD
#define TRI_PHY_CTRL_REG            0x0
#define TRI_PHY_IDENTIFIER_L_REG    0x2
#define TRI_PHY_IDENTIFIER_H_REG    0x3
#define TRI_PHY_ANAR_REG            0x4
#define TRI_PHY_1KTCR_REG           0x9
#define TRI_PHY_EXTERN_SPEC_CTL_REG 0x10
#define TRI_PHY_AN_LINK_STATUS_REG  0x11
#define TRI_PHY_AUX_CTL_REG         0x12
#define TRI_PHY_LOOP_CTRL_REG       0x13
#define TRI_PHY_ESD_MONITOR         0x3180
#define TRI_PHY_ESD_MONITOR_ENABLE  0x1
#define TRI_PHY_LED_BASE_GPIO_T     85
#define TRI_PHY_GENIUS_EXPMD_REG    0x1d
#define TRI_PHY_GENIUS_EXPMA_REG    0x1e
#define TRI_PHY_TDR_OP_REG          0x17
#define TRI_PHY_TDR_CH0_STA_REG     0x1A6
#define TRI_PHY_TDR_CH0_LEN_REG     0x1AE

#define TRI_PHY_TDR_OP_CMD          0x302
#define TRI_PHY_TDR_CHANNEL 4

#ifdef CONFIG_MACH_TR6560
#define TRI_PHY_INNER_NUM           5
#elif defined(CONFIG_ARCH_YYXXXXB)
#define TRI_PHY_INNER_NUM           4
#else
#define TRI_PHY_INNER_NUM           3
#endif /* CONFIG_MACH_TR6560 */

#define tri_phy_bit_set(data, bit)  ((data) |= (1 << (bit)))
#define tri_phy_bit_clr(data, bit)  ((data) &= (~(1 << (bit))))
#define tri_phy_bit_get(data, bit)  ((0 == ((data) & (1 << (bit)))) ? 0 : 1)

#define TRI_PHY_PATCH_SIZE (64 * 1024)

#define TRI_PHY_MNG_TIMEOUT_SHORT (tri_jiffies + TRI_HZ / 10)

#ifdef TRI_VERSION_DEBUG
#define tri_phy_printmemdes(dbglevel, src, len, fmt, arg...) \
	tri_memdes(TRI_SRCMODULE_KDRIVER_PHY, dbglevel, \
			src, len, (tri_uchar8 *)fmt, ##arg)
#define tri_phy_systrace(ret, arg1, arg2, arg3, arg4) \
	tri_systrace(TRI_SRCMODULE_KDRIVER_PHY, ret, arg1, arg2, arg3, arg4)
#define tri_phy_debug(level, fmt, arg...) \
	tri_debug(TRI_SRCMODULE_KDRIVER_PHY, level, fmt, ##arg)
#define tri_phy_print(level, fmt, arg...) \
	tri_print(TRI_SRCMODULE_KDRIVER_PHY, level, fmt, ##arg)
#else
#define tri_phy_printmemdes(dbglevel, src, len, fmt, arg...)
#define tri_phy_systrace(ret, arg1, arg2, arg3, arg4)
#define tri_phy_debug(module, level, fmt, arg...)
#define tri_phy_print(level, fmt, arg...)
#endif

#ifdef __ENUM__
#endif

enum tri_phy_nego_e {
	TRI_PHY_NEGO_AUTO_E = 0,  /* 自协商 */
	TRI_PHY_NEGO_NO_AUTO_E    /* 强制 */
};

/* brief phy 速率模式枚举 */
enum tri_phy_speed_e {
	TRI_PHY_SPEED_10M_E = 0,
	TRI_PHY_SPEED_100M_E,
	TRI_PHY_SPEED_1000M_E,
	TRI_PHY_SPEED_2500M_E,
	TRI_PHY_SPEED_5000M_E,
	TRI_PHY_SPEED_10000M_E
};

/* brief phy 双工模式枚举 */
enum tri_phy_duplex_e {
	TRI_PHY_DUPLEX_HALF_E = 0,
	TRI_PHY_DUPLEX_FULL_E
};

enum tri_phy_link_state_e {
	TRI_PHY_PORT_LINK_DOWN_E = 0,
	TRI_PHY_PORT_LINK_UP_E,
	TRI_PHY_PORT_LINK_STATE_BUTT
};

enum tri_phy_ms_mode_e {
	TRI_PHY_SLAVER_E = 0,  /* 强制SLAVER */
	TRI_PHY_MASTER_E,      /* 强制MASTER */
	TRI_PHY_AUTO_SLAVER_E, /* auto_slave */
	TRI_PHY_AUTO_MASTER_E, /* auto_master */
	TRI_PHY_RESERVE_MS_CFG_E, /* 芯片默认配置 */
};

/* PHY环回模式 */
enum tri_phy_loop_e {
	TRI_PHY_NO_LOOP_E,
	TRI_PHY_IN_LOOP_E,    /* PHY内环回模式 */
	TRI_PHY_OUT_LOOP_E,   /* PHY外环回模式 */
};

/* ETH端口LED灯闪烁控制模式 */
enum tri_phy_led_workmode_e {
	TRI_PHY_LED_AUTO_E = 0,  /* LED灯自动 */
	TRI_PHY_LED_ON_E,        /* LED灯常亮 */
	TRI_PHY_LED_OFF_E,       /* LED灯常灭 */
	TRI_PHY_LED_BLINK_E,     /* LED灯以一定频率闪烁 */
};

/* ETH端口LED灯双灯/单灯模式 */
enum tri_phy_led_dual_mode_e {
	TRI_PHY_LED_SINGLE_MODE = 0, /* 单灯模式 */
	TRI_PHY_LED_DUAL_MODE,       /* 双灯模式 */
};

/* ETH端口LED灯极性控制模式 */
enum tri_phy_led_polarity_e {
	TRI_PHY_LED_POLARITY_POSITIVE = 0, /* 正极性 ON:拉低 OFF:拉高 */
	TRI_PHY_LED_POLARITY_NEGATIVE,     /* 负极性 ON:拉高 OFF:拉低 */
};

/* ETH端口LED灯单速率/多速率控制模式，只在双灯模式下有效 */
enum tri_phy_led_speed_e {
	TRI_PHY_LED_MULTI_SPEED = 0, /* 单速率模式 */
	TRI_PHY_LED_SINGLE_SPEED,    /* 多速率模式 */
};

/* PHY眼图测试模式 */
enum tri_phy_eye_testmode_e {
	TRI_PHY_EYE_1000M_MODE1_E = 0,    /* 1000M眼图模式1 */
	TRI_PHY_EYE_1000M_MODE2_E,        /* 1000M眼图模式2 */
	TRI_PHY_EYE_1000M_MODE3_E,        /* 1000M眼图模式3 */
	TRI_PHY_EYE_1000M_MODE4_E,        /* 1000M眼图模式4 */

	TRI_PHY_EYE_100M_CH_A_E = 4,      /* 100M眼图模式 通道A */
	TRI_PHY_EYE_100M_CH_B_E = 5,      /* 100M眼图模式 通道B */

	/* 10M眼图模式 通道A, 适合测试LINK_PULSE */
	TRI_PHY_EYE_10M_LP_CH_A_E = 6,

	/* 10M眼图模式 通道B, 适合测试LINK_PULSE */
	TRI_PHY_EYE_10M_LP_CH_B_E = 7,

	/*
	 * 10M眼图模式 通道A, 适合测试MAU；
	 * TP_IDL；Jitter with cable；Jitter without cable ，
	 * Differential Voltage；CM Voltage；Return Loss
	 */
	TRI_PHY_EYE_10M_CH_A_E = 8,

	/*
	 * 10M眼图模式 通道B, 适合测试MAU；
	 * TP_IDL；Jitter with cable；Jitter without cable ，
	 * Differential Voltage；CM Voltage；Return Loss
	 */
	TRI_PHY_EYE_10M_CH_B_E = 9,

	/* 10M眼图模式 HARMONIC 谐波测试模式 */
	TRI_PHY_EYE_10M_HARMONIC_E = 10,
};

enum tri_phy_tdr_status_e {
    TDR_OPEN_E = 1,
    TDR_SHORT_E = 2,
    TDR_50_OHM = 4,
    TDR_MAX
};

struct tri_phy_tdr_info_s {
    tri_uint32 phyid;
    tri_ushort16 sta[TRI_PHY_TDR_CHANNEL];
    tri_uint32 cable_len[TRI_PHY_TDR_CHANNEL];
};

#ifdef __STRUCT__
#endif

/* phy patch命令行结构 */
struct tri_phy_patch_cmd_s {
	tri_uint32 phyid;
	tri_char8  filename[64];
};

struct tri_phy_ext_xgphy_init_cmd_s {
	tri_uint32 phyid;
	tri_uint32 phy_type;    /* phy 型号类型 */
	tri_char8  filename[64];
};

struct tri_phy_ext_init_cmd_s {
	tri_uint32 phyid;
	tri_uint32 phy_type;    /* phy 型号类型 */
};

struct tri_phy_enable_cmd_s {
	tri_uint32 phy_id;      /* phy index */
	tri_uint32 phy_type;    /* phy 型号类型 */
	tri_uint32 enable;      /* phy寄存器数据 */
};


/* ETH端口LED灯闪烁控制 */
struct tri_phy_led_attr_s {
	tri_uint32 enable;
	enum tri_phy_led_workmode_e work_mode;  /* tri_phy_led_workmode_e */
	enum tri_phy_led_dual_mode_e dual_mode;
	enum tri_phy_led_polarity_e polarity;
	enum tri_phy_led_speed_e speed;
	/* 只在TRI_DP_ETH_LED_BLINK_E模式下有效，单位为50ms */
	tri_uint32 freq;
};

struct tri_phy_auto_neg_cap_s {
	tri_uint32 half_10m_en;      /* 10M半双工 */
	tri_uint32 half_100m_en;     /* 100M半双工 */
	tri_uint32 half_1000m_en;    /* 1000M半双工 */
	tri_uint32 full_10m_en;      /* 10M全双工 */
	tri_uint32 full_100m_en;     /* 100M全双工 */
	tri_uint32 full_1000m_en;    /* 1000M全双工 */
	tri_uint32 full_2p5g_en;     /* 2.5G全双工 */
	tri_uint32 full_5g_en;       /* 5G全双工 */
	tri_uint32 full_10g_en;      /* 10G全双工 */
};

struct tri_port_led_s {
	tri_v_u32 *io_sel_d4;
	tri_v_u32 *gpio_sel_d4;
};

struct tri_phy_op_reg_cmd_s {
	tri_uint32 phy_id;      /* phy index */
	tri_ushort16 reg_addr;  /* phy寄存器地址 */
	tri_ushort16 data;        /* phy寄存器数据 */
};

struct tri_phy_reg_s {
	tri_ushort16 addr;   /* phy寄存器地址 */
	tri_ushort16 data;   /* phy寄存器内容 */
};

/* phy信息收集 */
struct tri_phy_read_info_s {
	tri_uint32 phyid;    /* phyid */
	tri_uint32 phy_type;
	tri_uint32 num;      /* 需要收集的phy 寄存器数量 */
	struct tri_phy_reg_s *buf;      /* 存放收集信息的空间 */
};

struct tri_phy_ms_mode_s {
	tri_uint32 phyid;     /* phyid */
	tri_uint32 ms_mode;   /* phy主从模式 */
};

struct tri_phy_ge_debug_s {
	tri_uint32   phyid;
	tri_uint32   act;        /* 读写动作 */
	tri_uint32   phy_type;   /* phy类型 */
	tri_uint32   reg_type;   /* 寄存器类型: base/ extreg */
	tri_ushort16 addr;       /* 需要读/写的phy地址 */
	tri_ushort16 data;       /* 需要读/写的内容    */
};

struct tri_phy_xge_debug_s {
	tri_uint32   phyid;
	tri_uint32   act;    /* 读写动作 */
	tri_uint32   dev;    /* 器件ID */
	tri_ushort16 addr;   /* 需要读/写的phy地址 */
	tri_ushort16 data;   /* 需要读/写的内容    */
};

struct tri_phy_eee_cap_s {
	tri_uint32 eee_100base_tx;
	tri_uint32 eee_1000base_tx;
};

struct tri_phy_eee_status_s {
	tri_uint32 eee_lp_idle_tx;
	tri_uint32 eee_lp_idle_rx;
};

struct tri_phy_hook_s {
	/* phy端口使能或不使能 */
	tri_uint32(*tri_phy_set_power)(tri_uint32 phyid, tri_uint32 enable);

	/* 设置phy流控能力 */
	tri_uint32(*tri_phy_set_pause)(tri_uint32 phyid, tri_uint32 enable);

	/* 获取phy流控能力 */
	tri_uint32(*tri_phy_get_pause)(tri_uint32 phyid, tri_uint32 *enable);

	/* 设置phy工作模式 */
	tri_uint32(*tri_phy_set_workmode)(tri_uint32 phyid, tri_uint32 work_mode);

	/* 查询phy工作模式 */
	tri_uint32(*tri_phy_get_workmode)(tri_uint32 phyid, tri_uint32 *work_mode);

	/* 设置phy自协商属性 */
	tri_uint32(*tri_phy_set_auto_neg_cap)(tri_uint32 phyid,
		struct tri_phy_auto_neg_cap_s *an_cap);

	/* 查询phy自协商属性 */
	tri_uint32(*tri_phy_get_auto_neg_cap)(tri_uint32 phyid,
		struct tri_phy_auto_neg_cap_s *an_cap);

	/* 设置phy端口环回模式 */
	tri_uint32(*tri_phy_set_loopback)(tri_uint32 phyid, tri_uint32 loopback);

	/* 查询phy端口环回模式 */
	tri_uint32(*tri_phy_get_loopback)(tri_uint32 phyid,
		enum tri_phy_loop_e *loopback);

	/* 设置phy端口ed */
	tri_uint32(*tri_phy_set_ed)(tri_uint32 phyid, tri_uint32 data);

	/* 查询phy端口ed */
	tri_uint32(*tri_phy_get_ed)(tri_uint32 phyid, tri_uint32 *data);

	/* 获取phy端口状态 */
	tri_uint32(*tri_phy_get_status)(tri_uint32 phyid, tri_uint32 *status);

	/* 设置led状态 */
	tri_uint32(*tri_phy_set_led)(tri_uint32 phyid,
	    struct tri_phy_led_attr_s *attr);

	/* 查询led状态 */
	tri_uint32(*tri_phy_get_led)(tri_uint32 phyid,
	    struct tri_phy_led_attr_s *attr);

	/* 设置phy端口主从模式 */
	tri_uint32(*tri_phy_set_ms_mode)(tri_uint32 phyid, tri_uint32 mode);

	/* 查询phy端口主从模式 */
	tri_uint32(*tri_phy_get_ms_mode)(tri_uint32 phyid, tri_uint32 *mode);

	/* 设置phy眼图测试模式 */
	tri_uint32(*tri_phy_set_eye_test_mode)(tri_uint32 phyid, tri_uint32 mode);

	/* 设置phy端口mdi模式 */
	tri_uint32(*tri_phy_set_mdi_mode)(tri_uint32 phyid, tri_uint32 mode);

	/* 查询phy端口mdi模式 */
	tri_uint32(*tri_phy_get_mdi_mode)(tri_uint32 phyid, tri_uint32 *mode);

	/* 以太PHY的接收bist设置 */
	tri_uint32(*tri_phy_set_rx_bist)(tri_uint32 phyid, tri_uint32 en,
		tri_uint32 *status_out);

	/* 以太PHY的接收bist获取 */
	tri_uint32(*tri_phy_get_rx_bist)(tri_uint32 phyid, tri_uint32 *en,
		tri_uint32 *status);

	/* 以太口ED状态获取 */
	tri_uint32(*tri_phy_get_ed_status)(tri_uint32 phyid, tri_uint32 *ed);

	/* 以太PHY收包统计获取 */
	tri_uint32(*tri_phy_get_rx_pkt_cnt)(tri_uint32 phyid, tri_uint32 *cnt,
					  tri_uint32 *err_cnt);

	/* 以太PHY收包统计清除 */
	tri_uint32(*tri_phy_clr_rx_pkt_cnt)(tri_uint32 phyid);

	/* phy寄存器操作，可读写基本寄存器和扩展寄存器 */
	tri_uint32(*tri_phy_op_reg)(struct tri_phy_ge_debug_s *reg);

	/* xge phy寄存器操作，clause45读写 */
	tri_uint32(*tri_phy_op_xge_reg)(struct tri_phy_xge_debug_s *reg);

	/* 一键收集phy寄存器信息 */
	tri_uint32(*tri_phy_get_reg_info)(struct tri_phy_read_info_s *info);

	/* 加载firmware */
	tri_uint32(*tri_phy_patch)(tri_uint32 phyid, const tri_char8 *name);

	/* 查询phy patch版本号，芯片版本号 */
	tri_uint32(*tri_phy_get_patch_version)(tri_uint32 phyid,
		tri_uint32 *version);

	/* 设置EEE能力 */
	tri_uint32(*tri_phy_set_eee_cap_adv)(tri_uint32 phyid,
		struct tri_phy_eee_cap_s *cap);

	/* 查询EEE能力 */
	tri_uint32(*tri_phy_get_eee_cap_adv)(tri_uint32 phyid,
					   struct tri_phy_eee_cap_s *cap);

	/* 查询phy EEE 本端能力 */
	tri_uint32(*tri_phy_get_eee_cap_local)(tri_uint32 phyid,
					     struct tri_phy_eee_cap_s *cap);

	/* 查询phy EEE 对端能力 */
	tri_uint32(*tri_phy_get_eee_cap_remote)(tri_uint32 phyid,
					      struct tri_phy_eee_cap_s *cap);

	/* 配置外置phy的smart eee lpi开关 */
	tri_uint32(*tri_phy_set_eee_lpi_en)(tri_uint32 phyid, tri_uint32 enable);

	/* 查询外置phy的smart eee lpi开关 */
	tri_uint32(*tri_phy_get_eee_lpi_en)(tri_uint32 phyid, tri_uint32 *enable);

	/* 查询phy EEE状态 */
	tri_uint32(*tri_phy_get_eee_status)(tri_uint32 phyid,
					  struct tri_phy_eee_status_s *status);

	/* 外置phy初始化 */
	tri_uint32(*tri_phy_init)(tri_uint32 phyid);
};

struct tri_phy_ops_s {
	/* mdio消息中的phyid由5bit确定，phy芯片固定这5bit，
	 * mdio匹配中了，数据就发到对应的这个phy */
	tri_uint32 phyid;

	struct tri_phy_hook_s hook;
};

#ifdef __DECLARE__
#endif

tri_uint32 tri_phy_set_power(tri_uint32 phyid, tri_uint32 type, tri_uint32 enable);
tri_uint32 tri_phy_set_pause(tri_uint32 phyid, tri_uint32 type, tri_uint32 enable);
tri_uint32 tri_phy_get_pause(tri_uint32 phyid, tri_uint32 type, tri_uint32 *enable);
tri_uint32 tri_phy_set_workmode(tri_uint32 phyid, tri_uint32 type,
			      tri_uint32 work_mode);
tri_uint32 tri_phy_get_workmode(tri_uint32 phyid, tri_uint32 type,
			      tri_uint32 *work_mode);
tri_uint32 tri_phy_set_auto_neg_cap(tri_uint32 phyid, tri_uint32 type,
				  struct tri_phy_auto_neg_cap_s *an_cap);
tri_uint32 tri_phy_get_auto_neg_cap(tri_uint32 phyid, tri_uint32 type,
				  struct tri_phy_auto_neg_cap_s *an_cap);
tri_uint32 tri_phy_set_loopback(tri_uint32 phyid, tri_uint32 type,
			      tri_uint32 loopback);
tri_uint32 tri_phy_get_loopback(tri_uint32 phyid, tri_uint32 type,
			      enum tri_phy_loop_e *pem_loopback);
tri_uint32 tri_phy_set_ed(tri_uint32 phyid, tri_uint32 type, tri_uint32 data);
tri_uint32 tri_phy_get_ed(tri_uint32 phyid, tri_uint32 type, tri_uint32 *data);
tri_uint32 tri_phy_get_status(tri_uint32 phyid, tri_uint32 type, tri_uint32 *status);
tri_uint32 tri_phy_set_led(tri_uint32 phyid, tri_uint32 type,
			 struct tri_phy_led_attr_s *attr);
tri_uint32 tri_phy_get_led(tri_uint32 phyid, tri_uint32 type,
			 struct tri_phy_led_attr_s *attr);
tri_uint32 tri_phy_set_ms_mode(tri_uint32 phyid, tri_uint32 type, tri_uint32 mode);
tri_uint32 tri_phy_get_ms_mode(tri_uint32 phyid, tri_uint32 type, tri_uint32 *mode);
tri_uint32 tri_phy_set_eye_test_mode(tri_uint32 phyid, tri_uint32 type,
				   tri_uint32 mode);
tri_uint32 tri_phy_set_mdi_mode(tri_uint32 phyid, tri_uint32 type, tri_uint32 mode);
tri_uint32 tri_phy_get_mdi_mode(tri_uint32 phyid, tri_uint32 type, tri_uint32 *mode);
tri_uint32 tri_phy_get_patch_version(tri_uint32 phyid, tri_uint32 type,
				   tri_uint32 *verion);
tri_uint32 tri_phy_set_rx_bist(tri_uint32 phyid, tri_uint32 type, tri_uint32 en,
			     tri_uint32 *status_out);
tri_uint32 tri_phy_get_rx_bist(tri_uint32 phyid, tri_uint32 type, tri_uint32 *en,
			     tri_uint32 *status);
tri_uint32 tri_phy_get_ed_status(tri_uint32 phyid, tri_uint32 type, tri_uint32 *ed);
tri_uint32 tri_phy_get_rx_pkt_cnt(tri_uint32 phyid, tri_uint32 type,
				tri_uint32 *cnt, tri_uint32 *err_cnt);
tri_uint32 tri_phy_clr_rx_pkt_cnt(tri_uint32 phyid, tri_uint32 type);
tri_uint32 tri_phy_op_reg(struct tri_phy_ge_debug_s *reg);
tri_uint32 tri_phy_op_xge_reg(struct tri_phy_xge_debug_s *reg);
tri_uint32 tri_phy_get_reg_info(struct tri_phy_read_info_s *info);
tri_uint32 tri_phy_patch(tri_uint32 phyid, tri_uint32 phy_type,
		       const tri_char8 *name);
tri_uint32 tri_phy_set_eee_cap_adv(tri_uint32 phyid, tri_uint32 type,
				 struct tri_phy_eee_cap_s *cap);
tri_uint32 tri_phy_get_eee_cap_adv(tri_uint32 phyid, tri_uint32 type,
				 struct tri_phy_eee_cap_s *cap);
tri_uint32 tri_phy_get_eee_cap_local(tri_uint32 phyid, tri_uint32 type,
				   struct tri_phy_eee_cap_s *cap);
tri_uint32 tri_phy_get_eee_cap_remote(tri_uint32 phyid, tri_uint32 type,
				    struct tri_phy_eee_cap_s *cap);
tri_uint32 tri_phy_get_eee_status(tri_uint32 phyid, tri_uint32 type,
				struct tri_phy_eee_status_s *status);
tri_uint32 tri_phy_set_eee_lpi_en(tri_uint32 phyid, tri_uint32 type,
				tri_uint32 enable);
tri_uint32 tri_phy_get_eee_lpi_en(tri_uint32 phyid, tri_uint32 type,
				tri_uint32 *enable);
tri_uint32 tri_phy_ext_init(tri_uint32 phyid, tri_uint32 phy_type);
tri_uint32 tri_phy_ops_reg(struct tri_phy_ops_s *ops, tri_uint32 type);
tri_uint32 tri_phy_ops_unreg(struct tri_phy_ops_s *ops, tri_uint32 type);
tri_void tri_phy_ops_dump(tri_void);
tri_int32 tri_phy_tdr_get(struct tri_phy_tdr_info_s *tdr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_PHY_H__ */
