#pragma once

//
// ... easyj header files
//
#include <easyj/details/import.hpp>

namespace easyj::details {

    template<typename T>
    concept Aggregate = is_aggregate_v<T> && ! Introspective<T>;

} // end of namespace easyj::details
