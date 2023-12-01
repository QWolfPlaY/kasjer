cmake_minimum_required(VERSION 3.26)
project(kasjer)

option(EXT_BUILD_DIR "Output build result to different directory" OFF)

add_compile_definitions(
        LOGGING_LEVEL=spdlog::level::debug
)

if (EXT_BUILD_DIR) # DOESNT WORK :(
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_BINARY_DIR  ${CMAKE_SOURCE_DIR}/build/debug)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_BINARY_DIR  ${CMAKE_SOURCE_DIR}/build/release)
    else ()
        message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(include/cpp-core)
add_subdirectory(include/spdlog)
add_subdirectory(src/bin_generator)

add_executable(kasjer src/main.cpp)

target_include_directories(kasjer PRIVATE
        include
)

target_link_libraries(kasjer PRIVATE
        core
        spdlog
)

add_executable(bin_generator_exec
        src/bin_generator_exec/main.cpp
        include/cpp-core/core.cpp
        src/bin_generator/bin_generator.cpp
)

target_include_directories(bin_generator_exec PUBLIC
        include
        src/bin_generator
)

target_link_libraries(bin_generator_exec PUBLIC
        core
        bin_generator
        spdlog
)

target_compile_definitions(bin_generator_exec PRIVATE LOGGING_LEVEL=spdlog::level::debug)

add_library(decoder src/decoder/decoder.cpp src/decoder/decoder.h)

target_include_directories(decoder PUBLIC
        src/bin_generator
)

target_link_libraries(decoder PUBLIC
        core
        bin_generator
)
