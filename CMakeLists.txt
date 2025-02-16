cmake_minimum_required(VERSION 3.16)

project(BaseMacro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src/ui)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB ASSETS_FILES assets/*)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp

        src/widgets/dialoghowtouse.cpp
        src/widgets/dialogtips.cpp
        src/widgets/dialogabout.cpp
        src/widgets/settingswindow.cpp
        src/widgets/macroeditor.cpp

        src/core/actionpool.cpp
        src/core/baseaction.cpp
        src/core/configmanager.cpp
        src/core/filemanager.cpp
        src/core/macrobuild.cpp
        src/core/threadmanager.cpp
)

set(PROJECT_HEADERS
        src/mainwindow.h

        src/widgets/DialogBase.h
        src/widgets/dialoghowtouse.h
        src/widgets/dialogtips.h
        src/widgets/dialogabout.h
        src/widgets/settingswindow.h
        src/widgets/macroeditor.h

        src/core/actionpool.h
        src/core/baseaction.h
        src/core/configmanager.h
        src/core/DefaultConstants.h
        src/core/filemanager.h
        src/core/macrobuild.h
        src/core/threadmanager.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BaseMacro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${ASSETS_FILES}
        src/ui/mainwindow.ui
        src/ui/dialogabout.ui
        src/ui/dialoghowtouse.ui
        src/ui/dialogtips.ui
        src/ui/settingswindow.ui
        src/ui/macroeditor.ui
    )
else()
    if(ANDROID)
        add_library(BaseMacro SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
    else()
        add_executable(BaseMacro
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
    endif()
endif()

qt_add_resources(BaseMacro "icon"
    PREFIX "/"
    FILES
        assets/logo.ico
        assets/logo.png
        assets/bracket.png
        assets/break-continue.png
        assets/code.png
        assets/delay.png
        assets/find.png
        assets/goto.png
        assets/if.png
        assets/keyboard.png
        assets/label.png
        assets/loop.png
        assets/mouse.png
        assets/paste.png
        assets/stop.png
        assets/website.png
)


target_include_directories(BaseMacro PRIVATE include ${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS})
target_link_libraries(BaseMacro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BaseMacro)
endif()
set_target_properties(BaseMacro PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BaseMacro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BaseMacro)
endif()
