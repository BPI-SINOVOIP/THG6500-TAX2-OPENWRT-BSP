/*
 */

#ifndef __TRI_LOGDEF_H__
#define __TRI_LOGDEF_H__

tri_void tri_log_systrace(tri_uint32 module, tri_uchar8 *file,
			tri_uchar8 *func, tri_uint32 line,
			tri_uint32 retcode, tri_uint32 arg1,
			tri_uint32 arg2, tri_uint32 arg3, tri_uint32 arg4);

tri_void tri_log_debug(tri_uint32 module, const tri_char8 *file,
		     tri_uchar8 *func, tri_uint32 line, tri_uint32 dbglevel,
		     tri_uchar8 *fmt, ...);

tri_void tri_log_print(tri_uint32 module, tri_uint32 dbglevel,
		     tri_uchar8 *fmt, ...);

tri_void tri_log_mem(tri_uint32 module, tri_uint32 dbglevel, tri_uchar8 *src,
		   tri_uint32 len);

tri_void tri_syslog_send(tri_uint32 module, tri_uint32 level,
		       tri_uint32 retcode, tri_uchar8 *fmt, ...);

/* mlog日志类型定义 */
enum tri_mlog_lv_e {
	TRI_MLOG_LV_NONE  = 0,
	TRI_MLOG_LV_FATAL = 1,
	TRI_MLOG_LV_ERROR = 2,
	TRI_MLOG_LV_WARN  = 4,
	TRI_MLOG_LV_INFO  = 8
};

/* mlog输出 */
#define TRI_MLOG_OUTPUTMAXLEN 512
tri_void tri_mlog_print(tri_uchar8 *module, tri_uchar8 *fmt, ...);
typedef tri_void (*tri_atp_mlog_print)(const char *,
				     enum tri_mlog_lv_e, const char *, ...);

#ifdef TRI_VERSION_DEBUG
#define tri_systrace(module, ret, arg1, arg2, arg3, arg4)                  \
	tri_log_systrace((tri_uint32)module, (tri_uchar8 *)__FILE__,         \
			(tri_uchar8 *)__func__, (tri_uint32)__LINE__,       \
			(tri_uint32)ret, (tri_uint32)arg1, (tri_uint32)arg2, \
			(tri_uint32)arg3, (tri_uint32)arg4)

#define tri_debug(module, level, fmt, arg...)                     \
	tri_log_debug((tri_uint32)module, (tri_char8 *)__FILE__,    \
		     (tri_uchar8 *)__func__, (tri_uint32)__LINE__, \
		     (tri_uint32)level, (tri_uchar8 *)fmt, ##arg)

#define tri_print(module, level, fmt, arg...)                                \
	tri_log_print((tri_uint32)module, (tri_uint32)level, (tri_uchar8 *)fmt, \
		     ##arg)

#define tri_memdes(module, level, src, len, fmt, arg...) do { \
		tri_debug(module, level, (tri_uchar8 *)fmt, ##arg);            \
		tri_log_mem(module, level, (tri_uchar8 *)src, (tri_uint32)len); \
	} while (0)

#define tri_syslog(module, level, ret, fmt, arg...)                          \
	tri_syslog_send((tri_uint32)module, (tri_uint32)level, (tri_uint32)ret, \
		       (tri_uchar8 *)fmt, ##arg)
#else
#define tri_systrace(module, ret, arg1, arg2, arg3, arg4)
#define tri_debug(module, level, fmt, arg...)
#define tri_print(module, level, fmt, arg...)                                \
	tri_log_print((tri_uint32)module, (tri_uint32)level, (tri_uchar8 *)fmt, \
		     ##arg)
#define tri_memdes(module, level, src, len, fmt, arg...)
#define tri_syslog(module, level, ret, fmt, arg...)
#endif

#define tri_bug() do { \
		tri_printk("\r\n%s(%d):", __func__, __LINE__); \
		dump_stack();                                 \
	} while (0)

#endif /* __TRI_LOGDEF_H__ */