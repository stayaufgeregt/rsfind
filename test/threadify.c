
#include <stdio.h>
#include <stdlib.h>#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>


#define NBTH 4
#define NB_APP 64

bool availableThreads[NBTH];
sem_t availableSem;
sem_t semTab;

int output[NB_APP];

typedef struct{
	int order;
	int id;
	int threadid;
}argth;

int getNextId(){
	for(int i=0; i<NBTH; i++)
		if(availableThreads[i]){
			availableThreads[i]=0;
			return i;
		}
	return -1;
}

void *thread_1(void *arg)
{
	output[((argth*)arg)->order]=((argth*)arg)->id;
	printf("I was here  : %d\n",((argth*)arg)->id);
	sleep(5);
	availableThreads[((argth*)arg)->threadid]=1;
	sem_post(&availableSem);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NBTH];
	argth args[NBTH];
	sem_init(&availableSem,0,NBTH);
	sem_init(&semTab,0,1);
	for(int i=0; i<NBTH; i++)
		availableThreads[i]=1;
	

    for(int i=0; i<NB_APP; i++){
		
		
		sem_wait(&availableSem);
			sem_wait(&semTab);
				int threadID=getNextId();
				printf("thread ID : %d\n",threadID);fflush(stdout);
				availableThreads[threadID]=0;
			sem_post(&semTab);
			
		args[threadID].order=i;
		args[threadID].id=NB_APP-i-1;
		args[threadID].threadid=threadID;
		
		if (pthread_create(threads+threadID, NULL, thread_1, args+threadID)) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	//for(int i=0; i<NBTH; i++)printf("Thread : %d \n",output[i]);
    printf("Après la création du thread.\n");
    return EXIT_SUCCESS;
}


