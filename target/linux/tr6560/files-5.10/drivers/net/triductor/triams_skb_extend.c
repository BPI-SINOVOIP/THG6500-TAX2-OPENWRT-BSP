#include <tr6560/net/triams_exskbuff.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netfilter/nf_conntrack_common.h>

static void skb_priv_extend_copy(struct sk_buff *new, const struct sk_buff *old)
{
	if ((new == NULL) || (old == NULL))
		return;

	nf_conntrack_get(EXT_SKB_MEM(old, nfct_ppp));
	EXT_SKB_MEM(new, nfct_ppp) = EXT_SKB_MEM(old, nfct_ppp);
	EXT_SKB_MEM(new, br_acc_flag) = EXT_SKB_MEM(old, br_acc_flag);
	memcpy(EXT_SKB_MEM(new, chip_cb), EXT_SKB_MEM(old, chip_cb),
		sizeof(EXT_SKB_MEM(old, chip_cb)));
}

static int skb_priv_extend_free(struct sk_buff *skb)
{
	if (skb)
		nf_conntrack_put(EXT_SKB_MEM(skb, nfct_ppp));
	return 1;
}

void rtos_skb_extend_init(void)
{
	skb_priv_copy = skb_priv_extend_copy;
	wifipktfree = skb_priv_extend_free;
}


