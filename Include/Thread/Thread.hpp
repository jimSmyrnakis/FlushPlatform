#pragma once

#include "Definitions.hpp"

namespace Flush{
    
    

    

    class Runnable{
        public:
            virtual void Loop(void) = 0;
            virtual void Init(void) = 0;
            virtual void Fini(void) = 0; 

            virtual void Stop(void)  = 0;
            virtual void Start(void) = 0;
    };
    
    class Thread{
        
        protected:
                    Thread (void) = default;
            virtual ~Thread(void) = default;
        public:

            virtual void SetRunnable(Runnable* runnable) = 0;
            virtual Runnable* GetRunnable(void) const = 0;

            virtual void Create(void) = 0;

            virtual void Stop(void) = 0;
            virtual void Start(void) = 0;

            virtual bool IsStopped(void) const = 0;

      
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