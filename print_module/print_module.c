#include <linux/module.h>        // module_init  module_exit
#include <linux/init.h>            // __init   __exit
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/bio.h>
#include <linux/mempool.h>

struct mytest_struct{
    char a[26];
    char c;
    char z;
};

// 模块安装函数
static int __init print_module_init(void)
{
    unsigned char *kmalloctest;
    unsigned char *kzalloctest;
    unsigned char *__kmalloctest;
    unsigned char *kcalloctest;
    unsigned char *kmalloc_array_test;
    
    struct kmem_cache *cachep = NULL;
    struct mytest_struct *bodyp = NULL;
    struct mytest_struct *bodyp2 = NULL;
    struct mytest_struct *bodyp3 = NULL;

    struct mytest_struct *bodyp_node = NULL;
    struct mytest_struct *bodyp_node_trace = NULL;

    unsigned char *kmalloc_node_test;
    unsigned char *kzalloc_node_test;
    unsigned char *__kmalloc_node_test;
    unsigned char *kcalloc_node_test;
    unsigned char *kmalloc_array_node_test;

    //struct bio* testbio = bio_alloc(GFP_NOIO, 0);
    //struct bio* testbio1 = bio_kmalloc(GFP_NOIO, 0);
    //bio_put(testbio);
    //bio_put(testbio1);

    //mempool_t *mempool = mempool_create_kmalloc_pool(10, sizeof(struct mytest_struct));
    //struct mytest_struct *bodyp = mempool_alloc(mempool, GFP_KERNEL);
    //mempool_free(bodyp, mempool);

    kmalloctest = (unsigned char*)kmalloc(100, 0);
    //kzalloctest = (unsigned char*)kzalloc(150, GFP_KERNEL);
    //__kmalloctest = (unsigned char*)__kmalloc(205, GFP_KERNEL);
    //kcalloctest = (unsigned char*)kcalloc(10, 30, GFP_KERNEL);
    //kmalloc_array_test = (unsigned char*)kmalloc_array(10, 40, GFP_KERNEL);

    //printk(KERN_DEBUG "cache-size:%lu\n",sizeof(struct mytest_struct));
    //cachep = kmem_cache_create("adventural-cache", sizeof(struct mytest_struct), 0, SLAB_HWCACHE_ALIGN, NULL);
    //bodyp = (struct mytest_struct*) kmem_cache_alloc(cachep, GFP_ATOMIC & ~__GFP_DMA);
    //bodyp2 = (struct mytest_struct*) kmem_cache_zalloc(cachep, GFP_ATOMIC & ~__GFP_DMA);
    //bodyp3 = (struct mytest_struct*) kmem_cache_alloc_trace(cachep, GFP_ATOMIC & ~__GFP_DMA, 28);

    //kmalloc_node_test = (unsigned char*)kmalloc_node(400, 0, 0);
    //kzalloc_node_test = (unsigned char*)kzalloc_node(20, GFP_KERNEL, 0);
    //__kmalloc_node_test = (unsigned char*)__kmalloc_node(92, GFP_KERNEL, 0);
    //kcalloc_node_test = (unsigned char*)kcalloc_node(20, 30, GFP_KERNEL, 0);
    //kmalloc_array_node_test = (unsigned char*)kmalloc_array_node(10, 10, GFP_KERNEL, 0);

    //bodyp_node = (struct mytest_struct*) kmem_cache_alloc_node(cachep, GFP_ATOMIC & ~__GFP_DMA, 0);
    //bodyp_node_trace = (struct mytest_struct*) kmem_cache_alloc_node_trace(cachep, GFP_ATOMIC & ~__GFP_DMA, 0, 28);
	
    //kfree(kzalloctest);
    //kmem_cache_free(cachep,bodyp);
    return 0;
}

static void __exit print_module_exit(void)
{
    printk(KERN_INFO "adventural_exit helloworld exit\n");
}

module_init(print_module_init);
module_exit(print_module_exit);

MODULE_LICENSE("GPL");                // 描述模块的许可证
MODULE_AUTHOR("adventural");          // 描述模块的作者
MODULE_DESCRIPTION("module test");    // 描述模块的介绍信息
//MODULE_ALIAS("alias xxx");          // 描述模块的别名信息
