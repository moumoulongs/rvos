#include "os.h"

extern char end[]; // kernel后第一个地址

/*
 * _alloc_start points to the actual start address of heap pool
 * _alloc_end points to the actual end address of heap pool
 * _num_pages holds the actual max number of pages we can allocate.
 */

void freerange(void *pa_start, void * pa_end);

//页结构体
struct run {  
	struct run *next;
};

//存放未分配页
struct {
	struct run *freelist;
}kmem;

void kinit()
{
	freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64_t)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

//释放内存
void kfree(void *pa)
{
	struct run *r;

	if(((uint64_t)pa % PGSIZE) != 0 || (char*)pa < end || (uint64_t)pa >= PHYSTOP)
    panic("kfree");
	// memset(pa,1,PGSIZE);
	r = (struct run*)pa;
	r->next = kmem.freelist;
	kmem.freelist = r;

}

void *kalloc(void)
{
	struct run *pa;
	pa = kmem.freelist;
	if(pa)
		kmem.freelist = pa->next;
	if(pa)
		memset((char*)pa,5,PGSIZE);
	return (void*)pa;
}



