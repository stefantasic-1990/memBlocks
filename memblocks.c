#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define ARENA_SIZE (16 * 1024 * 1024) // 16 MB
#define WORD_SIZE sizeof(void*)
#define MEMBLOCK_HEADER_SIZE ((sizeof(struct memblockHeader) + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
#define MEMBLOCK_FOOTER_SIZE ((sizeof(struct memblockHeader) + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
#define SMALLEST_MEMBLOCK_SIZE (MEMBLOCK_HEADER_SIZE + MEMBLOCK_FOOTER_SIZE + WORD_SIZE)
struct memblockHeader {
    struct memblockHeader* next;
    size_t size;
    bool free;
};
struct memblockFooter {
    size_t size;
    bool free;
};

static struct memblockHeader* free_list = NULL;

void* getBlock(size_t size) {
    if (size == 0) {
        return NULL;
    }
    struct blockHeader* block = free_list;
    size_t aligned_size = (SMALLEST_MEMBLOCK_SIZE + size - 1) & ~(WORD_SIZE -1);

    while (block) {
        
    }


}

void freeBLock(void* block) {

}