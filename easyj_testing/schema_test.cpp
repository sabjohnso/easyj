//
// ... Standard header files
//
#include <type_traits>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <nlohmann/json.hpp>

//
// ... easyj header files
//
#include <easyj/easyj.hpp>

namespace easyj::testing {
   using nlohmann::json;

   TEST(schema, boolean) {
      json schema = json_schema(std::type_identity<bool>{});
      ASSERT_EQ(schema.count("type"), 1);
      ASSERT_EQ(schema[ "type" ], "boolean");
   }

   TEST(schema, integral) {
      json schema = json_schema(std::type_identity<int>{});
      ASSERT_EQ(schema.count("type"), 1);
      ASSERT_EQ(schema[ "type" ], "integer");

      ASSERT_EQ(schema.count("minimum"), 1);
      ASSERT_EQ(schema[ "minimum" ], std::numeric_limits<int>::min());

      ASSERT_EQ(schema.count("maximum"), 1);
      ASSERT_EQ(schema[ "maximum" ], std::numeric_limits<int>::max());
   }

   TEST(schema, floating_point) {
      json schema = json_schema(std::type_identity<double>{});
      ASSERT_EQ(schema.count("type"), 1);
      ASSERT_EQ(schema[ "type" ], "number");
   }

} // end of namespace easyj::testing
