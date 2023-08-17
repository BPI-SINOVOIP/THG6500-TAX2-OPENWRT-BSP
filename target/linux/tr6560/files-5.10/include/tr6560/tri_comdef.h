/*
 */

#ifndef __TRI_COMDEF_H__
#define __TRI_COMDEF_H__

#include "tri_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define TRI_DISABLE 0
#define TRI_ENABLE  1

#define TRI_FALSE 0
#define TRI_TRUE  1

#define TRI_INVALID_VLAN_ID 0xFFF
#define TRI_MAGICAL         0x68776877
#define TRI_HZ              HZ
#define TRI_FUNCNAME_MAXLEN 128

#define TRI_FILE_S FILE
#define TRI_DIR_S  DIR

#define TRI_IPC_PREX     "hcall_"

#define TRI_NUM_0     0
#define TRI_NUM_1     1
#define TRI_NUM_2     2
#define TRI_NUM_3     3
#define TRI_NUM_4     4
#define TRI_NUM_5     5
#define TRI_NUM_6     6
#define TRI_NUM_7     7
#define TRI_NUM_8     8
#define TRI_NUM_9     9
#define TRI_NUM_10    10
#define TRI_NUM_11    11
#define TRI_NUM_12    12
#define TRI_NUM_16    16
#define TRI_NUM_20    20
#define TRI_NUM_30    30
#define TRI_NUM_32    32
#define TRI_NUM_50    50
#define TRI_NUM_64    64
#define TRI_NUM_100   100
#define TRI_NUM_127   127
#define TRI_NUM_128   128
#define TRI_NUM_244   244
#define TRI_NUM_256   256
#define TRI_NUM_500   500
#define TRI_NUM_512   512
#define TRI_NUM_1000  1000
#define TRI_NUM_2000  2000
#define TRI_NUM_10000 10000

/* 获取成员在结构体中的偏移 */
#define tri_member_offset(type, mem) ((tri_uint32) & ((type *)0)->mem)

/* 4字节对齐返回需要补齐的余量 */
#define tri_byte_align_value(val)   (((val) & 0x3) ? (0x4 - ((val) & 0x3)) : 0)
#define tri_byte_align_offset(ptr)  ((tri_uint32)(ptr) & 0x3)
#define tri_byte_align(ptr)         ((tri_uint32)(ptr) & (~0x3))

#define tri_set_bit(var, bit)       ((var) |= (0x1 << (bit)))
#define tri_clr_bit(var, bit)       ((var) &= (~(0x1 << (bit))))

enum tri_bool_e {
	TRI_FALSE_E = 0,
	TRI_TRUE_E
};

/* notify id 统一定义 */
enum tri_notify_id_e {
	TRI_NOTIFYID_DYINGGASP_E = 1,
	TRI_NOTIFYID_UCI_CFG_E,

	TRI_NOTIFYID_SLIC_E,
	TRI_NOTIFYID_VOIP_E,

	TRI_NOTIFYID_OAM_MSG_E,        /* OAM事件 */
	TRI_NOTIFYID_OAM_UCI_E,        /* OAM接收UCI notify事件 */

	TRI_NOTIFYID_DBGLOG_E,         /* 调试日志 */
	TRI_NOTIFYID_SYSLOG_E,         /* 系统日志 */

	TRI_NOTIFYID_OMCI_MSG_E,       /* omci消息 */
	TRI_NOTIFYID_OMCI_REGSTA_E,    /* OMCI注册状态跳变 */
	TRI_NOTIFYID_OMCI_ROGUESTA_E,  /* 流氓ONU监测 */
	TRI_NOTIFYID_OMCI_UCI_E,       /* OMCI接收UCI notify事件 */

	TRI_NOTIFYID_WEB_UCI_E,        /* OMCI接收UCI notify事件 */
	TRI_NOTIFYID_TR069_UCI_E,      /* OMCI接收UCI notify事件 */
	TRI_NOTIFYID_UCISHELL_UCI_E,   /* UCISHELL接收UCI notify事件 */

	TRI_NOTIFYID_PLC_MSG_E,

	TRI_NOTIFYID_UCI_CLI_E,
	TRI_NOTIFYID_OAM_CLI_E,
	TRI_NOTIFYID_WEB_CLI_E,
	TRI_NOTIFYID_TR069_CLI_E,
	TRI_NOTIFYID_OMCI_CLI_E,
	TRI_NOTIFYID_VOIP_CLI_E,
	TRI_NOTIFYID_UCISHELL_CLI_E,
	TRI_NOTIFYID_SEC_CLI_E,
	TRI_NOTIFYID_PLC_HOST_CLI_E,
	TRI_NOTIFYID_PLC_GUEST_CLI_E,

	TRI_NOTIFYID_BUTT_E,
};

/* 内存数据读写结构体 */
struct tri_mem_s {
	tri_handle addr; /* 内存地址 */
	tri_uint32 data; /* 内存数据 */
};

/* 注册的函数指针类型定义 */
typedef tri_int32(*TRI_FUNCCALLBACK_EXT)(tri_void *data,
	tri_uint32 inlen, tri_uint32 *outlen);
typedef tri_int32(*TRI_FUNCCALLBACK)(tri_void *data, tri_uint32 inlen);
typedef tri_int32(*TRI_FUNC_VOID)(tri_void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_COMDEF_H__ */
