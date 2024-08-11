#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define MEMBLOCK_HEADER_SIZE sizeof(struct memBlock) // define the size of the memory block header
#define WORD_SIZE sizeof(void*) // define the word size of the system to be the size of a pointer in bytes

// function prototypes
void* xmalloc(size_t size);
void xfree(void* ptr);

// memBlock struct
struct memBlock {
    size_t size;          // size of the memory block in bytes
    struct memBlock* next;   // pointer to the next memory block in the free list
};

int main() {
    printf("Word size is %zu bytes\n", WORD_SIZE);
    printf("MemBlock header size is %zu bytes\n\n", MEMBLOCK_HEADER_SIZE);

    // test requesting 8 bytes, expecting to get an 8 byte block
    void* ptr8 = xmalloc(8);
    printf("Allocating 8 bytes\n");
    if (ptr8 == NULL) {
        printf("Allocation failed requesting 8 bytes");
    } else {
        printf("Allocation succeeded\n");
        struct memBlock* block = (void*)(char*)ptr8 - MEMBLOCK_HEADER_SIZE;
        printf("The size of this memory block is: %zu bytes\n\n", block->size);
    }

    // test requesting 6 bytes, expecting to get an 8 byte block
    void* ptr6 = xmalloc(6);
    printf("Allocating 6 bytes\n");
    if (ptr6 == NULL) {
        printf("Allocation failed requesting 6 bytes");
    } else {
        printf("Allocation succeeded\n");
        struct memBlock* block = (void*)(char*)ptr6 - MEMBLOCK_HEADER_SIZE;
        printf("The size of this memory block is: %zu bytes\n\n", block->size);
    }

    // test requesting 10 bytes, expecting to get a 16 byte block
    void* ptr10 = xmalloc(6);
    if (ptr10 == NULL) {
        printf("Allocation failed requesting 6 bytes");
    } else {
        printf("Allocation succeeded\n");
        struct memBlock* block = (void*)(char*)ptr10 - MEMBLOCK_HEADER_SIZE;
        printf("The size of this memory block is: %zu\n", block->size);
    }
    
}