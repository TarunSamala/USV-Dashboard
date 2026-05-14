cmake_minimum_required(VERSION 3.22)

project(USVDashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#
# QT MODULES
#

find_package(Qt6 REQUIRED COMPONENTS

    Core
    Quick
    QuickControls2
    SerialPort

    Widgets
    OpenGL
)

#
# OPENGL
#

find_package(OpenGL REQUIRED)

#
# QT STANDARD SETUP
#

qt_standard_project_setup()

#
# EXECUTABLE
#

qt_add_executable(app

    #
    # MAIN
    #

    src/main.cpp

    #
    # MODELS
    #

    src/models/telemetry_provider.cpp
    src/models/telemetry_parser.cpp

    #
    # SERIAL
    #

    src/serial/serial_reader.cpp

    #
    # LOGGER
    #

    src/logger/event_logger.cpp
    src/logger/csv_logger.cpp
    src/logger/system_logger.cpp

    #
    # RUNTIME
    #

    src/runtime/dashboard_runtime.cpp
    src/runtime/calibration_controller.cpp

    #
    # VISUALIZATION
    #

    src/visualization/VesselItem.cpp
    src/visualization/VesselItem.h

    src/visualization/VesselRenderer.cpp
    src/visualization/VesselRenderer.h

    
)

#
# THEME SINGLETON
#

set_source_files_properties(

    qml/Dashboard/theme/Theme.qml

    PROPERTIES

        QT_QML_SINGLETON_TYPE TRUE
)

#
# QML MODULE
#

qt_add_qml_module(app

    URI Dashboard

    VERSION 1.0

    QML_FILES

        #
        # MAIN
        #

        qml/Dashboard/Main.qml

        #
        # PANELS
        #

        qml/Dashboard/panels/TopControlBar.qml

        qml/Dashboard/panels/OperationsPanel.qml

        qml/Dashboard/panels/OrientationPanel.qml

        qml/Dashboard/panels/SensorMatrixPanel.qml

        qml/Dashboard/panels/WatchdogPanel.qml

        qml/Dashboard/panels/VisualizationPanel.qml

        #
        # COMPONENTS
        #

        qml/Dashboard/components/PanelFrame.qml

        qml/Dashboard/components/SectionTitle.qml

        qml/Dashboard/components/TelemetryValue.qml

        qml/Dashboard/components/CompassWidget.qml

        qml/Dashboard/components/SensorCell.qml

        qml/Dashboard/components/StatusIndicator.qml

        #
        # THEME
        #

        qml/Dashboard/theme/Theme.qml
)

#
# INCLUDE DIRECTORIES
#

target_include_directories(app PRIVATE

    src

    src/models
    src/logger
    src/serial
    src/runtime
    src/visualization
)

#
# LINK LIBRARIES
#

target_link_libraries(app PRIVATE

    #
    # QT
    #

    Qt6::Core

    Qt6::Quick

    Qt6::QuickControls2

    Qt6::SerialPort

    Qt6::Widgets

    Qt6::OpenGL

    #
    # OPENGL
    #

    OpenGL::GL

    OpenGL::GLU
)