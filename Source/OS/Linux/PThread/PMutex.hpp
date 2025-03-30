#pragma once

#include <Thread/Mutex.hpp>
#include <pthread.h>


namespace Flush{
    class PMutex : public Mutex{
        protected:
            PMutex(void);
            ~PMutex(void);

        public:
            virtual void Lock(void)     override;
            virtual void UnLock(void)   override;
            virtual bool IsLock(void)   override;

        public:

            pthread_mutex_t* GetId(void) ;

        private:
            pthread_mutex_t*     m_MutexId;     // allocated on the heap
            pthread_mutexattr_t* m_Attributes;  // is gona allocated on the heap too

        private:
            friend Mutex* NewMutex(void);
            friend void DeleteMutex(Mutex* ptr);
    };
}