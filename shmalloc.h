#ifndef _SHMALLOC_H_
#define _SHMALLOC_H_


char* get_block(char* library_mem_block, int block_msgid);
void free_block(char* block_ptr, int block_msgid);

#endif  