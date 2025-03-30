#pragma once

#include <Thread/Condition.hpp>
#include <pthread.h>
#include "PMutex.hpp"

namespace Flush{
    class PCondition : public Condition{

        protected:
            PCondition(void);
            virtual ~PCondition(void);

        public:
            virtual Mutex& GetMutex(void) override;
            virtual void Signal(void)   override;
            virtual void Wait(void)     override;

        private:
            PMutex*                 m_Mutex;

            pthread_cond_t*         m_Id ;
            pthread_condattr_t*     m_Attributes;

            friend Condition* NewCondition(void);
            friend void DeleteCondition(Condition* ptr);

    };


}