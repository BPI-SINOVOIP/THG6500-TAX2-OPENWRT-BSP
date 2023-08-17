/*
 */

#ifndef __TRI_NOTIFY_H__
#define __TRI_NOTIFY_H__

#define TRI_NOTIFY_MSG_MAX 256       /* 告警支持最大消息/进程个数 0x100 */
#define TRI_NOTIFY_MSG_LEN_MAX 4000  /* 告警支持最大消息长度 */

struct tri_notify_msg_s {
	uintptr_t pid;       /* 消息归属进程ID */
	uintptr_t notifyid;  /* 唯一消息ID  */
	tri_uint32 len;       /* 消息长度 */
	tri_uint32 orgpid;    /* 消息发送者进程 */
	tri_uint32 ret;       /* 回调函数返回值 */
	tri_void *context;    /* 消息内容 */
};

/* 内核态主动上报消息接口函数 */
tri_uint32 tri_notify_send(uintptr_t notifyid, tri_void *msgdata,
			 tri_uint32 msglen);

/* hash初始化函数 */
tri_uint32 tri_notify_init(tri_void);

/* hash退出函数 */
tri_void tri_notify_exit(tri_void);

#endif /* __TRI_NOTIFY_H__ */