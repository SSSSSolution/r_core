cmake_minimum_required(VERSION 3.13)

project(
    r_core
    VERSION 1.0
    LANGUAGES CXX
)

add_library(r_core
    src/core.cpp
    src/executor.cpp
)

include_directories(include)
target_include_directories(r_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(r_core
    PUBLIC pthread
)

target_compile_features(r_core PUBLIC cxx_std_14)
set_target_properties(r_core PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(r_core PROPERTIES PUBLIC_HEADER
    "include/r_core/core.h"
)

add_executable(r_core_test
    src/core.cpp
    src/executor.cpp
    test/r_core_test.cpp
)
target_link_libraries(r_core_test
    PUBLIC pthread
)
#target_include_directories(r_core_test PRIVATE include)


# install
#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
install(TARGETS r_core
        EXPORT r_coreTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    r_coreConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT r_coreTargets
        FILE r_coreTargets.cmake
        NAMESPACE r_core::
        DESTINATION lib/cmake/r_core
)

configure_file(cmake/r_coreConfig.cmake.in r_coreConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/r_coreConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/r_coreConfigVersion.cmake"
              DESTINATION lib/cmake/core
)



