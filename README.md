# USV Dashboard

A lightweight, cross-platform dashboard for monitoring and visualizing telemetry data from an Unmanned Surface Vehicle (USV). Built using Qt 6 (C++ and QML), the application provides a modular UI foundation for real-time robotics systems.

## Features

* Qt Quick (QML) based UI
* Modular dashboard layout (top, left, center, logs)
* Cross-platform architecture (Linux / Windows)
* QML module-based structure
* Portable Windows executable (no Qt installation required)

## Tech Stack

* C++20
* Qt 6 (Core, Quick, QuickControls2)
* CMake
* MinGW (Windows build)

## Project Structure

```
USV-Dashboard/
├── src/                # C++ source files
├── qml/                # QML UI modules
│   └── Dashboard/
│       └── Main.qml
├── CMakeLists.txt
└── README.md
```

## Build Instructions (Windows)

Ensure Qt 6 with MinGW is installed.

```
cmake -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/mingw_64
cmake --build build
```

Run:

```
cd build
app.exe
```

## Deployment

To create a portable executable:

```
windeployqt app.exe
```

Package the following for distribution:

* app.exe
* Qt6*.dll
* platforms/
* qml/
* Dashboard/

## Release

Download the latest release from the GitHub Releases section. Extract and run `app.exe`.

## Roadmap

* Real-time telemetry ingestion
* Graph visualization (power, speed, depth)
* Event monitoring system
* GPS tracking and mapping
* Camera integration

## License

MIT License
