#ifndef THREADS_H_
#define THREADS_H_

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>#include <unistd.h>
#include <pthread.h>

int available;
bool workingThread[NB_THREAD_MAX];

void *thread_1(void *arg)
{
    printf("Nous sommes dans le thread.\n");
    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread1;
    printf("Avant la création du thread.\n");
    if (pthread_create(&thread1, NULL, thread_1, NULL)) {
    perror("pthread_create");
    return EXIT_FAILURE;
    }
    if (pthread_join(thread1, NULL)) {
    perror("pthread_join");
    return EXIT_FAILURE;
    }
    printf("Après la création du thread.\n");
    return EXIT_SUCCESS;
}



#endif