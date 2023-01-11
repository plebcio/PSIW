#include <string.h>

#include "common.h"
#include "library_user.h"

void spawn_processes(int n_process, int* child_pids, process_info proc_base);
void run_process(process_info proc_base);
void clean_up(int* child_pids, int msgid);
char* init_mem_pool(int key, int n_blocks, int block_msgid); 

int main(int argc, char const *argv[])
{
    // set up message queue, semaphore table and shared memmory 
    
    int msgid = msgget(MY_KEY, IPC_CREAT|0600);
    if (msgid == -1){
        perror("creating message queue");
        exit(2);
    }
    // clear mess queue 
    msgctl(msgid, IPC_RMID, NULL);
    msgid = msgget(MY_KEY, IPC_CREAT|0600);
    if (msgid == -1){
        perror("creating message queue");
        exit(2);
    }

    // mess queue for memory pool
    int block_msgid = msgget(MY_KEY + 0x15, IPC_CREAT|0600);
    if (block_msgid == -1){
        perror("creating message queue");
        exit(2);
    }
    // clear mess queue 
    msgctl(block_msgid, IPC_RMID, NULL);
    
    block_msgid = msgget(MY_KEY, IPC_CREAT|0600);
    if (block_msgid == -1){
        perror("creating message queue");
        exit(2);
    }


    // TODO change - dont need this many semaphores
    int semid = semget(MY_KEY, NSemOps, IPC_CREAT|0600);
    if (semid == -1){
        perror("creating sem table");
        exit(3);
    }

    if (semctl(semid, sem_lib_state, SETVAL, 1) == -1){
        perror("Nadanie wartosci semaforowi 1");
        exit(1);
    }

    if (semctl(semid, sem_free_spots, SETVAL, K) == -1){
        perror("Nadanie wartosci semaforowi 1");
        exit(1);
    }


    int shmid = shmget(MY_KEY, NLibStates*sizeof(int), IPC_CREAT|0600);
    if (shmid == -1){
        perror("Utworzenie segmentu pamieci wspoldzielonej");
        exit(1);
    }
    
    int* shm_ptr = (int*)shmat(shmid, NULL, 0);
    if (shm_ptr == NULL){
        perror("Przylaczenie segmentu pamieci wspoldzielonej");
        exit(1);
    }
    // init the memory
    shm_ptr[lib_tick] = 1;
    shm_ptr[number_of_free_spots] = K;
    shm_ptr[len_queued_writer_reading_list] = 0;
    shm_ptr[number_of_readers] = 0;

    char* mem_pool = init_mem_pool(MY_KEY, 100, block_msgid);

    process_info base_info = {
        NULL, // empty linked list
        semid,
        msgid,
        shm_ptr,
        mem_pool,
    };

    int child_pids[N];
    spawn_processes(N, child_pids, base_info);
    
    // let subprocesses run
    sleep(200);
    
    // kill children and clean up memory
    clean_up(child_pids, msgid);

    return 0;
}

void spawn_processes(int n_process, int* child_pids, process_info proc_base){
    for (int i = 0; i < n_process; i++){
        int pid = fork();
        if (pid == 0) {
            // child
            // start rest fucntion
            fflush(stdout);
            run_process(proc_base);
            return; 

        } 
        else if (pid == -1){
            perror("Failed to create child process with fork");
            exit(1);
        } 
        else { 
            printf("created process %d\n", pid);
            child_pids[i] = pid;
        }
    }

    // main process returns and monitors child processes
    return; 
}

void run_process(process_info proc_base){
    srand(time(NULL));


    while (1)
    {   
        #define ms 1000
        // sleep for a bit - so output can be readable
        usleep(500 * ms);
        #undef ms

        if (rand() % READER_TO_WRITER_RATIO == 0){
            writer_cycle(&proc_base);
        } else {
            reader_cycle(&proc_base);
        }
    }
}

void clean_up(int* child_pids, int msgid){

    printf("\nStarted killing childern\n"); fflush(stdout);
    usleep(200);

    // kill child processes - end the session
    for (int i = 0; i < N; i++){
        
        
        int err = kill(child_pids[i], 3); // TODO change signal to something that can be caught -> freeing memory
        if (err) {
            perror("Failed to kill child processes");
            exit(1);
        } else {
            printf("killed %d\n", child_pids[i]);
        }
    }


    // system handles freeing this memory and the linked list memory
    // TODO change
    // very ugly solution - change the signal to stop or sth, clean the mem 
    // and then kill the children

    // msg_buf_elem tmp_mess;

    // while( msgrcv(msgid, &tmp_mess, sizeof(msg_buf_elem), 0, IPC_NOWAIT) != -1)
    // {
    //     printf("Mess: %s\n", tmp_mess.mess.mess);
    //     // free the message string
    //     free(tmp_mess.mess.mess);
    // }
}



char* init_mem_pool(int key, int n_blocks, int block_msgid){

    int shmid = shmget(key + 0x15, sizeof(char)*n_blocks, IPC_CREAT|0600);
    if (shmid == -1){
        perror("Utworzenie segmentu pamieci wspoldzielonej");
        exit(1);
    }
    
    char* const shm_ptr = (char*)shmat(shmid, NULL, 0);
    if (shm_ptr == NULL){
        perror("Przylaczenie segmentu pamieci wspoldzielonej");
        exit(1);
    }

    // send messages with pointers

    for (int offset_count = 0; offset_count < n_blocks; offset_count++){
        block_ptr_package tmp_mess;
        tmp_mess.mtype = 1;
        tmp_mess.block_ptr = shm_ptr + (offset_count*MAX_MESS_SIZE);

        int res = msgsnd(block_msgid, &tmp_mess, sizeof(block_ptr_package), 0);
        if (res != 0){
            perror("sending mempool pointer message"); 
            exit(2);
        }
    }    

    return shm_ptr;
}