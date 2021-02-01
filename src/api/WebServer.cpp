#include "WebServer.h"

namespace krystal::api {

WebServer::WebServer(int port, int threads)
    : m_threads(threads)
    , m_addr(Pistache::Ipv4::any(), port)
    , m_endpoint(m_addr) {
}

void WebServer::start() {
    auto options = Pistache::Http::Endpoint::options();
    options.threads(m_threads);

    m_endpoint.init(options);
    m_endpoint.setHandler(m_router.handler());
    m_endpoint.serveThreaded();
}

Pistache::Rest::Router& WebServer::getRouter() {
    return m_router;
}

void WebServer::stop() {
    m_endpoint.shutdown();
}
}
