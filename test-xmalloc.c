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

    int bytes[] = {6,8,10,20,30};
    int bytes_l = sizeof(bytes) / sizeof(bytes[0]);

    for (int i = 0; i < bytes_l; i++) {
        void* ptr = xmalloc(bytes[i]);
        printf("Allocating %i bytes\n", bytes[i]);
        if (ptr == NULL) {
            printf("Allocation failed requesting %i bytes", bytes[i]);
        } else {
            printf("Allocation succeeded\n");
            struct memBlock* block = (void*)(char*)ptr - MEMBLOCK_HEADER_SIZE;
            printf("The size of the header plus data is: %zu bytes\n", (block->size + MEMBLOCK_HEADER_SIZE));
            printf("The size of this memory block is: %zu bytes\n\n", block->size);
        }
    }    
}