/*
 */
#ifndef __TRI_HAL_TRI_H__
#define __TRI_HAL_TRI_H__

#include <tr6560/tri_typedef.h>
#include <tr6560/hal/tri_hal_uni.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define TRI_HAL_GPIO_BIT_MAX 32
#define TRI_HAL_DSCP_MAP_MAX 64
#define TRI_HAL_5116_SDSIF_CFG_ADDR 0x14280000
#define TRI_HAL_5116_SDSIF_BIST_CTR_ADDR 0x14280008
#define TRI_HAL_5116_SDSIF_BIST_STA_ADDR 0x1428000c

#define TRI_HAL_OPTICAL_DATA_LEN 120
#define TRI_HAL_PWM_ATTR_DATA_LEN 64
#define TRI_HAL_EFUSE_MSK_LEN 8
#define TRI_HAL_EFUSE_HUK_LEN 8
#define TRI_HAL_EFUSE_JAK_LEN 8
#define TRI_HAL_EFUSE_PUBKH_LEN 8

#if (defined CONFIG_ARCH_YYXXXXC) || (defined CONFIG_MACH_TR6560)
#define TRI_HAL_MAC_L2ITEM_COUNT 520
#else
#define TRI_HAL_MAC_L2ITEM_COUNT 264
#endif

enum tri_hal_ic_version_e {
	TRI_HAL_IC_NULL_E = 0, /* NULL */
	TRI_HAL_IC_XXXXC_E, /* xxxx */
	TRI_HAL_IC_XXXXB_E, /* xxxx */
	TRI_HAL_IC_VER_NUM_E
};

struct tri_hal_tri_version_s {
	enum tri_hal_ic_version_e tri_version;
	tri_uint32 vendor;
	tri_uint32 firmware; /* 软件固件版本信息 */
};

/* GPIO 管脚工作模式 */
enum tri_hal_gpio_mode_e {
	TRI_HAL_GPIO_MODE_INPUT_E = 0, /* gpio的方向为输入 */
	TRI_HAL_GPIO_MODE_OUTPUT_E, /* gpio的方向为输出 */
	TRI_HAL_GPIO_INTR_LOW_LEVEL_E, /* 低电平触发中断输入模式 */
	TRI_HAL_GPIO_INTR_HIGH_LEVEL_E, /* 高电平触发中断输入模式 */
	TRI_HAL_GPIO_INTR_DOWN_EDGE_E, /* 下降沿触发中断输入模式 */
	TRI_HAL_GPIO_INTR_UP_EDGE_E, /* 上升沿触发中断输入模式 */
};

enum tri_hal_gpio_pull_mode {
	TRI_HAL_GPIO_PULL_DOWN_MODE = 0, /* 管脚弱下拉 */
	TRI_HAL_GPIO_PULL_UP_MODE,
};

/* GPIO 管脚中断属性 */
struct tri_hal_gpio_irq_s {
	tri_uint32 gpio; /* 引脚编号 */
	enum tri_hal_gpio_mode_e mode; /* 中断触发模式 */
};

/* I2C工作模式 */
enum tri_hal_i2c_baud_rate_e {
	TRI_HAL_I2C_100k_E = 0, /* 100k */
	TRI_HAL_I2C_400k_E, /* 400k */
	TRI_HAL_I2C_34000k_E, /* 高速速率 3.4M */
};

/* 地址模式 */
enum tri_hal_i2c_addr_mode_e {
	TRI_HAL_I2C_ADDR_7_BIT_E = 0, /* 7bit地址长度 */
	TRI_HAL_I2C_ADDR_10_BIT_E /* 10bit地址长度 */
};

/* I2C读写模式选择 */
enum tri_hal_i2c_wr_mode_e {
	TRI_HAL_I2C_NORMAL_MODE_E = 0, /* 00：当前地址读写模式,默认为此模式 */
	TRI_HAL_I2C_BURST_MODE_E /* 01：burst read/write 读写模式 */
};

/* 光模块发光控制模式 */
enum tri_hal_optical_tx_mode_e {
	TRI_HAL_OPTICAL_UP_TX_AUTO_E = 0, /* 逻辑自动控制 */
	TRI_HAL_OPTICAL_UP_TX_ENABLE_E, /* 常发光 */
	TRI_HAL_OPTICAL_UP_TX_DISABLE_E, /* 不发光 */
};

/* 光模块发光控制 */
enum tri_hal_optical_power_ctrl_e {
	TRI_HAL_OPTICAL_OFF_E = 0, /* Power ON */
	TRI_HAL_OPTICAL_ON_E, /* Power OFF */
};

/* 看门狗模式结构体 */
enum tri_hal_wdt_mode_e {
	TRI_HAL_WDT_USER_MODE_E = 0, /* <0: 用户喂狗 */
	TRI_HAL_WDT_AUTO_MODE_E, /* <1: 内核自动喂狗 */
};

