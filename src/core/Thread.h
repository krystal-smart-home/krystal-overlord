#pragma once

#include <thread>

namespace krystal::core {

struct IThread {
    virtual void join() = 0;
};

class Thread : public IThread {
public:
    template <typename Function, typename... Args>
    explicit Thread(Function&& function, Args&&... args)
        : m_thread(std::forward<Function>(function), std::forward<Args>(args)...) {}

    void join() override {
        m_thread.join();
    }

private:
    std::thread m_thread;
};
}
