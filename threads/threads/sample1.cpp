#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void *functionC(void *ptr);
int  counter = 0;
int sem;

#define NSEMS 1
#define SEMFLAG (IPC_CREAT| 0666)
union semun {
       int              val;    /* Value for SETVAL */
       struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
       unsigned short  *array;  /* Array for GETALL, SETALL */
       struct seminfo  *__buf;  /* Buffer for IPC_INFO
				   (Linux specific) */
};

main()
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   key_t key =ftok(".",'s'); // Get a semaphore based on current directory
   sem = semget(key, NSEMS, SEMFLAG);

   union semun x;
   x.val = 1;
   semctl(sem, 0, SETVAL, x); // Set value for semaphore 0
   // Now it is set to one, one person will be able to access at a time

   printf("Got semaphore %d\n",sem);

   /* Create independent threads each of which will execute functionC */

   if( (rc1=pthread_create( &thread1, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }

   if( (rc2=pthread_create( &thread2, NULL, &functionC, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL); 

   exit(0);
}


void *functionC(void *ptr)
{
   int tmp;
   struct sembuf semopdata;

   semopdata.sem_num = 0;
   semopdata.sem_op = -1; // Subtract one from the semaphore
   semopdata.sem_flg = SEM_UNDO;

   semop(sem,&semopdata,1); // One semaphore Operation
   tmp = counter;
   sleep(1);
   tmp++;
   counter = tmp;
   printf("Counter value: %d\n",counter);
   semopdata.sem_op = 1; // add one to the semaphore
   semop(sem,&semopdata,1); // One semaphore Operation
}
