#include <linux/module.h>        // module_init  module_exit
#include <linux/init.h>            // __init   __exit
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/bio.h>
#include <linux/mempool.h>
#include <linux/gfp.h>
#include <linux/mm.h>

struct mytest_struct{
    char a[26];
    char c;
    char z;
};

void kmalloc_test(void)
{
    unsigned char *kmalloctest;
    unsigned char *kzalloctest;
    unsigned char *__kmalloctest;
    unsigned char *kcalloctest;
    unsigned char *kmalloc_array_test;

    kmalloctest = (unsigned char*)kmalloc(200, 0);
    kzalloctest = (unsigned char*)kzalloc(150, GFP_KERNEL);
    __kmalloctest = (unsigned char*)__kmalloc(8200, GFP_KERNEL);
    kcalloctest = (unsigned char*)kcalloc(10, 30, GFP_KERNEL);
    kmalloc_array_test = (unsigned char*)kmalloc_array(10, 40, GFP_KERNEL);

    kfree(kmalloctest);
    kzfree(kzalloctest);
    kfree(__kmalloctest);
    kfree(kcalloctest);
    kfree(kmalloc_array_test);
}

void kmalloc_node_test(void)
{
    unsigned char *kmalloc_node_test;
    unsigned char *kzalloc_node_test;
    unsigned char *__kmalloc_node_test;
    unsigned char *kcalloc_node_test;
    unsigned char *kmalloc_array_node_test;

    kmalloc_node_test = (unsigned char*)kmalloc_node(20, 0, 0);
    kzalloc_node_test = (unsigned char*)kzalloc_node(20, GFP_KERNEL, 0);
    __kmalloc_node_test = (unsigned char*)__kmalloc_node(92, GFP_KERNEL, 0);
    kcalloc_node_test = (unsigned char*)kcalloc_node(20, 30, GFP_KERNEL, 0);
    kmalloc_array_node_test = (unsigned char*)kmalloc_array_node(10, 10, GFP_KERNEL, 0);

    kfree(kmalloc_node_test);
    kzfree(kzalloc_node_test);
    kfree(__kmalloc_node_test);
    kfree(kcalloc_node_test);
    kfree(kmalloc_array_node_test);
}

void krealloc_test(void)
{
    unsigned char *kmalloctest;
    unsigned char *krealloctest;
    kmalloctest = (unsigned char*)kmalloc(200, 0);
    krealloctest = __krealloc(kmalloctest, 8193, GFP_KERNEL);

    kfree(kmalloctest);
    kfree(krealloctest);
}

void kmem_cache_test(void)
{
    struct kmem_cache *cachep = NULL;
    struct mytest_struct *bodyp = NULL;
    struct mytest_struct *bodyp2 = NULL;

    cachep = kmem_cache_create("adventural-cache", sizeof(struct mytest_struct), 0, SLAB_HWCACHE_ALIGN, NULL);
    bodyp = (struct mytest_struct*) kmem_cache_alloc(cachep, GFP_ATOMIC & ~__GFP_DMA);
    bodyp2 = (struct mytest_struct*) kmem_cache_zalloc(cachep, GFP_ATOMIC & ~__GFP_DMA);

    kmem_cache_free(cachep, bodyp);
    kmem_cache_free(cachep, bodyp2);
}

void kmem_cache_node_test(void)
{
    struct kmem_cache *cachep = NULL;
    struct mytest_struct *bodyp_node = NULL;

    cachep = kmem_cache_create("adventural-cache", sizeof(struct mytest_struct), 0, SLAB_HWCACHE_ALIGN, NULL);

    bodyp_node = (struct mytest_struct*) kmem_cache_alloc_node(cachep, GFP_ATOMIC & ~__GFP_DMA, 0);

    kmem_cache_free(cachep, bodyp_node);
}

void kmem_cache_bulk_test(void)
{
    struct kmem_cache *cachep = NULL;
    void *p[20];

    cachep = kmem_cache_create("adventural-cache", sizeof(struct mytest_struct), 0, SLAB_HWCACHE_ALIGN, NULL);

    kmem_cache_alloc_bulk(cachep, GFP_KERNEL, 20, p);

    kmem_cache_free_bulk(cachep, 20, p);
}

void buddy_test(void)
{
    struct page* page1;
    struct page* page2;
    unsigned long addr1;
    unsigned long addr2;
    void* addr3;

    page1 = alloc_pages(GFP_KERNEL, 4);
    page2 = alloc_pages_node(0, GFP_KERNEL, 3);
    addr1 = get_zeroed_page(GFP_KERNEL);
    addr2 = __get_free_pages(GFP_KERNEL, 2);
    addr3 = alloc_pages_exact(8200, GFP_KERNEL);

    __free_pages(page1, 4);
    __free_pages(page2, 3);
    free_page(addr1);
    free_pages(addr2, 2);
    free_pages_exact(addr3, 8200);
}

void percpu_test(void)
{
    void __percpu* addr;
    addr = alloc_percpu(int);
    free_percpu(addr);
}

void mempool_test(void)
{
    struct kmem_cache *cachep = kmem_cache_create("adventural-cache", sizeof(struct mytest_struct), 0, SLAB_HWCACHE_ALIGN, NULL);
    
    mempool_t *mempool1 = mempool_create_slab_pool(10, cachep);
    mempool_t *mempool2 = mempool_create_page_pool(3, 3);
    mempool_t *mempool3 = mempool_create_kmalloc_pool(10, sizeof(struct mytest_struct));
    mempool_t *mempool4 = mempool_create_kmalloc_pool(1, 8200);
    
    struct mytest_struct *bodyp_mem1 = mempool_alloc(mempool1, GFP_KERNEL);
    struct page* page = mempool_alloc(mempool2, GFP_KERNEL);
    void* bodyp_mem3 = mempool_alloc(mempool3, GFP_KERNEL);
    void* bodyp_mem4 = mempool_alloc(mempool4, GFP_KERNEL);

    mempool_free(bodyp_mem1, mempool1);
    mempool_free(page, mempool2);
    mempool_free(bodyp_mem3, mempool3);
    mempool_free(bodyp_mem4, mempool4);
}

// 模块安装函数
static int __init print_module_init(void)
{
    kmalloc_test();
    krealloc_test();
    kmalloc_node_test();
    kmem_cache_test();
    kmem_cache_node_test();
    kmem_cache_bulk_test();
    buddy_test();
    percpu_test();
    mempool_test();

    return 0;
}

static void __exit print_module_exit(void)
{
    printk(KERN_INFO "adventural_exit helloworld exit\n");
}

module_init(print_module_init);
module_exit(print_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("adventural");
MODULE_DESCRIPTION("module test");
