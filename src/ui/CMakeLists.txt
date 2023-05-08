
# Get source files
file(GLOB_RECURSE sources *.cpp)

# Get dependencies
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Create targets
add_executable(chip8_qt ${sources})
target_compile_features(chip8_qt PRIVATE cxx_std_20)
target_link_libraries(chip8_qt PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets chip8)
target_include_directories(chip8_qt PRIVATE "${CMAKE_SOURCE_DIR}/lib")

set_target_properties(chip8_qt PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output")