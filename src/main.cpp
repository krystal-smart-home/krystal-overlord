#include <iostream>

#include "core/Logger.h"
#include "core/ServiceManager.hpp"
#include "supervisor/SupervisorService.h"

using namespace krystal;

int main() {
    core::initLogging();
    KRYSTAL_INFO("Logger set up");

    krystal::core::ServiceManager serviceManager;

	auto supervisorService = std::make_shared<supervisor::SupervisorService>();

	serviceManager.registerService(supervisorService);


	serviceManager.start();

    return 0;
}
