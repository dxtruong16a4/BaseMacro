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

file(GLOB RESOURCES_FILES resources/*)

set(PROJECT_SOURCES
        # main
        src/main.cpp
        src/mainwindow.cpp
        # widgets
        src/widgets/dialoghowtouse.cpp
        src/widgets/dialogtips.cpp
        src/widgets/dialogabout.cpp
        src/widgets/settingswindow.cpp
        src/widgets/macroeditor.cpp
        # core
        src/core/baseaction.cpp
        src/core/configmanager.cpp
        src/core/dialogpool.cpp
        src/core/filemanager.cpp
        src/core/macrobuild.cpp
        src/core/threadmanager.cpp
        # Action mode
        src/actionmode/dialogclick.cpp
        src/actionmode/dialogkeyboard.cpp
        src/actionmode/dialogdelay.cpp
        # utils
        src/utils/helper.cpp
)

set(PROJECT_HEADERS
        # main
        src/mainwindow.h
        # widgets
        src/widgets/dialoghowtouse.h
        src/widgets/dialogtips.h
        src/widgets/dialogabout.h
        src/widgets/settingswindow.h
        src/widgets/macroeditor.h
        # core
        src/core/baseaction.h
        src/core/configmanager.h
        src/core/DefaultConstants.h
        src/core/DialogBase.h
        src/core/dialogpool.h
        src/core/filemanager.h
        src/core/macrobuild.h
        src/core/threadmanager.h
        # Action mode
        src/actionmode/dialogclick.h
        src/actionmode/dialogkeyboard.h
        src/actionmode/dialogdelay.h
        # utils
        src/utils/helper.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BaseMacro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${ASSETS_FILES}
        # Main UI
        src/ui/mainwindow.ui
        src/ui/dialogabout.ui
        src/ui/dialoghowtouse.ui
        src/ui/dialogtips.ui
        src/ui/settingswindow.ui
        src/ui/macroeditor.ui
        # Action mode UI
        src/ui/dialogclick.ui
        src/ui/dialogkeyboard.ui
        src/ui/dialogdelay.ui
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
        resources/icon/arrow_down.png
        resources/icon/arrow_up.png
        resources/icon/logo.ico
        resources/icon/logo.png
        resources/icon/bracket.png
        resources/icon/break-continue.png
        resources/icon/clipboard.png
        resources/icon/code.png
        resources/icon/connected.png
        resources/icon/delay.png
        resources/icon/disconnected.png
        resources/icon/exe.png
        resources/icon/find.png
        resources/icon/goto.png
        resources/icon/if.png
        resources/icon/keyboard.png
        resources/icon/label.png
        resources/icon/location.png
        resources/icon/loop.png
        resources/icon/mouse.png
        resources/icon/open.png
        resources/icon/playing.gif
        resources/icon/stop.png
        resources/icon/switch.png
        resources/icon/window.png
        # style.qss
        resources/style.qss
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
