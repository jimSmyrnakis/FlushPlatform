#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <pthread.h>

void* FirstThread(void* args){
    printf("Thread test (arg: %d) \n" , *((int*)args));

    return NULL;
}

int main(int argc , char** argv){

    pthread_t   id ;
    int         arg = 100;
    pthread_create(&id , NULL , FirstThread , &arg);

    printf("Main Thread test  \n" );

    pthread_exit(NULL);
    return 0;
}