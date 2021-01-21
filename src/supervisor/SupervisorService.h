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
    explicit SupervisorService()
        : core::Service("SupervisorService") {
    }

    core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        auto events = eventProvider.getAll();

		KRYSTAL_INFO("Received {} events", events.size());
        for (auto& event : events) {
			KRYSTAL_INFO("Handling event");
			event->on<event::NewControllerConnected>(BIND_CALLBACK(onNewControllerConnected));
            event->on<event::NewDeviceConnected>(BIND_CALLBACK(onNewDeviceConnected));
        }

        return core::ServiceState::active;
    }

    void start() override {
    }

    void stop() override {
    }

private:
    void onNewControllerConnected(std::shared_ptr<event::NewControllerConnected> event) {
        auto controller = std::make_shared<device::Controller>(event->name);
        auto id = controller->getId();
        m_controllers[id] = controller;

        event->setResult<event::NewControllerRegistered>(id);
    }

    void onNewDeviceConnected(std::shared_ptr<event::NewDeviceConnected> event) {
        event->setResult<event::NewDeviceRegistered>();
    }

    std::unordered_map<int, std::shared_ptr<device::Controller>> m_controllers;
};
}
