cmake_minimum_required(VERSION 3.26)
project(city-members)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent to fetch external libraries
include(FetchContent)

# Fetch the fmt library
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.1.1
)
FetchContent_MakeAvailable(fmt)

# Add the executable
add_executable(city-members main.cpp
        src/City.cpp
        src/Member.cpp
        src/MemberBase.cpp
        helper.cpp)
target_link_libraries(city-members fmt)