/*
 */

#ifndef __TRI_CFE_BR_CMD_H__
#define __TRI_CFE_BR_CMD_H__

#ifndef TRI_HW_INTF_NAME_MAXLEN
#define TRI_HW_INTF_NAME_MAXLEN 16
#endif

struct tri_cfe_intf_basicinfo_s {
	tri_char8 fatherif[TRI_HW_INTF_NAME_MAXLEN];
	tri_char8 subif[TRI_HW_INTF_NAME_MAXLEN];
};

struct tri_cfe_intf_addrootif_cmd_s {
	struct tri_cfe_intf_basicinfo_s basicinfo;
	tri_uint32 porttype; /* 类型是tri_cfe_phyport_type_e */
	tri_uint32 phyport;  /* 类型是tri_hal_port_e */
	tri_uint32 defvlan;  /* 端口默认vlan */
	tri_uint32 defpri;   /* 端口默认优先级 */
	tri_uint32 chn;
};

struct tri_cfe_intf_activeif_cmd_s {
	tri_char8 ifname[TRI_HW_INTF_NAME_MAXLEN];
};

struct tri_cfe_intf_addsubif_cmd_s {
	struct tri_cfe_intf_basicinfo_s basicinfo;
	tri_uint32 mapmode;   /* 目前只支持vlan匹配模式 */
	tri_uint32 matchmode; /* 预留域暂时不起作用 */
	tri_ushort16 vid;     /* 与父节点VID映射的key */
	tri_uint32 vid_flag;  /* 用户指定vlan: 1 不指定: 0 */
	tri_ushort16 pri;
};

struct tri_res_intf_relateif_cmd_s {
	struct tri_cfe_intf_basicinfo_s basicinfo;
};

struct tri_cfe_intf_configattr_s {
	tri_char8 ifname[TRI_HW_INTF_NAME_MAXLEN];
	tri_uchar8 attr[128];
};

struct tri_cfe_intf_br_dump_s {
	tri_char8 ifname[TRI_HW_INTF_NAME_MAXLEN];
	tri_uint32 allflag;
};

#endif /* __TRI_CFE_CMD_BR_H__ */