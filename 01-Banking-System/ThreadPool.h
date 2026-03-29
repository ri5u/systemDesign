#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <semaphore>
#include <atomic>

class ThreadPool{
private: 
    //all the workers thread
    std::vector<std::thread> workers;

    //The task queue
    std::queue<std::function<void()>> tasks;
    
    std::mutex queueMutex;
    std::counting_semaphore<100> taskSemaphore(100);

    std::atomic<bool> stopFlag;

    void workerLoop();

public:
    ThreadPool(size_t numThread);
    ~ThreadPool();
    
    void pushTask(std::function<void()> task);
};
