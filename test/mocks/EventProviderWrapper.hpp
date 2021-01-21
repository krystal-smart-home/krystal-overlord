#pragma once

#include <xvent/EventProvider.h>

class EventProviderWrapper {
    inline static const std::string target = "target";

public:
    explicit EventProviderWrapper()
        : m_eventEmitter(m_container) {
        m_container[target] = xvent::CategoryToEventQueue{};
    }

    template <typename T, typename... Args>
    auto pushEvent(Args&&... args) {
        return m_eventEmitter.emitTo<T>(target, std::forward<Args>(args)...);
    }

    xvent::EventProvider get() {
        return xvent::EventProvider{ m_container[target] };
    }

private:
    xvent::EventContainer m_container;
    xvent::EventEmitter m_eventEmitter;
};
