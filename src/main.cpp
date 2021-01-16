#include <iostream>

#include "core/Logger.h"
#include "core/ServiceManager.hpp"

using namespace krystal;

int main() {
    core::initLogging();
    KRYSTAL_INFO("Logger set up");

    krystal::core::ServiceManager serviceManager;

    return 0;
}
