/*
 */

#ifndef __TRI_WARNING_H__
#define __TRI_WARNING_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define TRI_LOG_OUTPUTMAXLEN    2048
#define TRI_SYSLOG_DATALEN      128

/* 最多八个类型,因为DEBUG为UCHAR8类型 */
enum tri_dbglevel_e {
	TRI_LOG_LEVEL_EMC_E = 0, /* 紧急 */
	TRI_LOG_LEVEL_ALM_E,     /* 告警 */
	TRI_LOG_LEVEL_EVT_E,     /* 事件 */
	TRI_LOG_LEVEL_ERR_E,     /* 错误 */
	TRI_LOG_LEVEL_WRN_E,     /* 提示 */
	TRI_LOG_LEVEL_MSG_E,     /* 消息 */
	TRI_LOG_LEVEL_INFO_E,    /* 信息 */
	TRI_LOG_LEVEL_DBG_E,     /* 调试 */
};

enum tri_log_systrace_e {
	TRI_LOG_SYSTRACE_DISABLE_E,
	TRI_LOG_SYSTRACE_ENABLE_E,
	TRI_LOG_SYSTRACE_FAIL_E,
	TRI_LOG_SYSTRACE_SUCC_E,
	TRI_LOG_SYSTRACE_CNT_E,
};

struct tri_log_cfg_s {
	tri_uint32 srcmodule;
	tri_uint32 maskdbgflag;  /* bit0: 31,每个比特对应tri_dbglevel_e枚举 */
	/*
	 * 0x0: 关闭不输出; 0x1: 输出所有信息; 0x2: 只输出失败信息;
	 * 0x3: 只输出成功信息;0x4: 按照配置返回值精确匹配
	 */
	tri_uchar8 systraceflag;
	tri_uchar8 printflag;
	tri_uchar8 flag;         /* bit0:1远程打印 bit0:0本地打印 */
	tri_uchar8 resv;
	tri_uint32 retcode;
};

struct tri_syslog_s {
	tri_uint32 module;
	tri_uint32 level;
	tri_uint32 retcode;
	tri_uchar8 content[TRI_SYSLOG_DATALEN];
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_WARNING_H__ */
