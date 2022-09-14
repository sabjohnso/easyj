configure_file(config.hpp.in config.hpp)

add_library(easyj_header INTERFACE)
set_target_properties(easyj_header PROPERTIES EXPORT_NAME header)
target_include_directories(easyj_header
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${easyj_INSTALL_INCLUDEDIR}>)

target_link_libraries(easyj_header INTERFACE introspection::header nlohmann_json::nlohmann_json
  pfr::header)

add_library(easyj::header ALIAS easyj_header)

install(TARGETS easyj_header
  EXPORT easyj_EXPORTS
  RUNTIME DESTINATION ${easyj_INSTALL_BINDIR}
  LIBRARY DESTINATION ${easyj_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${easyj_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${easyj_INSTALL_INCLUDEDIR}/easyj)
