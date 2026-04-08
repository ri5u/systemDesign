#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <semaphore>
#include <atomic>

class ThreadPool{
private: 
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::counting_semaphore<1000000> taskSemaphore;
    std::atomic<bool> stopFlag;
    size_t numThreads;

    void workerLoop();


public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    void start(); 
 
    void stop();
    void pushTask(std::function<void()> task);
};
