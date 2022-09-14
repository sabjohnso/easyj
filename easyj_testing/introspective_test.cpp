//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... external header files
//
#include <introspection/introspection.hpp>
#include <introspection/macros.hpp>
#include <nlohmann/json.hpp>

//
// ... easyj header files
//
#include <easyj/easyj.hpp>

namespace easyj::testing {

   using nlohmann::json;

   using easyj::to_json;

   struct Point {
      double x{};
      double y{};
      INTROSPECTION_DATA(Point, x, y);
   };

   struct Triangle {
      Point v1{};
      Point v2{};
      Point v3{};
      INTROSPECTION_DATA(Triangle, v1, v2, v3);
   };

   TEST(introspective, to_json) {
      json expected = {
        {"Point", {{"x", 2.0}, {"y", 3.0}}}
      };

      const Point p{.x = 2.0, .y = 3.0};
      json j = p;

      ASSERT_EQ(j, expected);
   }

   TEST(introspective, to_json_nested) {
      json expected = {
        {"Triangle",
         {{"v1", {{"Point", {{"x", 0.0}, {"y", 0.0}}}}},
          {"v2", {{"Point", {{"x", 1.0}, {"y", 0.0}}}}},
          {"v3", {{"Point", {{"x", 0.0}, {"y", 1.0}}}}}}}
      };

      const Triangle tri{
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
      };

      json j = tri;

      ASSERT_EQ(j, expected);
   }

} // end of namespace easyj::testing
