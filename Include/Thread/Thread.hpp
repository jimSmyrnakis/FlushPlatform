#pragma once

#include "Definitions.hpp"

namespace Flush{
    
    

    typedef u32 (*Entry)(void);

    
    class Thread{
        
        protected:
                    Thread (void) = default;
            virtual ~Thread(void) = default;
        public:
            virtual void    SetEntry(Entry entry)         = 0;
            virtual Entry   GetEntry(void)          const = 0;
            virtual void    Create(void)                  = 0;
      
        private:

            friend Thread* NewThread(void);
            friend void DeleteThread(Thread* ptr);
    };

    Thread* NewThread(void);
    void DeleteThread(Thread* ptr);

}