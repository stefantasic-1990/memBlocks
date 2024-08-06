#include <stddef.h>

#define MEMBLOCK_HEADER_SIZE sizeof(struct memBlock) // define the size of the memory block header
#define WORD_SIZE sizeof(void*) // define the word size of the system to be the size of a pointer in bytes

// memory block struct
struct memBlock {
    size_t size;          // size of the memory block in bytes
    struct memBlock* next;   // pointer to the next memory block in the free list
};

static struct memBlock* free_list = NULL; // global pointer to the free list (the first element in the free list)

// memory allocation function
void* xmalloc(size_t size) {
    // 0. if requested size is zero, return a NULL
    if (size == 0) return NULL;

    // 1. adjust size to include header and align it
    block_size = MEMBLOCK_HEADER_SIZE + size;
    aligned_block_size = (block_size + WORD_SIZE - 1) & ~(WORD_SIZE - 1) // power of 2 alignment

    // 2. traverse the free list to find a suitable block

    // 3. remove block from the free list and return a pointer to the memory

    // 4. if no suitable block is found, request more memory from the system using sbrk

    // 5. initialize the new block and return a pointer to the memorys
}

// memory deallocation function
void xfree(void* ptr) {
    if (!ptr) return;

    // 1. get the block header from the pointer

    // 2. add the block to the free list
}