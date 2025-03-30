#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define DEFAULT_THREADS_COUNT 10

#define __debugbreak asm("int3")

#define MyAssert(cond , message) if (!(cond)) { fprintf(stderr , message); __debugbreak; }

void* ThreadEntry(void* args);
bool  isUNumber(const char* text);


int main(int argc , char** argv){

    pthread_t* ids;
    uint32_t   cnt;
    if (argc == 2){
        if (isUNumber(argv[1])){
            cnt = atoi(argv[1]);
            if (cnt == 0){
                MyAssert(0 , "Bad parameter: Number must be greater than zero !!!");
            }
        }
        else {
            MyAssert(0 , "Bad parameter: Not a number !!!");
            exit(1);
        }
            
    }
    else{
        cnt = DEFAULT_THREADS_COUNT;
    }

    ids = new pthread_t[cnt + 1];
    ids[0] = pthread_self();

    for (int i = 1 ; i <= cnt ; i++){
        pthread_create(ids + i , NULL , ThreadEntry , NULL);
    }
    
    ThreadEntry(NULL);

    for (int i = 1; i <= cnt; i++){
        void* retval_ptr;
        int status = pthread_join(ids[i] , &retval_ptr );
        if (status != 0){
            fprintf(stderr , "Thread Join Failed\n");
        }
        if (retval_ptr != NULL){
            printf("????\n" );
        }
        fprintf(stderr , "Thread Join Good\n");
    }


    pthread_exit(NULL);
    return 0;
}



void* ThreadEntry(void* args){
    printf("Thread id %d \n" , gettid());

    return NULL;
}


bool  isUNumber(const char* text){
    if (text == nullptr)
        return false;

    size_t len = strlen(text);

    for (int i = 0; i < len; i++){
        if ( !( (text[i] >= '0') && (text[i] <= '9') ) ){
            return false;
        }
    }

    return true;

}