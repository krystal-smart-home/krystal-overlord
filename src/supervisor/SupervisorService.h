#pragma once

#include <memory>
#include <unordered_map>

#include "core/Logger.h"
#include "core/Service.h"
#include "device/Controller.h"
#include "device/Device.h"

#include "event/api/GetControllers.h"
#include "event/device/NewController.h"
#include "event/device/NewDevice.h"


namespace krystal::supervisor {

class SupervisorService : public core::Service {
public:
    explicit SupervisorService();

    core::ServiceState update(const xvent::EventProvider& eventProvider) override;

    void start() override;
    void stop() override;

private:
    void onGetControllers(std::shared_ptr<event::api::GetControllers::Request> event);
    void onNewController(std::shared_ptr<event::device::NewController::Request> event);
    void onNewDevice(std::shared_ptr<event::device::NewDevice::Request> event);

    std::unordered_map<int, std::shared_ptr<device::Controller>> m_controllers;
};
}
