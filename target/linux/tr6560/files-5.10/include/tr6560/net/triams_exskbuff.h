#ifndef __LINUX_AMS_EXSKBUFF_H
#define __LINUX_AMS_EXSKBUFF_H

#include <linux/skbuff.h>

#define SKB_PRIVATE_SIZE 128

struct triams_exsk_buf {
	char chip_cb[80];
	struct nf_conntrack *nfct_ppp;
	unsigned int br_acc_flag;
};

/* skbuff_head_cache : skb + private data */
/* skbuff_fclone_cache : skb1 + skb2 + atomic_t + skb1 private + skb2 private */
static inline char *get_exsk_buf_pos(const struct sk_buff *skb)
{
	if (likely(skb->fclone == SKB_FCLONE_UNAVAILABLE))
		return (char *)(skb + 1);
	else if (skb->fclone == SKB_FCLONE_ORIG)
		return (char*)skb + sizeof(struct sk_buff_fclones);
	else if (skb->fclone == SKB_FCLONE_CLONE)
		return (char*)(skb + 1) + sizeof(atomic_t) + SKB_PRIVATE_SIZE;

	return (char *)(skb + 1);
}

#define EXT_SKB_MEM(skb, mem) \
	(((struct triams_exsk_buf*)get_exsk_buf_pos(skb))->mem)

#endif /* __LINUX_AMS_EXSKBUFF_H */
