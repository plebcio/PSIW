#ifndef _SEM_H_
#define _SEM_H_

#include "common.h"

static struct sembuf buf;

void sem_raise(int semid, int semnum){
   buf.sem_num = semnum;
   buf.sem_op = 1;
   buf.sem_flg = 0;
   if (semop(semid, &buf, 1) == -1){
      perror("Opening semaphore");
      exit(1);
   }
}

void sem_lower(int semid, int semnum){
   buf.sem_num = semnum;
   buf.sem_op = -1;
   buf.sem_flg = 0;
   if (semop(semid, &buf, 1) == -1){
      perror("Closing semaphore");
      exit(1);
   }
}

#endif