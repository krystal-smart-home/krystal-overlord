#pragma once

#include <cstring>
#include <memory>

#include "msg/Message.h"
#include "net/SocketProxy.h"

constexpr int headerLength = 4;

namespace krystal::transmission {

class Transmitter {
public:
    explicit Transmitter(std::shared_ptr<net::ITcpSocket> socket)
        : m_socket(std::make_shared<net::SocketProxy>(socket)) {
    }

    std::shared_ptr<msg::Deserializable> readMessage() {
        auto messageLength = readMessageLength();
        auto [message, _] = m_socket->receive(messageLength);
    }

    void sendMessage(std::shared_ptr<msg::Serializable> message) {
        auto buffer = message->serialize();
        sendMessageLength(buffer.size());
        m_socket->send(buffer);
    }

private:
    uint32_t readMessageLength() {
        auto [messageLengthBuffer, _] = m_socket->receive(headerLength);
        uint32_t messageLength;
        std::memcpy(&messageLength, &messageLengthBuffer[0], headerLength);
        return messageLength;
    }

    void sendMessageLength(uint32_t length) {
        char* lengthBytes = static_cast<char*>(static_cast<void*>(&length));
        m_socket->send(std::string(lengthBytes, headerLength));
    }

    std::shared_ptr<net::SocketProxy> m_socket;
};
}
