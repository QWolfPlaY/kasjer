cmake_minimum_required(VERSION 3.26)
project(kasjer)

option(EXT_BUILD_DIR "Output build result to different directory" OFF)
option(BIN_GENERATOR_EXEC "Creates executable from bin_generator instead of library" ON)

add_compile_definitions(
        LOGGING_LEVEL=spdlog::level::debug
)

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

add_subdirectory(include/cpp-core)
add_subdirectory(include/spdlog)

add_executable(kasjer src/main.cpp)

target_include_directories(kasjer PRIVATE
        include
)

target_link_libraries(kasjer PRIVATE
        core
        spdlog
)

add_library(bin_generator
        src/bin_generator/bin_generator.cpp
        src/bin_generator/bin_generator.h
)

target_include_directories(bin_generator PRIVATE
        include
)

target_link_libraries(bin_generator PRIVATE
        core
        spdlog
)

add_executable(bin_generator_exec
        src/bin_generator/exec/main.cpp
        src/bin_generator/bin_generator.cpp
        src/bin_generator/bin_generator.h
        include/cpp-core/core.cpp
        include/cpp-core/core.h
)

target_include_directories(bin_generator_exec PRIVATE
        include
        src/bin_generator
)

target_link_libraries(bin_generator_exec PRIVATE
        core
        spdlog
        bin_generator
)

target_compile_definitions(bin_generator_exec PRIVATE LOGGING_LEVEL=spdlog::level::debug)