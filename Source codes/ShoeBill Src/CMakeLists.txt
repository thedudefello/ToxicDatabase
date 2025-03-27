cmake_minimum_required(VERSION 3.8)
project("Win32.Shoebill.Joke.Virus")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

set(RESOURCE
    "Resource/resource.rc"
    "Resource/resource.h"
)

set(SOURCE
    "src/Common.hpp"
    "src/main.cpp"
    "src/MainWindow.cpp"
    "src/Effect.cpp"
    "src/CloseProc.cpp"
    "src/BSOD.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE} ${RESOURCE})

if (WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES)
endif()