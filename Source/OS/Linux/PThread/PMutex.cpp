#include "PMutex.hpp"
#include "PThread.hpp"
#include <err.h>
#include <errno.h>

namespace Flush{

    PMutex::PMutex(void){
        m_MutexId = new pthread_mutex_t;
        m_Attributes = new pthread_mutexattr_t;
        
        PThreadCheck( pthread_mutexattr_init(m_Attributes) );
        int type = PTHREAD_MUTEX_NORMAL; // to avoid unitentional deadlocks
        #ifdef FLUSH_DEBUG
            type = PTHREAD_MUTEX_ERRORCHECK;
        #endif 
        PThreadCheck( pthread_mutexattr_settype(m_Attributes , type ) );
        PThreadCheck( pthread_mutex_init(m_MutexId , m_Attributes ) );

    }

    PMutex::~PMutex(void){
        PThreadCheck( pthread_mutexattr_destroy(m_Attributes) );
        PThreadCheck( pthread_mutex_destroy(m_MutexId) );

        if (m_MutexId)
            delete m_MutexId;
        
        if (m_Attributes)
            delete m_Attributes;
    }

    void PMutex::Lock(void)     {
        int status;
        PThreadCheck( status = pthread_mutex_lock(m_MutexId) );
        #ifdef FLUSH_DEBUG
            /* TODO -- Code that explicity says the error of a deadlock*/
        #endif

        
    }

    void PMutex::UnLock(void)   {
        int status;
        PThreadCheck( status = pthread_mutex_unlock(m_MutexId) );
        #ifdef FLUSH_DEBUG
            /* TODO -- Code that explicity says the error of this method here */
        #endif
    }

    bool PMutex::IsLock(void)   {
        int status = pthread_mutex_trylock(m_MutexId);
        switch(status){
            case 0      : return false;
            case EBUSY  : return true;
            default     : FLUSH_ASSERT(0 , "pthread_mutex_trylock return's an error ", 0); return true;
        }
        return true;
    }

    Mutex* NewMutex(void){
        return new PMutex();
    }

    void DeleteMutex(Mutex* ptr){
        if (ptr)
            delete ptr;
    }
}