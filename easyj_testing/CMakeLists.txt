find_package(GTest)

macro(easyj_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name} PRIVATE
    easyj::header
    GTest::gtest_main)
  set_target_properties(${exe_name}
    PROPERTIES
    CXX_STANDARD ${easyj_CXX_STANDARD})
  add_test(${test_name} ${exe_name})
endmacro()

easyj_add_test(introspective introspective_test introspective_test.cpp)
easyj_add_test(aggregate aggregate_test aggregate_test.cpp)
