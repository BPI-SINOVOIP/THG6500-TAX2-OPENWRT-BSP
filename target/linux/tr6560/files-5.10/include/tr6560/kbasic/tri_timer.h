/*
 */

#ifndef __TRI_TIMER_H__
#define __TRI_TIMER_H__

typedef tri_void (*tri_timer_func)(struct timer_list *timer);

tri_void tri_timer_stop(struct timer_list *timer);

tri_void tri_timer_start(struct timer_list *timer, tri_timer_func func);

tri_void tri_timer_init(struct timer_list *timer, tri_uint32 timeout);

tri_void tri_timer_set_nexttimeout(struct timer_list *timer, tri_uint32 timeout,
				 tri_uint32 mintime);

#endif /* __TRI_TIMER_H__ */
