cmake_minimum_required(VERSION 3.5)

project(NotToday VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt6 6.1.2 REQUIRED COMPONENTS Core)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory("tools")

set(PROJECT_SOURCES
        main.cpp

        widgets/dashboard.h widgets/dashboard.cpp
        widgets/mainwindow.h widgets/mainwindow.cpp
        widgets/tabmodel.h widgets/tabmodel.cpp
        widgets/tabwidget.h widgets/tabwidget.cpp
        widgets/taskdialog.h widgets/taskdialog.cpp
        widgets/taskmanagement.h widgets/taskmanagement.cpp
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NotToday
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(NotToday SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(NotToday
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NotToday PRIVATE Qt${QT_VERSION_MAJOR}::Widgets LibTools)

set_target_properties(NotToday PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NotToday)
endif()

###############################################################################
##########          Doxygen
###############################################################################
find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()

set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

add_custom_target(BuildDoc ALL
  COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
  COMMENT "Generating Doxygen documentation"
  VERBATIM
)

###############################################################################
##########          TESTING
###############################################################################

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests.cpp ${LibTools_TESTS})
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests gtest_main LibTools)

include(GoogleTest)
gtest_discover_tests(tests)
enable_testing()
