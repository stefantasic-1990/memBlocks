#include <math.h>

#define FREELIST_AMOUNT 10
#define FREELIST_DISTRIBUTION_INITIAL 100
#define FREELIST_DISTRIBUTION_FACTOR 0.7
#define FREELIST_DISTRIBUTION_RATIO 0.7

#define BLOCK_ALIGNMENT_SIZE 16
#define BLOCK_METADATA_SIZE ((sizeof(blockMetadata) + BLOCK_ALIGNMENT_SIZE -1) & ~(BLOCK_ALIGNMENT_SIZE -1))
#define BLOCK_SMALLEST_SIZE ((2 * BLOCK_METADATA_SIZE) + BLOCK_ALIGNMENT_SIZE)

typedef struct {
    size_t size;
    bool free;
} blockMetadata;

typedef struct {
    blockMetadata* next_header;
    blockMetadata* prev_header;
} listPtrs;

blockMetadata* free_lists[FREELIST_AMOUNT];

void* allocate_memory(size) {
    void* memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
}

blockMetadata* initialize_blocks(blockMetadata* header, int block_size, int block_amount) {
    for (k=0; k < small_block_amount; k++) {
        header->size = block_size;
        header->free = true;
        footer = (void*)((char*)header + BLOCK_METADATA_SIZE + block_size)
        *footer = *header;
        header = (void*)((char*)footer + BLOCK_METADATA_SIZE);
    }

    return header;
}

void init() {
    
    // initialize each list
    for (i=0 ; i < FREELIST_AMOUNT; i++) {

        // calculate block amounts
        int block_amount = FREELIST_DISTRIBUTION_INITIAL * pow(0.7, i);
        int small_block_amount = block_amount * FREELIST_DISTRIBUTION_RATIO;
        int large_block_amount = block_amount - small_block_amount;
        
        // calculate block data sizes
        int small_block_data_size = BLOCK_ALIGNMENT_SIZE + (i * 2 * BLOCK_ALIGNMENT_SIZE);
        int large_block_data_size = small_block_data_size + BLOCK_ALIGNMENT_SIZE;
        
        // calculate memory requirement
        int list_memory_size = (small_block_amount * small_block_data_size) + (large_block_amount * large_block_data_size) + (block_amount * 2 * BLOCK_METADATA_SIZE);
        
        // allocate current list memory from the OS
        free_lists[i] = allocate_memory(list_memory_size);

        // initialize blocks
        initialize_blocks(initialize_blocks(free_lists[i], small_block_data_size, small_block_amount), large_block_data_size, large_block_amount)
    }
}