enum tri_hal_prbs_mode_e {
	TRI_HAL_BIST_0101HF_E, /* 高频模式 0101 */
	TRI_HAL_BIST_0101LF_E, /* 低频模式 0101 */
	TRI_HAL_BIST_MIXED_E, /* 混合信号模式 */
	TRI_HAL_BIST_USERDEF_E, /* 自定义信号模式 */
	TRI_HAL_BIST_PRBS7_E, /* <PRBS7 */
	TRI_HAL_BIST_PRBS15_E, /* <PRBS15 */
	TRI_HAL_BIST_PRBS23_E, /* <PRBS23 */
	TRI_HAL_BIST_PRBS31_E, /* <PRBS31 */
	TRI_HAL_BIST_NUM_E,
};

enum tri_hal_pri_tag_identify_e {
	TRI_HAL_PRI_TAG_IDENTIFY_OFF = 0, /* 不识别优先级 */
	TRI_HAL_PRI_TAG_IDENTIFY_ON = 1, /* 识别优先级 */
};

/* GPIO 管脚属性 */
struct tri_hal_gpio_attr_s {
	tri_uint32 gpio; /* GPIO 管脚，范围：0~255 */
	enum tri_hal_gpio_mode_e mode; /* GPIO工作模式 */
	tri_uint32 drv_level; /* 驱动能力等级，取值:0~7 */
};

/* GPIO 管脚输入、输出电平参数 */
struct tri_hal_gpio_level_s {
	tri_uint32 gpio; /* GPIO 管脚，范围：0~255 */
	tri_uint32 level; /* 管脚电平参数，取值:0、1 */
};

/* I2C基本属性配置 */
struct tri_hal_i2c_attr_s {
	tri_uint32 index; /* [0,1]  i2c1  i2c0 */
	enum tri_hal_bool_e enable; /* 使能i2c */
	enum tri_hal_i2c_addr_mode_e addr_mode; /* 地址模式 */
	enum tri_hal_i2c_baud_rate_e baud_rate; /* 从器件工作波特率 */
};

/* I2C command 结构体 */
struct tri_hal_i2c_command_s {
	tri_uint32 host_addr; /* I2C host 地址 */
	tri_uint32 dev_addr; /* I2C 设备地址 */
	tri_uint32 reg_len; /*  I2C 内部寄存器地址长度 */
	tri_uint32 reg_addr; /*  I2C 内部寄存器地址 */
	tri_uint32 data_len;
	tri_uchar8 data[16]; /* 寄存器数据, 长度16 */
};

/* I2C data 结构体 */
struct tri_hal_i2c_data_s {
	tri_uint32 host_addr; /* I2C host 地址 */
	tri_uint32 dev_addr; /* I2C 设备地址 */
	tri_uchar8 *data; /* 收/发数据指针 */
	tri_uint32 length; /* 收/发数据长度 */
	enum tri_hal_i2c_wr_mode_e i2c_wr_mode; /* 数据读写模式 */
};

struct tri_hal_optical_attr_s {
	tri_uint32 enable; /* <光模块使能 */

	/* 光模块发光使能电平 */
	tri_uint32 level;
	enum tri_hal_optical_tx_mode_e tx_mode;
};

/* 光模块属性 */
struct tri_hal_optical_power_s {
	enum tri_hal_optical_power_ctrl_e rx; /* RX Power Ctrl */
	enum tri_hal_optical_power_ctrl_e tx; /* TX Power Ctrl */
};
/*
 * 光模块信息数据
 */
struct tri_hal_optical_data_s {
	tri_uchar8 data[TRI_HAL_OPTICAL_DATA_LEN]; /* buffer */
};

/* led灯状态 */
enum tri_hal_led_sta_e {
	TRI_HAL_LED_AUTO_E = 0, /* led灯自动亮灭 */
	TRI_HAL_LED_FORCE_ON_E, /* 强制led灯亮 */
	TRI_HAL_LED_FORCE_OFF_E, /* 强制led灯灭 */
	TRI_HAL_LED_FORCE_BLINK_E, /* 强制led灯闪烁 */
};

/* lan led灯控制 */
struct tri_hal_lan_led_sta_s {
	enum tri_hal_port_e port; /* lan port号 */
	enum tri_hal_led_sta_e led_sta; /* led灯状态 */
};

struct tri_hal_link_led_attr_s {
	tri_uint32 led_polarity;  /* ETH LED正反极性配置 0:正 1:负 */
};

struct tri_hal_dscp_map_s {
	tri_uchar8 pri[TRI_HAL_DSCP_MAP_MAX]; /* dscp[6bit] 映射的pri[3bit] */
};

