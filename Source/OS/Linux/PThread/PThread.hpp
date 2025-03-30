#include <Thread/Thread.hpp>
#include <pthread.h>

#define PThreadCheck(function) if ((function) != 0) \
{  LOG_ENGINE_ERROR( "pthread error ( line %d , function: %s , file: %s) - function failed " , __LINE__ , #function , __FILE__); }

namespace Flush{
    typedef void* (*PEntry)(void*);
    class UniquePThread : public Thread{
        public:
            UniquePThread(void) ;
            virtual ~UniquePThread(void);

            virtual void SetEntry(Entry  entry) override;
            virtual Entry  GetEntry(void) const override;

            virtual void Create(void) override;

        private:
            pthread_attr_t  m_Attributes    ;
            pthread_t       m_Id            ;
            Entry           m_Entry         ;
            PEntry          m_PthreadEntry  ;
            pthread_once_t  m_InitOnce      ;
            bool            m_HasCreated    ;

        private:

            friend Thread* NewThread(void);
            friend void DeleteThread(Thread* ptr);
    };
}