#include "Json.h"

#include <sstream>

#include <jsoncpp/json/json.h>

namespace krystal::core {

JsonBuilder::JsonBuilder() {
    reset();
}

std::string JsonBuilder::build() {
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errors;

    if (!Json::parseFromStream(builder, m_jsonStream, &root, &errors)) {
    }

    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, root);
}

JsonBuilder& JsonBuilder::beginObject() {
    if (m_shouldInsertComma)
        m_jsonStream << ',';
    m_jsonStream << "{";
    m_shouldInsertComma = false;
    return *this;
}

JsonBuilder& JsonBuilder::beginObject(const std::string& name) {
    m_jsonStream << '"' << name << "\": {";
    m_shouldInsertComma = false;
    return *this;
}

JsonBuilder& JsonBuilder::endObject() {
    m_jsonStream << '}';
    m_shouldInsertComma = true;
    return *this;
}

JsonBuilder& JsonBuilder::beginArray(const std::string& name) {
    if (m_shouldInsertComma)
        m_jsonStream << ',';
    m_jsonStream << '"' << name << "\": [";
    m_shouldInsertComma = false;
    return *this;
}

JsonBuilder& JsonBuilder::endArray() {
    m_jsonStream << ']';
    m_shouldInsertComma = true;
    return *this;
}

void JsonBuilder::reset() {
    m_jsonStream.clear();
    m_shouldInsertComma = false;
}
}
