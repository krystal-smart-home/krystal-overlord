#pragma once

#include "event/Misc.hpp"

namespace krystal::event::device {

struct NewDevice {
    DECLARE_EVENT(Request){};

    DECLARE_EVENT(Response){};
};
}
