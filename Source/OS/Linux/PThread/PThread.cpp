#include "PThread.hpp"
#include <stdio.h>
#include <stdlib.h>


namespace Flush{

    class DefaultRunnable : public Runnable{

        public:

            u32 Run(void) {
                FLUSH_ASSERT(0 , "Default Runnable is running !!!" , 0);
            }

            virtual u32 Start(void) {
                FLUSH_ASSERT(0 , "Default Runnable is starting !!!" , 0);
            }

            virtual u32 Stop(void) {
                FLUSH_ASSERT(0 , "Default Runnable is stopped !!!" , 0);
            }

    };

    static DefaultRunnable NullRunnable;

    void* pthreadRun(void* thread){
        
        if (thread == nullptr){
            FLUSH_ASSERT(0 , "Pthread Initiallize thread function has nullptr for parameter !!!" , 0);
            return NULL;
        }
        PThread& th = *((PThread*)thread);

        if (th.m_HasCreated == false){
            FLUSH_ASSERT(0 , "Pthread has not created yet !!!" , 0);
            return NULL;
        }
        
        Runnable* ent = (Runnable*) th.GetRunnable();
        uptr res;

        pthread_cleanup_push(pthreadStop , thread);
        if (th.m_HasRunned){
            res = ent->Run();
        }
        else{
            res = ent->Start();
            th.m_HasRunned = true;
        }
        pthread_cleanup_pop(0);

        return ((void*)res);
    }

    void pthreadStop(void* thread){

        if (thread == nullptr){
            FLUSH_ASSERT(0 , "Pthread Initiallize thread function has nullptr for parameter !!!" , 0);
            return ;
        }

        PThread& th = *((PThread*)thread);

        if (th.m_HasCreated == false){
            FLUSH_ASSERT(0 , "Pthread has not created yet !!!" , 0);
            return ;
        }
        
        Runnable* ent = (Runnable*) th.GetRunnable();
        uptr res = ent->Stop();
        
    }
    
    PThread::PThread(void) {

        m_PthreadEntry  = pthreadRun;
        m_HasCreated = false;
        m_HasRunned  = false;
        m_Runnable = &NullRunnable;
        //Initiallize attributes - 
        PThreadCheck(pthread_attr_init(&m_Attributes) );

        // Set Detached thread - means that thread is independend and must behave like that
        // when no longer exist's for example , then all the space that once have now must 
        // be freed and no longer exist (not let it became zombie thread, waiting for someone to free him
        // with a join call )
        PThreadCheck(pthread_attr_setdetachstate(&m_Attributes , PTHREAD_CREATE_DETACHED ));
        int dontCare;
        //set thread cancelable
        PThreadCheck(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE , &dontCare));
        //make a cancel request pending until the next cancle point
        PThreadCheck(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , &dontCare));
    }

    PThread::~PThread(void){
        PThreadCheck(pthread_attr_destroy(&m_Attributes));
    }

    void PThread::SetRunnable(Runnable* runnable) {
        
        if (!runnable){
            FLUSH_ASSERT(0 , "SetRunnable(Runnable* runnable) runnable is nullptr !!!", 0);
            m_Runnable = &NullRunnable;
            return;
        }

        if (!m_HasCreated){
            FLUSH_ASSERT(0 , "SetRunnable(Runnable* runnable) is Called after Create(void) has called !!!" , 0 );
            return;
        }

        m_Runnable = runnable; 
    }

    Runnable* PThread::GetRunnable(void) const {
        FLUSH_ASSERT(m_Runnable != &NullRunnable, "No runnable is set yet !!!", 0);

        return m_Runnable;
    }

    void PThread::Create(void){
        

        if (m_HasCreated){
            FLUSH_ASSERT(0 , "Create(void) Method Have already called for this thread " , 0);
            return ;
        }

        PThreadCheck(pthread_create(&m_Id , &m_Attributes , m_PthreadEntry , this) );

         

        m_HasCreated = true;
        
    }

    void Cancel(Thread* thread){

        if (thread == nullptr){
            FLUSH_ASSERT(0 , "void Cancel(Thread* thread) has a nullptr pointer thread !!!" , 0);
            return;
        }

        PThread& th = (*(PThread*)thread);
        if (th.m_HasCreated == false){
            FLUSH_ASSERT(0 , "void Cancel(Thread* thread) thread has not created yet !!!" , 0);
            return;
        }

        PThreadCheck(pthread_cancel( th.m_Id));
    }

    void TestCancel(void){
        pthread_testcancel();
    }

    Thread* NewThread(void){
        return new PThread();
    }

    void DeleteThread(Thread* ptr){
        if (ptr)
            delete ptr;
    }
}