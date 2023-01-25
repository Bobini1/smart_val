cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    smart_val
    VERSION 0.1.0
    DESCRIPTION "like smart pointers but stored as values"
    HOMEPAGE_URL "https://github.com/Bobini1"
    LANGUAGES NONE
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(smart_val_smart_val INTERFACE)
add_library(smart_val::smart_val ALIAS smart_val_smart_val)

set_property(
    TARGET smart_val_smart_val PROPERTY
    EXPORT_NAME smart_val
)

target_include_directories(
    smart_val_smart_val ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(smart_val_smart_val INTERFACE cxx_std_11)

target_link_libraries(smart_val_smart_val)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT smart_val_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of smart_val"
  )
endif()

include(cmake/dev-mode.cmake)
