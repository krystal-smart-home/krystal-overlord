#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include "core/Service.h"

namespace krystal::api {

using namespace Pistache;

using Pistache::Http::ResponseWriter;
using Pistache::Rest::Request;

static void testHandler(const Request& req, ResponseWriter res) {
    res.send(Http::Code::Ok, "Hello world");
}

class ApiService : public core::Service {
public:
    explicit ApiService()
        : core::Service("ApiService")
        , m_addr(Pistache::Ipv4::any(), 8888)
        , m_endpoint(m_addr) {
    }

    core::ServiceState update(const xvent::EventProvider& eventProvider) override {
        return core::ServiceState::active;
    }

    void start() override {
        using namespace Pistache::Rest;

        Routes::Post(m_router, "/hello", Routes::bind(testHandler));

        m_endpoint.setHandler(m_router.handler());
        m_endpoint.serveThreaded();
    }
    void stop() override {
        m_endpoint.shutdown();
    }

private:
    Pistache::Address m_addr;
    Pistache::Rest::Router m_router;
    Pistache::Http::Endpoint m_endpoint;
};
}
