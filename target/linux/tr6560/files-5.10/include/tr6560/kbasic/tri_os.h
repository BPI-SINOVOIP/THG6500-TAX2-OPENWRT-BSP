/*
 */

#ifndef __TRI_OS_H__
#define __TRI_OS_H__

#define TRI_GFP_ATOMIC               GFP_ATOMIC
#define TRI_CLONE_KERNEL             CLONE_KERNEL
#define TRI_SIGKILL                  SIGKILL
#define TRI_TASK_INTERRUPTIBLE       TASK_INTERRUPTIBLE
#define TRI_TASK_UNINTERRUPTIBLE     TASK_UNINTERRUPTIBLE

#define TRI_CHECKSUM_PARTIAL         CHECKSUM_PARTIAL
#define TRI_EINTR                    (-EINTR)

#define TRI_DECIMALISM               10

#define tri_ker_readb(reg) (*((volatile tri_uchar8 *)(reg)))
#define tri_ker_readw(reg) (*((volatile tri_ushort16 *)(reg)))
#define tri_ker_readdw(reg) (*((volatile tri_uint32 *)(reg)))

#define tri_ker_writeb(data, reg) (*((volatile tri_uchar8 *)(reg)) = (data))
#define tri_ker_writew(data, reg) (*((volatile tri_ushort16 *)(reg)) = (data))
#define tri_ker_writedw(data, reg) (*((volatile tri_uint32 *)(reg)) = (data))

/* os marco defined */
#define tri_va_list   va_list
#define tri_va_start  va_start
#define tri_va_end    va_end

/* os function */
#define tri_malloc(size)    kmalloc(size, TRI_GFP_ATOMIC)
#define tri_dmamalloc(size) kmalloc(size, GFP_DMA)
#define tri_kmalloc         kmalloc
#define tri_sg_page         sg_page

#define tri_virt_to_dma         virt_to_dma
#define tri_dma_to_virt         dma_to_virt
#define tri_free                kfree
#define tri_memcmp              memcmp
#define tri_kernelkmalloc(size) kmalloc(size, GFP_KERNEL)
#define tri_dma_addr_t          dma_addr_t
#define tri_strcmp            strcmp
#define tri_strncmp           strncmp
#define tri_strlen            strlen
#define tri_strsep            strsep
#define tri_printk            printk
#define tri_simple_strtoul    simple_strtoul
#define tri_copy_from_user    copy_from_user
#define tri_copy_to_user      copy_to_user

#define tri_lower lower

#define tri_jhash       jhash
#define tri_jhash2      jhash2
#define tri_jhash_1word jhash_1word
#define tri_jhash_2word jhash_2word
#define tri_jhash_3word jhash_3word

#define tri_create_proc_entry create_proc_entry
#define tri_remove_proc_entry remove_proc_entry
#define tri_proc_dir_entry struct proc_dir_entry
#define tri_proc_create proc_create

#define tri_misc_register              misc_register
#define tri_misc_deregister            misc_deregister
#define tri_register_module_notifier   register_module_notifier
#define tri_unregister_module_notifier unregister_module_notifier
#define tri_notifier_block             struct notifier_block
#define tri_module                     struct module
#define tri_khal_symbol                struct kernel_symbol

#define tri_thread    kernel_thread
#define tri_kill_proc kill_pid
#define tri_daemonize daemonize

#define tri_get_random_bytes get_random_bytes
#define tri_wmb wmb

#define tri_schedule_timeout  schedule_timeout

#define tri_timer_list        struct timer_list
#define tri_add_timer         add_timer
#define tri_del_timer         del_timer
#define tri_del_timer_sync    del_timer_sync
#define tri_timer_pending     timer_pending
#define tri_mod_timer         mod_timer

#define tri_time_after_eq     time_after_eq
#define tri_time_before       time_before
#define tri_msecs_to_jiffies  msecs_to_jiffies

#define tri_jiffies           jiffies
#define tri_udelay            udelay
#define tri_mdelay            mdelay
#define tri_msleep            msleep

#define tri_wait_queue_head_t                    wait_queue_head_t
#define tri_init_waitqueue_head                  init_waitqueue_head
#define tri_wait_event_interruptible             wait_event_interruptible
#define tri_wait_event_interruptible_timeout     wait_event_interruptible_timeout
#define tri_wake_up_interruptible                wake_up_interruptible

