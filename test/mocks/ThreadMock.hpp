#include <gmock/gmock.h>

#include "core/Thread.h"

struct ThreadMock : public krystal::core::IThread {
    template <typename Function, typename... Args>
    explicit ThreadMock(Function&& function, Args&&... args) {
        std::invoke<Function, Args...>(std::forward<Function>(function), std::forward<Args>(args)...);
        ++ctorCalls;
    }

    void join() override {
        ++joinCalls;
    }

    static void clear() {
        ctorCalls = 0;
        joinCalls = 0;
    }

    inline static int ctorCalls = 0;
    inline static int joinCalls = 0;
};