struct tri_hal_dscp_pri_map_s {
	tri_uint32 dscp; /* dscp值 */
	tri_uint32 pri_map; /* dscp值所映射的pri值 */
};

struct tri_hal_serdes_status_s {
	tri_uint32 bist_err_start; /* bist错误记录 */
	tri_uint32 bist_sync; /* bist是否同步 */
	tri_uint32 bist_err_cnt; /* bist错误统计 */
};

struct tri_hal_sds_prbs_param_s {
	tri_uint32 enable; /* 打开、关闭prbs测试 */
	tri_uint32 rx_pattern; /* prbs接收模式 */
	tri_uint32 tx_pattern; /* prbs发送模式 */
	tri_uint32 check_mode; /* 0:sync,1:free */
};

struct tri_hal_sds_prbs_result_s {
	/*
	 * PRBS checker error status
	 * The bit is set to 1 when at least one error is detected
	 */
	unsigned int err_status;
	/* give the portion of the 26 bit error counter */
	unsigned int exp;
	unsigned int err_count; /* PRBS错误计数 */
};

struct tri_hal_efuse_stat_s {
	tri_uint32 jtag_forbid; /* 禁止JTAG功能 */
	tri_uint32 secboot_en; /* 使能安全启动 */
	tri_uint32 debug_forbid; /* 禁止CPU读MSK/HUK等不可读区域 */
	tri_uint32 gm_forbid; /* 国密算法禁止 */
	tri_uint32 jtag_auth; /* Jtag认证模式 */

	/*
	 * ARM JTAG权限控制 ；
	 * 00：可以debug安全世界；
	 * 01：默认关闭debug安全世界，通过配置系统控制器打开权限；
	 * 11：永久禁止debug安全世界
	 */
	tri_uint32 armdebug_mode;
	tri_uint32 jtag_efuse_forbid; /* JTAG读写efuse禁止 */
	tri_uint32 tsensor_trim_offset; /* TSENSOR校准温度偏差码信息 */
	tri_uint32 vsensor_trim_offset; /* VSENSOR校准电压偏差码信息 */
	tri_uint32 bootrom_forbid;
	tri_uint32 osc_ring_lvt_freq; /* CP测试时烧写，工艺对电路延时的影响 */
	tri_uint32 osc_ring_svt_freq; /* CP测试时烧写，工艺对电路延时的影响 */
	tri_uint32 osc_ring_hvt_freq; /* CP测试时烧写，工艺对电路延时的影响 */
	tri_uchar8 dieid[20];
	tri_uchar8 ext_dieid[6];
};

struct tri_hal_efuse_data_s {
	tri_uint32 revoked_key_mask; /* 生产时注销丢失的密钥 */
	tri_uint32 bl_nvcounter; /* 生产时注销失效的boot版本 */
	tri_uint32 os_nvcounter[7]; /* 生产时注销失效的OS版本 */
	tri_uint32 msk[TRI_HAL_EFUSE_MSK_LEN];
	tri_uint32 huk[TRI_HAL_EFUSE_HUK_LEN];
	tri_uint32 jak[TRI_HAL_EFUSE_JAK_LEN];
	tri_uint32 pubkh[TRI_HAL_EFUSE_PUBKH_LEN];
	tri_uint32 secboot_en;
	tri_uint32 debug_forbid;
	tri_uint32 gm_forbid;
	tri_uint32 jtag_auth;
	tri_uint32 armdebug_mode;
	tri_uint32 jtag_efuse_forbid;
};

struct tri_hal_pwm_attr_s {
	tri_uint32 index; /* LED 编号0,1 */
	tri_uint32 mode; /* 呼吸灯的亮度模式 */
	tri_uint32 step_size; /* 步长,必须小于32 ，大于0 */
	tri_uint32 type; /* PWM类型,0负脉冲,1正脉冲 */
	tri_uint32 state; /* LED状态,0失能,1使能 */
	tri_uint32 val0; /* 只在模式0,2有效 */
	tri_uint32 val1; /* 只在模式2有效 */
	tri_uchar8 table[TRI_HAL_PWM_ATTR_DATA_LEN];
};

/* 获取芯片版本信息 */
tri_uint32 tri_kernel_hal_tri_version_get(
	struct tri_hal_tri_version_s *pversion);

/* 获取GPIO管脚属性 */
tri_uint32 tri_kernel_hal_gpio_attr_get(struct tri_hal_gpio_attr_s *attr);

/* 配置GPIO管脚属性 */
tri_uint32 tri_kernel_hal_gpio_attr_set(struct tri_hal_gpio_attr_s *attr);

/* 输出GPIO管脚电平 */
tri_uint32 tri_kernel_hal_gpio_write(struct tri_hal_gpio_level_s *level);

