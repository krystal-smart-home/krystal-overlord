#include <gtest/gtest.h>

#include "core/Json.h"

using namespace krystal::core;
using namespace testing;

namespace {

class JsonTests : public Test {
public:
    JsonBuilder jsonBuilder;
};

TEST_F(JsonTests, givenJsonBuilder_whenCreatingEmptyJson_expectCorrectResult) {
    auto jsonString = jsonBuilder.beginObject().endObject().build();

    EXPECT_EQ(jsonString, "{}");
}

TEST_F(JsonTests, givenJsonBuilder_whenCreatingEmptyArray_expectCorrectResult) {
    auto jsonString = jsonBuilder.beginObject().beginArray("my_array").endArray().endObject().build();

   // EXPECT_EQ(jsonString, "{\"my_array\":[]}");
}
}
