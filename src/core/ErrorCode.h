#pragma once

namespace krystal::core {


// clang-format off
enum class ErrorCode {
    noSpecified = 0,

    invalidJsonString = 100,

    couldNotBindSocket				= 200,
    couldNotListen					= 201,
    receivedInvalidNumberOfBytes	= 202,
    couldNotSendWholeBuffer			= 203,
    acceptedSocketIsInvalid			= 204
};


// clang-format on
}
