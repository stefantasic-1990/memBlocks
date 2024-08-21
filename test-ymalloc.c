#include <stdio.h>
#include <stdbool.h>

#define WORD_SIZE sizeof(void*)
#define MEMBLOCK_HEADER_SIZE ((sizeof(struct blockHeader) + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
#define MEMBLOCK_FOOTER_SIZE ((sizeof(struct blockFooter) + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
#define SMALLEST_BLOCK_SIZE (MEMBLOCK_HEADER_SIZE + MEMBLOCK_FOOTER_SIZE + WORD_SIZE)

// external functions
void* ymalloc(size_t size);
void yfree(void* block);
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

    int bytes[] = {64, 120, 240, 500};
    int bytes_len = sizeof(bytes) / sizeof(bytes[0]);
    struct blockHeader* allocated_blocks[bytes_len];

    // TEST 1: allocate blocks of various byte sizes
    for (int i = 0; i < bytes_len; i++) {
        void* ptr = ymalloc(bytes[i]);
        printf("Allocating %i bytes\n", bytes[i]);
        if (ptr == NULL) {
            printf("Allocation failed requesting %i bytes", bytes[i]);
        } else {
            printf("Allocation succeeded\n");
            struct blockHeader* block = (void*)((char*)ptr - MEMBLOCK_HEADER_SIZE);
            struct blockFooter* block_footer = (void*)((char*)block + MEMBLOCK_HEADER_SIZE + block->size);
            printf("The total size of this block is (header and footer plus data): %zu bytes\n", (block_footer->size + MEMBLOCK_HEADER_SIZE + MEMBLOCK_FOOTER_SIZE));
            printf("The data size of this block is: %zu bytes\n", block_footer->size);
            allocated_blocks[i] = block;
        }
        yprintfl();
    }

    // TEST 2: deallocate all blocks and check the free list is accurate
    for (int i = (bytes_len -1); i >= 0; i--) {
        printf("Freeing block with data size %zu bytes\n", allocated_blocks[i]->size);
        void* block_data = (char*)allocated_blocks[i] + MEMBLOCK_HEADER_SIZE;
        yfree(block_data);
        printf("Block successfully freed\n");
        yprintfl();
    }

    // // TEST 3: allocate the first, middle, and last block in the free list, causing splitting
    // void* alloc_first = ymalloc(8); // allocate 8 which will split the 64 byte block into two 8 byte blocks
    // yprintfl();

    // void* alloc_middle = ymalloc(160); // allocate 8 which will split the 504 byte block into a 152 byte block and a 304 byte block
    // yprintfl();

    // void* alloc_last = ymalloc(300); // allocate 8 which will split the 504 byte block into a 152 byte block and a 304 byte block
    // yprintfl();

    // // TEST 4: deallocate all blocks and check the free list is accurate and that the splits are accurate
    // yfree(alloc_first);
    // yfree(alloc_middle);
    // yfree(alloc_last);
    // yprintfl();

    // TEST 5: allocate the first, last, and middle block in the free list, causing coalescence
    void* alloc_coa1 = ymalloc(176); // coalesce the 64 byte and 120 byte blocks, split to allocate and leave an 8 byte block
    yprintfl();

    void* alloc_coa2 = ymalloc(784); // coalesce the 8 byte, 240 byte, and 504 byte blocks, split to allocate and leave a 16 byte byte block
    yprintfl();

    void* alloc_coa3 = ymalloc(200); // coalesce the 16 byte, and the last large block, to leave only one large block
    yprintfl();
}