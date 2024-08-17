#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define MEMBLOCK_HEADER_SIZE sizeof(struct blockHeader)
#define MEMBLOCK_FOOTER_SIZE sizeof(struct blockFooter)

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

void initializeMemory() {

}

void* blockCoalesce(void* ptr) {
    
}

void* blockSplit(void* ptr) {
    
}

void* ymalloc(size_t size) {

}

void yfree(void* ptr) {
    
}