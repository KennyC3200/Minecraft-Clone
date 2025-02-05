#ifndef ThreadPool_HPP
#define ThreadPool_HPP

#include <functional>
#include <thread>

namespace Utils {
class ThreadPool {
public:
    void Start();
    void QueueJob(std::function<void()>& job);
    void Stop();
    void Busy();

private:
    void ThreadLoop();

    bool should_terminate = false;
    std::mutex queue_mutex;
    std::condition_variable mutex_condition;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
};
}

#endif
