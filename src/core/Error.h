#pragma once

#include "ErrorBase.hpp"
#include "ErrorCode.h"

namespace krystal::core {

KRYSTAL_DEFINE_ERROR(Error);
KRYSTAL_DEFINE_ERROR(Fatal);

KRYSTAL_DEFINE_SUB_ERROR(JsonError, Error);
}
