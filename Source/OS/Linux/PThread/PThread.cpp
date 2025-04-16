#include "PThread.hpp"
#include <stdio.h>
#include <stdlib.h>


namespace Flush{

    class DefaultRunnable : public Runnable{

        public:

            virtual void Loop(void) override {
                FLUSH_ASSERT(0 , "Default Runnable is Looping !!!" , 0);
            }

            virtual void Init(void) override {
                FLUSH_ASSERT(0 , "Default Runnable is Initiallize !!!" , 0);
            }

            virtual void Fini(void) override {
                FLUSH_ASSERT(0 , "Default Runnable is Finallized !!!" , 0);
            }

            virtual void Start(void) override {
                FLUSH_ASSERT(0 , "Default Runnable is Started !!!" , 0);
            }

            virtual void Stop(void) override {
                FLUSH_ASSERT(0 , "Default Runnable is Stopped !!!" , 0);
            }

    };

    static DefaultRunnable NullRunnable;

    void* pthreadRun(void* thread){
        
        if (thread == nullptr){
            FLUSH_ASSERT(0 , "Pthread Initiallize thread function has nullptr for parameter !!!" , 0);
            return NULL;
        }
        PThread& th = *((PThread*)thread);

        
        
        Runnable* ent = (Runnable*) th.GetRunnable();
        uptr res;

        pthread_cleanup_push(pthreadCancel , thread);
            ent->Init();
            while (true){
                ent->Loop();
                
                if (th.IsStopped()){
                    ent->Stop();
                    while(th.IsStopped()) TestCancel();
                    ent->Start();
                }
                TestCancel();
            }
        pthread_cleanup_pop(1);
        


        return ((void*)res);
    }

    void pthreadCancel(void* thread){

        

        if (thread == nullptr){
            FLUSH_ASSERT(0 , "Pthread Initiallize thread function has nullptr for parameter !!!" , 0);
            return ;
        }

        PThread& th = *((PThread*)thread);

        if (th.m_IsDeleted) return;
        
        Runnable* ent = (Runnable*) th.GetRunnable();
        ent->Fini();

        if (th.m_Attributes)
        PThreadCheck( pthread_attr_destroy(th.m_Attributes) );
        
        if (th.m_Attributes) delete th.m_Attributes;
        if (th.m_Id) delete th.m_Id;

        th.m_Attributes = nullptr;
        th.m_Id = nullptr;

        th.m_IsDeleted = true;
    }
    
    PThread::PThread(void) {

        m_PthreadEntry  = pthreadRun;
        m_HasCreated = false;
        m_Runnable = &NullRunnable;
        m_Attributes = new pthread_attr_t;
        m_Id = new pthread_t;
        m_Mutex = NewMutex();
        m_Stop = false;
        m_IsDeleted = false;
        
        
        //Initiallize attributes - 
        PThreadCheck(pthread_attr_init(m_Attributes) );
        // Set Detached thread - means that thread is independend and must behave like that
        // when no longer exist's for example , then all the space that once have now must 
        // be freed and no longer exist (not let it became zombie thread, waiting for someone to free him
        // with a join call )
        PThreadCheck(pthread_attr_setdetachstate(m_Attributes , PTHREAD_CREATE_DETACHED ));
        int dontCare;
        //set thread cancelable
        PThreadCheck(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE , &dontCare));
        //make a cancel request pending until the next cancle point
        PThreadCheck(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , &dontCare));
    }

    PThread::~PThread(void){
        Cancel(this);
    }

    void PThread::SetRunnable(Runnable* runnable) {
        
        if (!runnable){
            FLUSH_ASSERT(0 , "SetRunnable(Runnable* runnable) runnable is nullptr !!!", 0);
            m_Runnable = &NullRunnable;
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



        PThreadCheck(pthread_create(m_Id , m_Attributes , m_PthreadEntry , this) );

         
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

        PThreadCheck(pthread_cancel( *th.m_Id));
    }

    void PThread::Stop(void) {
        m_Mutex->Lock();
        m_Stop = true;
        m_Mutex->UnLock();
    }

    void PThread::Start(void) {
        m_Mutex->Lock();
        m_Stop = false;
        m_Mutex->UnLock();
    }

    bool PThread::IsStopped(void) const {
        bool res;
        m_Mutex->Lock();
        res = m_Stop;
        m_Mutex->UnLock();

        return res;
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