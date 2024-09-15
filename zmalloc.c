





/*
- segregated free lists (segregated fit with specific class sizes (some powers of 2 classes)
- min block size is the word size x2, so on 64 bit 16 bytes... and blocks are multiples of 16 so 16, 32, 48, 64,...
- first fit placement strategy (if on the low end of the class size, search from front, otherwise from behind)
  - stop the search if 
- immediate block split, searching from the left, but split on multiples of 16 only
- deferred coalesce, searching from the right, coalesce into multiples of 16 only
 - wax and wane as blocks are split and coalesced.
*/