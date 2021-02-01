#pragma once

#include <memory>

#include "WebServer.h"
#include "controllers/ControllersController.h"
#include "core/Service.h"
#include "routes/ControllerRoutes.h"

namespace krystal::api {

class ApiService : public core::Service {
public:
    explicit ApiService();

    core::ServiceState update(const xvent::EventProvider& eventProvider) override;

	void start() override;
    void stop() override;

private:
    WebServer m_webServer;

    std::shared_ptr<controllers::ControllersController> m_controllersController;

    routes::ControllerRoutes m_controllerRoutes;
};
}