#define tri_spinlock_t                   spinlock_t
#define tri_spin_lock_init               spin_lock_init
#define tri_spin_lock                    spin_lock
#define tri_spin_unlock                  spin_unlock
#define tri_spin_lock_irq                spin_lock_irq
#define tri_spin_unlock_irq              spin_unlock_irq
#define tri_spin_lock_irqsave            spin_lock_irqsave
#define tri_spin_unlock_irqrestore       spin_unlock_irqrestore
#define tri_spin_lock_bh                 spin_lock_bh
#define tri_spin_unlock_bh               spin_unlock_bh
#define tri_local_irq_enable             local_irq_enable
#define tri_local_irq_disable            local_irq_disable
#define tri_local_bh_enable              local_bh_enable
#define tri_local_bh_disable             local_bh_disable
#define tri_disable_irq                  disable_irq
#define tri_enable_irq                   enable_irq

#define tri_sockaddr              struct sockaddr
#define tri_packet_type_s         struct packet_type
#define tri_sk_buff_s             struct sk_buff
#define tri_dev_alloc_skb         dev_alloc_skb
#define tri_dev_kfree_skb_any     dev_kfree_skb_any
#define tri_skb_copy              skb_copy
#define tri_skb_recycle_check     skb_recycle_check
#define tri_skb_clone             skb_clone
#define tri_skb_cloned            skb_cloned
#define tri_skb_shared            skb_shared
#define tri_skb_headroom          skb_headroom
#define tri_skb_push              skb_push
#define tri_skb_reserve           skb_reserve
#define tri_skb_put               skb_put
#define tri_skb_pull              skb_pull
#define tri_skb_get               skb_get
#define tri_kfree_skb             kfree_skb
#define tri_dev_kfree_skb         dev_kfree_skb
#define tri_eth_type_trans        eth_type_trans
#define tri_netdev_alloc_skb_ip_align netdev_alloc_skb_ip_align
#define tri_skb_shinfo            skb_shinfo
#define tri_skb_copy_expand       skb_copy_expand

#define tri_dev_add_pack          dev_add_pack
#define tri_dev_remove_pack       dev_remove_pack

#define tri_device_s              struct device
#define tri_set_dma_ops           set_dma_ops
#define tri_dma_set_mask          dma_set_mask
#define tri_dma_set_coherent_mask dma_set_coherent_mask

#define tri_dma_map_single        dma_map_single
#define tri_dma_unmap_single      dma_unmap_single
#define tri_dma_unmap_page        dma_unmap_page
#define tri_dma_alloc_coherent    dma_alloc_coherent
#define tri_dma_free_coherent     dma_free_coherent
#define tri_dma_mapping_error     dma_mapping_error

#define tri_net_device_s           struct net_device
#define tri_net_device_stats_s     struct net_device_stats
#define tri_net_device_ops         struct net_device_ops
#define tri_netdev_notifier_info_s struct netdev_notifier_info
#define tri_net_bridge_fdb_entry_s struct net_bridge_fdb_entry

#define tri_ifreq_s                 struct ifreq
#define tri_netdev_priv             netdev_priv
#define tri_netif_rx                netif_rx
#define tri_netif_receive_skb       netif_receive_skb
#define tri_netif_tx_disable        netif_tx_disable
#define tri_netif_start_queue       netif_start_queue
#define tri_netif_queue_stopped     netif_queue_stopped
#define tri_netif_wake_queue        netif_wake_queue
#define tri_netif_rx_schedule_prep  netif_rx_schedule_prep
#define tri_netif_rx_schedule       __netif_rx_schedule
#define tri_crypto_ahash_digestsize crypto_ahash_digestsize
#define tri_crypto_ahash_reqtfm     crypto_ahash_reqtfm
#define tri_scatterwalk_sg_next     scatterwalk_sg_next
#define tri_scatterwalk_map_and_copy scatterwalk_map_and_copy

#if (LINUX_VERSION_CODE > KERNEL_VERSION(3, 18, 0))
#define tri_alloc_netdev_mq(sizeof_priv, name, setup, count) \
	alloc_netdev_mq(sizeof_priv, name, NET_NAME_UNKNOWN, setup, count)
#define tri_alloc_netdev(sizeof_priv, name, setup) \
	alloc_netdev(sizeof_priv, name, NET_NAME_UNKNOWN, setup)
#else
#define tri_alloc_netdev_mq       alloc_netdev_mq
#define tri_alloc_netdev          alloc_netdev
#endif

#define tri_alloc_etherdev        alloc_etherdev
#define tri_ether_setup           ether_setup
#define tri_register_netdevice    register_netdevice
#define tri_unregister_netdev     unregister_netdev
#define tri_free_netdev           free_netdev
#define tri_rtnl_trylock          rtnl_trylock
#define tri_ioremap               ioremap
#define tri_iounmap               iounmap

#define TRI_SA_SHIRQ              IRQF_SHARED

#if (LINUX_VERSION_CODE > KERNEL_VERSION(3, 19, 0))
#define TRI_IRQF_DISABLED         0
#else
#define TRI_IRQF_DISABLED         IRQF_DISABLED
#endif

