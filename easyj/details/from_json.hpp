#pragma once

//
// ... easyj header files
//
#include <easyj/details/import.hpp>

namespace easyj::details {

   template<Introspective T>
   void
   from_json(const json& j, T& arg) {
      string type_name = string(bare_type_name<T>);

      assert(j.is_object());
      assert(ssize(j) == 1);

      const json& fields = j[ type_name ];

      [ & ]<auto... Index>(index_sequence<Index...>) {
         (
           [ & ] {
              const string name{member_name<T, Index>};
              assert(field.count(name));
              get<Index>(arg) = fields[ name ];
           }(),
           ...);
      }
      (make_index_sequence<pfr::tuple_size_v<T>>());
   }

} // end of namespace easyj::details
