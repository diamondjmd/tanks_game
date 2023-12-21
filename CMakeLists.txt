cmake_minimum_required(VERSION 3.12)
project(tanks_game_project)

set(CMAKE_CXX_STANDARD 17)


# Set the path to Vcpkg toolchain file
# CMAKE_TOOLCHAIN_FILE "<path_to_vcpkg_directory>/scripts/buildsystems/vcpkg.cmake"
set(CMAKE_TOOLCHAIN_FILE "/home/joe/vcpkg/scripts/buildsystems/vcpkg.cmake")


# Trying to find preinstalled SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # If SFML is not found - download and build from source
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    #  Work around potential issues when building sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()


find_package(nlohmann_json REQUIRED)

if (nlohmann_json_FOUND)
    message(STATUS "The nlohmann_json installed in the system will be used")
else()
    message(STATUS " Not found The nlohmann_json library in the system")
endif()

# Unfortunately, up to C++20 https://en.cppreference.com/w/cpp/numeric/constants
# no convenient cross-platform way to get pi.
# define below is needed to enable M_PI
if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_subdirectory(src)
add_subdirectory(tests)

# set (exec_name "tanks")