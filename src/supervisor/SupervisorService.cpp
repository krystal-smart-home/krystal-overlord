#include "SupervisorService.h"

namespace krystal::supervisor {

#define BIND_CALLBACK(function) std::bind(&SupervisorService::function, this, std::placeholders::_1)

SupervisorService::SupervisorService()
    : core::Service("SupervisorService") {
}

core::ServiceState SupervisorService::update(const xvent::EventProvider& eventProvider) {
    auto events = eventProvider.getAll();

    KRYSTAL_INFO("Received {} events", events.size());
    for (auto& event : events) {
        KRYSTAL_INFO("Handling event");

        event->on<event::NewControllerConnected>(BIND_CALLBACK(onNewControllerConnected));
        event->on<event::NewDeviceConnected>(BIND_CALLBACK(onNewDeviceConnected));
        event->on<event::GetControllers>(BIND_CALLBACK(onGetControllers));
    }

    return core::ServiceState::active;
}

void SupervisorService::start() {
}

void SupervisorService::stop() {
}

void SupervisorService::onGetControllers(std::shared_ptr<event::GetControllers> event) {
    std::vector<device::ControllerModel> controllers;
    for (auto& [_, controller] : m_controllers)
        controllers.emplace_back(controller->getModel());

    event->setResult<event::Controllers>(controllers);
}

void SupervisorService::onNewControllerConnected(std::shared_ptr<event::NewControllerConnected> event) {
    auto controller = std::make_shared<device::Controller>(event->name);
    auto id = controller->getId();
    m_controllers[id] = controller;

    event->setResult<event::NewControllerRegistered>(id);
}

void SupervisorService::onNewDeviceConnected(std::shared_ptr<event::NewDeviceConnected> event) {
    event->setResult<event::NewDeviceRegistered>();
}
}
