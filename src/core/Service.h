#pragma once

#include <atomic>
#include <memory>
#include <string>

#include <xvent/EventEmitter.h>
#include <xvent/EventListener.h>
#include <xvent/EventProvider.h>

namespace krystal::core {

enum class ServiceState {
    active,
    finished
};

class Service : public xvent::EventListener {
public:
    explicit Service(const std::string& name);

    virtual ServiceState update(const xvent::EventProvider&) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    const std::string& getName() const;

    void setEventEmitter(std::shared_ptr<xvent::EventEmitter> eventEmitter) {
        m_eventEmitter = eventEmitter;
    }

protected:
    std::string m_name;
    std::shared_ptr<xvent::EventEmitter> m_eventEmitter = nullptr;
};
}
