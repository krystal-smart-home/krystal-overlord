#pragma once

#include <concepts>

#include "Session.h"
#include "service/Service.h"

#include <boost/asio.hpp>

using namespace boost;
using namespace boost::asio::ip;

namespace krystal::net {

// TODO: update clang-format
template <typename T>
requires std::derived_from<T, Session>&& std::constructible_from<T, tcp::socket> class AcceptorService : public service::Service {
public:
    explicit AcceptorService(const std::string& name)
        : Service(name)
        , m_acceptor(asyncContext, tcp::endpoint(tcp::v4(), 7777)) {
        waitForConnection();
    }

    void waitForConnection() {
        m_acceptor.async_accept([this](system::error_code& ec, tcp::socket socket) {
            if (!ec) {
                auto session = std::make_shared<T>(std::move(socket));
                onConnection(session);
            }

            waitForConnection();
        });
    }

    void update() override {
    }

    void onInit() override {
        asyncContext.run();
    }

    void onShutdown() override {
        asyncContext.shutdown();
    }

    virtual void onMessage() {
    }

    virtual void onConnection(std::shared_ptr<T> connection) {
    }

protected:
    tcp::acceptor m_acceptor;
    asio::io_context asyncContext;
};

}