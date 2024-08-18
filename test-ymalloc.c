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
    printf("The smallest possible block size is %zu bytes.\n", SMALLEST_BLOCK_SIZE);
}