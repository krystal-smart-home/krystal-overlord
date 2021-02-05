#include "core/Service.h"

#include "core/Thread.h"
// #include "net/Socket.h"

namespace krystal::transmission {

// clang-format off
template <typename Thread = core::Thread> requires std::derived_from<Thread, core::IThread>
class TransmissionService : public core::Service {
    // clang-format on

public:
    explicit TransmissionService()
        : core::Service("TransmissionService") {
    }

    core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        return core::ServiceState::active;
    }

    void start() override {
        //     m_acceptor = std::make_unique<net::Socket>(8889);
    }

    void stop() override {
    }

private:
    //   std::unique_ptr<net::ISocket> m_acceptor;
};
}
