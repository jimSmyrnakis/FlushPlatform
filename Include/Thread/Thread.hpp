#pragma once

#include "Definitions.hpp"

namespace Flush{
    
    

    typedef u32  (*Run)(void);
    typedef u32  (*Initiallize)(void);
    typedef u32  (*Finallize)(void);
    typedef u32  (*Stop)(void);
    typedef void (*CRoutine)(void* args);

    class Runnable{
        public:
            virtual u32 Run(void) = 0;
            virtual u32 Start(void) = 0;
            virtual u32 Stop(void) = 0; 
    };
    
    class Thread{
        
        protected:
                    Thread (void) = default;
            virtual ~Thread(void) = default;
        public:

            virtual void SetRunnable(Runnable* runnable) = 0;
            virtual Runnable* GetRunnable(void) const = 0;

            virtual void Create(void) = 0;
      
        private:
            friend void TestCancel(void); 
            friend void Cancle(Thread* thread);
            friend Thread* NewThread(void);
            friend void DeleteThread(Thread* ptr);
    };

    void TestCancel(void);
    void Cancel(Thread* thread);
    Thread* NewThread(void);
    void DeleteThread(Thread* ptr);

     

}