#include "Scheduler.hpp"
#include <iostream>

void Scheduler::add(std::function<void()> task, std::time_t timestamp)
{
    threads.insert( std::pair<std::time_t, std::function<void()>>(timestamp, task) );
}

void Scheduler::controlWorker()
{

    time_t currentTime = time(NULL);

    for( const auto& [timeToRun, function] : threads )
    {

        if( currentTime == timeToRun )
        {

            std::thread threadToRun(function);

            threadToRun.detach();

        }

    }

}



void Scheduler::run()
{

    while(1)
    {

        std::thread threadControlWorker(&Scheduler::controlWorker, this);

        threadControlWorker.detach();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    }

}
