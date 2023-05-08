
find_package(GTest 1.11.0 REQUIRED QUIET)

# Get source files
file(GLOB_RECURSE sources *.cpp)

add_executable(chip8_tests ${sources})
target_compile_definitions(chip8_tests PRIVATE TESTING_ENABLED)
target_compile_features(chip8_tests PRIVATE cxx_std_20)
target_link_libraries(chip8_tests PRIVATE GTest::gtest_main chip8)
target_include_directories(chip8_tests PRIVATE ${PROJECT_SOURCE_DIR}/lib)

