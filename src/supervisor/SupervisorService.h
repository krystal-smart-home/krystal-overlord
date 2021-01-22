#pragma once

#include <memory>
#include <unordered_map>

#include "core/Logger.h"
#include "core/Service.h"
#include "device/Controller.h"
#include "device/Device.h"
#include "event/DeviceEvents.h"

namespace krystal::supervisor {

#define BIND_CALLBACK(function) std::bind(&SupervisorService::function, this, std::placeholders::_1)

class SupervisorService : public core::Service {
public:
    explicit SupervisorService();

    core::ServiceState update(const xvent::EventProvider& eventProvider) override;

    void start() override;
    void stop() override;

private:
    void onGetControllers(std::shared_ptr<event::GetControllers> event);
    void onNewControllerConnected(std::shared_ptr<event::NewControllerConnected> event);
    void onNewDeviceConnected(std::shared_ptr<event::NewDeviceConnected> event);

    std::unordered_map<int, std::shared_ptr<device::Controller>> m_controllers;
};
}
