#pragma once

#include <memory>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace krystal::transmission::net {

class ITcpSocket {
public:
    struct Factory {
        virtual std::shared_ptr<ITcpSocket> create(int port) = 0;
    };
    virtual int bind() = 0;
    virtual int listen(int q = 5) = 0;
    virtual void close() = 0;

    virtual std::shared_ptr<ITcpSocket> accept() = 0;

    virtual int send(const std::string& buffer) = 0;
    virtual std::pair<std::string, int> receive(uint16_t bytes) = 0;
};

class TcpSocket : public ITcpSocket {
public:
    struct Factory : ITcpSocket::Factory {
        std::shared_ptr<ITcpSocket> create(int port) {
            int socket = ::socket(AF_INET, SOCK_STREAM, 0);

            if (socket < 0)
                return nullptr;

            int flag = 1;
            if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(int)) < 0)
                return nullptr;

            return std::make_unique<TcpSocket>(socket, port);
        }
    };

    explicit TcpSocket(int sock, int port, sockaddr_in addr = sockaddr_in{})
        : m_socket(sock)
        , m_port(port)
        , m_addr(addr) {
    }

    int bind() override {
        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(m_port);
        m_addr.sin_addr.s_addr = INADDR_ANY;

        return ::bind(m_socket, (sockaddr*)&m_addr, sizeof(m_addr));
    }

    int listen(int q = 5) override {
        return ::listen(m_socket, 5);
    }

    std::shared_ptr<ITcpSocket> accept() override {
        sockaddr_in addr;
        socklen_t len = sizeof((sockaddr*)&addr);
        int unixSocket = ::accept(m_socket, (sockaddr*)&addr, &len);
        if (unixSocket < 0)
            return nullptr;

        return std::make_unique<TcpSocket>(unixSocket, 111, std::move(addr));
    }

    void close() override {
        ::shutdown(m_socket, SHUT_RDWR);
        ::close(m_socket);
    }

    int send(const std::string& buffer) override {
        auto bufferSize = buffer.size();
        return ::send(m_socket, &buffer[0], bufferSize, MSG_NOSIGNAL);
    }

    std::pair<std::string, int> receive(uint16_t bytes) override {
        std::string buffer;
        buffer.resize(bytes);
        auto bytesReceived = ::recv(m_socket, &buffer[0], bytes, 0);
        return { buffer, bytesReceived };
    }

private:
    int m_socket;
    int m_port;
    sockaddr_in m_addr;
};
}
