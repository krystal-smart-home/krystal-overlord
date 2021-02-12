#pragma once

#include "Message.h"

namespace krystal::transmission::msg {

struct Handshake {
    // clang-format off
	SERIALIZABLE(Response) {
   			
    };

    DESERIALIZABLE(Request) {
   		explicit Request(Json::Value& json) {

   		}

 		std::string name;
    };
    // clang-format on
};
}
