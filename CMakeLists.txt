cmake_minimum_required(VERSION 3.7)

project(dde-introduction
        VERSION 1.0.0)

set(BIN_NAME dde-introduction)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS -Wall)

# Sources files
file(GLOB SRCS "src/*.h"
               "src/*.cpp"
               "src/modules/*.h"
               "src/modules/*.cc")

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Dtk REQUIRED Widget)

# driver-manager
add_executable(${BIN_NAME} ${SRCS})
target_include_directories(${BIN_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS})
target_link_libraries(${BIN_NAME} PRIVATE
  ${DtkWidget_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Concurrent_LIBRARIES}
  ${DFrameworkdbus_LIBRARIES}
  )

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

# bin
install(TARGETS ${BIN_NAME} DESTINATION bin)

# desktop
install (FILES dde-introduction.desktop DESTINATION share/applications)
