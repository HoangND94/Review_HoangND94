cmake_minimum_required(VERSION 3.22)
project(s06_quality_case VERSION 6.0.0 LANGUAGES C)

include(CTest)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CMOCKA REQUIRED IMPORTED_TARGET cmocka)

option(BUILD_CRASH_FIXTURE "Build the intentionally crashing triage fixture" OFF)

add_library(gateway_stats STATIC src/gateway_stats.c)
target_include_directories(gateway_stats PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
target_compile_features(gateway_stats PUBLIC c_std_17)
set_target_properties(gateway_stats PROPERTIES
  C_STANDARD 17
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(gateway_stats PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)

add_executable(gateway_stats_tests tests/test_stats.c)
target_link_libraries(gateway_stats_tests PRIVATE gateway_stats PkgConfig::CMOCKA)
target_compile_features(gateway_stats_tests PRIVATE c_std_17)
target_compile_options(gateway_stats_tests PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)
set_target_properties(gateway_stats_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
add_test(NAME gateway_stats_contract COMMAND gateway_stats_tests)

if(BUILD_CRASH_FIXTURE)
  add_executable(gateway_crash_fixture fixtures/legacy_crash.c)
  target_compile_features(gateway_crash_fixture PRIVATE c_std_17)
  target_compile_options(gateway_crash_fixture PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)
  set_target_properties(gateway_crash_fixture PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/apps")
endif()
