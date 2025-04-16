#include <Definitions.hpp>
#include <Thread/Thread.hpp>
#include <Thread/Mutex.hpp>
#include <Thread/Condition.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace Flush;

bool pingTurn = true;
Mutex* mutex = NewMutex();

Thread* thrPing  = NewThread();
Thread* thrPong  = NewThread();
Thread* thrTimer = NewThread();



class Ping : public Runnable {

    public:



    virtual void Loop(void) override {
        mutex->Lock();
        pingTurn = false;
        printf("Ping\n");
        mutex->UnLock();
        while(pingTurn == false) sleep(1);
    }

    virtual void Init(void) override {
        printf( "Ping Hi !!! \n" );
        __flush_breakpoint;
    }

    virtual void Fini(void) override {
        printf( "Ping Bye !!! \n" );
        if (!pingTurn && mutex->IsLock())
            mutex->UnLock();
        __flush_breakpoint;
    }

    virtual void Stop(void) override {
        printf( "Ping Stop !!! \n" );
        
    }

    virtual void Start(void) override {
        printf( "Ping Start !!!\n");
    }

};

class Pong : public Runnable {

    public:



    virtual void Loop(void) override {
        mutex->Lock();
        pingTurn = true;
        printf("Pong\n");
        mutex->UnLock();
        while(pingTurn) sleep(1);
    }

    virtual void Init(void) override {
        printf( "Pong Hi !!! \n" );
        __flush_breakpoint;
    }

    virtual void Fini(void) override {
        printf( "Pong Bye !!! \n" );
        if (pingTurn && mutex->IsLock())
            mutex->UnLock();

        __flush_breakpoint;
    }

    virtual void Stop(void) override {
        printf( "Pong Stop !!! \n" );
        
    }

    virtual void Start(void) override {
        printf( "Pong Start !!!\n");
    }

};

class Timer : public Runnable {
    public:



    virtual void Loop(void) override {
        usleep(2);
        thrPing->Stop();
        thrPong->Stop();
        usleep(2);
        thrPing->Start();
        thrPong->Start();
        
    }

    virtual void Init(void) override {
        printf( "Timer Hi !!! \n" );
        __flush_breakpoint;
    }

    virtual void Fini(void) override {
        printf( "Timer Bye !!! \n" );
        __flush_breakpoint;
    }

    virtual void Stop(void) override {
        printf( "Timer Stop !!! \n" );
        
    }

    virtual void Start(void) override {
        printf( "Timer Start !!!\n");
    }
};

Runnable* ping = new Ping();
Runnable* pong = new Pong();
Runnable* timer= new Timer();

int main(int argc , char** argv){
    thrTimer->SetRunnable(timer);
    thrPing->SetRunnable(ping);
    thrPong->SetRunnable(pong);


    thrPing->Create();
    thrPong->Create();
    thrTimer->Create();

    std::cin.get();
    thrTimer->Stop();
    std::cin.get();
    Cancel(thrTimer);
    Cancel(thrPing);
    Cancel(thrPong);
    std::cin.get();
    return 0;
}