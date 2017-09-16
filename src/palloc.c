#include "palloc.h"
#include <sys/mman.h>
#include <unistd.h>

//#define NULL (void *) 0

long PageSize = 4096; //sysconf(_SC_PAGE_SIZE);

void *palloc(size_t size)
{
    long pages = (size / PageSize) * PageSize + (size % PageSize == 0 ? 0 : PageSize) + PageSize;
    char *memory = (char *) mmap(NULL, pages, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    mprotect((void *)(memory + pages - PageSize), PageSize, PROT_NONE);
    return (memory + PageSize - size);
}