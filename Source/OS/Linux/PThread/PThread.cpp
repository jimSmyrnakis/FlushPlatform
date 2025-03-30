#include "PThread.hpp"



namespace Flush{

    void* pthreadInit(void* entry){
        
        if (entry == nullptr){
            FLUSH_ASSERT(0 , "Pthread Initiallize thread function has argument of entry nullptr !!!" , 0);
            return NULL;
        }

        Entry ent = (Entry) entry;
        u32 res = ent();

        return NULL;
    }
    
    UniquePThread::UniquePThread(void) {

        m_Entry         = nullptr;
        m_PthreadEntry  = pthreadInit;
        m_HasCreated = false;
        //Initiallize attributes - 
        PThreadCheck(pthread_attr_init(&m_Attributes) );

        // Set Detached thread - means that thread is independend and must behave like that
        // when no longer exist's for example , then all the space that once have now must 
        // be freed and no longer exist (not let it became zombie thread, waiting for someone to free him
        // with a join call )
        PThreadCheck(pthread_attr_setdetachstate(&m_Attributes , PTHREAD_CREATE_DETACHED ));

    }

    UniquePThread::~UniquePThread(void){
        PThreadCheck(pthread_attr_destroy(&m_Attributes));
    }

    void UniquePThread::SetEntry(Entry entry){
        FLUSH_ASSERT(entry , "At SetEntry method - parameter entry is nullptr" , 0);
        m_Entry = *entry;
    }

    Entry UniquePThread::GetEntry(void) const{
        return m_Entry;
    }

    void UniquePThread::Create(void){
        
        if (m_Entry == nullptr){
            FLUSH_ASSERT(0 , "Create Method has no entry function to create the thread entry point !!!" , 0);
            return;
        }

        if (m_HasCreated){
            FLUSH_ASSERT(0 , "Create Method Have already called for this thread " , 0);
            return ;
        }

        PThreadCheck(pthread_create(&m_Id , &m_Attributes , m_PthreadEntry , &m_Entry) );
        
    }

    Thread* NewThread(void){
        return new UniquePThread();
    }

    void DeleteThread(Thread* ptr){
        if (ptr)
            delete ptr;
    }
}