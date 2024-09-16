#include <math.h>

#define FREELIST_AMOUNT 10
#define FREELIST_DISTRIBUTION_INITIAL 100
#define FREELIST_DISTRIBUTION_FACTOR 0.7

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

void init() {
    
    // initialize each list
    for (i=0 ; i <= FREELIST_AMOUNT; i++) {

        // calculate current list number of blocks
        int list_number_of_blocks = FREELIST_DISTRIBUTION_INITIAL * pow(0.7, i);
        int small_block_amount = list_number_of_blocks / 2;
        int large_block_amount = list_number_of_blocks - small_block_amount;
        
        // calculate current list block data sizes
        int small_block_data_size = BLOCK_ALIGNMENT_SIZE + (i * 2 * BLOCK_ALIGNMENT_SIZE);
        int large_block_data_size = small_block_data_size + BLOCK_ALIGNMENT_SIZE;
        
        // calculate current list memory requirement
        int list_byte_size = list_number_of_blocks * ((2 * BLOCK_METADATA_SIZE) + (small_block_data_size + BLOCK_ALIGNMENT_SIZE/2))
        
        // allocate current list memory from the OS
        free_lists[i] = mmap(
            NULL, 
            list_byte_size, 
            PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANONYMOUS, 
            -1, 
            0
        );

        if (arena == MAP_FAILED) {
            perror("mmap");
            exit(EXIT_FAILURE);
        }

        // initialize current list block pointers
        blockMetadata* current_block_header = free_lists[i];
        blockMetadata* current_block_footer = NULL;
        
        // initialize current list small blocks
        for (k=0; k < small_block_amount; k++) {
            current_block_header->size = small_block_data_size;
            current_block_header->free = true;
            current_block_footer = (void*)((char*)current_block_header + BLOCK_METADATA_SIZE + small_block_data_size)
            current_block_footer->size = current_block_header->size;
            current_block_footer->free = current_block_header->free;
            current_block_header = (void*)((char*)current_block_footer + BLOCK_METADATA_SIZE)
        }

        // initialize current list large blocks
        for (j=0; k < large_block_amount; j++) {
            current_block_header->size = large_block_data_size;
            current_block_header->free = true;
            current_block_footer = (void*)((char*)current_block_header + BLOCK_METADATA_SIZE + large_block_data_size)
            current_block_footer->size = current_block_header->size;
            current_block_footer->free = current_block_header->free;
            current_block_header = (void*)((char*)current_block_footer + BLOCK_METADATA_SIZE)
        }
    }
}



/* BIN SIZES

LIST 1 (SMALL): 16, 32
LIST 2 (MEDIUM): 48, 64
LIST 3 (LARGE): 80, 96

*/




/* NOTES
- segregated free lists (segregated fit with specific class sizes (some powers of 2 classes)
- min block size is the word size x2, so on 64 bit 16 bytes... and blocks are multiples of 16 so 16, 32, 48, 64,...
- first fit placement strategy (if on the low end of the class size, search from front, otherwise from behind)
  - stop the search if 
- immediate block split, searching from the left, but split on multiples of 16 only
- deferred coalesce, searching from the right, coalesce into multiples of 16 only
 - wax and wane as blocks are split and coalesced.
*/

/*
- minimum block size is 16, blocks in general are multiples of 16
- segregated free lists, each list contains a range of block sizes that are multiplels of 16
- first fit placement strategy
*/