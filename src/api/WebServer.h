#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

namespace krystal::api {

class WebServer {
public:
    explicit WebServer(int port, int threads = 4);

    void start();
    void stop();

    Pistache::Rest::Router& getRouter();

private:
    int m_threads;

    Pistache::Address m_addr;
    Pistache::Rest::Router m_router;
    Pistache::Http::Endpoint m_endpoint;
};
}
