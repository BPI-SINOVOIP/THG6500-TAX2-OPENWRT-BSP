/*
 */

#ifndef __TRI_HLP_H__
#define __TRI_HLP_H__

#define TRI_HLP_FUNCNAME_MAXLEN TRI_FUNCNAME_MAXLEN
/* MISC_DYNAMIC_MINOR 动态申请 */
#define TRI_HLP_MISC_DYNAMIC_MINOR 0x00000013
#define TRI_HLP_MISCDEVNAME "tri_hlp"

/* 系统支持最大命令数 */
#define TRI_HLP_HASHSIZE 0x3FF
#define TRI_HLP_ITEMSIZE 16
#define TRI_HLP_CONFLICTSIZE 1024
/* 系统支持高层协议长度 */
#define TRI_HLP_DATABUFF 4096

struct tri_hlp_head_s {
	tri_uint32 len;
	tri_uchar8 funcname[TRI_HLP_FUNCNAME_MAXLEN];
	tri_uchar8 text[4];
};

struct tri_hlp_exhead_s {
	tri_uint32 len1;
	tri_uint32 len2;
};

tri_uint32 tri_hlp_init(tri_void);
tri_void tri_hlp_exit(tri_void);

#endif /* __TRI_HLP_H__ */