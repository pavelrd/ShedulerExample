#include "Scheduler.hpp"
#include <iostream>

void Scheduler::add( std::function<void()> task, std::time_t timestamp )
{

    mutexAddLock.lock();

    TaskInfo info;

    info.functionToRun = task;

    threads.insert( { timestamp, info } );

    mutexAddLock.unlock();

}

void Scheduler::controlWorker()
{

    mutexAddLock.lock();

    time_t currentTime = time(NULL);

    for( auto& [timeToRun, info] : threads )
    {

        if( (!info.runned) && ( currentTime > timeToRun ) )
        {

            std::thread threadToRun(info.functionToRun);

            info.runned = true;

            threadToRun.detach();

        }

    }

    mutexAddLock.unlock();

}

void Scheduler::controlCycle()
{
    while(runned)
    {

        std::thread threadControlWorker(&Scheduler::controlWorker, this);

        threadControlWorker.detach();

        std::this_thread::sleep_for(std::chrono::milliseconds(QUANTUM_TIME_MS));

    }
}

void Scheduler::run()
{

    std::thread threadControlCycle(&Scheduler::controlCycle, this);

    threadControlCycle.detach();

    runned = true;

}

void Scheduler::stop()
{
    runned = false;
}

