/*
 */

#ifndef __TRI_HASH_H__
#define __TRI_HASH_H__

struct tri_hash_head_s {
	tri_uint32 hashsize;
	tri_uint32 currnum;
	tri_void *matchcallback;
	tri_void *comparecallback;
	tri_void *freekeycallback;
	tri_void *freedatacallback;
	tri_void *hashitems;
};

struct tri_hash_item_s {
	struct tri_list_head listhead;
	tri_void *keyobject;
	tri_void *dataobject;
};

/* 根据关键字key计算HASH索引值,输入关键字返回HASH索引 */
typedef tri_uint32 (*tri_hash_matchcallback)(tri_void *keyobject);

/* 相等返回0:TRI_RET_SUCC 否则非0 */
typedef tri_uint32 (*tri_hash_comparecallback)(tri_void *keyobject1,
					     tri_void *keyobject2);

typedef tri_void (*tri_hash_freecallback)(tri_void *object);

typedef tri_void (*tri_hash_dump_displaycallback)(tri_uint32 indx,
						tri_uint32 conflictindx,
						tri_void *key, tri_void *data);

typedef tri_void (*tri_hash_dump_single_callback)(tri_void *data, tri_uint32 *data1,
						tri_uint32 *data2);

typedef tri_void (*tri_hash_dump_sum_callback)(tri_uint32 indx,
					     tri_uint32 conflictindx,
					     tri_uint32 data1, tri_uint32 data2);

tri_uint32 tri_hash_init(tri_uint32 hashsize, tri_void **hashtable,
		       tri_void *matchcallback, tri_void *comparecallback,
		       tri_void *freekeycallback,
		       tri_void *freedatacallback);

tri_uint32 tri_hash_free(tri_void **hashtable);

tri_uint32 tri_hash_insert(struct tri_hash_head_s *hashtable, tri_void *keyobject,
			 tri_void *dataobject);

tri_uint32 tri_hash_remove(struct tri_hash_head_s *hashtable, tri_void *keyobject);

tri_uint32 tri_hash_find(struct tri_hash_head_s *hashtable, tri_void *keyobject,
		       tri_void **dataobject);

tri_uint32 tri_hash_dump(tri_void *hashtable);

tri_uint32 tri_hash_dump_display(tri_void *hashtable,
			       const tri_void *callback);

tri_uint32 tri_hash_dump_pos_display(const tri_void *hashtable,
				   const tri_void *callback,
				   const tri_void *sum_callback,
				   const tri_void *single_callback,
				   tri_uint32 start_pos,
				   tri_uint32 end_pos);

tri_uint32 tri_hash_fastfind(struct tri_hash_head_s *hashtable, tri_void *keyobject,
			   tri_void **dataobject);

#endif /* __TRI_HASH_H__ */