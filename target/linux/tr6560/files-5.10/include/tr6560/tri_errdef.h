/*
 */

#ifndef __TRI_ERRDEF_H__
#define __TRI_ERRDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*
 * 按照字母顺序排列
 */
enum tri_ret_base_e {
	/* 返回成功 */
	TRI_RET_SUCC                     = 0,
	/* 返回通用错误码 */
	TRI_RET_FAIL                     = 0xFFFFFFFF,
	/* 返回码起始数值 */
	TRI_RET_BASEVALUE                = 0x70000000,
	/* 芯片不支持该功能 */
	TRI_RET_TRI_NOT_SUPPORTED       = (TRI_RET_BASEVALUE | 0x01),
	/* 芯片号错误 */
	TRI_RET_TRI_ID_ERROR            = (TRI_RET_BASEVALUE | 0x02),
	/* CRC校验错误错误 */
	TRI_RET_CRC_ERR                  = (TRI_RET_BASEVALUE | 0x03),
	/* 返回设备忙 */
	TRI_RET_DEVBUSY                  = (TRI_RET_BASEVALUE | 0x04),
	/* 返回设备空 */
	TRI_RET_DEVEMPTY                 = (TRI_RET_BASEVALUE | 0x05),
	/* 返回设备满 */
	TRI_RET_DEVFULL                  = (TRI_RET_BASEVALUE | 0x06),
	/* 返回设备超时 */
	TRI_RET_DEVTIMEOUT               = (TRI_RET_BASEVALUE | 0x07),
	/* 设备未使能 */
	TRI_RET_DEVCLOSE                 = (TRI_RET_BASEVALUE | 0x08),
	/* 打开文件错误 */
	TRI_RET_FILE_OPEN_FAIL           = (TRI_RET_BASEVALUE | 0x09),
	/* 关闭文件错误 */
	TRI_RET_FILE_CLOSE_FAIL          = (TRI_RET_BASEVALUE | 0x0A),
	/* 读文件错误 */
	TRI_RET_FILE_READ_FAIL           = (TRI_RET_BASEVALUE | 0x0B),
	/* 写文件错误 */
	TRI_RET_FILE_WRITE_FAIL          = (TRI_RET_BASEVALUE | 0x0C),
	/* 初始化失败 */
	TRI_RET_INIT_FAIL                = (TRI_RET_BASEVALUE | 0x0D),
	/* 返回item不存在 */
	TRI_RET_ITEM_NOTEXIST            = (TRI_RET_BASEVALUE | 0x0E),
	/* 返回item已经存在 */
	TRI_RET_ITEM_EXIST               = (TRI_RET_BASEVALUE | 0x0F),
	/* 返回item表项满 */
	TRI_RET_ITEM_FULL                = (TRI_RET_BASEVALUE | 0x10),
	/* 返回item表项异常 */
	TRI_RET_ITEM_EXCEPT              = (TRI_RET_BASEVALUE | 0x11),
	/* 返回无效参数 */
	TRI_RET_INVALID_PARA             = (TRI_RET_BASEVALUE | 0x12),
	/* 错误的状态 */
	TRI_RET_INVALID_STATE            = (TRI_RET_BASEVALUE | 0x13),
	/* 非法VLAN ID */
	TRI_RET_INVALID_VLAN_ID          = (TRI_RET_BASEVALUE | 0x14),
	/* 优先级类型错误 */
	TRI_RET_INVALID_PRIORITY_TYPE    = (TRI_RET_BASEVALUE | 0x15),
	/* MAC地址老化时间非法 */
	TRI_RET_INVALID_MAC_AGE_TIME     = (TRI_RET_BASEVALUE | 0x16),
	/* MAC地址学习数非法 */
	TRI_RET_INVALID_MAC_LEARN_LIMIT  = (TRI_RET_BASEVALUE | 0x17),
	/* MAC地址非法 */
	TRI_RET_INVALID_MAC_ADDR         = (TRI_RET_BASEVALUE | 0x18),
	/* 端口TAG类型错误 */
	TRI_RET_INVALID_PORT_TAG_MODE    = (TRI_RET_BASEVALUE | 0x19),
	/* 错误的地址 */
	TRI_RET_INVALID_ADDR             = (TRI_RET_BASEVALUE | 0x1A),
	/* 分配内存失败 */
	TRI_RET_MALLOC_FAIL              = (TRI_RET_BASEVALUE | 0x1B),
	/* 释放内存失败 */
	TRI_RET_MFREE_FAIL               = (TRI_RET_BASEVALUE | 0x1C),
	/* 未知的消息类型 */
	TRI_RET_MSG_UNKNOWN              = (TRI_RET_BASEVALUE | 0x1D),
	/* 接收到的消息长度错误 */
	TRI_RET_MSG_RCV_ERRSIZE          = (TRI_RET_BASEVALUE | 0x1E),
	/* 返回输入空指针 */
	TRI_RET_NULLPTR                  = (TRI_RET_BASEVALUE | 0x1F),
	/* 返回不支持 */
	TRI_RET_NOTSUPPORT               = (TRI_RET_BASEVALUE | 0x20),
	/* 返回超出系统范围 */
	TRI_RET_OUTRANG                  = (TRI_RET_BASEVALUE | 0x21),
	/* 写寄存器失败 */
	TRI_RET_REG_WRITE_ERR            = (TRI_RET_BASEVALUE | 0x22),
	/* 读寄存器失败 */
	TRI_RET_REG_READ_ERR             = (TRI_RET_BASEVALUE | 0x23),
	/* 重复操作 */
	TRI_RET_REPEAT_OPER              = (TRI_RET_BASEVALUE | 0x24),
	/* 系统调用失败 */
	TRI_RET_SYS_CALLFAIL             = (TRI_RET_BASEVALUE | 0x25),
	/* 执行失败 */
	TRI_RET_SYS_EXCEPTION            = (TRI_RET_BASEVALUE | 0x26),
	/* 等待信号返回 */
	TRI_RET_SIGNAL                   = (TRI_RET_BASEVALUE | 0x27),
	/* 发送超时 */
	TRI_RET_TIMEOUT                  = (TRI_RET_BASEVALUE | 0x28),
	/* 创建定时器失败 */
	TRI_RET_TIMER_CREATE_FAIL        = (TRI_RET_BASEVALUE | 0x29),
	/* 表满 */
	TRI_RET_TABLE_FULL               = (TRI_RET_BASEVALUE | 0x2A),
	/* 表中已存在 */
	TRI_RET_TABLE_EXIST              = (TRI_RET_BASEVALUE | 0x2B),
	/* 表中不存在 */
	TRI_RET_TABLE_NOTEXIST           = (TRI_RET_BASEVALUE | 0x2C),
	/* 返回item表项异常 */
	TRI_RET_TABLE_EXCEPT             = (TRI_RET_BASEVALUE | 0x2D),
	/* 没有初始化 */
	TRI_RET_UNINIT                   = (TRI_RET_BASEVALUE | 0x2E),
	/* 已经初始化 */
	TRI_RET_ALREADYINIT              = (TRI_RET_BASEVALUE | 0x2F),
	/* 返回没有打开或者激活 */
	TRI_RET_UNACTIVE                 = (TRI_RET_BASEVALUE | 0x30),
	/* 返回创建进程失败 */
	TRI_RET_FORKFAIL                 = (TRI_RET_BASEVALUE | 0x31),
	/* 返回没有发现 */
	TRI_RET_NOTFIND                  = (TRI_RET_BASEVALUE | 0x32),
	/* 返回未期待异常 */
	TRI_RET_UNEXCEPT                 = (TRI_RET_BASEVALUE | 0x33),
	/* 返回期待非空 */
	TRI_RET_NOTEMPTY                 = (TRI_RET_BASEVALUE | 0x34),
	/* 线程创建失败 */
	TRI_RET_THREAD_CREATE_FAIL       = (TRI_RET_BASEVALUE | 0x35),
	/* 返回操作终止 */
	TRI_RET_STOP                     = (TRI_RET_BASEVALUE | 0X37),
};

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __TRI_ERRDEF_H__ */