#define TRI_IRQ_HANDLED           IRQ_HANDLED
#define TRI_IRQ_NONE              IRQ_NONE
#define TRI_KM_SOFTIRQ0           KM_SOFTIRQ0
#define TRI_KM_SOFTIRQ1           KM_SOFTIRQ1
#define TRI_EPERM                 EPERM
#define TRI_EINVAL                EINVAL
#define TRI_EIO                   EIO
#define TRI_ENOMEM                ENOMEM
#define TRI_EBUSY                 EBUSY
#define TRI_ENXIO                 ENXIO
#define TRI_ENOTSUPP              ENOTSUPP
#define TRI_EBADMSG               EBADMSG
#define TRI_EUCLEAN               EUCLEAN

#define tri_request_irq           request_irq

#define tri_irq_handler_t         irq_handler_t
#define tri_irqreturn_t           irqreturn_t
#define tri_free_irq              free_irq
#define tri_local_irq_restore     local_irq_restore
#define tri_local_irq_save        local_irq_save

#define tri_tasklet_struct        struct tasklet_struct
#define tri_tasklet_init          tasklet_init
#define tri_tasklet_schedule      tasklet_schedule
#define tri_tasklet_tri_schedule   tasklet_tri_schedule
#define tri_tasklet_kill          tasklet_kill

#define tri_init_mutex(sem)       sema_init(sem, 1)

#define TRI_DMA_BIDIRECTIONAL     DMA_BIDIRECTIONAL
#define TRI_DMA_FROM_DEVICE       DMA_FROM_DEVICE
#define TRI_DMA_TO_DEVICE         DMA_TO_DEVICE
#define tri_dma_mapping_error     dma_mapping_error
#define tri_bus_to_virt           __bus_to_virt
#define tri_virt_to_bus           __virt_to_bus
#define tri_dma_set_mask          dma_set_mask
#define tri_dma_set_coherent_mask dma_set_coherent_mask

#define tri_ndelay                ndelay

#define tri_task_struct           struct task_struct
#define tri_kthread_create        kthread_create
#define tri_kthread_stop          kthread_stop
#define tri_kthread_run           kthread_run
#define tri_kthread_should_stop   kthread_should_stop
#define tri_kthread_bind          kthread_bind
#define tri_schedule              schedule
#define tri_wake_up_process       wake_up_process
#define tri_set_current_state     set_current_state
#define tri_cond_resched          cond_resched
#define tri_task_pid_nr           task_pid_nr
#define tri_current               current

#define tri_likely                likely
#define tri_unlikely              unlikely

#define tri_atomic_t              atomic_t
#define tri_atomic_set            atomic_set
#define tri_atomic_read           atomic_read
#define tri_atomic_inc            atomic_inc
#define tri_atomic_dec            atomic_dec
#define tri_atomic_dec_and_test   atomic_dec_and_test
#define tri_atomic_inc_and_test   atomic_inc_and_test
#define tri_atomic_inc_return     atomic_inc_return
#define tri_atomic_init           ATOMIC_INIT

#define tri_napi_struct           struct napi_struct
#define tri_netif_napi_add        netif_napi_add
#define tri_napi_enable           napi_enable
#define tri_napi_disable          napi_disable
#define tri_napi_schedule_prep    napi_schedule_prep
#define tri_napi_schedule         __napi_schedule
#define tri_napi_complete         napi_complete

#define tri_compare_ether_addr    ether_addr_equal

#define tri_skb_set_network_header   skb_set_network_header
#define tri_skb_reset_network_header skb_reset_network_header

#define tri_skb_dst                  skb_dst
#define tri_dst_entry                struct dst_entry
#define tri_nf_conn                  struct nf_conn
#define tri_nf_conn_help             struct nf_conn_help
#define tri_nfct_help                nfct_help
#define tri_nf_ct_is_dying           nf_ct_is_dying
#define tri_nf_conntrack_tuple_hash  struct nf_conntrack_tuple_hash
#define tri_nf_ct_is_confirmed       nf_ct_is_confirmed
#define tri_nf_ct_get                nf_ct_get
#define tri_nf_ct_ipv6_skip_exthdr   nf_ct_ipv6_skip_exthdr

#define tri_ip_tunnel_s              struct ip_tunnel
#define tri_rtable_s                 struct rtable
#define tri_neighbour_s              struct neighbour

#define tri_csum_replace4            csum_replace4
#define tri_csum_replace2            csum_replace2
#define tri_ip_decrease_ttl          ip_decrease_ttl
#define tri_ip_compute_csum          ip_compute_csum

#define tri_dev_put                  dev_put
#define tri_dev_hold                 dev_hold
#define tri_prefetch                 prefetch

