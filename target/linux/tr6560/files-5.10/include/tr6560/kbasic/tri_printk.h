/*
 */

#ifndef __TRI_PRINTK_H__
#define __TRI_PRINTK_H__

tri_void tri_print_mem(tri_uint32 len, tri_uchar8 *ptr);

tri_void tri_print_mem_ushort(tri_uint32 len, tri_uchar8 *ptr);

tri_void tri_print_mem_uint(tri_uint32 len, tri_uchar8 *ptr);

tri_void tri_print_mem_ushort_hton(tri_uint32 len, tri_uchar8 *ptr);

tri_void tri_print_mem_uint_hton(tri_uint32 len, tri_uchar8 *ptr);

#define tri_print_mem_des(len, ptr, fmt, arg...)  do { \
		tri_printk((tri_uchar8 *)fmt, ##arg); \
		tri_print_mem_uint_hton((tri_uint32)(len), (tri_uchar8 *)(ptr)); \
	} while (0)

#endif /* __TRI_PRINTK_H__ */