#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>

namespace krystal::containers {

template <typename K, typename V>
class AtomicMap {
    class Proxy {
    public:
        explicit Proxy(std::shared_ptr<V> data, std::lock_guard<std::mutex>&& guard)
            : m_data(data)
            , m_guard(guard) {
        }

        std::shared_ptr<V> operator->() {
            return m_data;
        }

    private:
        std::shared_ptr<V> m_data;
        std::lock_guard<std::mutex> m_guard;
    };

    template <typename T>
    using GuardedValue = std::pair<std::mutex, std::shared_ptr<T>>;

public:
    std::lock_guard<std::mutex> lock() {
        return std::lock_guard<std::mutex>{ m_mutex };
    }

    bool hasKey(const K& key) {
        return m_map.contains(key);
    }

    bool canAcquireValue(const K& key) {
        std::lock_guard guard{ m_mutex };

        if (auto& mutex = m_map[key].first; mutex.try_lock()) {
            mutex.release();
            return true;
        }
        return false;
    }

    Proxy operator[](const K& key) {
        return at(key);
    }

    Proxy at(const K& key) {
        std::lock_guard guard{ m_mutex };

        auto& v = m_map[key];
        return Proxy{ v.first, std::lock_guard{ v.second } };
    }

private:
    std::mutex m_mutex;
    std::unordered_map<K, GuardedValue<V>> m_map;
};
}
