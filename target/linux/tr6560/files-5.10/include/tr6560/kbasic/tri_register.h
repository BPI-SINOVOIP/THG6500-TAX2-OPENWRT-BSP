/*
 */

#ifndef __TRI_REGISTER_H__
#define __TRI_REGISTER_H__

/* 用于电平配置 */
enum tri_level_e {
	TRI_LOW_LEVEL_E = 0,
	TRI_HIGH_LEVEL_E
};

/* 用于信号触发沿配置 */
enum tri_edge_e {
	TRI_UP_EDGE_E = 0, /* 上升沿 */
	TRI_DOWN_EDGE_E,   /* 下降沿 */
};

/* 定义的变量，用于设置一个bit为1或0 */
#define TRI_BIT31_1 (0x00000001 << 31)
#define TRI_BIT30_1 (0x00000001 << 30)
#define TRI_BIT29_1 (0x00000001 << 29)
#define TRI_BIT28_1 (0x00000001 << 28)
#define TRI_BIT27_1 (0x00000001 << 27)
#define TRI_BIT26_1 (0x00000001 << 26)
#define TRI_BIT25_1 (0x00000001 << 25)
#define TRI_BIT24_1 (0x00000001 << 24)
#define TRI_BIT23_1 (0x00000001 << 23)
#define TRI_BIT22_1 (0x00000001 << 22)
#define TRI_BIT21_1 (0x00000001 << 21)
#define TRI_BIT20_1 (0x00000001 << 20)
#define TRI_BIT19_1 (0x00000001 << 19)
#define TRI_BIT18_1 (0x00000001 << 18)
#define TRI_BIT17_1 (0x00000001 << 17)
#define TRI_BIT16_1 (0x00000001 << 16)
#define TRI_BIT15_1 (0x00000001 << 15)
#define TRI_BIT14_1 (0x00000001 << 14)
#define TRI_BIT13_1 (0x00000001 << 13)
#define TRI_BIT12_1 (0x00000001 << 12)
#define TRI_BIT11_1 (0x00000001 << 11)
#define TRI_BIT10_1 (0x00000001 << 10)
#define TRI_BIT09_1 (0x00000001 << 9)
#define TRI_BIT08_1 (0x00000001 << 8)
#define TRI_BIT07_1 (0x00000001 << 7)
#define TRI_BIT06_1 (0x00000001 << 6)
#define TRI_BIT05_1 (0x00000001 << 5)
#define TRI_BIT04_1 (0x00000001 << 4)
#define TRI_BIT03_1 (0x00000001 << 3)
#define TRI_BIT02_1 (0x00000001 << 2)
#define TRI_BIT01_1 (0x00000001 << 1)
#define TRI_BIT00_1 0x00000001

#define TRI_BIT31_0 (~TRI_BIT31_1)
#define TRI_BIT30_0 (~TRI_BIT30_1)
#define TRI_BIT29_0 (~TRI_BIT29_1)
#define TRI_BIT28_0 (~TRI_BIT28_1)
#define TRI_BIT27_0 (~TRI_BIT27_1)
#define TRI_BIT26_0 (~TRI_BIT26_1)
#define TRI_BIT25_0 (~TRI_BIT25_1)
#define TRI_BIT24_0 (~TRI_BIT24_1)
#define TRI_BIT23_0 (~TRI_BIT23_1)
#define TRI_BIT22_0 (~TRI_BIT22_1)
#define TRI_BIT21_0 (~TRI_BIT21_1)
#define TRI_BIT20_0 (~TRI_BIT20_1)
#define TRI_BIT19_0 (~TRI_BIT19_1)
#define TRI_BIT18_0 (~TRI_BIT18_1)
#define TRI_BIT17_0 (~TRI_BIT17_1)
#define TRI_BIT16_0 (~TRI_BIT16_1)
#define TRI_BIT15_0 (~TRI_BIT15_1)
#define TRI_BIT14_0 (~TRI_BIT14_1)
#define TRI_BIT13_0 (~TRI_BIT13_1)
#define TRI_BIT12_0 (~TRI_BIT12_1)
#define TRI_BIT11_0 (~TRI_BIT11_1)
#define TRI_BIT10_0 (~TRI_BIT10_1)
#define TRI_BIT09_0 (~TRI_BIT09_1)
#define TRI_BIT08_0 (~TRI_BIT08_1)
#define TRI_BIT07_0 (~TRI_BIT07_1)
#define TRI_BIT06_0 (~TRI_BIT06_1)
#define TRI_BIT05_0 (~TRI_BIT05_1)
#define TRI_BIT04_0 (~TRI_BIT04_1)
#define TRI_BIT03_0 (~TRI_BIT03_1)
#define TRI_BIT02_0 (~TRI_BIT02_1)
#define TRI_BIT01_0 (~TRI_BIT01_1)
#define TRI_BIT00_0 (~TRI_BIT00_1)

