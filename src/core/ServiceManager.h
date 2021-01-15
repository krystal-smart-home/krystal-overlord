#pragma once

#include <memory>
#include <vector>

#include "Service.h"

namespace krystal::core {

class ServiceManager {
public:
	ServiceManager();

	void registerService(std::shared_ptr<Service> service) {
    }

private:
};
}
