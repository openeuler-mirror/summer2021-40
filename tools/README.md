Summer2021-No.40 统计一个内核模块占用的内存

#### tools目录介绍
##### getfunction.py文件

getfunction.py函数提取了mm模块当中所有通过EXPORT_SYMBOL导出的函数，然后与drivers目录去比对，drivers目录内的文件使用到的函数记录到found.txt当中，未使用到的记录到not-found.txt当中，作为统计函数来源的参考。

下面是筛选出来的函数一些与内存分配、释放相关的函数

```c
get_page()
put_page()

bdi_register()
bdi_put()

balloon_page_alloc()---->alloc_page()

// dma_pool
dma_pool_create()--->kmalloc_node()
dma_pool_destroy()
dma_pool_alloc()--->pool_alloc_page()--->kmalloc()
dma_pool_free()
dmam_pool_create()
dmam_pool_destroy()

put_vaddr_frames()--->put_page()
frame_vector_create()--->kvmalloc()
frame_vector_destroy()--->kvfree()

// mempool
mempool_exit()
mempool_destroy() 
mempool_init()
mempool_create()
mempool_create_node()
mempool_resize()
mempool_alloc()
mempool_free()
mempool_alloc_slab()
mempool_free_slab()
mempool_kmalloc()
mempool_kfree()

// buddy
__get_free_pages()
get_zeroed_page()
__free_pages()
free_pages()
__page_frag_cache_drain()
page_frag_free()
alloc_pages_exact()
free_pages_exact()

// percpu
__alloc_percpu()
free_percpu()

sp_free()
sp_alloc()

// slab
kmem_cache_alloc()
kmem_cache_alloc_node() 
kmem_cache_free()
kfree()
ksize()
kmem_cache_size()
kmem_cache_create_usercopy()
kmem_cache_create()
kmem_cache_destroy() 
kmem_cache_shrink()
krealloc()
kzfree()
kfree()

put_pages_list()
release_pages()
__pagevec_release()
kfree_const()

// vmalloc
kvmalloc_node()
kvfree()
vmalloc_to_page()
vmalloc_to_pfn()
vfree()
__vmalloc()
vmalloc()
vzalloc()
vmalloc_user()
vmalloc_node()
vzalloc_node()
vmalloc_32()
vmalloc_32_user()
remap_vmalloc_range()
alloc_vm_area()
free_vm_area()

zs_malloc()
zs_free()
zs_compact()
zs_create_pool()
zs_destroy_pool()
```

##### get.py文件

get.py文件提供的功能是读取所有模块下的usedmemory，然后将结果存储到memory.txt中
