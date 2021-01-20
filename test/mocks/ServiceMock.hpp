#include <gmock/gmock.h>

#include "core/Service.h"

class ServiceMock : public krystal::core::Service {
public:
    ServiceMock(const std::string name = "ServiceMock")
        : Service(name) {
    }

    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(krystal::core::ServiceState, update, (const xvent::EventProvider&), (override));
};
