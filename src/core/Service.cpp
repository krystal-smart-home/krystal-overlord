#include "Service.h"

namespace krystal::core {
Service::Service(const std::string& name)
    : m_name(name) {
}

const std::string& Service::getName() const {
    return m_name;
}
}
