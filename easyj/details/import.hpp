#pragma once

//
// ... Standard header files
//
#include <string>
#include <utility>

//
// ... external header files
//
#include <introspection/introspection.hpp>
#include <nlohmann/json.hpp>
#include <pfr/core.hpp>

namespace easyj::details {

   using std::index_sequence;
   using std::make_index_sequence;
   using std::string;

   using nlohmann::json;

   using pfr::get;

   using introspection::bare_type_name;
   using introspection::member_count;
   using introspection::member_name;
   using introspection::concepts::Introspective;

} // end of namespace easyj::details
