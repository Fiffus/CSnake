cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME "snake")
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(" ")
message("########### ${PROJECT_NAME} ###########")
message("#")
message("#  PROJECT_DIR: ${PROJECT_DIR}")
message("#")

project(${PROJECT_NAME}
        LANGUAGES C
        VERSION 1.0
)

# Set ROOT_DIR
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

# Set BUILD variables
set(CMAKE_C_STANDARD 23)

# Set C Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")

# Get all source files
set(SOURCE_DIR ${PROJECT_DIR}/src)
message("#  SOURCE_DIR: ${SOURCE_DIR}")

file(GLOB_RECURSE SOURCES
        "${SOURCE_DIR}/**/*.c"
        "${SOURCE_DIR}/*.c"
)

# Get all header files
set(HEADER_DIR ${PROJECT_DIR}/include)
message("#  HEADER_DIR: ${HEADER_DIR}")
message("#")

file(GLOB_RECURSE HEADERS
        "${HEADER_DIR}/**/*.h"
        "${HEADER_DIR}/*.h"
)

# Add SDL2 Headers
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIR})

# Create executable
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
)

# Add headers
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR})

# Add Math.h library
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${MATH_LIBRARY})
endif()

# Add SDL2
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_ttf::SDL2_ttf)

# Copy executable to build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy $<TARGET_FILE:${PROJECT_NAME}>
        ${ROOT_DIR}/.out/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)

# Copy resources
set(RESOURCE_DIR ${ROOT_DIR}/resources)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCE_DIR} ${ROOT_DIR}/.out/resources
    COMMENT "Copying resources to the output directory"
)

message("#")
message("#  OUTPUT_BINARY: " ${ROOT_DIR}/.out/)
message("# ")
message("#######################################")
message(" ")
