#pragma once

//
// ... easyj header files
//
#include <easyj/details/concepts.hpp>
#include <easyj/details/import.hpp>
#include <nlohmann/json.hpp>

namespace easyj::details {

    template<typename T>
    void
    json_schema_function(T) {}

    inline json
    json_schema_function(type_identity<bool>) {
        return {
            {"type", "boolean"}
        };
    }

    template<integral T>
    json
    json_schema_function(type_identity<T>) {
        return {
            {"type",    "integer"                    },
            {"minimum", std::numeric_limits<T>::min()},
            {"maximum", std::numeric_limits<T>::max()}
        };
    }

    template<floating_point T>
    json
    json_schema_function(type_identity<T>) {
        return {
            {"type", "number"}
        };
    }


    template<Aggregate T>
    json
    json_schema_function(type_identity<T>) {
        return {
            {"type", "object"},
            {
                "properties",
                {  {
                        "Point",
                        {   {"type", "array"},
                            {
                                "prefixItems",
                                []<auto... Index>(index_sequence<Index...>) {
                                    return json({
                                        json_schema_function(type_identity<decltype(pfr::get<Index>(declval<T>()))>{}
                                                            ) ...});
                                }
                                (make_index_sequence<pfr::tuple_size_v<T>>())

                            }
                            , { "additionalItems", false }
                        }
                    }
                }
            },
            {"required", {"Point"}},
            { "additionalProperties", false }
        };
    }

    struct json_schema_fn {
        template<typename T>
        constexpr auto
        operator()(type_identity<T>) const {
            return json_schema_function(type_identity<T> {});
        }
    };

    template<typename T>
    constexpr T static_const{};

    constexpr const auto& json_schema = static_const<json_schema_fn>;

} // end of namespace easyj::details
