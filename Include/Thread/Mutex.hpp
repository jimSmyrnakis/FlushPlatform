#pragma once 

#include "../Definitions.hpp"

namespace Flush{
    class Mutex{

        protected:
            Mutex(void) = default;
            virtual ~Mutex(void) = default;
        public:
            virtual void Lock(void)   = 0;
            virtual void UnLock(void) = 0;
            virtual bool IsLock(void) = 0;


            Mutex(const Mutex& _cp) = delete;
            Mutex(Mutex&& _mv) = delete;
            Mutex& operator=(const Mutex& ) = delete;
            Mutex& operator=(Mutex&& )  = delete;

        private:

            friend Mutex* NewMutex(void);
            friend void DeleteMutex(Mutex* ptr);
        
    };

    Mutex* NewMutex(void);
    void DeleteMutex(Mutex* ptr);
}