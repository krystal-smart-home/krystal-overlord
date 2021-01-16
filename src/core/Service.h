#pragma once

#include <atomic>
#include <string>

namespace krystal::core {

class Service {
public:
    explicit Service(const std::string& name);

    virtual void update(std::atomic_bool& isRunning) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    const std::string& getName() const;

protected:
    std::string m_name;
};
}
