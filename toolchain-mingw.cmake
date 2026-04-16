set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

set(CMAKE_PREFIX_PATH "/home/satvara/Qt/6.7.3/mingw_64")

set(CMAKE_IGNORE_PATH "/usr/lib/cmake;/usr/lib;/usr/include")

set(CMAKE_FIND_ROOT_PATH "/home/satvara/Qt/6.7.3/mingw_64")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(QT_HOST_PATH "/usr")

set(CMAKE_AUTOMOC_EXECUTABLE "/usr/lib/qt6/bin/moc")
set(CMAKE_AUTORCC_EXECUTABLE "/usr/lib/qt6/bin/rcc")
set(CMAKE_AUTOUIC_EXECUTABLE "/usr/lib/qt6/bin/uic")