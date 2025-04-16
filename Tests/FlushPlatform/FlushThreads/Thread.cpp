#include <Definitions.hpp>
#include <Thread/Thread.hpp>
#include <Thread/Mutex.hpp>
#include <Thread/Condition.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace Flush;

class TestRunnable : public Runnable {

    public:

    virtual void Loop(void) override {
        printf( "Hi this is a loop method !!! \n" );
        
    }

    virtual void Init(void) override {
        printf( "Hi !!! \n" );
    }

    virtual void Fini(void) override {
        printf( "Bye !!! \n" );
    }

    virtual void Stop(void) override {
        printf( " Stopped !!!\n");
    }

    virtual void Start(void) override {
        printf("Started !!!\n");
    }

};

int main(int argc , char** argv){
    Thread* thr = NewThread();
    Runnable* run = new TestRunnable();
    thr->SetRunnable(run);
    thr->Create();

    std::cin.get();
    thr->Stop();
    std::cin.get();
    thr->Start();
    std::cin.get();
    Cancel(thr);
    std::cin.get();
    return 0;
}