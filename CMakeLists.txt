cmake_minimum_required(VERSION 3.7)

project(dde-introduction
        VERSION 1.0.0)

set(BIN_NAME dde-introduction)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Sources files
file(GLOB SRCS "src/*.h"
               "src/*.cpp"
               "src/*.cc"
               "src/*/*.cpp"
               "src/*/*.h"
               "src/*/*.cc")

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Dtk REQUIRED Widget)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(DFrameworkdbus REQUIRED)

# driver-manager
add_executable(${BIN_NAME} ${SRCS} dde-introduction.qrc)
target_include_directories(${BIN_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS} ${DFrameworkdbus_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} PRIVATE
    ${DtkWidget_LIBRARIES}
    ${DtkCore_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${DFrameworkdbus_LIBRARIES}
    ${Qt5Multimedia_LIBRARIES}
    ${Qt5MultimediaWidgets_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
    )

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

# bin
install(TARGETS ${BIN_NAME} DESTINATION bin)

# desktop
install (FILES dde-introduction.desktop DESTINATION share/applications)

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

    # generate qm
    execute_process(COMMAND bash "translate_generation.sh"
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif ()


# qm files
file(GLOB QM_FILES "translations/*.qm")
install(FILES ${QM_FILES} DESTINATION share/dde-introduction/translations)
