cmake_minimum_required(VERSION 3.22)
project(s05_gateway_package VERSION 5.0.0 LANGUAGES C)

include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/apps")

function(configure_gateway_target target_name)
  target_compile_features(${target_name} PUBLIC c_std_17)
  set_target_properties(${target_name} PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO)
  target_include_directories(${target_name}
    PUBLIC
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
  target_compile_options(${target_name} PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)
endfunction()

add_library(gateway_static STATIC src/gateway.c)
set_target_properties(gateway_static PROPERTIES
  OUTPUT_NAME gateway_core
  POSITION_INDEPENDENT_CODE ON)
configure_gateway_target(gateway_static)

add_library(gateway_shared SHARED src/gateway.c)
set_target_properties(gateway_shared PROPERTIES
  OUTPUT_NAME gateway_core
  VERSION 5.0.0
  SOVERSION 5
  C_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES)
target_compile_definitions(gateway_shared PRIVATE GATEWAY_BUILD_SHARED)
configure_gateway_target(gateway_shared)

add_executable(gateway_demo apps/demo.c)
target_link_libraries(gateway_demo PRIVATE gateway_shared)
target_compile_features(gateway_demo PRIVATE c_std_17)
target_compile_options(gateway_demo PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)
set_target_properties(gateway_demo PROPERTIES BUILD_RPATH "$ORIGIN/../lib")

if(BUILD_TESTING)
  add_executable(gateway_static_test tests/test_api.c)
  target_link_libraries(gateway_static_test PRIVATE gateway_static)
  target_compile_features(gateway_static_test PRIVATE c_std_17)
  target_compile_options(gateway_static_test PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)

  add_executable(gateway_shared_test tests/test_api.c)
  target_link_libraries(gateway_shared_test PRIVATE gateway_shared)
  target_compile_features(gateway_shared_test PRIVATE c_std_17)
  target_compile_options(gateway_shared_test PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)
  set_target_properties(gateway_shared_test PROPERTIES BUILD_RPATH "$ORIGIN/../lib")

  add_test(NAME static_api_contract COMMAND gateway_static_test)
  add_test(NAME shared_api_contract COMMAND gateway_shared_test)
endif()
