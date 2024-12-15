cmake_minimum_required(VERSION 3.16)

project(Room-Planner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Room-Planner
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc

        room-editor/zoomablegraphicsview.h
        room-editor/roomeditor.h room-editor/roomeditor.cpp
        room-editor/popuplabel.h room-editor/popuplabel.cpp
        tools/itool.h
        tools/walltool.h tools/walltool.cpp
        room-editor/WallPoint/Direction.h
        room-editor/Grid.h

        tools/dragtool.h tools/dragtool.cpp
        room-editor/InteractivePoint/gridpoint.h room-editor/InteractivePoint/gridpoint.cpp
        room-editor/SceneObjects/roomeditorobject.h
        room-editor/SceneObjects/rewall.h room-editor/SceneObjects/rewall.cpp
        room-editor/SceneObjects/rewindow.h room-editor/SceneObjects/rewindow.cpp
        room-editor/SceneObjects/redoor.h room-editor/SceneObjects/redoor.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Room-Planner APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Room-Planner SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Room-Planner
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Room-Planner PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Room-Planner)
endif()
set_target_properties(Room-Planner PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Room-Planner
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Room-Planner)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
