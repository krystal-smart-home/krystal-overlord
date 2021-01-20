#pragma once

#include "core/Service.h"

namespace krystal::supervisor {

class SupervisorService : public core::Service {
public:
    explicit SupervisorService()
        : core::Service("SupervisorService") {
    }

	core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        auto events = eventProvider.getAll();

        for (auto& event : events) {
        }

        return core::ServiceState::active;
    }

    void start() override {
    }

    void stop() override {
    }

private:
};
}
