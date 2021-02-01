#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include "api/controllers/ControllersController.h"

using Pistache::Http::ResponseWriter;
using Pistache::Rest::Request;
using namespace Pistache;

using namespace Pistache::Rest;

namespace krystal::api::routes {

using namespace controllers;

class ControllerRoutes {
public:
    ControllerRoutes(std::shared_ptr<ControllersController> controller)
        : m_controllersController(controller) {
    }

    void setup(const std::string& version, Pistache::Rest::Router& router) {
        Routes::Get(router, version + "/controller", Routes::bind(&ControllerRoutes::controllerGet, this));
        Routes::Get(router, version + "/controller/:id", Routes::bind(&ControllerRoutes::controllerIdGet, this));
    }

private:
    void controllerGet(const Request& req, ResponseWriter res) {
        res.send(Http::Code::Ok, "Hello world");
    }

    void controllerIdGet(const Request& req, ResponseWriter res) {
        res.send(Http::Code::Ok, "Hello world");
    }

    std::shared_ptr<ControllersController> m_controllersController;
};
}
