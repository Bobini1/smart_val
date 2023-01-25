if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/smart_val-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

# Project is configured with no languages, so tell GNUInstallDirs the lib dir
set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package smart_val)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT smart_val_Development
)

install(
    TARGETS smart_val_smart_val
    EXPORT smart_valTargets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# Allow package maintainers to freely override the path for the configs
set(
    smart_val_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(smart_val_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${smart_val_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT smart_val_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${smart_val_INSTALL_CMAKEDIR}"
    COMPONENT smart_val_Development
)

install(
    EXPORT smart_valTargets
    NAMESPACE smart_val::
    DESTINATION "${smart_val_INSTALL_CMAKEDIR}"
    COMPONENT smart_val_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
