// shmalloc - like malloc but for shared memory
// fixed size block memory allocator for shared memory
// implemented with msg queue and shared memory

// pointers to free memory blocks are stores as messages inside a message queue

#include "common.h"
#include "shmalloc.h"

char* get_block(char* library_mem_block, int block_msgid){
    printf("Allocating block\n"); fflush(stdout);

    block_ptr_package new_block;

    int res = msgrcv(block_msgid, &new_block, sizeof(block_ptr_package), 0, 0);
    if (res != 0){
        perror("reciving mempool pointer message"); 
        exit(2);
    }

    // return the underlaying pointer
    return new_block.block_ptr;

}

void free_block(char* block_ptr, int block_msgid){
    printf("Freeing block\n"); fflush(stdout);

    block_ptr_package old_block;

    old_block.mtype = 1;
    old_block.block_ptr = block_ptr;

    int res = msgsnd(block_msgid, &old_block, sizeof(block_ptr_package), 0);
    if (res != 0){
        perror("sending mempool pointer message"); 
        exit(2);
    }
}



