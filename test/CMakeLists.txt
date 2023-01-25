cmake_minimum_required(VERSION 3.14)

project(smart_valTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(smart_val REQUIRED)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(smart_val_test source/smart_val_test.cpp)
target_link_libraries(
    smart_val_test PRIVATE
    smart_val::smart_val
    Catch2::Catch2WithMain
)
target_compile_features(smart_val_test PRIVATE cxx_std_11)

catch_discover_tests(smart_val_test)

# ---- End-of-file commands ----

add_folders(Test)
