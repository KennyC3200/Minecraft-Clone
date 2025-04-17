#include "thread_pool.h"

void f1(std::vector<int>& nums, int* sum) {
    *sum = 0;
    for (auto& num : nums) {
        *sum += num;
    }
}

void f2(std::vector<int>& nums, int* prod) {
    *prod = 1;
    for (auto& num : nums) {
        *prod *= num;
    }
}

void ThreadPool::Init() {
    // Get max # of threads available
    uint num_threads = std::thread::hardware_concurrency();
    for (uint i = 0; i < num_threads; i++) {
        threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
    }
}

void ThreadPool::Destroy() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (std::thread& active_thread : threads) {
        active_thread.join();
    }
    threads.clear();
}

void ThreadPool::QueueJob(const std::function<void()>& job) {
    // NOTE: Follow RAII. Need local scope for lock destruction and hence automatic unlock of mutex
    {
        // You need a mutex here to ensure that 
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

void ThreadPool::ThreadLoop() {
    while (true) {
        // NOTE: Follow RAII. Need local scope for lock destruction and hence automatic unlock of mutex
        std::function<void()> job;
        {
            // RAII lock
            std::unique_lock<std::mutex> lock(queue_mutex);

            // When first called, it automatically releases the mutex and puts the thread to sleep
            // When condition_variable is notified by some other thread, the thread wakes up
            // Automatically re-acquires mutex
            // Checks parity of predicate (lambda expression)
            mutex_condition.wait(lock, [this] {
                return !jobs.empty() || should_terminate;
            });

            if (should_terminate) {
                return;
            }

            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}

bool ThreadPool::Busy() {
    bool busy;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        busy = !jobs.empty();
    }
    return busy;
}
