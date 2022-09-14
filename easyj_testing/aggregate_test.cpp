//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... external header files
//
#include <nlohmann/json.hpp>

//
// ... easyj header files
//
#include <easyj/easyj.hpp>

namespace easyj::testing {
   using easyj::to_json;
   using nlohmann::json;

   using easyj::to_json;

   struct Point {
      double x{};
      double y{};
   };

   struct Triangle {
      Point v1{};
      Point v2{};
      Point v3{};
   };

   TEST(easyj, nonintrospective_aggregate_to_json) {
      json expected = {
        {"Point", {2.0, 3.0}}
      };
      const Point p{2.0, 3.0};
      json j = p;
      ASSERT_EQ(j, expected);
   }

   TEST(introspective, nonintrospective_aggregate_to_json_nested) {
      json expected = {
        {"Triangle",
         {{{"Point", {0.0, 0.0}}},
          {{"Point", {1.0, 0.0}}},
          {{"Point", {0.0, 1.0}}}}}
      };

      const Triangle tri{
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
      };

      json j = tri;

      ASSERT_EQ(j, expected);
   }

} // namespace easyj::testing
