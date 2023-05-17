
# Get source files
file(GLOB_RECURSE sources *.cpp)

# Get dependencies
find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Create targets
add_executable(chip8_qml ${sources})
target_compile_features(chip8_qml PRIVATE cxx_std_20)
target_link_libraries(chip8_qml PRIVATE Qt6::Gui Qt6::Quick Qt6::Qml chip8)
target_include_directories(chip8_qml PRIVATE "${CMAKE_SOURCE_DIR}/lib")

qt_add_qml_module(chip8_qml
        URI chip8
        VERSION 1.0
        QML_FILES
            ui/main.qml
        DEPENDENCIES
            QtQuick
)