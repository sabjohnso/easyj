#pragma once

//
// ... easyj header files
//
#include <easyj/details/import.hpp>

namespace easyj::details {

   template<typename T>
   void
   json_schema_function(T) {}

   json
   json_schema_function(type_identity<bool>) {
      return {
        {"type", "boolean"}
      };
   }

   template<integral T>
   json
   json_schema_function(type_identity<T>) {
      return {
        {"type",    "integer"                      },
        {"minimum", std::numeric_limits<int>::min()},
        {"maximum", std::numeric_limits<int>::max()}
      };
   }

   template<floating_point T>
   json
   json_schema_function(type_identity<T>) {
      return {
        {"type", "number"}
      };
   }

   struct json_schema_fn {
      template<typename T>
      constexpr auto
      operator()(type_identity<T>) const {
         return json_schema_function(type_identity<T>{});
      }
   };

   template<typename T>
   constexpr T static_const{};

   constexpr const auto& json_schema = static_const<json_schema_fn>;

} // end of namespace easyj::details
