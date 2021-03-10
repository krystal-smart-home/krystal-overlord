#pragma once

namespace krystal::core {

enum class ErrorCode {
    noSpecified = 0,

    invalidJsonString = 100,

    couldNotBindSocket = 200,
    couldNotListen = 201,
    receivedInvalidNumberOfBytes = 202,
    couldNotSendWholeBuffer = 203,
    acceptedSocketIsInvalid = 204
};

}