#pragma once

#include "event/Misc.hpp"

namespace krystal::event::api {

struct GetControllers {
    DECLARE_EVENT(Request){};

    DECLARE_EVENT(Response) {
        explicit Response(std::vector<device::ControllerModel> controllers)
            : controllers(controllers) {
        }

        std::vector<device::ControllerModel> controllers;
    };
};
}
