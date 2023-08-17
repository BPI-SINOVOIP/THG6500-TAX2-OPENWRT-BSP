/*
		其原理为,在内核态声明后,自动创建一个对应的,函数头为
		TRI_HLP_IPC_PREX固定格式的系统调用函数。
		该系统调用函数在ko模块插入时候被系统自动添加到内核数据库中,
		用户态通过通用ioctl调用触发该函数,由自动创建的函数,转换为对应的
		函数原型对原函数进行调用。
		================================================================
		IPC命名规则,TRI_EXPORT_IPC固定作为前缀,后面跟两位数字,
			    每个数字从0-9范围,
			    第一位为输入参数个数;
			    第二位为在同样输入个数情况下,不同的数据原型,
			    	主要区分数值(0)和指针(1).
		================================================================
		IPC00
		----------------------------------------------------------------
		eg. tri_int32 func(tri_void)  使用该宏导出,被用户态自动调用
		================================================================
		IPC10
		----------------------------------------------------------------
		eg. tri_int32 func(tri_uint32 arg)   使用该宏导出,被用户态自动调用
		----------------------------------------------------------------
		IPC11
		----------------------------------------------------------------
		eg. tri_int32 func(tri_void *arg) 使用该宏导出,被用户态自动调用
		================================================================
		IPC30 特殊类型,inlen为data指针指向的实际长度,
		      outlen为返回值长度,不能大于inlen
		----------------------------------------------------------------
		eg. tri_int32 func(tri_void *data, tri_uint32 inlen,
			tri_uint32 outlen) 使用该宏导出,被用户态自动调用
 */

#ifndef __TRI_SYMBOL_H__
#define __TRI_SYMBOL_H__

/* eg. tri_int32 func(tri_void) 使用该宏导出,被用户态自动调用 */
#define TRI_IPC_CALL_ARG00(func)                                       \
	static tri_int32 hcall_##func(tri_void *data, tri_uint32 size, \
				     tri_uint32 *outlen)             \
	{                                                           \
		return func();                                      \
	}                                                           \
	EXPORT_SYMBOL(hcall_##func);

/* eg. tri_int32 func(tri_uint32 arg) 使用该宏导出,被用户态自动调用 */
#define TRI_IPC_CALL_ARG10(func)                                       \
	static tri_int32 hcall_##func(tri_void *data, tri_uint32 size, \
				     tri_uint32 *outlen)             \
	{                                                           \
		tri_uchar8 *arg_data = (tri_uchar8 *)data +           \
			sizeof(struct tri_hlp_exhead_s);             \
		tri_uint32 arg = *((tri_uint32 *)arg_data);           \
		if (data == NULL) \
			return TRI_RET_FAIL; \
		return func(arg);                                   \
	}                                                           \
	EXPORT_SYMBOL(hcall_##func);

/* eg. tri_int32 func(tri_void *arg) 使用该宏导出,被用户态自动调用 */
#define TRI_IPC_CALL_ARG11(func)                                       \
	static tri_int32 hcall_##func(tri_void *data, tri_uint32 size, \
				     tri_uint32 *outlen)             \
	{                                                           \
		tri_uchar8 *arg_data = (tri_uchar8 *)data +           \
			sizeof(struct tri_hlp_exhead_s);             \
		tri_void *arg = (tri_void *)arg_data;                 \
		if (data == NULL) \
			return TRI_RET_FAIL; \
		return func(arg);                                   \
	}                                                           \
	EXPORT_SYMBOL(hcall_##func);

/*
 * eg. tri_int32 func(tri_void *data, tri_uint32 inlen, tri_uint32 *outlen)
 * 使用该宏导出,被用户态自动调用 特殊类型,inlen为data指针指向的实际长度,
 * outlen为返回值长度,不能大于inlen
 */
#define TRI_IPC_CALL_ARG30(func)                                            \
	static tri_int32 hcall_##func(tri_void *data, tri_uint32 inlen,     \
				     tri_uint32 *outlen)                  \
	{                                                                \
		struct tri_hlp_exhead_s *exhead =                         \
			(struct tri_hlp_exhead_s *)data;                  \
		tri_uchar8 *arg_data = (tri_uchar8 *)data +                \
			sizeof(struct tri_hlp_exhead_s);                  \
		tri_uint32 *out = NULL; \
		if (data == NULL) \
			return TRI_RET_FAIL; \
		out = (tri_uint32 *)(arg_data + exhead->len1); \
		return func((tri_void *)arg_data, exhead->len1, out);     \
	}                                                                \
	EXPORT_SYMBOL(hcall_##func);
#ifdef TRI_SDK_DEBUG
#define TRI_EXPORT_IPC00(func) TRI_IPC_CALL_ARG00(func)
#define TRI_EXPORT_IPC10(func) TRI_IPC_CALL_ARG10(func)
#define TRI_EXPORT_IPC11(func) TRI_IPC_CALL_ARG11(func)
#define TRI_EXPORT_IPC30(func) TRI_IPC_CALL_ARG30(func)
#else
#define TRI_EXPORT_IPC00(func)
#define TRI_EXPORT_IPC10(func)
#define TRI_EXPORT_IPC11(func)
#define TRI_EXPORT_IPC30(func)
#endif

#endif /* __TRI_SYMBOL_H__ */