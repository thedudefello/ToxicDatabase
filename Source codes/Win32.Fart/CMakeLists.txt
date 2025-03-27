cmake_minimum_required(VERSION 3.12)
project("MegaPerdey")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(RESOURCE
    "Resource/resource.rc"
    "Resource/resource.h"
)

set(SOURCE
    "src/Common.hpp"
    "src/Volume.cpp"
    "src/main.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE} ${RESOURCE})
