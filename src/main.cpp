#include <iostream>

#include "core/Logger.h"
#include "core/ServiceManager.hpp"
#include "supervisor/SupervisorService.h"
#include "transmission/TransmissionService.h"
#include "api/ApiService.h"

using namespace krystal;

int main() {
    core::initLogging();
    KRYSTAL_INFO("Logger set up");

    krystal::core::ServiceManager serviceManager;

    auto supervisorService = std::make_shared<supervisor::SupervisorService>();
    auto transmissionService = std::make_shared<transmission::TransmissionService>();
	auto apiService = std::make_shared<api::ApiService>();

    serviceManager.registerService(supervisorService);
    serviceManager.registerService(transmissionService);
	serviceManager.registerService(apiService);

    serviceManager.start();

    return 0;
}
