#pragma once

#include <xvent/Event.h>

namespace krystal::event {

struct NewControllerConnected : xvent::EventBase<NewControllerConnected> {
    explicit NewControllerConnected(const std::string& name)
        : name(name) {
    }

    std::string name;
};

struct NewControllerRegistered : xvent::EventBase<NewControllerRegistered> {
    explicit NewControllerRegistered(int id)
        : controllerId(id) {
    }

    int controllerId;
};

struct NewDeviceConnected : xvent::EventBase<NewDeviceConnected> {
};

struct NewDeviceRegistered : xvent::EventBase<NewDeviceRegistered> {
};
}
