cmake_minimum_required(VERSION 3.7)
project(ping-icon)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK REQUIRED gtkmm-3.0)
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(SOURCE_FILES
        main.cc
        PingIcon.cc
        PingIcon.h)

set(LIBRARIES
        ${GTK_LIBRARIES}
        pthread)

add_executable(ping-icon ${SOURCE_FILES})
target_link_libraries(ping-icon ${LIBRARIES})
install(TARGETS ping-icon DESTINATION bin)
