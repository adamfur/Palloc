#ifndef __PALLOC_H__
#  define __PALLOC_H__
#  include <sys/types.h>

extern void *__palloc(size_t size);
extern void __pfree(void *ptr);

#define palloc(size) __palloc(size)
#define pfree(ptr) __pfree(ptr)

#endif
