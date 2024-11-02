#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <functional>
#include <map>

class Scheduler
{
public:

    void add(std::function<void()> task, std::time_t timestamp);
    void run();

private:

    std::multimap <std::time_t, std::function<void()>> threads;

    void controlWorker();

};


#endif
