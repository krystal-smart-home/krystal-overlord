#pragma once

#include <xvent/Event.h>

#include "device/ControllerModel.h"

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

struct GetControllers : xvent::EventBase<GetControllers> {};

struct Controllers : xvent::EventBase<Controllers> {
    explicit Controllers(std::vector<device::ControllerModel> controllers)
        : controllers(controllers) {
    }

    std::vector<device::ControllerModel> controllers;
};

struct NewDeviceConnected : xvent::EventBase<NewDeviceConnected> {
};

struct NewDeviceRegistered : xvent::EventBase<NewDeviceRegistered> {
};
}
