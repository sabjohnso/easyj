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

   using easyj::from_json;
   using easyj::to_json;

   struct Point {
      double x{};
      double y{};
      constexpr bool
      operator<=>(const Point&) const = default;
   };

   struct Triangle {
      Point v1{};
      Point v2{};
      Point v3{};

      constexpr bool
      operator<=>(const Triangle&) const = default;
   };

   TEST(easyj, nonintrospective_aggregate_to_json) {
      json expected = {
        {"Point", {2.0, 3.0}}
      };
      const Point p{2.0, 3.0};
      json j = p;
      ASSERT_EQ(j, expected);
   }

   TEST(easyj, nonintrospective_aggregate_from_json) {
      const Point expected{2.0, 3.0};
      json pjson = {
        {"Point", {2.0, 3.0}}
      };

      Point p = pjson;

      ASSERT_EQ(p, expected);
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

   TEST(introspective, nonintrospective_aggregate_from_json_nested) {
      const Triangle expected{
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
      };

      json trijson = {
        {"Triangle",
         {{{"Point", {0.0, 0.0}}},
          {{"Point", {1.0, 0.0}}},
          {{"Point", {0.0, 1.0}}}}}
      };

      Triangle tri = trijson;

      ASSERT_EQ(tri, expected);
   }

} // namespace easyj::testing
