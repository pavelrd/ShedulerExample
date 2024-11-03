#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <functional>
#include <map>
#include <mutex>

class Scheduler
{
public:

    void add(std::function<void()> task, std::time_t timestamp);
    void run();
    void stop();

private:

    struct TaskInfo
    {
        std::function<void()> functionToRun;
        bool runned = false;
    };

    std::multimap <std::time_t, TaskInfo> threads;

    void controlWorker();

    void controlCycle();

    std::mutex mutexAddLock;

    bool runned = false;

    enum
    {
        QUANTUM_TIME_MS = 100
    };

};


#endif
