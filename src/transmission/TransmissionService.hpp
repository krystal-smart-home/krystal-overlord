#include "core/Service.h"

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
        , m_serverSocket(std::make_shared<net::SocketProxy>(socketFactory->create(port))) {
    }

    void start() override {
        m_serverSocket->bind();
        m_serverSocket->listen();
    }

    void stop() override {
        m_serverSocket->close();
    }

    core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        return core::ServiceState::active;
    }

private:
    std::shared_ptr<net::ITcpSocket> m_serverSocket;
};
}