/* 读取GPIO管脚电平 */
tri_uint32 tri_kernel_hal_gpio_read(struct tri_hal_gpio_level_s *level);

/* 设置IIC模块的属性 */
tri_uint32 tri_kernel_hal_i2c_attr_set(struct tri_hal_i2c_attr_s *attr);

/* 获取IIC模块的属性 */
tri_uint32 tri_kernel_hal_i2c_attr_get(struct tri_hal_i2c_attr_s *attr);

/* 普通iic读接口 */
tri_uint32 tri_kernel_hal_i2c_cmd_read(struct tri_hal_i2c_command_s *cmd);

/* 普通iic写接口 */
tri_uint32 tri_kernel_hal_i2c_cmd_write(struct tri_hal_i2c_command_s *cmd);

/* 连续iic读接口 */
tri_uint32 tri_kernel_hal_i2c_data_send(struct tri_hal_i2c_data_s *data);

/* 连续iic写接口 */
tri_uint32 tri_kernel_hal_i2c_data_receive(struct tri_hal_i2c_data_s *data);

/* 光模块属性设置 */
tri_uint32 tri_kernel_hal_optical_attr_get(struct tri_hal_optical_attr_s *attr);

/* 光模块属性获取 */
tri_uint32 tri_kernel_hal_optical_attr_set(struct tri_hal_optical_attr_s *attr);

/* 光模块发光控制 */
tri_uint32 tri_kernel_hal_optical_power_set(struct tri_hal_optical_power_s *power);

/* 光模块发光状态查询 */
tri_uint32 tri_kernel_hal_optical_power_get(struct tri_hal_optical_power_s *power);

/* 获取光模块信息数据 */
tri_uint32 tri_kernel_hal_optical_data_get(struct tri_hal_optical_data_s *data);

/* 看门狗模式设置 */
tri_uint32 tri_kernel_hal_wdt_mode_set(enum tri_hal_wdt_mode_e mode);

/* 看门狗喂狗接口 */
tri_uint32 tri_kernel_hal_wdt_clear(tri_void);

/* lan led灯状态控制 */
tri_uint32 tri_kernel_hal_phy_led_ctl(struct tri_hal_lan_led_sta_s *led);

/* link led灯状态控制 */
tri_uint32 tri_kernel_hal_link_led_set(struct tri_hal_link_led_attr_s *attr);

/* 初始化SPI */
tri_uint32 tri_kernel_hal_init_spi_for_serdes(tri_void);
/* 配置PRBS模式 */
tri_uint32 tri_kernel_hal_set_prbs_mode(enum tri_hal_prbs_mode_e type);

/* 获取sdsif统计 */
tri_uint32 tri_kernel_hal_get_serdes_status(struct tri_hal_serdes_status_s *arg);

/* 设置serdes prbs参数 */
tri_uint32 tri_kernel_hal_set_serdes_prbs(struct tri_hal_sds_prbs_param_s *arg);

/* 获取sdsif统计 */
tri_uint32 tri_kernel_hal_get_serdes_result(struct tri_hal_sds_prbs_result_s *arg);

/* 配置DSCP和PBIT的映射关系 */
tri_uint32 tri_kernel_hal_dscp_map_set(struct tri_hal_dscp_pri_map_s *map);

/* 获取DSCP和PBIT的映射关系 */
tri_uint32 tri_kernel_hal_dscp_map_get(struct tri_hal_dscp_pri_map_s *map);

/* 删除DSCP和PBIT的映射关系 */
tri_uint32 tri_kernel_hal_dscp_map_del(struct tri_hal_dscp_pri_map_s *map);

/* 获取sensor temperature */
tri_uint32 tri_kernel_hal_sensor_temp_get(tri_int32 *temp);

/* 删除DSCP和PBIT的映射关系 */
tri_uint32 tri_kernel_hal_pri_tag_identify_get(
	enum tri_hal_pri_tag_identify_e *pem_enable);

/* 删除DSCP和PBIT的映射关系 */
tri_uint32 tri_kernel_hal_pri_tag_identify_set(
	enum tri_hal_pri_tag_identify_e enable);

/* 获取efuse控制状态 */
tri_int32 tri_kernel_hal_efuse_get(struct tri_hal_efuse_stat_s *stat);

/* efuse装备命令烧写 */
tri_int32 tri_kernel_hal_efuse_set(struct tri_hal_efuse_data_s *data);

/* 配置PWM属性 */
tri_uint32 tri_kernel_hal_pwm_attr_set(struct tri_hal_pwm_attr_s *attr);

/* 获取PWM属性 */
tri_uint32 tri_kernel_hal_pwm_attr_get(struct tri_hal_pwm_attr_s *attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_HAL_TRI_H__ */
