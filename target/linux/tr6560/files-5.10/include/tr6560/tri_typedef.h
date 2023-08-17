/*
 */

#ifndef __TRI_TYPEDEF_H__
#define __TRI_TYPEDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*********************************************************/

#ifndef tri_void
#define tri_void void
#endif

/*********************************************************/

#ifndef tri_char8
#define tri_char8 char
#endif

#ifndef tri_short16
#define tri_short16 short
#endif

#ifndef tri_int32
#define tri_int32 int
#endif

#ifndef tri_long32
#define tri_long32 long
#endif

#ifndef tri_long64
#define tri_long64 long long
#endif

/*********************************************************/

#ifndef tri_uchar8
#define tri_uchar8 unsigned char
#endif

#ifndef tri_ushort16
#define tri_ushort16 unsigned short
#endif

#ifndef tri_uint32
#define tri_uint32 unsigned int
#endif

#ifndef tri_ulong32
#define tri_ulong32 unsigned long
#endif

#ifndef tri_ulong64
#define tri_ulong64 unsigned long long
#endif

#ifndef tri_uint64
#define tri_uint64 unsigned long long
#endif

/*********************************************************/

#ifndef tri_size_t
#define tri_size_t tri_uint32
#endif

/*********************************************************/

#ifndef tri_v_u8
#define tri_v_u8 volatile unsigned char
#endif

#ifndef tri_iomem
#define tri_iomem tri_void __iomem
#endif

#ifndef tri_v_u16
#define tri_v_u16 volatile unsigned short
#endif

#ifndef tri_v_u32
#define tri_v_u32 volatile unsigned int
#endif

#ifndef tri_v_u64
#define tri_v_u64 volatile unsigned long long
#endif

#ifndef tri_handle
#define tri_handle unsigned long
#endif

#define TRI_NULL  0

/*********************************************************/

#ifndef tri_io_address
#define tri_io_address(x) IO_ADDRESS(x)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_TYPEDEF_H__ */
