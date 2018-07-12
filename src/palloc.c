#include "palloc.h"
#include <sys/mman.h>
#include <unistd.h>

//#define NULL (void *) 0

const long PageSize = 4096; //sysconf(_SC_PAGE_SIZE);

typedef struct
{
    size_t Size;
    void *Start;
    char Data[];
} palloc_t;

void *__palloc(size_t size)
{
    size += (size_t) sizeof(palloc_t);
    long pages = (size / PageSize) * PageSize + (size % PageSize == 0 ? 0 : PageSize) + PageSize;
    char *memory = (char *) mmap(NULL, pages, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    mprotect((void *)(memory + pages - PageSize), PageSize, PROT_NONE);
    palloc_t *data = (palloc_t *) (memory + pages - PageSize - size);

    data->Size = pages;
    data->Start = (void *) memory;
    return data->Data;
}

void __pfree(void *ptr)
{
    palloc_t *data = (palloc_t *) ptr - 1;

    munmap(data->Start, data->Size);
}