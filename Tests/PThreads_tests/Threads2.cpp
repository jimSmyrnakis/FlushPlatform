#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>


#define THREADS_NUMBER 50000

pthread_t MainId;

void* GenericThreadEntryFunctionPoint(void* args){
    pthread_t MyId = pthread_self();
    printf("Thread test (arg: %d , kernal thread id: %d) , Thread id is main thread : %s\n" , *((int*)args) , gettid() 
    , (pthread_equal(MainId , MyId) != 0) ? "true" : "false");
    return NULL;
}


int main(int argc , char** argv){

    pthread_t   id ;
    int         arg = 100;
    int status;
    MainId = pthread_self();
    for (int i =0; i < THREADS_NUMBER ; i++){
        status = pthread_create(&id , NULL , GenericThreadEntryFunctionPoint , &arg);
        if (status != 0){
            fprintf(stderr , "Error -- pthread_create faield to create a new thread !!! Application Terminates :(");
            exit(1);
        }
    }
    


    printf("Main kernel Thread id : %d  \n" , gettid() );


    pthread_exit(GenericThreadEntryFunctionPoint(&arg));
    return 0;
}