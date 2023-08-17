/*
 */

#ifndef __TRI_GPIO_H__
#define __TRI_GPIO_H__

#include <tr6560/tri_typedef.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef __DEFINE__
#endif
#define tri_gpio_systrace(ret, arg1, arg2, arg3, arg4) \
	tri_systrace(TRI_KSOC_SDK_L2_GPIO, ret, arg1, arg2, arg3, arg4)
#define tri_gpio_debug(level, fmt, arg...) \
	tri_debug(TRI_KSOC_SDK_L2_GPIO, level, fmt, ##arg)

/*
 * 管脚驱动能力:
 * 00:4mA；
 * 01:3mA；
 * 10:2mA；
 * 11:1mA。
 */
#define TRI_GPIO_DS_MAX        0x7    /* 最大驱动能力 */

#define TRI_GPIO_BIT_PERGROUP  32     /* 每组gpio个数 */

#define TRI_GPIO_NUM_MAX       63     /* GPIO最大编号 */

#ifdef __API__
#endif
tri_uint32 tri_gpio_get_io_cfg_addr(tri_uint32 gpio);
tri_uint32 tri_gpio_write(struct tri_hal_gpio_level_s *level);
tri_uint32 tri_gpio_read(struct tri_hal_gpio_level_s *level);
tri_uint32 tri_gpio_get_attr(struct tri_hal_gpio_attr_s *attr);
tri_uint32 tri_gpio_set_attr(struct tri_hal_gpio_attr_s *attr);
tri_uint32 tri_gpio_set_pull_mode(tri_uint32 gpio,
	enum tri_hal_gpio_pull_mode mode);
tri_uint32 tri_gpio_clear_irq(tri_uint32 gpio);
tri_uint32 tri_gpio_get_group_irq(tri_uint32 group, tri_uint32 *status);
tri_int32  tri_gpio_init(tri_void);
tri_void tri_gpio_exit(tri_void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TRI_GPIO_H__ */

