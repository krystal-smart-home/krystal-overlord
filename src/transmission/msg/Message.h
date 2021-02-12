#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>

#include "core/Json.h"

namespace krystal::transmission::msg {

struct Serializable {
    virtual std::string serialize() = 0;
};

struct Deserializable : public std::enable_shared_from_this<Deserializable> {
    template <typename T>
    bool is() {
        return getType() == typeid(T);
    }

    template <typename T>
    std::shared_ptr<T> as() {
        return std::dynamic_pointer_cast<T>(shared_from_this());
    }

    virtual std::type_index getType() = 0;
};

template <typename T>
struct DeserializableMiddleware : Deserializable {
    std::type_index getType() override {
        return typeid(T);
    }
};
};

#define DESERIALIZABLE(ClassName) struct ClassName : DeserializableMiddleware<ClassName>
#define SERIALIZABLE(ClassName) struct ClassName : Serializable
