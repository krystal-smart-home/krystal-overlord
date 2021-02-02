#pragma once

#include "event/Misc.hpp"

#include "device/ControllerDescription.h"

namespace krystal::event::api {

struct GetControllers {
    DECLARE_EVENT(Request){};

    DECLARE_EVENT(Response) {
        explicit Response(std::vector<device::ControllerDescription> controllers)
            : controllers(controllers) {
        }

        std::vector<device::ControllerDescription> controllers;
    };
};
}
