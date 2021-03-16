#pragma once

#include "DeviceSession.h"
#include "net/AcceptorService.h"

namespace krystal::device {

class DeviceService : public net::AcceptorService<DeviceSession> {
public:
private:
};

}