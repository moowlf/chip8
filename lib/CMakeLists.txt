
find_package(spdlog 1.10.0 REQUIRED)

# Get source files
file(GLOB_RECURSE sources *.cpp)

# Create targets
add_library(chip8 STATIC ${sources})
target_link_libraries(chip8 PRIVATE spdlog::spdlog)
target_compile_features(chip8 PRIVATE cxx_std_20)
target_compile_definitions(chip8 PRIVATE TESTING_ENABLED)
