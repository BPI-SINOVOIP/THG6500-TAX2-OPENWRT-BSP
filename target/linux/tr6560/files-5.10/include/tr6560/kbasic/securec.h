/**------------------------------------------------------------------
 * Copyright(C), Triductor Technologies Co., Ltd. 2014 All rights reserved.
 * ------------------------------------------------------------------
 * @brief   simple adapt securec lib for kernel module
 *          the user of this secure c library should include this header file
 *          in you source code. This header file declare all supported API
 *          prototype of the library, such as memcpy_s, strcpy_s, wcscpy_s,
 *          strcat_s, strncat_s, sprintf_s, scanf_s, and so on.
 * @version 1.0
 * @date    2014/12/9
 * -----------------------------------------------------------------*/

#ifndef ___SECUREC_H__
#define ___SECUREC_H__

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>

/* invalid parameter range */
#ifndef ERANGE
#define ERANGE (34)
#endif

#define INLINE inline



#define TRI_BIT_MODIFY(reg, bit, value) ((0 == (value))  ? TRI_BIT_CLR((reg), (bit)) : TRI_BIT_SET((reg), (bit)))
#ifndef TRI_KDEBUG
#define TRI_KDEBUG(fmt, arg...) printk("\n\r  FUNC = %s:%u \n\r "fmt" \n\r", __func__, __LINE__, ## arg)
#endif
#define TRI_EDGE_CHECK(arg) ((TRI_UP_EDGE_E == arg) || (TRI_DOWN_EDGE_E == arg))
#define TRI_LEVEL_CHECK(arg) ((TRI_HIGH_LEVEL_E == arg) || (TRI_LOW_LEVEL_E == arg))
#define TRI_BOOL_CHECK(arg) ((TRI_TRUE_E == arg) || (TRI_FALSE_E == arg))

#define TRI_MALLOC(size) (kmalloc(size, GFP_KERNEL))
#define TRI_FREE kfree


#define TRI_SDK_RET_CHECK(ui_ret) \
    do \
    {\
        if (TRI_RET_SUCCESS != ui_ret)\
        {\
            TRI_KDEBUG("return not success,ret %#x\n", ui_ret); \
            return ui_ret; \
        } \
    } while (0)
    
#define TRI_SDK_PTR_CHECK(ptr) \
    do \
    {\
        if (TRI_NULL == ptr)\
        {\
            TRI_KDEBUG("null pointer \n"); \
            return TRI_RET_NULL_PTR; \
        } \
    } while (0)



typedef int error_t;

#define memcmp_s(p1, p2, n) memcmp(p1, p2, n)

/* memset: void *memset(void *s, int c, size_t count) */
static inline error_t memset_s(void *dest, size_t dest_max, int c, size_t count)
{
    count = count > dest_max ? dest_max : count;
    (void)memset(dest, c, count);
    return 0;
}

/* memcpy: void *memcpy(void *dest, const void *src, size_t count)*/
static inline error_t memcpy_s(void *dest, size_t dest_max, const void *src, size_t count)
{
    count = count > dest_max ? dest_max : count;
    (void)memcpy(dest, src, count);
    return 0;
}

/* memmove: void *memmove(void *dest, const void *src, size_t count) */
static inline error_t memmove_s(void *dest, size_t dest_max, const void *src, size_t count)
{
    count = count > dest_max ? dest_max : count;
    (void)memmove(dest, src, count);
    return 0;
}

/* strcpy: char *strcpy(char *dest, const char *src) */
static inline error_t strcpy_s(char *dest, size_t dest_max, const char *src)
{
    (void)strncpy(dest, src, dest_max);
    /* If there is no null byte among the first n bytes of src,
     * the string placed in dest will not be null terminated.
     */
    dest[dest_max - 1] = '\0';
    return 0;
}

/* strncpy: char *strncpy(char *dest, const char *src, size_t count) */
static inline error_t strncpy_s(char *dest, size_t dest_max, const char *src, size_t count)
{
    dest_max--;
    if (count > dest_max) {
        count = dest_max;
    }
    (void)strncpy(dest, src, count);
    dest[count] = '\0';
    return 0;
}

/* strcat: char *strcat(char *dest, const char *src) */
static inline error_t strcat_s(char *dest, size_t dest_max, const char *src)
{
    size_t length = strlen(dest);
    dest_max--;
    if (dest_max > length) {
        (void)strncat(dest, src, (dest_max - length));
        /* strncat ensure dest to be null terminated in kernel */
        return 0;
    }
    return -ERANGE;
}

/* strncat: char *strncat(char *dest, const char *src, size_t count) */
static inline error_t strncat_s(char *dest, size_t dest_max, const char *src, size_t count)
{
    size_t length = strlen(dest);
    dest_max--;
    if (dest_max > length) {
        length = dest_max - length;
        count = count > length ? length : count;
        (void)strncat(dest, src, count);
        /* strncat ensure dest to be null terminated in kernel */
        return 0;
    }
    return -ERANGE;
}

/* sprintf: int sprintf(char *buf, const char *fmt, ...) */
int osal_sprintf_s(char *dest, size_t dest_max, const char *fmt, ...);
//#define sprintf_s osal_sprintf_s

/* snprintf: int snprintf(char *buf, size_t size, const char *fmt, ...) */
int osal_snprintf_s(char *dest, size_t dest_max, size_t size, const char *fmt, ...);
//#define snprintf_s osal_snprintf_s

/* vsprintf: int vsprintf(char *buf, const char *, va_list args) */
static inline int vsprintf_s(char *dest, size_t dest_max, const char *format, va_list arglist)
{
    dest[dest_max - 1] = '\0';
    return vsnprintf(dest, dest_max - 1, format, arglist);
}

/* vsnprintf: int vsnprintf(char *buf, size_t size, const char *fmt, va_list args) */
static inline int vsnprintf_s(char *dest, size_t dest_max, size_t count, const char *format, va_list arglist)
{
    int r;
    if (count > dest_max) {
        count = dest_max;
    }
    r = vsnprintf(dest, count, format, arglist);
    dest[count - 1] = '\0';
    return r;
}

static inline int sprintf_s(char *dest, size_t dest_max, const char *fmt, ...)
{
    int retval;
    va_list ap;

    va_start(ap, fmt);
    retval = vsprintf_s(dest, dest_max, fmt, ap);
    va_end(ap);

    if ((0 <= retval) && (dest_max <= (size_t) retval)) {
        retval = -1;
    }

    return retval;
}

static inline int snprintf_s(char *dest, size_t dest_max, size_t size, const char *fmt, ...)
{
    int retval;
    va_list ap;

    if (size < dest_max) {
        dest_max = size;
    }

    va_start(ap, fmt);
    retval = vsnprintf_s(dest, dest_max, size, fmt, ap);
    va_end(ap);

    if ((0 <= retval) && (dest_max <= (size_t) retval)) {
        retval = -1;
    }

    return retval;
}

static inline void *malloc_s(char *desc, size_t size)
{
    return kmalloc(size, GFP_KERNEL | GFP_ATOMIC);
}

static inline void free_s(void *ptr)
{
    if (ptr)
        kfree(ptr);
}

//#define tri_free free_s

#endif

