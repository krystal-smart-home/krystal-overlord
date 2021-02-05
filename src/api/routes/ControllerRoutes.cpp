#include "ControllerRoutes.h"

#include "Routes.h"
#include "api/RouterWrapper.h"
#include "api/controllers/ControllersController.h"

namespace krystal::api::routes {

using namespace controllers;

ControllerRoutes::ControllerRoutes(std::shared_ptr<ControllersController> controller)
    : m_controllersController(controller) {
}

void ControllerRoutes::setup(const std::string& version, RouterWrapper& router) {
    router.get(version + "/controller", router.bindSafe(&ControllerRoutes::controllerGet, this));
    router.get(version + "/controller/:id", router.bindSafe(&ControllerRoutes::controllerIdGet, this));
}

void ControllerRoutes::controllerGet(const Request& req, ResponseWriter& res) {
    res.send(Http::Code::Ok, "Hello world");
}

void ControllerRoutes::controllerIdGet(const Request& req, ResponseWriter& res) {
    res.send(Http::Code::Ok, "Hello world");
}
}
