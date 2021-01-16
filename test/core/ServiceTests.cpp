#include <gtest/gtest.h>

#include "core/Service.h"

using namespace krystal::core;

namespace {

TEST(ServiceTests, givenService_whenGettingName_shouldReturnProperName) {
    static const std::string name = "testService";

    struct TestService : Service {
        TestService()
            : Service(name) {}

        void start() override {}
        void stop() override {}
        void update(std::atomic_bool& isRunning) override {}
    };

    TestService testService;
    EXPECT_EQ(testService.getName(), name);
}
}
