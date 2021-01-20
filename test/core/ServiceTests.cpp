#include <gtest/gtest.h>

#include "core/Service.h"

#include "mocks/ServiceMock.hpp"

using namespace krystal::core;

namespace {

TEST(ServiceTests, givenService_whenGettingName_shouldReturnProperName) {
    static const std::string name = "testService";

    ServiceMock service(name);

    EXPECT_EQ(service.getName(), name);
}
}
