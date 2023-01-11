#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> 
#include <sys/msg.h>

#include "linked_list.h"

#include "params.h"

#define MY_KEY 0x11

#define MAX_MESS_SIZE 50 // messages don't need to be the same size, just ease of use

// representation of library state - helper enums
#define NSemOps 2
enum SemOps { sem_lib_state, sem_free_spots };
#define NLibStates 4
enum LibStates { number_of_free_spots, lib_tick, number_of_readers, len_queued_writer_reading_list };

// state which each process needs to track
typedef struct {
    Node* library_ticks;
    int semid;
    int msgid;
    int* library_state;
    char* library_mem_block;
} process_info;

// message structs
typedef struct message{
    int mess_count;
    char mess[MAX_MESS_SIZE];
    
}message;

typedef struct msg_buf_elem{
    long mtype;
    message mess;

} msg_buf_elem;

// struct for shared memory 
typedef struct {
    long mtype;
    char* block_ptr;
} block_ptr_package;


#endif 