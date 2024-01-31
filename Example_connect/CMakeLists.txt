cmake_minimum_required(VERSION 3.14)

project(Example_connect LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


add_executable(Example_connect
  main.cpp
  counter.h counter.cpp
  displayer.h displayer.cpp
)
target_link_libraries(Example_connect Qt${QT_VERSION_MAJOR}::Core)


include(GNUInstallDirs)
install(TARGETS Example_connect
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
