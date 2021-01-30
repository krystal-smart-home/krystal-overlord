#pragma once

#include <string>

namespace krystal::device {

enum class DeviceType {
    sensor,
    state
};

struct DeviceModel {
    int id;
    std::string name;
    DeviceType type;
};
}