/* 定义的变量，用于设置bit掩码 */
#define TRI_BITMASK_LOW01 0x00000001
#define TRI_BITMASK_LOW02 0x00000003
#define TRI_BITMASK_LOW03 0x00000007
#define TRI_BITMASK_LOW04 0x0000000f
#define TRI_BITMASK_LOW05 0x0000001f
#define TRI_BITMASK_LOW06 0x0000003f
#define TRI_BITMASK_LOW07 0x0000007f
#define TRI_BITMASK_LOW08 0x000000ff
#define TRI_BITMASK_LOW09 0x000001ff
#define TRI_BITMASK_LOW10 0x000003ff
#define TRI_BITMASK_LOW11 0x000007ff
#define TRI_BITMASK_LOW12 0x00000fff
#define TRI_BITMASK_LOW14 0x00003fff
#define TRI_BITMASK_LOW15 0x00007fff
#define TRI_BITMASK_LOW16 0x0000ffff
#define TRI_BITMASK_LOW18 0x0003ffff
#define TRI_BITMASK_LOW20 0x000fffff
#define TRI_BITMASK_LOW22 0x003fffff
#define TRI_BITMASK_LOW24 0x00ffffff
#define TRI_BITMASK_LOW28 0x0fffffff
#define TRI_BITMASK_LOW30 0x3fffffff
#define TRI_BITMASK_LOW31 0x7fffffff
#define TRI_BITMASK_LOW32 0xffffffff

#define tri_reg_write(addr, val) \
	(*(volatile uintptr_t*)(uintptr_t)(addr) = (val))
#define tri_reg_read(addr, val) \
	((val) = *(volatile uintptr_t*)(uintptr_t)(addr))

/* 1:单BIT 操作 */
#define tri_bit_get(reg, bit) ((((reg) & (bit)) == 0) ? 0 : 1)
#define tri_bit_set(reg, bit) ((reg) |= (bit))
#define tri_bit_clr(reg, bit) ((reg) &= (~(bit)))

/* val bit 为 1 被 设置为 1 */
static inline tri_void tri_reg_rw_set_mask(tri_uint32 addr,
	tri_uint32 val, tri_uint32 mask)
{
	tri_uint32 data;
	tri_reg_read(addr, data);
	tri_reg_write(addr, (data & (~(mask))) | (val));
}

static inline tri_void tri_reg_rw_set(tri_uint32 addr, tri_uint32 val)
{
	tri_uint32 data;
	tri_reg_read(addr, data);
	tri_reg_write(addr, (data | (val)));
}

static inline tri_void tri_reg_rw_clr(tri_uint32 addr, tri_uint32 val)
{
	tri_uint32 data;
	tri_reg_read(addr, data);
	tri_reg_write(addr, data &(~(val)));
}

static inline tri_void tri_reg_rw_set_bit(tri_uint32 addr, tri_uint32 bit)
{
	tri_uint32 data;
	tri_reg_read(addr, data);
	tri_reg_write(addr, data | (1 << (bit)));
}

static inline tri_void tri_reg_rw_clr_bit(tri_uint32 addr, tri_uint32 bit)
{
	tri_uint32 data;
	tri_reg_read(addr, data);
	tri_reg_write(addr, data &(~(1 << (bit))));
}

#endif /* __TRI_REGISTER_H__ */