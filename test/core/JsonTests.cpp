#include <gtest/gtest.h>

#include "core/Error.h"
#include "core/Json.h"

using namespace krystal::core;
using namespace testing;

namespace {

class JsonTests : public Test {
public:
    JsonBuilder jsonBuilder;
};

TEST_F(JsonTests, givenInvalidJsonString_whenParsing_shouldThrow) {
    std::string corruptedJson = "{\"Hello\": {}";
    EXPECT_THROW(parseJson(corruptedJson), JsonError);
}

TEST_F(JsonTests, givenValidJsonString_whenParsing_shouldReturnJsonObject) {
    std::string corruptedJson = "{\"Hello\": \"World\"}";
    auto json = parseJson(corruptedJson);

    EXPECT_TRUE(json.isMember("Hello"));
    EXPECT_EQ(json["Hello"], "World");
}

TEST_F(JsonTests, givenJsonBuilder_whenCreatingEmptyJson_shouldGiveCorrectResult) {
    auto jsonString = jsonBuilder.beginObject().endObject().build();

    EXPECT_EQ(jsonString, "{}");
}

TEST_F(JsonTests, givenJsonBuilder_whenCreatingEmptyArray_shouldGiveCorrectResult) {
    auto jsonString = jsonBuilder.beginObject().beginArray("my_array").endArray().endObject().build();

    // EXPECT_EQ(jsonString, "{\"my_array\":[]}");
}
}
