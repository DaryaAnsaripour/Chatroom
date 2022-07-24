cmake_minimum_required(VERSION 3.1.0)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIRECTORY src)
set(INCLUDE_DIRECTORY headers)

set(SOURCES
    ${SRC_DIRECTORY}/Timestamp.cpp
    ${SRC_DIRECTORY}/Tablefile.cpp
    ${SRC_DIRECTORY}/Userserver.cpp
    ${SRC_DIRECTORY}/User.cpp
    ${SRC_DIRECTORY}/Group.cpp
    ${SRC_DIRECTORY}/Server.cpp
)

include_directories(${INCLUDE_DIRECTORY})
add_executable(${PROJECT_NAME}
    ${SRC_DIRECTORY}/main.cpp
    ${SOURCES})

target_link_libraries(${PROJECT_NAME}
pthread)
