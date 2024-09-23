#include <math.h>
#include <stdbool.h>

#define FREELIST_AMOUNT 10
#define FREELIST_DISTRIBUTION_INITIAL 100
#define FREELIST_DISTRIBUTION_FACTOR 0.7
#define FREELIST_DISTRIBUTION_RATIO 0.6

#define PLATFORM_WORD_SIZE sizeof(void*)
#define BLOCK_ALIGNMENT_SIZE 2 * WORD_SIZE
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

static blockMetadata* free_lists[FREELIST_AMOUNT];

// allocate memory from the operating system
void* allocate_memory(size) {
    void* memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
}

// initialize an amount of contiguous blocks of certain size in memory
blockMetadata* initialize_blocks(blockMetadata* curr_header, int block_size, int block_amount, bool back_link) {

    // initialize first block
    listPtrs* curr_ptrs = (void*)((char*)curr_header + BLOCK_METADATA_SIZE);
    blockMetadata* curr_footer = (void*)((char*)curr_ptrs + block_size);

    curr_header->size = block_size;
    curr_header->free = true;
    *curr_footer = *curr_header;

    curr_ptrs->next_header = NULL;
    if (back_link != true) {
        curr_ptrs->prev_header = NULL;
    } else (
        listPtrs* prev_ptrs = (void*)((char*)curr_header - BLOCK_METADATA_SIZE - block_size);
        blockMetadata* prev_header = (void*)((char*)prev_ptrs - BLOCK_METADATA_SIZE);
        curr_ptrs->prev_header = prev_header;
        prev_ptrs->next_header = curr_header;
    )

    curr_header = (void*)((char*)curr_footer + BLOCK_METADATA_SIZE);;

    // initialize rest of blocks
    for (k=0; k < small_block_amount - 1; k++) {
        listPtrs* curr_ptrs = (void*)((char*)curr_header + BLOCK_METADATA_SIZE);
        blockMetadata* curr_footer = (void*)((char*)curr_ptrs + block_size);
        listPtrs* prev_ptrs = (void*)((char*)curr_header - BLOCK_METADATA_SIZE - block_size);
        blockMetadata* prev_header = (void*)((char*)prev_ptrs - BLOCK_METADATA_SIZE);

        curr_header->size = block_size;
        curr_footer->free = true;
        *curr_footer = *curr_header;

        curr_ptrs->next_header = NULL;
        curr_ptrs->prev_header = prev_header;
        prev_ptrs->next_header = curr_header;

        curr_header = (void*)((char*)curr_footer + BLOCK_METADATA_SIZE);
    }

    return curr_header;
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
        initialize_blocks(initialize_blocks(free_lists[i], small_block_data_size, small_block_amount, false), large_block_data_size, large_block_amount, true)
    }
}


// print amount of blocks of each size and status
void print_block_stats() {
    for (i=0; i < FREELIST_AMOUNT; i++) {
        current_block = free_lists[i];
        current_
    }
}