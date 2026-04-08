#include "ThreadPool.h"
#include <functional>
#include <mutex>
#include <thread>

ThreadPool::ThreadPool(size_t numThreads) : taskSemaphore(0) , stopFlag(false), numThreads(numThreads) {}

void ThreadPool::start() {
    for(size_t i = 0; i < numThreads; i++){
        workers.emplace_back(&ThreadPool::workerLoop, this);
    }
}

void ThreadPool::workerLoop() {
    while(true) {
        taskSemaphore.acquire();
        if(stopFlag) break;
        std::function<void()> task;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if(tasks.empty()) continue;
            task = std::move(tasks.front());
            tasks.pop();
        }

        task();
    }
}

void ThreadPool::pushTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
    }
    taskSemaphore.release(); 
}

void ThreadPool::stop() {
    if (stopFlag) return;
    stopFlag = true;
    taskSemaphore.release(workers.size());
    for(std::thread& active_workers : workers){
        if (active_workers.joinable()) {
            active_workers.join();
        }
    }
    workers.clear();
}

ThreadPool::~ThreadPool() {
    stop();
}
