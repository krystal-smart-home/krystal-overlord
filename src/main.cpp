#include <iostream>

#include "api/ApiService.h"
#include "core/Logger.h"
#include "core/ServiceManager.hpp"
#include "core/Thread.h"
#include "supervisor/SupervisorService.h"
#include "transmission/TransmissionService.hpp"
#include "transmission/net/TcpSocket.h"

using namespace krystal;

int main() {
    core::initLogging();
    KRYSTAL_INFO("Logger set up");

    krystal::core::ServiceManager serviceManager;

    auto socketFactory = std::make_shared<transmission::net::TcpSocket::Factory>();

    auto supervisorService = std::make_shared<supervisor::SupervisorService>();
    auto transmissionService = std::make_shared<transmission::TransmissionService<core::Thread>>(socketFactory);
    auto apiService = std::make_shared<api::ApiService>();

    serviceManager.registerService(supervisorService);
    serviceManager.registerService(transmissionService);
    serviceManager.registerService(apiService);

    serviceManager.start();

    return 0;
}
