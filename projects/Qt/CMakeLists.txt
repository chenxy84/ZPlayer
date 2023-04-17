cmake_minimum_required(VERSION 3.5)

project(zplayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(ROOT_PATH ${CMAKE_MODULE_PATH}/../..)
include("../../src/zplayer_core.cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        player_controller.cpp
        player_controller.h
        IJKMediaPlayer/ijkplayer_qt.cc
        IJKMediaPlayer/ijkplayer_qt.h）
)

qt_add_executable(zplayer
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(zplayer PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets  
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    player_core)

set_target_properties(zplayer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS zplayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(zplayer)
endif()
