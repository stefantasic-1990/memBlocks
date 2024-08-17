#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define ARENA_SIZE (16 * 1024 * 1024) // 16 MB
#define WORD_SIZE sizeof(void*)

// memory aligned header and footer sizes
#define MEMBLOCK_HEADER_SIZE (sizeof(struct blockHeader) + WORD_SIZE - 1) & ~(WORD_SIZE - 1)
#define MEMBLOCK_FOOTER_SIZE (sizeof(struct blockFooter) + WORD_SIZE - 1) & ~(WORD_SIZE - 1)

// memory block header
struct blockHeader {
    struct blockHeader* next;
    size_t size;
    bool free;
};

// memory block footer
struct blockFooter {
    struct blockHeader* prev;
    size_t size;
    bool free;
};

struct blockHeader* free_list = NULL;

void* mapArena() {
    // map a large block of memory
    void* arena = mmap(
        NULL, 
        ARENA_SIZE, 
        PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS, 
        -1, 
        0
    );

    if (arena == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }    

    return arena;
}

void* blockCoalesce(void* ptr) {
    
}

void* blockSplit(void* ptr) {
    
}

void* ymalloc(size_t size) {
    // if requested block size is zero, return NULL
    if (size == 0) return NULL;

    // adjust requested size to account for memory alignment and header/footer
    size_t aligned_size = (MEMBLOCK_HEADER_SIZE + MEMBLOCK_FOOTER_SIZE + size + WORD_SIZE - 1) & ~(WORD_SIZE -1);

    struct blockHeader* curr = free_list;

    // search through the free list for a suitable block
    while (curr) {
        if (curr->size >= aligned_size) {
            
        }
    }

    // if no suitable block found, request more memory from the system

}

void yfree(void* ptr) {
    
}