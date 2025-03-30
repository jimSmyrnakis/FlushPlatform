#include "PCondition.hpp"
#include "PThread.hpp"

namespace Flush{

    PCondition::PCondition(void){
        // allocate the space for this cross threads variables
        m_Mutex = (PMutex*)NewMutex();
        m_Id = new pthread_cond_t;
        m_Attributes = new pthread_condattr_t;

        PThreadCheck( pthread_condattr_init(m_Attributes) );

        PThreadCheck( pthread_cond_init(m_Id , m_Attributes) );

    }

    PCondition::~PCondition(void){

        PThreadCheck( pthread_condattr_destroy(m_Attributes) );
        PThreadCheck( pthread_cond_destroy(m_Id) );


        // free the space for these cross threads variables
        if (m_Id)
            delete m_Id;
        
        if (m_Attributes)
            delete m_Attributes;

        DeleteMutex(m_Mutex);

    }

    Mutex& PCondition::GetMutex(void) { return *m_Mutex; }
    void PCondition::Signal(void)   {
        FLUSH_ASSERT(m_Id , " OUT OF MEMORY !!!", 0);
        FLUSH_ASSERT(m_Attributes , " OUT OF MEMORY !!!", 0);
        PThreadCheck ( pthread_cond_broadcast(m_Id) );
    }
    void PCondition::Wait(void)     {
        FLUSH_ASSERT(m_Id , " OUT OF MEMORY !!!", 0);
        FLUSH_ASSERT(m_Attributes , " OUT OF MEMORY !!!", 0);
        PThreadCheck ( pthread_cond_wait(m_Id , m_Mutex->GetId()) );
    }

    Condition* NewCondition(void){
        return new PCondition();
    }

    void DeleteCondition(Condition* ptr){
        delete ptr;
    }
}