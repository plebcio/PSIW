CC = gcc
FLAGS = -Wall
INCLUDES = common.h params.h 

all: czypis

czypis: main.o library_user.o library.o linked_list.o library_user.h $(INCLUDES)
	$(CC) $(FLAGS) main.o library_user.o library.o linked_list.o -o main.out

main.o: main.c $(INCLUDES)
	$(CC) $(FLAGS) -c main.c

library_user.o: library_user.c library_user.h semaphores.h library.h $(INCLUDES) 
	$(CC) $(FLAGS) -c library_user.c

library.o: library.c library.h $(INCLUDES)
	$(CC) $(FLAGS) -c library.c

shmalloc.o: shmalloc.c shmalloc.h $(INCLUDES)
	$(CC) $(FLAGS) -c shmalloc.c

linked_list.o: linked_list.c linked_list.h 
	$(CC) $(FLAGS) -c linked_list.c

clean:
	rm -rf *.o *.out test