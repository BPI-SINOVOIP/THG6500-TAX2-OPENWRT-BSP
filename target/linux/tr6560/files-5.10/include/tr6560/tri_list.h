/*
 */

#ifndef __TRI_LIST_H__
#define __TRI_LIST_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**************************List Function**************************/
struct tri_list_head {
	struct tri_list_head *next, *prev;
};

#define tri_list_init_head(ptr) \
	do { \
		(ptr)->next = (ptr); \
		(ptr)->prev = (ptr); \
	} while (0)

#define tri_list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define tri_list_for_each_safe_init(pos, n, head, cur) \
	for (pos = (cur)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define tri_list_for_each_safe_reverse(pos, n, head) \
	for (pos = (head)->prev, n = pos->prev; pos != (head); \
		pos = n, n = pos->prev)

#define tri_offsetof(type, member) ((tri_uint32) & ((type *)0)->member)

#define tri_list_entry(ptr, type, member) ({ \
		const typeof(((type *)0)->member) *__mptr = (ptr); \
		(type *)((char *)__mptr - tri_offsetof(type, member)); })

#define tri_list_getnext(head) ((head != (head)->next) ? \
		((head)->next) : (TRI_NULL))

#define tri_list_getprev(head) ((head != (head)->prev) ? \
		((head)->prev) : (TRI_NULL))

#define tri_list_for_each_entry(pos, head, member) \
	for (pos = tri_list_entry((head)->next, typeof(*pos), member); \
		&pos->member != (head); \
		pos = tri_list_entry(pos->member.next, typeof(*pos), member))

#define tri_list_for_each_entry_safe(pos, n, head, member) \
	for (pos = tri_list_entry((head)->next, typeof(*pos), member), \
		n = tri_list_entry(pos->member.next, typeof(*pos), member); \
		&pos->member != (head); \
		pos = n, n = tri_list_entry(n->member.next, typeof(*n), member))

#define tri_list_for_each_entry_reverse(pos, head, member) \
	for (pos = tri_list_entry((head)->prev, typeof(*pos), member); \
		&pos->member != (head); \
		pos = tri_list_entry(pos->member.prev, typeof(*pos), member))

#define tri_list_for_each_entry_reverse_safe(pos, n, head, member) \
	for (pos = tri_list_entry((head)->prev, typeof(*pos), member), \
		n = tri_list_entry(pos->member.prev, typeof(*pos), member); \
		&pos->member != (head); \
		pos = n, n = tri_list_entry(n->member.prev, typeof(*n), member))

#define tri_list_for_each_entry_continue(pos, head, member) \
	for (pos = tri_list_entry(pos->member.next, typeof(*pos), member); \
		&pos->member != (head); \
		pos = tri_list_entry(pos->member.next, typeof(*pos), member))

#define tri_list_for_each_entry_continue_reverse(pos, head, member) \
	do { \
		for (pos = tri_list_entry(pos->member.prev, \
			typeof(*pos), member); \
			&pos->member != (head); \
			pos = tri_list_entry(pos->member.prev, \
				typeof(*pos), member)) \
	} while (0)



static inline int tri_list_is_last(struct tri_list_head *list,
	struct tri_list_head *head)
{
	return list->next == head;
}

static inline void __tri_list_add(struct tri_list_head *newlist,
	struct tri_list_head *prev,
	struct tri_list_head *next)
{
	next->prev = newlist;
	newlist->next = next;
	newlist->prev = prev;
	prev->next = newlist;
}

static inline void tri_list_add(struct tri_list_head *newlist,
	struct tri_list_head *head)
{
	__tri_list_add(newlist, head, head->next);
}

static inline void tri_list_add_tail(struct tri_list_head *newlist,
	struct tri_list_head *head)
{
	__tri_list_add(newlist, head->prev, head);
}

static inline void __tri_list_del(struct tri_list_head *prev,
	struct tri_list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void tri_list_del(struct tri_list_head *entry)
{
	__tri_list_del(entry->prev, entry->next);
	entry->next = TRI_NULL;
	entry->prev = TRI_NULL;
}

static inline int tri_list_empty(struct tri_list_head *head)
{
	return head->next == head;
}

static inline int tri_list_hang(struct tri_list_head *entry)
{
	return ((entry->prev != TRI_NULL) && (entry->next != TRI_NULL));
}

static inline tri_void tri_list_insert(struct tri_list_head *cur,
	struct tri_list_head *newlist)
{
	cur->prev->next = newlist;
	newlist->next = cur;
	newlist->prev = cur->prev;
	cur->prev = newlist;
}

static inline tri_void tri_list_insert_after(struct tri_list_head *cur,
	struct tri_list_head *newlist)
{
	cur->next->prev = newlist;
	newlist->next = cur->next;
	newlist->prev = cur;
	cur->next = newlist;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TRI_LIST_H__ */
