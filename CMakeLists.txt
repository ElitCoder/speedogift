# CMake version
cmake_minimum_required(VERSION 3.1)

# Project definition
project(speedogift CXX)

# Sources
set(CLIENT_SRCS
        client/src/SpeedogiftClient.cpp
        client/src/ClientProcessor.cpp)

set(SERVER_SRCS
        server/src/ServerProcessor.cpp
        server/src/SpeedogiftServer.cpp)

set(SHARED_SRCS
        shared/src/API.cpp
        shared/src/APIAuth.cpp
        shared/src/APIAuthReply.cpp
        shared/src/APIListReply.cpp)

# Compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic)

# Dependencies
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

# Executable
add_executable(speedogift_client ${SHARED_SRCS} ${CLIENT_SRCS})
add_executable(speedogift_server ${SHARED_SRCS} ${SERVER_SRCS})

# Includes
target_include_directories(speedogift_client PRIVATE shared/src)
target_include_directories(speedogift_server PRIVATE shared/src)

# Linking
target_link_libraries(speedogift_client PRIVATE spdlog::spdlog)
target_link_libraries(speedogift_client PRIVATE ncnet)
target_link_libraries(speedogift_server PRIVATE spdlog::spdlog)
target_link_libraries(speedogift_server PRIVATE ncnet)