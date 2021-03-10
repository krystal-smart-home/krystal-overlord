#include "Log.h"

namespace krystal::core {

void initLogging() {
    spdlog::set_pattern("%^[%d-%m-%Y %T] [Th: %t] %-7l [krystal-overlord]: %v - [%s:%#]%$");
    spdlog::set_level(spdlog::level::trace);
}
}