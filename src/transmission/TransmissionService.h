#include "core/Service.h"

namespace krystal::transmission {

class TransmissionService : public core::Service {
public:
    explicit TransmissionService()
        : core::Service("TransmissionService") {
    }

    core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        return core::ServiceState::active;
    }

    void start() override {
    }

    void stop() override {
    }

};
}
