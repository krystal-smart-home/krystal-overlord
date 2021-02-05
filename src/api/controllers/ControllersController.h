#pragma once

#include <memory>

#include <xvent/EventEmitter.h>

namespace krystal::api::controllers {

class ControllersController {
public:
    explicit ControllersController(std::shared_ptr<xvent::EventEmitter> eventEmitter)
        : m_eventEmitter(eventEmitter) {
    }

private:
    std::shared_ptr<xvent::EventEmitter> m_eventEmitter;
};
}
