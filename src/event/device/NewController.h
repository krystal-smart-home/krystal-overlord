#pragma once

#include <string>

#include "event/Misc.hpp"

namespace krystal::event::device {

struct NewController {
    DECLARE_EVENT(Request) {
        explicit Request(const std::string& name)
            : name(name) {
        }

        std::string name;
    };

    DECLARE_EVENT(Response) {
        explicit Response(int id)
            : controllerId(id) {
        }

        int controllerId;
    };
};
}
