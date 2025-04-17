#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
    void Init();
    void Destroy();
    void QueueJob(const std::function<void()>& job);
    bool Busy();

private:
    // Each thread should be running on its own thread loop, waiting for a new job
    void ThreadLoop();

    // Tells threads to stop looking for jobs
    bool should_terminate = false;

    // Queue of jobs
    std::queue<std::function<void()>> jobs;

    // Prevent data races to the jobs queue
    std::mutex queue_mutex;

    // Allow jobs to wait on new jobs or termination
    std::condition_variable mutex_condition;

    std::vector<std::thread> threads;
};
