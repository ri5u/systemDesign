#include "ThreadPool.h"
#include <functional>
#include <mutex>
#include <thread>
ThreadPool::ThreadPool() : taskSemaphore(0) , stopFlag(false) {}
void ThreadPool::start() {
    const int num_workers = std::thread::hardware_concurrency();
    // const int num_workers = 2;
    for(int i = 0; i < num_workers; i++){
        workers.emplace_back(std::thread(&ThreadPool::workerLoop, this));
    }
}

void ThreadPool::workerLoop() {
    while(true) {
        taskSemaphore.acquire();
        if(stopFlag) break;
        std::function<void()> task;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if(tasksQueue.empty()) continue;
            task = tasksQueue.front();
            tasksQueue.pop();
        }

        task();
    }
}

void ThreadPool::pushTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasksQueue.push(task);
    }
    taskSemaphore.release(); 
}

void ThreadPool::stop() {
    stopFlag = true;
    taskSemaphore.release(workers.size());
    for(std::thread& active_workers : workers){
        active_workers.join();
    }
    workers.clear();
}

ThreadPool::~ThreadPool() {
    ThreadPool::stop();
}
