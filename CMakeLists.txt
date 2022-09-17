cmake_minimum_required(VERSION 3.12)

project(easyj VERSION 0.1.0 LANGUAGES C CXX)

if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(easyj_BUILD_TESTING "Build the easyj tests" ON)
endif()

set(easyj_CXX_STANDARD 20 CACHE STRING "C++ standard for easyj")

include(GNUInstallDirs)
set(easyj_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(easyj_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(easyj_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(easyj_INSTALL_CONFDIR ${easyj_INSTALL_LIBDIR}/cmake/easyj-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(easyj_deps)

add_subdirectory(easyj)

if(easyj_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(easyj_testing)
  endif()
endif()

install(EXPORT easyj_EXPORTS
  NAMESPACE easyj::
  FILE easyj-exports.cmake
  DESTINATION ${easyj_INSTALL_CONFDIR})

configure_file(easyj-config.cmake.in easyj-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/easyj-config.cmake
  DESTINATION ${easyj_INSTALL_CONFDIR})
