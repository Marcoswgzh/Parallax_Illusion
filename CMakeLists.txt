cmake_minimum_required(VERSION 3.10)
project(parallax)

# Include all .cpp files from src as source files
file(GLOB SOURCES src/*.cpp)

add_executable(parallax ${SOURCES})

# Set env file path
set(ENV_FILE "${CMAKE_SOURCE_DIR}/.env")

# Make sure that .env exists
if(NOT EXISTS ${ENV_FILE})
    message(FATAL_ERROR "Error: .env not found at ${CMAKE_SOURCE_DIR}")
endif()

# Read the content from .env into ENV_CONTENT
file(READ "${CMAKE_SOURCE_DIR}/.env" ENV_CONTENT)

# Split content into lines
separate_arguments(ENV_LINES UNIX_COMMAND "${ENV_CONTENT}")

# Make all environmental variables available in the cpp program by adding properties
foreach(line IN LISTS ENV_LINES)
    # Continue on empty lines or comments
    if(line MATCHES "^\\s*$" AND line MATCHES "^#")
        continue()
    endif()

    # Get the name and value of the current environmental variable
    string(REGEX MATCH "^[^=]+" VAR_NAME "${line}")
    string(REGEX REPLACE "^[^=]+=" "" VAR_VALUE "${line}")

    # Add quotes
    set(MACRO_VALUE "\"${VAR_VALUE}\"")

    message(STATUS "Adding compile definition: ${VAR_NAME}=${MACRO_VALUE}")
    target_compile_definitions(parallax PRIVATE ${VAR_NAME}=${MACRO_VALUE})
endforeach()

# Find and parse the OPENCV_PATH env variable
string(REGEX MATCH "OPENCV_PATH=[\"']?([^\"'\n\r]+)[\"']?" _ ${ENV_CONTENT})

# Clean and store the env variable (cmake treats it as a list, so we have to remove the =; prefix)
string(REGEX REPLACE "^[=;]+" "" OpenCV_ENV "${CMAKE_MATCH_1}")
set(OpenCV_DIR "${OpenCV_ENV}/4.12.0_11/lib/cmake/opencv4")
message(STATUS "Using opencv in directory: ${OpenCV_DIR}")

# Find opencv
find_package(OpenCV REQUIRED)

# Compile Glad
add_library(glad external/glad/glad.c)

# Looks in external/glad for header files and adds them to all targets which include it.
target_include_directories(glad PUBLIC external/glad)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Compile GLFW
add_subdirectory(external/glfw-3.4)

# Link all dependencies
target_link_libraries(parallax PRIVATE ${OpenCV_LIBS} glfw glad OpenGL::GL)

# For language support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
