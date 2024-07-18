cmake_minimum_required(VERSION 3.5)

project(mysql-demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".LIB" ".dll" ".DLL" ".dylib")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 指定库文件的相对路径
set(MYSQL_DIR "lib/mysql-connector-c++-8.0.33")
include_directories(${MYSQL_DIR}/include)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mysql-demo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ui.cpp
        rs.qrc
        customtreewidget.h customtreewidget.cpp
        data.cpp
        connect.cpp
        dbquery.h dbquery.cpp

        tab.h tab.cpp
        tabitem.h
        tableinfotabitem.h tableinfotabitem.cpp
        commonutils.h commonutils.cpp
        resultutils.h resultutils.cpp
        tableinfopage.h tableinfopage.cpp
        querypage.h querypage.cpp
        connectdialog.h connectdialog.cpp
        connectinfo.h connectinfo.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mysql-demo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(mysql-demo SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(mysql-demo
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(mysql-demo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

file(GLOB_RECURSE MYSQL_LIBRARIES "${MYSQL_DIR}/lib64/*.dylib")
# 遍历找到的所有库文件
foreach(MYSQL_LIBRARY ${MYSQL_LIBRARIES})
    message(${MYSQL_LIBRARY})
    # 添加库到目标
    target_link_libraries(mysql-demo PRIVATE ${MYSQL_LIBRARY})
endforeach()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.mysql-demo)
endif()
set_target_properties(mysql-demo PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS mysql-demo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mysql-demo)
endif()
