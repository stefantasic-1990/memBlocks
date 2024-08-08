#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define MEMBLOCK_HEADER_SIZE sizeof(struct memBlock) // define the size of the memory block header
#define WORD_SIZE sizeof(void*) // define the word size of the system to be the size of a pointer in bytes

// function prototypes
void* xmalloc(size_t size);
void xfree(void* ptr)

// memBlock struct
struct memBlock {
    size_t size;          // size of the memory block in bytes
    struct memBlock* next;   // pointer to the next memory block in the free list
};

int main() {

    // test requesting 8 bytes
    void* 8ptr = xmalloc(8);
    if (8ptr = NULL) {
        printf("Allocation failed requesting 8 bytes");
    } else {
        printf("Allocation succeeded");
        struct memBlock* block = (void*)(char*)8ptr - MEMBLOCK_HEADER_SIZE;
        printf("The size of this memory block is: %zu", block->size)
    }

    // test requesting 6 bytes
    void* 6ptr = xmalloc(6);
    if (6ptr = NULL) {
        printf("Allocation failed requesting 6 bytes");
    } else {
        printf("Allocation succeeded");
        struct memBlock* block = (void*)(char*)8ptr - MEMBLOCK_HEADER_SIZE;
        printf("The size of this memory block is: %zu", block->size)
    }
    
}