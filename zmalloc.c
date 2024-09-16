#define NUM_LISTS 10
#define DISTRIBUTION_DIVISION_FACTOR 1.5
#define DISTRIBUTION_INITIAL_NUMBER 256

typedef struct {
    size_t size;
    bool free;
} blockMetadata;

typedef struct {
    blockMetadata* next_header;
    blockMetadata* prev_header;
} listPtrs;

blockMetadata* free_lists[NUM_LISTS];

void init() {
    list_size = DISTRIBUTION_INITIAL_NUMBER;
    int block_size = (i+1)*16;
    for (i=0 ; i <= 10; i++) {
        for (k=0; k < list_size/2; k++) {
            // create blocks for the left side of the list
        }
        block_size += 16;
        for (j=0; k < list_size/2; j++) {
            // create blocks for the right side of the list
        }
        block_size += 16;
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