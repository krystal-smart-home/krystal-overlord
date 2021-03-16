#pragma once

#include <string>

namespace krystal::service {

class Service {
public:
    Service(const std::string& name)
        : m_name(name)
        , m_isRunning(true) {
    }

    virtual void update() = 0;
    virtual void onInit() = 0;
    virtual void onShutdown() = 0;

    void run() {
        while (m_isRunning)
            update();
    }

    void stop() {
        m_isRunning = false;
    }

    std::string getName() const {
        return m_name;
    }

private:
    std::string m_name;
    bool m_isRunning;
};
}