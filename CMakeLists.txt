cmake_minimum_required(VERSION 3.10)
project(Hangar CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug by default so GDB (Week 10) can show your variable names and source lines.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Absolute path to the data/ folder, so the program works no matter
# which directory you run it from.
set(hangar_data_dir "${CMAKE_SOURCE_DIR}/data")

# The Pilot class lives in its own small library so the Pilot self-checks
# do not depend on the menu code compiling.
add_library(pilot_core STATIC src/pilot.cpp)
target_include_directories(pilot_core PUBLIC include)

add_library(hangar_core STATIC
    src/mech.cpp
    src/battle_sim.cpp
    src/roster_io.cpp
    src/input.cpp
    src/pilot_menu.cpp
)
target_link_libraries(hangar_core PUBLIC pilot_core)
target_include_directories(hangar_core PUBLIC include)

add_executable(hangar app/main.cpp)
target_link_libraries(hangar PRIVATE hangar_core)
target_compile_definitions(hangar PRIVATE HANGAR_DATA_DIR="${hangar_data_dir}")

# Self-check: run ./build/check_io to test your roster_io functions.
add_executable(check_io tests/check_io.cpp)
target_link_libraries(check_io PRIVATE hangar_core)
target_compile_definitions(check_io PRIVATE HANGAR_DATA_DIR="${hangar_data_dir}")

# Week 9 Pilot self-checks. They are not built by default, because each one only
# compiles once you reach that checkpoint:
#   cmake --build build --target check_cp1 && ./build/check_cp1
foreach(checkpoint cp1 cp2 cp3)
    add_executable(check_${checkpoint} EXCLUDE_FROM_ALL tests/check_${checkpoint}.cpp)
    target_link_libraries(check_${checkpoint} PRIVATE pilot_core)
    target_include_directories(check_${checkpoint} PRIVATE tests)
endforeach()

enable_testing()
add_test(NAME check_io COMMAND check_io)
