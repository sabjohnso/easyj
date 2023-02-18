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

    template<typename T>
    constexpr std::type_identity<std::remove_cvref_t<T>> type{};

    TEST(schema, boolean) {
        ASSERT_EQ(
        json({
            {"type", "boolean"}
        }),
        json_schema(type<bool>));
    }

    TEST(schema, integral) {
        ASSERT_EQ(
        json({
            {"type",    "integer"                      },
            {"minimum", std::numeric_limits<int>::min()},
            {"maximum", std::numeric_limits<int>::max()}
        }),
        json_schema(type<int>));

        ASSERT_EQ(
        json({
            {"type",    "integer"                           },
            {"minimum", std::numeric_limits<unsigned>::min()},
            {"maximum", std::numeric_limits<unsigned>::max()}
        }),
        json_schema(type<unsigned>));
    }

    TEST(schema, floating_point) {
        ASSERT_EQ(
        json({
            {"type", "number"}
        }),
        json_schema(type<double>));
    }

    TEST(schema, nonintrospective_aggregate) {
        struct Point {
            double x;
            double y;
        };
        ASSERT_EQ(
        json({
            {"type",                 "object" },
            {
                "properties",
                {   {
                        "Point",
                        {   {"type", "array"},
                            {
                                "prefixItems",
                                {{{"type", "number"}}, {{"type", "number"}}}
                            },
                            {"additionalItems", false}
                        }
                    }
                }
            },
            {"required",             {"Point"}},
            {"additionalProperties", false    }
        }),
        json_schema(type<Point>));
    }

} // end of namespace easyj::testing
