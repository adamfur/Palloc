#ifndef __PALLOC_H__
#  define __PALLOC_H__
#  include <sys/types.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

EXTERN void *__palloc(size_t size);
EXTERN void __pfree(void *ptr);

#define palloc(size) __palloc(size)
#define pfree(ptr) __pfree(ptr)

#endif
