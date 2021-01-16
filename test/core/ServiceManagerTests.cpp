#include <gtest/gtest.h>

#include "core/ServiceManager.hpp"

using namespace krystal::core;

namespace {

struct MockThread : public IThread {
    template <typename Function, typename... Args>
    explicit MockThread(Function&& function, Args&&... args) {
        ++ctorCalls;
    }

    void join() override {
        ++joinCalls;
    }

    static void clear() {
        joinCalls = 0;
        ctorCalls = 0;
    }

    inline static int joinCalls = 0;
    inline static int ctorCalls = 0;
};

struct MockService : public Service {
    MockService()
        : Service("MockService") {}

    void update(std::atomic_bool& isRunning) override {
        if (--stopAfterCalls <= 0)
            isRunning = false;
        ++updateCalls;
    }

    void start() override {
        ++startCalls;
    }

    void stop() override {
        ++stopCalls;
    }

    int startCalls = 0;
    int stopCalls = 0;
    int updateCalls = 0;

    int stopAfterCalls = 1;
};

class ServiceManagerTests : public testing::Test {
    void SetUp() override {
        MockThread::clear();
    }
};

TEST_F(ServiceManagerTests, givenServiceManagerAndRegisteredService_whenStartingManager_shouldCallStartAndStop) {
    ServiceManager<MockThread> manager;
    auto service = std::make_shared<MockService>();
    manager.registerService(service);

    manager.start();

    EXPECT_EQ(service->startCalls, 1);
    EXPECT_EQ(service->stopCalls, 1);

    EXPECT_EQ(MockThread::ctorCalls, 1);
    EXPECT_EQ(MockThread::joinCalls, 1);
}

TEST_F(ServiceManagerTests, givenServiceManagerAndTwoRegisteredServices_whenStartingManager_shouldCallStartAndStop) {
    ServiceManager<MockThread> manager;
    auto service = std::make_shared<MockService>();
    auto service2 = std::make_shared<MockService>();

    manager.registerService(service);
    manager.registerService(service2);

    manager.start();

    EXPECT_EQ(service->startCalls, 1);
    EXPECT_EQ(service->stopCalls, 1);

    EXPECT_EQ(service2->startCalls, 1);
    EXPECT_EQ(service2->stopCalls, 1);

    EXPECT_EQ(MockThread::ctorCalls, 2);
    EXPECT_EQ(MockThread::joinCalls, 2);
}
}
