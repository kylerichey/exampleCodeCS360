#include <pthread.h>
#include <stdio.h>
#include<queue>
#include<iostream>
#include<stdlib.h>
#include<semaphore.h>
#define NUM_THREADS     10
#define NQUEUE 20

sem_t full, empty, mutex;



class myqueue{
	 std::queue<int> stlqueue;
	public:
	void push(int sock)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		stlqueue.push(sock);
		sem_post(&mutex);
		sem_post(&full);
	}
	int pop(){
		sem_wait(&full);
		sem_wait(&mutex);
		int rval = stlqueue.front();
		stlqueue.pop();
		sem_post(&mutex);
		sem_post(&empty);
		
		return(rval);
		
	}
}sockqueue;

int tid;

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   //pthread_exit(NULL);
   while(1)
   {
	    std::cout<< "Got " << sockqueue.pop()<<std::endl;
   }
}

int main (int argc, char *argv[])
{
	
	 sem_init(&full, PTHREAD_PROCESS_PRIVATE, 0);
	 sem_init(&empty, PTHREAD_PROCESS_PRIVATE, NQUEUE);
	 sem_init(&mutex, PTHREAD_PROCESS_PRIVATE, 1);
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   
   for(int i=0; i<10;i++)
   {
	   sockqueue.push(i);
   }
   

   
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         return(0);
      }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}