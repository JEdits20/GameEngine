#include <array>
#include <queue>
#include <atomic>
#include <mutex>
#include <memory>

template<typename T, size_t RingCapacity>
class SingleProducerSingleConsumerQueue {
public:
    SingleProducerSingleConsumerQueue() : head(0), tail(0) {}

    bool push(std::unique_ptr<T> item) {
        size_t currentTail = tail.load(std::memory_order_relaxed);
        size_t nextTail = (currentTail + 1) % RingCapacity;

        if (nextTail == head.load(std::memory_order_acquire)) {
            std::lock_guard lock(overflowMutex);
            fallbackQueue.push(std::move(item));
            return false;
        }

        ring[currentTail] = std::move(item);
        tail.store(nextTail, std::memory_order_release);
        return true;
    }

    std::unique_ptr<T> pop() {
        size_t currentHead = head.load(std::memory_order_relaxed);
        if (currentHead == tail.load(std::memory_order_acquire)) {
            std::lock_guard lock(overflowMutex);
            if (fallbackQueue.empty()) return nullptr;

            auto event = std::move(fallbackQueue.front());
            fallbackQueue.pop();
            return event;
        }

        auto item = std::move(ring[currentHead]);
        head.store((currentHead + 1) % RingCapacity, std::memory_order_release);
        return item;
    }

    size_t overflowSize() const {
        std::lock_guard lock(overflowMutex);
        return fallbackQueue.size();
    }

private:
    std::array<std::unique_ptr<T>, RingCapacity> ring;
    std::atomic<size_t> head;
    std::atomic<size_t> tail;

    mutable std::mutex overflowMutex;
    std::queue<std::unique_ptr<T>> fallbackQueue;
};