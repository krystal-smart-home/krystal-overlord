#pragma once

#include <boost/asio.hpp>

using namespace boost;
using namespace boost::asio::ip;

namespace krystal::net {

class Session {
public:
    explicit Session(tcp::socket socket)
        : m_socket(std::move(socket)) {
    }

    void readMessage() {
        constexpr int maxBufferSize = 1024;
        char buffer[maxBufferSize];

        m_socket.async_read_some(asio::buffer(buffer, maxBufferSize), [this](system::error_code ec, std::size_t length) {
            if (!ec) {
            }

            readMessage();
        });
    }

private:
    tcp::socket m_socket;
};
}
