#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define MEMBLOCK_HEADER_SIZE sizeof(struct blockHeader)
#define MEMBLOCK_FOOTER_SIZE sizeof(struct blockFooter)
#define ARENA_SIZE (16 * 1024 * 1024) // 16 MB
#define WORD_SIZE sizeof(void*)

// memory block header
struct blockHeader {
    struct blockHeader* next;
    size_t size;
    bool free;
};

// memory block footer
struct blockFooter {
    size_t size;
    bool free;
};

struct blockHeader* free_list = NULL;

void* mapArena() {
    void* arena = mmap(
        NULL, 
        ARENA_SIZE, 
        PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS, 
        -1, 0);

    of (arena == MAP_FAILED) {
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

}

void yfree(void* ptr) {
    
}