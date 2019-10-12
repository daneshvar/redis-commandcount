cmake_minimum_required(VERSION 3.0)
set (PROJECT_VERSION "1.0")
set(PROJECT_NAME cmdcount)
file(GLOB SOURCES src/*.[ch])

add_definitions(-DCMDCOUNT_MOD_VER=${PROJECT_VERSION})
add_definitions(-DCMDCOUNT_MOD_NAME="${PROJECT_NAME}")

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(deps/)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME}
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)
