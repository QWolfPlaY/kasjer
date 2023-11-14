cmake_minimum_required(VERSION 3.26)
project(kasjer)

option(EXT_BUILD_DIR "Output build result to diffrent directory" OFF)

if (EXT_BUILD_DIR)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/debug)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/release)
    else ()
        message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "EXECUTABLE")

add_subdirectory(${CMAKE_SOURCE_DIR}/include/cpp-core)

add_executable(kasjer src/main.cpp)

target_include_directories(kasjer PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(kasjer PRIVATE
        core
)

add_executable(bin_generator
        src/bin_generator/bin_generator.cpp
        src/bin_generator/bin_generator.h)

target_include_directories(bin_generator PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(bin_generator PRIVATE
        core
)