cmake_minimum_required(VERSION 3.22)

project(USVDashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2)

qt_standard_project_setup()

qt_add_executable(app
    src/main.cpp
)

qt_add_qml_module(app
    URI Dashboard
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(app
    PRIVATE Qt6::Core Qt6::Quick Qt6::QuickControls2
)