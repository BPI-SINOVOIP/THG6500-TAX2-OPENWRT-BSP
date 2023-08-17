/*triductor dual image design*/
#ifndef __OFPART_TRI_PARTITIONS_H
#define __OFPART_TRI_PARTITIONS_H

#ifdef CONFIG_MTD_TRIDUCTOR_NAND
int tr6560_partitions_post_parse(struct mtd_info *mtd, struct mtd_partition *parts, int nr_parts);
#else
static inline int tr6560_partitions_post_parse(struct mtd_info *mtd, struct mtd_partition *parts,
						int nr_parts)
{
	return -EOPNOTSUPP;
}
#endif

#endif
