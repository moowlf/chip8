cmake_minimum_required(VERSION 3.16)
project(chip8 CXX)

# Conan
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CONAN_CMAKE_SILENT_OUTPUT true)

include(conan)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_CURRENT_SOURCE_DIR} BUILD missing SETTINGS ${SETTINGS} OUTPUT_QUIET)

# Chip8 Library
add_subdirectory(lib)

# Graphical mode
add_subdirectory(src)

# Tests
option(BUILD_TESTING "Flag to activate/deactivate the building of tests" ON)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
