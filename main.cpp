#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <random>

#include "Scheduler.hpp"

using namespace std;

std::multimap <std::string, time_t> threadsToRun =
{
    {"First Thread",  1 },
    {"Second Thread", 2 },
    {"Third Thread",  2 },
    {"Four Thread",   2 },
    {"Five Thread",   5 },
    {"Six Thread",    6 },
    {"Seven Thread",  7 }
};

int main()
{

    time_t nowTimestamp = time(NULL);

    Scheduler scheduler;

    for( const auto& [description, extraTime] : threadsToRun )
    {

        auto threadSample = [description](){ while(1) { cout << description << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(1000)); } return;};

        scheduler.add( threadSample, nowTimestamp + extraTime );

    }

    scheduler.run();

    uint32_t cycleThreadNumber = 0;

    while(1)
    {

        nowTimestamp = time(NULL);

        auto threadSample = [cycleThreadNumber](){ cout << "Cycle thread " << cycleThreadNumber << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(1000)); };

        scheduler.add( threadSample, nowTimestamp );

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        cycleThreadNumber += 1;

    }

    return 0;

}
