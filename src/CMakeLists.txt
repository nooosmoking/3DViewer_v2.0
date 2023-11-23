cmake_minimum_required(VERSION 3.5)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        3DCore
        3DExtras
        3DRender
        3DInput
        REQUIRED)

set(PROJECT_SOURCES
        resourses.qrc
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        model.h
)

add_executable(untitled
    ${PROJECT_SOURCES}
)

target_link_libraries(untitled
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::3DCore
    Qt::3DExtras
    Qt::3DRender
    Qt::3DInput
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled)
endif()


set(PROJECT_SOURCES_TEST
        resourses.qrc
        test_qt.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        model.h
)

add_executable(untitled_test
    ${PROJECT_SOURCES_TEST}
)

target_link_libraries(untitled_test
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::3DCore
    Qt::3DExtras
    Qt::3DRender
    Qt::3DInput
    gtest 
    gtest_main
)

