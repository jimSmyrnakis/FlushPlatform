#pragma once

#include "Mutex.hpp"

namespace Flush{
    class Condition{
        protected:
            Condition(void);
            virtual ~Condition(void);

        public:

            virtual Mutex& GetMutex(void)   = 0 ;
            virtual void Signal(void)       = 0 ;
            virtual void Wait(void)         = 0 ;

        private:
            friend Condition* NewCondition(void);
            friend void DeleteCondition(Condition* ptr);
    };

    Condition* NewCondition(void);
    void DeleteCondition(Condition* ptr);
}