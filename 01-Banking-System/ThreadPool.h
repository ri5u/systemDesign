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
    std::queue<std::function<void()>> tasksQueue;
    std::mutex queueMutex;
    std::counting_semaphore<100000> taskSemaphore;
    std::atomic<bool> stopFlag;

    void workerLoop();

public:
    ThreadPool();
    ~ThreadPool();
    void start(); 
    void stop();
    void pushTask(std::function<void()> task);
};
