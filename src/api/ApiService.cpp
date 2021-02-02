#include "ApiService.h"

namespace krystal::api {

ApiService::ApiService()
    : core::Service("ApiService")
    , m_webServer(8888) {}

core::ServiceState ApiService::update(const xvent::EventProvider& eventProvider) {
    return core::ServiceState::active;
}

void ApiService::start() {
	m_controllersController = std::make_shared<controllers::ControllersController>(m_eventEmitter->clone());
	m_controllerRoutes = std::make_shared<routes::ControllerRoutes>(m_controllersController);


	auto& router = m_webServer.getRouter();
    const std::string version = "/v1";

    m_controllerRoutes->setup(version, router);

    m_webServer.start();
}

void ApiService::stop() {
    m_webServer.stop();
}
}
