#include "core/Service.h"

#include "ConnectionManager.hpp"
#include "core/Thread.h"
#include "net/SocketProxy.h"
#include "net/TcpSocket.h"

namespace krystal::transmission {

// clang-format off
template <typename Thread = core::Thread> requires std::derived_from<Thread, core::IThread>
class TransmissionService : public core::Service {
    // clang-format on

public:
    explicit TransmissionService(std::shared_ptr<net::ITcpSocket::Factory> socketFactory, int port = 7777)
        : core::Service("TransmissionService")
        , m_connectionManager(std::make_shared<ConnectionManager<Thread>>(socketFactory, m_eventEmitter->clone(), port)) {
    }

    void start() override {
        m_connectionManager->startThreaded();
    }

    void stop() override {
		m_connectionManager->stop();
	}

    core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        return core::ServiceState::active;
    }

private:
    std::shared_ptr<ConnectionManager<Thread>> m_connectionManager;
};
}
