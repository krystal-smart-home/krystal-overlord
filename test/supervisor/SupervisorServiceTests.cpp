#include <gtest/gtest.h>

#include "supervisor/SupervisorService.h"

#include "mocks/EventProviderWrapper.hpp"

using namespace testing;
using namespace krystal;
using namespace krystal::supervisor;

namespace {

class SupervisorServiceTests : public Test {
public:
    void SetUp() override {
        m_supervisorService.start();
    }

    void TearDown() override {
        m_supervisorService.stop();
    }

    EventProviderWrapper m_eventProviderWrapper;
    SupervisorService m_supervisorService;
};

TEST_F(SupervisorServiceTests, givenControllerConnected_whenProcessingBySupervisorService_shouldResponseWithId) {
    const std::string controllerName = "name";
    auto result = m_eventProviderWrapper.pushEvent<event::device::NewController::Request>(controllerName);

    m_supervisorService.update(m_eventProviderWrapper.get());

    auto res = result.wait();
    ASSERT_TRUE(res->is<event::device::NewController::Response>());
    ASSERT_EQ(res->as<event::device::NewController::Response>()->controllerId, 0);
}
}
