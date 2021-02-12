#pragma once

#include <xvent/EventEmitter.h>

#include "Transmitter.h"
#include "core/Thread.h"
#include "event/device/NewController.h"
#include "net/SocketProxy.h"
#include "net/TcpSocket.h"

#include "msg/Handshake.hpp"

namespace krystal::transmission {
// clang-format off
template <typename Thread = core::Thread> requires std::derived_from<Thread, core::IThread> 
class ConnectionManager {
    // clang-format on
public:
    explicit ConnectionManager(std::shared_ptr<net::ITcpSocket::Factory> socketFactory,
        std::shared_ptr<xvent::EventEmitter> eventEmitter, int port)
        : m_socketFactory(socketFactory)
        , m_eventEmitter(eventEmitter)
        , m_port(port) {
    }

    void startThreaded() {
        try {
            m_acceptorSocket = std::make_shared<net::SocketProxy>(m_socketFactory->create(m_port));
            m_acceptorSocket->bind();
            m_acceptorSocket->listen(5);

            m_acceptorThread = std::make_shared<Thread>(&ConnectionManager::acceptLoop, this);
        } catch (core::NetError& e) {
        }
    }

    void stop() {
        m_acceptorSocket->close();
        m_acceptorThread->join();
    }

private:
    void acceptLoop() {
        try {
            auto socket = m_acceptorSocket->accept();
            auto transmitter = std::make_shared<Transmitter>(socket);

            auto handshakeRequest = transmitter->readMessage();

            if (not handshakeRequest->is<msg::Handshake::Request>()) {
            }

        } catch (core::NetError& e) {
        }
    }

    std::shared_ptr<Thread> m_acceptorThread;
    std::shared_ptr<net::SocketProxy> m_acceptorSocket;

    std::shared_ptr<net::ITcpSocket::Factory> m_socketFactory;
    std::shared_ptr<xvent::EventEmitter> m_eventEmitter;

    int m_port;
};
}
