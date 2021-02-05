#pragma once

#include <pistache/http.h>

#include "Routes.h"
#include "api/RouterWrapper.h"
#include "api/controllers/ControllersController.h"

using Pistache::Http::ResponseWriter;
using Pistache::Rest::Request;

namespace krystal::api::routes {

using namespace controllers;

class ControllerRoutes : public Routes {
public:
    ControllerRoutes(std::shared_ptr<ControllersController> controller);

    void setup(const std::string& version, RouterWrapper& router);

private:
    void controllerGet(const Request& req, ResponseWriter& res);
    void controllerIdGet(const Request& req, ResponseWriter& res);

    std::shared_ptr<ControllersController> m_controllersController;
};
}
