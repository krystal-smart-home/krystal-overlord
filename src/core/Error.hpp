#pragma once

#include <exception>

namespace krystal::core {

class Error : public std::exception {
};

class FatalError : public std::exception {
};
}
