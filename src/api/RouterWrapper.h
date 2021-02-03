#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

using Pistache::Http::ResponseWriter;
using Pistache::Rest::Request;
using namespace Pistache;

using namespace Pistache::Rest;

namespace krystal::api {

class RouterWrapper {
    using EndpointCallback = std::function<void(const Request&, ResponseWriter&)>;

public:
    explicit RouterWrapper(Pistache::Rest::Router& router)
        : m_router(router) {}

    void get(const std::string& url, Route::Handler&& handler) {
        Pistache::Rest::Routes::Get(m_router, url, handler);
    }

    void post(const std::string& url, Route::Handler&& handler) {
        Pistache::Rest::Routes::Post(m_router, url, handler);
    }

    template <typename Result, typename Cls, typename... Args, typename Obj>
    Route::Handler bindSafe(Result (Cls::*func)(Args...), Obj obj) {
        //        details::static_checks<details::BindChecks, Args...>();

        return [=](const Rest::Request& request, Http::ResponseWriter response) {
            try {
                (obj->*func)(request, response);
            } catch (...) {
                response.send(Http::Code::Ok, "Oppsie");
            }

            return Route::Result::Ok;
        };
    }

private:
    Pistache::Rest::Router& m_router;
};
}
