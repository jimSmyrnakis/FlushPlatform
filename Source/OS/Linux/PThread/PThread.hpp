#include <Thread/Thread.hpp>
#include <pthread.h>
#include "../Defs.hpp"

#define PThreadCheck(function) { \ 
    int status = (function); \ 
    if (status != 0) {   \
        LOG_ENGINE_ERROR( "pthread error ( line %d , function: %s , file: %s , Message: %s ) - function failed " ,\
             __LINE__ , #function , __FILE__ , flush_strerror(status));\
    }\
}

namespace Flush{

    typedef void* (*PEntry)(void*);
    
    class PThread : public Thread{
        protected:
            PThread(void) ;
            virtual ~PThread(void);
        public:
            
            virtual void SetRunnable(Runnable* runnable) override;
            virtual Runnable* GetRunnable(void) const override;
            virtual void Create(void) override;

        private:
            pthread_attr_t  m_Attributes    ;
            pthread_t       m_Id            ;
            PEntry          m_PthreadEntry  ;
            Runnable*       m_Runnable      ;
            bool            m_HasCreated    ;
            bool            m_HasRunned     ;

        private:

            friend void TestCancel(void); 
            friend void Cancle(Thread* thread);
            friend void DeleteThread(Thread* ptr);
            friend void Cancel(Thread* thread);
            friend Thread* NewThread(void);
            friend void* pthreadRun(void* thread);
            friend void  pthreadStop(void* thread);
    };

    void* pthreadRun(void* thread);
    void  pthreadStop(void* thread);

}