#pragma once

#include <sstream>

#include <jsoncpp/json/json.h>

namespace krystal::core {

Json::Value parseJson(const std::string&);

class JsonBuilder {
public:
    explicit JsonBuilder();

    std::string build();
    JsonBuilder& beginObject();
    JsonBuilder& beginObject(const std::string& name);
    JsonBuilder& endObject();
    JsonBuilder& beginArray(const std::string& name);
    JsonBuilder& endArray();

    template <typename T>
    JsonBuilder& addItem(const T& item) {
        if (m_shouldInsertComma)
            m_jsonStream << ',';
        m_jsonStream << item;
        m_shouldInsertComma = true;
        return *this;
    }

    template <typename T>
    JsonBuilder& addItem(const std::string& key, const T& value) {
        if (m_shouldInsertComma)
            m_jsonStream << ',';
        m_jsonStream << '"' << key << "\": " << value;
        m_shouldInsertComma = true;
        return *this;
    }

private:
    void reset();

    std::stringstream m_jsonStream;
    bool m_shouldInsertComma;
};
}
