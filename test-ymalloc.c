#include <stdio.h>
#include <stdbool.h>

#define WORD_SIZE sizeof(void*)
#define MEMBLOCK_HEADER_SIZE ((sizeof(struct blockHeader) + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
#define MEMBLOCK_FOOTER_SIZE ((sizeof(struct blockFooter) + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
#define SMALLEST_BLOCK_SIZE (MEMBLOCK_HEADER_SIZE + MEMBLOCK_FOOTER_SIZE + WORD_SIZE)

// external functions
void* ymalloc(size_t size);
void yprintfl();

// memory block header
struct blockHeader {
    struct blockHeader* next;
    struct blockHeader* prev;
    size_t size;
    bool free;
};

// memory block footer
struct blockFooter {
    size_t size;
    bool free;
};

int main() {
    printf("The length of the system word is %zu bytes.\n", WORD_SIZE);
    printf("The size of the memory block header is %zu bytes.\n", MEMBLOCK_HEADER_SIZE);
    printf("The size of the memory block footer is %zu bytes.\n", MEMBLOCK_FOOTER_SIZE);
    printf("The smallest possible block size is %zu bytes.\n\n", SMALLEST_BLOCK_SIZE);

    int bytes[] = {6, 10, 20, 100};
    int bytes_len = sizeof(bytes) / sizeof(bytes[0]);
    struct blockHeader* allocated_blocks[bytes_len];

    yprintfl();
    ymalloc(6);
    yprintfl();

    // for (int i = 0; i < bytes_len; i++) {
    //     void* ptr = ymalloc(bytes[i]);
    //     printf("Allocating %i bytes\n", bytes[i]);
    //     if (ptr == NULL) {
    //         printf("Allocation failed requesting %i bytes", bytes[i]);
    //     } else {
    //         printf("Allocation succeeded\n");
    //         struct blockHeader* block = (void*)((char*)ptr - MEMBLOCK_HEADER_SIZE);
    //         printf("The total size of this block is (header plus data): %zu bytes\n", (block->size + MEMBLOCK_HEADER_SIZE));
    //         printf("The data size of this block is: %zu bytes\n\n", block->size);
    //     }
    //     allocated_blocks[i] = ptr;
    // }
}