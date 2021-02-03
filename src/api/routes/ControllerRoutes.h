#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include "Routes.h"
#include "api/RouterWrapper.h"
#include "api/controllers/ControllersController.h"

using Pistache::Http::ResponseWriter;
using Pistache::Rest::Request;
using namespace Pistache;

using namespace Pistache::Rest;

namespace krystal::api::routes {

using namespace controllers;

class ControllerRoutes : public Routes {
public:
    ControllerRoutes(std::shared_ptr<ControllersController> controller)
        : m_controllersController(controller) {
    }

    void setup(const std::string& version, RouterWrapper& router) {
        router.get(version + "/controller", router.bindSafe(&ControllerRoutes::controllerGet, this));
        router.get(version + "/controller/:id", router.bindSafe(&ControllerRoutes::controllerIdGet, this));
    }

private:
    void controllerGet(const Request& req, ResponseWriter& res) {
        res.send(Http::Code::Ok, "Hello world");
    }

    void controllerIdGet(const Request& req, ResponseWriter& res) {
        res.send(Http::Code::Ok, "Hello world");
    }

    std::shared_ptr<ControllersController> m_controllersController;
};
}
