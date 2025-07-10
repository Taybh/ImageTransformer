cmake_minimum_required(VERSION 3.18)
project(MyApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

find_package(OpenCV REQUIRED)

set(SOURCES
    main.cpp
    calculateTransformedImage.cpp
)

set(HEADERS
    calculateTransformedImage.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} qml.qrc)

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    ${OpenCV_LIBS}
)

# Mac runtime path to OpenCV
set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "@executable_path/../lib;/opt/homebrew/opt/opencv/lib"
)
