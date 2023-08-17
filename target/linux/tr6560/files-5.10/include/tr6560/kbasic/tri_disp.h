/*
 */

#ifndef __TRI_DISP_H__
#define __TRI_DISP_H__

#define TRI_DISP_TBL_NAME_LEN 16
#define TRI_DISP_COL_NAME_LEN 16
#define TRI_DISP_ID_WIDTH 6

#define TRI_DISP_MAX_ROW_WIDTH 132
#define TRI_DISP_MAX_COL_WIDTH 64
/* 加两个空格和一个'\0' */
#define TRI_DISP_MAX_COL_DATA_WIDTH (TRI_DISP_MAX_COL_WIDTH + 3)

#define tri_disp_systrace(ret, arg1, arg2, arg3, arg4) \
	tri_systrace(TRI_SRCMODULE_KBASIC_DISP, ret, arg1, arg2, arg3, arg4)
#define tri_disp_debug(level, fmt, arg...) \
	tri_debug(TRI_SRCMODULE_KBASIC_DISP, level, fmt, ##arg)

/* 判断行数据是否有效 */
typedef tri_uint32 (*tri_disp_check_valid)(tri_uint32 row_addr, tri_uchar8 *valid);

/* 当数据源是结构体链表时,获取下一个结构体节点的地址 */
typedef tri_uint32 (*tri_disp_get_next_node)(tri_handle head_addr,
					   tri_handle cur_addr,
					   tri_handle *next_addr);

/* 列的显示格式 */
enum tri_disp_fmt_e {
	TRI_DISP_FMT_HEX_U8_E,      /* 数据源是1Byte */
	TRI_DISP_FMT_HEX_U16_E,     /* 数据源是2Byte */
	TRI_DISP_FMT_HEX_U32_E,     /* 数据源是4Byte */
	TRI_DISP_FMT_DECIMAL_U8_E,  /* 数据源是1Byte */
	TRI_DISP_FMT_DECIMAL_U16_E, /* 数据源是2Byte */
	TRI_DISP_FMT_DECIMAL_U32_E, /* 数据源是4Byte */
	TRI_DISP_FMT_IPV4_E,        /* 数据源是4Byte */
	TRI_DISP_FMT_IPV6_E,        /* 数据源是16Byte */
	TRI_DISP_FMT_MAC_E,         /* 数据源是6Byte */
	TRI_DISP_FMT_CHAR16_E,      /* 数据源是16Byte字符 */
	TRI_DISP_FMT_STRING_E,      /* 数据源是4Byte */
	TRI_DISP_FMT_MAX_E,         /* 无效 */
};

/* 列显示对齐方式 */
enum tri_disp_align_e {
	TRI_DISP_ALIGN_LEFT_E,
	TRI_DISP_ALIGN_MIDDLE_E,
	TRI_DISP_ALIGN_RIGHT_E,
};

/* 数据来源 */
enum tri_disp_data_src_e {
	TRI_DISP_SRC_MEM_ADDR_E,  /* 从内存地址获取 */
	TRI_DISP_SRC_ST_ARRAY_E,  /* 从struct数组获取 */
	TRI_DISP_SRC_ST_CHAIN_E,  /* 从struct链表获取 */
	TRI_DISP_SRC_REG_ADDR_E,  /* 从寄存器地址获取 */
	TRI_DISP_SRC_REG_ARRAY_E, /* 从寄存器数组或表项获取 */
};

struct tri_disp_st_array_base_s {
	uintptr_t base;            /* 结构体数组的基址 */
	tri_ushort16 size;          /* 结构体大小 */
	tri_ushort16 total;         /* 记录总条数 */
	tri_disp_check_valid check; /* 数据有效性判断方法,默认为NULL */
};

struct tri_disp_st_chain_base_s {
	tri_uint32 base;                 /* 链表头节点的内存地址 */
	tri_ushort16 size;               /* 结构体大小 */
	tri_ushort16 resv;
	tri_disp_check_valid check;      /* 数据有效性判断方法,默认为NULL */
	tri_disp_get_next_node get_next; /* 获取下一个节点的方法 */
};

struct tri_disp_reg_base_s {
	tri_uint32 base;            /* 寄存器表项基址 */
	tri_ushort16 width;         /* 寄存器宽度 */
	tri_ushort16 total;         /* 记录总条数 */
	tri_disp_check_valid check; /* 数据有效性判断方法,默认为NULL */
};

struct tri_disp_reg_field_s {
	tri_uchar8 bit_start; /* 字段起始bit */
	tri_uchar8 bit_end;   /* 字段截止bit */
};

/* 列信息 */
struct tri_disp_column_s {
	struct tri_list_head list;                 /* 字段链表 */
	tri_uchar8 name[TRI_DISP_COL_NAME_LEN + 1]; /* 字段名 */
	tri_uchar8 fmt;                            /* 数据显示格式 */
	tri_uchar8 align;                          /* 显示对齐方式 */
	tri_uchar8 width;                          /* 用户指定列宽度 */

	union {
		tri_ushort16 member_offset;            /* 结构体成员偏移字节 */
		uintptr_t memory_addr;                /* 内存地址 */
		tri_uint32 reg_addr;                   /* 寄存器地址 */
		struct tri_disp_reg_field_s reg_field; /* 寄存器bit范围 */
	};

};

/* 表信息 */
struct tri_disp_table_s {
	struct tri_list_head list;
	tri_uchar8 name[TRI_DISP_TBL_NAME_LEN + 1]; /* 表名 */
	tri_uchar8 col_sum;                        /* 列总数 */
	tri_uchar8 src;                            /* 数据获取来源 */
	struct tri_list_head col_list;             /* 所有列信息 */

	/* 横表有效 */
	union {
		/* 内存结构体数组基址信息 */
		struct tri_disp_st_array_base_s array_base;
		/* 内存结构体链表基址信息 */
		struct tri_disp_st_chain_base_s chain_base;
		/* 寄存器表项基址信息 */
		struct tri_disp_reg_base_s reg_base;
	};
};

struct tri_disp_create_table_s {
	tri_uchar8 *tbl_name;
	tri_uint32 total;
	enum tri_disp_data_src_e src;
	tri_uint32 base;
	tri_uint32 size;
	tri_disp_get_next_node get_next;
	tri_disp_check_valid check;
};

struct tri_disp_insert_column_s {
	tri_uchar8 *tbl_name;
	tri_uchar8 *col_name;
	enum tri_disp_fmt_e fmt;
	enum tri_disp_align_e align;
	tri_uint32 col_width;
	tri_uint32 data_addr;
	tri_uint32 bit_end;
};

/* 全局变量 */
struct tri_list_head *tri_disp_get_next_list(tri_void);

tri_int32 tri_disp_is_empty_list(tri_void);

/* 插入列 */
tri_uint32 tri_disp_insert_column(struct tri_disp_insert_column_s *column);

/* 删除表 */
tri_uint32 tri_disp_delete_table_by_name(tri_uchar8 *tbl);

/* 查询表 */
tri_uint32 tri_disp_find_tbl(tri_uchar8 *tbl_name, struct tri_disp_table_s **tbl);

#ifdef __MEM_ADDR
#endif
/* 创建表,数据为一维散列数据,直接从内存地址取值. */
tri_uint32 tri_disp_create_mem_addr_table(tri_uchar8 *tbl);

/* 插入列 */
tri_uint32 tri_disp_insert_mem_addr_column(tri_uchar8 *tbl, tri_uchar8 *col,
					 enum tri_disp_fmt_e fmt,
					 tri_uint32 addr);

/* 创建表,数据为二维表单,从结构体数组取值 */
tri_uint32 tri_disp_create_st_array_table(tri_uchar8 *tbl, tri_uint32 total,
					tri_uint32 base, tri_uint32 size,
					tri_disp_check_valid check);

/* 插入列 */
tri_uint32 tri_disp_insert_st_array_column(tri_uchar8 *tbl, tri_uchar8 *col,
					 enum tri_disp_fmt_e fmt,
					 tri_uint32 offset);

/* 创建表,数据为二维表单,从结构体链表取值 */
tri_uint32 tri_disp_create_st_chain_table(tri_uchar8 *tbl,
					tri_uint32 head_addr,
					tri_uint32 size,
					tri_disp_get_next_node get_next,
					tri_disp_check_valid check);

/* 插入列 */
tri_uint32 tri_disp_insert_st_chain_column(tri_uchar8 *tbl, tri_uchar8 *col,
					 enum tri_disp_fmt_e fmt,
					 tri_uint32 offset);

/* 创建表,数据为一维散列数据,直接从寄存器地址取值. */
tri_uint32 tri_disp_create_reg_addr_table(tri_uchar8 *tbl);

/* 插入寄存器数据列 */
tri_uint32 tri_disp_insert_reg_addr_column(tri_uchar8 *tbl, tri_uchar8 *col,
					 enum tri_disp_fmt_e fmt,
					 tri_uint32 addr);

/* 创建表,数据为二维表单,从表项寄存器或者寄存数组中取值 */
tri_uint32 tri_disp_create_reg_array_table(tri_uchar8 *tbl, tri_uint32 total,
					 tri_uint32 base, tri_uint32 size,
					 tri_disp_check_valid check);

/* 插入寄存器数据列 */
tri_uint32 tri_disp_insert_reg_array_column(tri_uchar8 *tbl, tri_uchar8 *col,
					  enum tri_disp_fmt_e fmt,
					  tri_uint32 bit_start,
					  tri_uint32 bit_end);

/* 导出表格数据到终端显示 */
tri_uint32 tri_disp_dump_table_data_by_name(tri_uchar8 *tbl);

/* 导出表格数据到终端显示 */
tri_uint32 tri_disp_dump_table_data_by_handle(struct tri_disp_table_s *tbl);

/* disp模块初始化 */
tri_uint32 tri_disp_init(tri_void);

/* disp模块初始化 */
tri_void tri_disp_exit(tri_void);

#endif /* __TRI_DISP_H__ */