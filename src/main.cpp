#include "core/Log.h"
#include "service/ServiceManager.h"

#include "device/DeviceSession.h"

using namespace krystal;

int main() {
    core::initLogging();
    KRYSTAL_INFO("Logger initialized.");

    auto serviceThreadFactory = std::make_shared<service::ServiceThread::Factory>();
    service::ServiceManager serviceManager { serviceThreadFactory };

    serviceManager.start();

    KRYSTAL_INFO("Finished, bye.");
    return 0;
}
