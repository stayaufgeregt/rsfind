
#include <stdio.h>
#include <stdlib.h>#include <unistd.h>
#include <pthread.h>

#define NBTH 4
#define NB_APP 64
int output[NBTH];

typedef struct{
	int order;
	int id;
}argth;

void *thread_1(void *arg)
{
	output[((argth*)arg)->order]=((argth*)arg)->id;
	printf("I was here  : %d\n",((argth*)arg)->id);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NBTH];
	
    printf("Avant la création du thread.\n");
	
	argth args[NBTH];
	
    for(int i=0; i<NB_APP; i++){
		
		args[i].order=i;
		args[i].id=NB_APP-i-1;
		
		for(int j=0;
		if (pthread_create(threads+i, NULL, thread_1, args+i)) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}
	
	for(int i=0; i<NBTH; i++){
		if (pthread_join(threads[i], NULL)) {
			perror("pthread_join");
			return EXIT_FAILURE;
		}
		//printf("Thread waiting : %d \n",output[i]);
	}

	//for(int i=0; i<NBTH; i++)printf("Thread : %d \n",output[i]);
    printf("Après la création du thread.\n");
    return EXIT_SUCCESS;
}


