#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

using Pistache::Http::ResponseWriter;
using Pistache::Rest::Request;
using namespace Pistache;

using namespace Pistache::Rest;

namespace krystal::api::routes {

class Routes {
    using EndpointCallback = std::function<void(const Request&, ResponseWriter&)>;

protected:
    void get(Pistache::Rest::Router& router, const std::string& url, Route::Handler&& handler) {
        Pistache::Rest::Routes::Get(router, url, handler);
    }

    void post(Pistache::Rest::Router& router, const std::string& url, Route::Handler&& handler) {
        Pistache::Rest::Routes::Post(router, url, handler);
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
};
}
