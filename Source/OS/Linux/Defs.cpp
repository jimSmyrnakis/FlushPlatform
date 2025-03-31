#include "Defs.hpp"
#include <pthread.h>

static pthread_mutex_t mutex  = PTHREAD_MUTEX_INITIALIZER;

static char unkown_message[] = "Unknown Error Type ";

char* flush_strerror(int err){

    pthread_mutex_lock(&mutex);

    char* msg = strerror(err);

    if (msg == nullptr){
        msg = unkown_message;
    }

    pthread_mutex_unlock(&mutex);
    
    return msg;

}