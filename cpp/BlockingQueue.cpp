#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

//$ g++ -dM -E -x c++ /dev/null | grep __cplusplus
//#define __cplusplus 201703L

#if __cplusplus >= 201703L
#include <optional>
#endif

template<typename T>
class BlockingQueue {
public:

    explicit BlockingQueue(size_t capacity) 
        : capacity_(capacity) {}

    // 生产者放入任务，队列满则阻塞
    void push(T item) {
        std::unique_lock<std::mutex> lock(mtx_);
        not_full_.wait(lock, [this] {
            return queue_.size() < capacity_ || stopped_;
        });
        
        if (stopped_) return;

        queue_.push(std::move(item));
        not_empty_.notify_one();
    }

#if __cplusplus >= 201703L

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        not_empty_.wait(lock, [this] {
            return !queue_.empty() || stopped_;
        });

        if (queue_.empty()) return std::nullopt;

        T item = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return item;
    }
#else

    //#if __cplusplus == 201402L

    // 消费者取出任务，队列为空则阻塞
    // C++14 没有 std::optional，
    // 这里用 pop(T& item) + bool 返回值
    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        not_empty_.wait(lock, [this] {
            return !queue_.empty() || stopped_;
        });

        if (queue_.empty()) return false;

        item = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return true;
    }


#endif

    void stop() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            stopped_ = true;
        }
        not_full_.notify_all();
        not_empty_.notify_all();
    }

private:

    std::queue<T> queue_;
    size_t capacity_;
    std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    bool stopped_ = false;
};

int main()
{
    BlockingQueue<int> q(5);

    std::thread producer([&q] {
        for (int i = 0; i < 10; ++i) {
            q.push(i);
            std::cout << "push: " << i << "\n";
        }
        q.stop();
    });

    std::thread consumer([&q] {
#if __cplusplus >= 201703L
        while (auto item = q.pop()) {
            std::cout << "pop: " << *item << "\n";
        }
#else
        int item = 0;
        while (q.pop(item)) {
            std::cout << "pop: " << item << "\n";
        }
#endif
    });

    producer.join();
    consumer.join();

    return 0;
}


