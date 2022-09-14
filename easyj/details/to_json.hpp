#pragma once

//
// ... easyj header files
//
#include <easyj/details/concepts.hpp>
#include <easyj/details/import.hpp>

namespace easyj::details {

   template<Introspective T>
   void
   to_json(json& j, const T& arg) {
      string type_name = string(bare_type_name<T>);
      j = json::object();
      j[ type_name ] = json::object();
      json& fields = j[ type_name ];
      [ & ]<auto... Index>(index_sequence<Index...>) {
         (
           [ & ] {
              fields[ string{member_name<T, Index>} ] = get<Index>(arg);
           }(),
           ...);
      }
      (make_index_sequence<member_count<T>>());
   }

   template<Aggregate T>
   void
   to_json(json& j, const T& arg) {
      string type_name(bare_type_name<T>);
      j = json::object();
      j[ type_name ] = json::array();
      json& fields = j[ type_name ];
      [ & ]<auto... Index>(index_sequence<Index...>) {
         ([ & ] { fields.push_back(get<Index>(arg)); }(), ...);
      }
      (make_index_sequence<pfr::tuple_size_v<T>>());
   }

} // end of namespace easyj::details