#define tri_semaphore                struct semaphore
#define tri_sema_init                sema_init
#define tri_up                       up
#define tri_down_trylock             down_trylock
#define tri_down_interruptible       down_interruptible

#define tri_rw_semaphore             struct rw_semaphore
#define tri_init_rwsem               init_rwsem
#define tri_up_read                  up_read
#define tri_down_read                down_read
#define tri_up_write                 up_write
#define tri_down_write               down_write
#define tri_down_read_trylock        down_read_trylock
#define tri_down_write_trylock       down_write_trylock

#define tri_thread_stop              kthread_stop
#define tri_thread_should_stop       kthread_should_stop

#define tri_seq_printf               seq_printf


#define tri_register_chrdev     register_chrdev
#define tri_unregister_chrdev   unregister_chrdev

#define tri_wait_event_interruptible_timeout wait_event_interruptible_timeout

#define tri_br_port_get_rcu                br_port_get_rcu
#define tri_net_bridge_port                struct net_bridge_port
#define tri_dst_neigh_lookup_skb           dst_neigh_lookup_skb

#define tri_filp_open           filp_open
#define tri_filp_close          filp_close
#define tri_file_s              struct file
#define tri_set_fs              set_fs
#define tri_get_fs              get_fs
#define tri_vfs_read            vfs_read
#define tri_vfs_write           vfs_write
#define TRI_KERNEL_DS           KERNEL_DS
#define tri_mm_segment_t        mm_segment_t
#define tri_loff_t              loff_t
#define TRI_O_RDONLY            O_RDONLY
#define TRI_O_RDWR              O_RDWR
#define TRI_O_CREAT             O_CREAT
#define TRI_O_APPEND            O_APPEND
#define TRI_IS_ERR              IS_ERR

#define tri_skb_frag_dma_map(dev, frag, offset, len, dir) \
	skb_frag_dma_map(dev, frag, 0, len, dir)

/*debug
通过此宏 ，可以打印skb信息
TRI_PRINT_MEM_DES( pst_skb->len, pst_skb->data, "dev:%s ifindex:%u skb_iif:%u", pst_skb->dev->name,pst_skb->dev->ifindex,pst_skb->skb_iif);
*/
#define TRI_NTOHL(data) ((tri_uint32)(((tri_uint32)(data) >> 24) \
        | ((tri_uint32)(data) << 24) \
        | (((tri_uint32)(data) >> 8) & 0x0000ff00) \
        | (((tri_uint32)(data) << 8) & 0x00ff0000)))

#define TRI_PRINT_MEM_UINT_HTON( len, ptr )    { \
	tri_uint32 i; tri_uchar8 *ptr_tmp = (tri_uchar8*)ptr; \
	for ( i=0; i < len; i+=sizeof(tri_uint32) ) \
	{  if ( 0 == (i%16)) tri_printk("\r\n[0x%08x] : ",i+(tri_uint32)ptr); tri_printk("%08x ",TRI_NTOHL(*(tri_uint32*)(ptr_tmp+i))); } tri_printk("\r\n"); \
}

#define TRI_PRINT_MEM_DES( len, ptr,fmt,arg...) do{\
						tri_printk((tri_uchar8 *)fmt, ##arg);  \
						TRI_PRINT_MEM_UINT_HTON((tri_uint32)(len),(tri_uchar8 *)(ptr));\
						}while(0)


tri_void tri_ipv6_ntop(tri_uchar8 *ip, tri_uchar8 *str, tri_uint32 size);

tri_void tri_ipv4_ntop(tri_uint32 ip, tri_uchar8 *str, tri_uint32 size);

tri_void tri_ipv6_ntoh(tri_uchar8 *srcip, tri_uint32 *dstip);

tri_void tri_ipv6_inet_pton(tri_uchar8 *srcip, tri_uchar8 *dstip);

tri_void tri_mactop(tri_uchar8 *mac, tri_uchar8 *str, tri_uint32 size);

tri_void tri_str_rev(tri_uchar8 *str, tri_uint32 len);

tri_uint32 tri_atoul(tri_char8 *str, tri_char8 **end, tri_uint32 base);

tri_uchar8 *tri_strtok_r(tri_uchar8 *org, const tri_char8 *demial);

struct net_device *tri_dev_get_by_index(tri_uint32 index);

struct net_device *tri_dev_get_by_skb(struct sk_buff *skb);

struct net_device *tri_dev_get_by_name(const tri_char8 *name);

tri_int32 tri_irq_set_affinity(tri_uint32 irq, tri_uint32 cpu);

tri_uint32 tri_sched_set_affinity(tri_uint32 pid, tri_uint32 cpu);

#endif /* __TRI_OS_H__ */
