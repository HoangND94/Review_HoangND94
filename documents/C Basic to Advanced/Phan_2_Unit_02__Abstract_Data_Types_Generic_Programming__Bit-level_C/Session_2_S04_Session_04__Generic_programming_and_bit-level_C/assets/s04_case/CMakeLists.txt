cmake_minimum_required(VERSION 3.22)
project(s04_generic_case LANGUAGES C)

include(CTest)

add_executable(s04_generic_case s04_case.c)
target_compile_features(s04_generic_case PRIVATE c_std_17)
set_target_properties(s04_generic_case PROPERTIES
  C_STANDARD 17
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(s04_generic_case PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Werror>)

add_test(NAME s04_generic_contract COMMAND s04_generic_case)
