#include "SupervisorService.h"

namespace krystal::supervisor {

#define BIND_CALLBACK(function) std::bind(&SupervisorService::function, this, std::placeholders::_1)

SupervisorService::SupervisorService()
    : core::Service("SupervisorService") {
}

core::ServiceState SupervisorService::update(const xvent::EventProvider& eventProvider) {
    auto events = eventProvider.getAll();

    // KRYSTAL_INFO("Received {} events", events.size());
    for (auto& event : events) {
        KRYSTAL_INFO("Handling event");

        // device
        event->on<event::device::NewController::Request>(BIND_CALLBACK(onNewController));
        event->on<event::device::NewDevice::Request>(BIND_CALLBACK(onNewDevice));

        // api
        event->on<event::api::GetControllers::Request>(BIND_CALLBACK(onGetControllers));
    }

    return core::ServiceState::active;
}

void SupervisorService::start() {
}

void SupervisorService::stop() {
}

void SupervisorService::onGetControllers(std::shared_ptr<event::api::GetControllers::Request> event) {
    std::vector<device::ControllerDescription> controllers;
    for (auto& [_, controller] : m_controllers)
        controllers.emplace_back(controller->getModel());

    event->setResult<event::api::GetControllers::Response>(controllers);
}

void SupervisorService::onNewController(std::shared_ptr<event::device::NewController::Request> event) {
    auto controller = std::make_shared<device::Controller>(event->name);
    auto id = controller->getId();
    m_controllers[id] = controller;

    event->setResult<event::device::NewController::Response>(id);
}

void SupervisorService::onNewDevice(std::shared_ptr<event::device::NewDevice::Request> event) {
    event->setResult<event::device::NewDevice::Response>();
}
}
