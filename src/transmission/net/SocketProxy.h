#pragma once

#include "TcpSocket.h"

#include "core/Error.h"

namespace krystal::transmission::net {

class SocketProxy : public ITcpSocket {
public:
    explicit SocketProxy(std::shared_ptr<ITcpSocket> socket)
        : m_socket(socket) {}

    int bind() override {
        auto returnCode = m_socket->bind();

        if (returnCode < 0)
            throw core::NetError{ core::ErrorCode::couldNotBindSocket };

        return returnCode;
    }

    int listen(int q = 5) override {
        auto returnCode = m_socket->listen(q);

        if (returnCode < 0)
            throw core::NetError{ core::ErrorCode::couldNotListen };

        return returnCode;
    }

    std::shared_ptr<ITcpSocket> accept() override {
        auto socket = m_socket->accept();

        if (socket == nullptr)
            throw core::NetError{ core::ErrorCode::acceptedSocketIsInvalid };

        return socket;
    }

    void close() override {
        m_socket->close();
    }

    int send(const std::string& buffer) override {
        auto bufferSize = buffer.size();
        auto bytesSent = m_socket->send(buffer);

        if (bufferSize != bytesSent)
            throw core::NetError{ core::ErrorCode::couldNotSendWholeBuffer };

        return bytesSent;
    }

    std::pair<std::string, int> receive(uint16_t bytes) override {
        auto [buffer, bytesReceived] = m_socket->receive(bytes);

        if (bytesReceived != bytes)
            throw core::NetError{ core::ErrorCode::receivedInvalidNumberOfBytes };

        return { buffer, bytesReceived };
    }

private:
    std::shared_ptr<ITcpSocket> m_socket;
};
}
