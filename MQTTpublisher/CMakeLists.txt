cmake_minimum_required(VERSION 3.16)

project(MQTTpublisher VERSION 0.1 LANGUAGES CXX)

set(Qt6_DIR C:/Qt/6.6.1/mingw_64/lib/cmake/Qt6)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "6.6.1")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS Mqtt REQUIRED)

add_executable(MQTTpublisher
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(MQTTpublisher 
    Qt6::Widgets
    Qt6::Network
    Qt6::Mqtt
)
