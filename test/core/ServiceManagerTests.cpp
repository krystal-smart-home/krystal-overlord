#include <gtest/gtest.h>

#include "core/ServiceManager.hpp"

#include "mocks/ServiceMock.hpp"
#include "mocks/ThreadMock.hpp"

using namespace testing;
using namespace krystal::core;

namespace {

class ServiceManagerTests : public testing::Test {
    void SetUp() override {
        ThreadMock::clear();
    }
};

TEST_F(ServiceManagerTests, givenServiceManagerAndRegisteredService_whenStartingManager_shouldCallStartAndStop) {
    ServiceManager<ThreadMock> manager;

    auto service = std::make_shared<ServiceMock>();

    EXPECT_CALL(*service, update(_)).Times(1).WillOnce(Return(ServiceState::finished));
    EXPECT_CALL(*service, start()).Times(1);
    EXPECT_CALL(*service, stop()).Times(1);

    manager.registerService(service);
    manager.start();

    EXPECT_EQ(ThreadMock::joinCalls, 1);
    EXPECT_EQ(ThreadMock::ctorCalls, 1);
}

TEST_F(ServiceManagerTests, givenServiceManagerAndTwoRegisteredServices_whenStartingManager_shouldCallStartAndStop) {
    ServiceManager<ThreadMock> manager;
    auto service = std::make_shared<ServiceMock>("s1");
    auto service2 = std::make_shared<ServiceMock>("s2");

    manager.registerService(service);
    manager.registerService(service2);

    EXPECT_CALL(*service, start()).Times(1);
    EXPECT_CALL(*service, stop()).Times(1);

    EXPECT_CALL(*service2, start()).Times(1);
    EXPECT_CALL(*service2, stop()).Times(1);

    EXPECT_CALL(*service, update(_)).Times(1).WillOnce(Return(ServiceState::finished));
    EXPECT_CALL(*service2, update(_)).Times(1).WillOnce(Return(ServiceState::finished));

    manager.start();

    EXPECT_EQ(ThreadMock::ctorCalls, 2);
    EXPECT_EQ(ThreadMock::joinCalls, 2);
}
}
