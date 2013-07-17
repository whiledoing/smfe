cmake_minimum_required(VERSION 2.8.0)

project(sensor_motion_feature_extraction)

###############################################################################
#
#   Global Settings
#
###############################################################################
option(BUILD_SHARED_LIBS "build shared libs or not, default is build static" OFF)
if(BUILD_SHARED_LIBS)
    add_definitions(-DBUILD_SHARED_LIBS)
endif()

option(SMFE_BUILD_TEST "whether to build test" ON)

set(_smfe_include_dirs  ${CMAKE_CURRENT_SOURCE_DIR}/include)

###############################################################################
#
#   Library
#
###############################################################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# aqulia
set(AQUILA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rd/aquila")
include(support_aquila)

# armadillo
set(ARMADILLO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rd/armadillo")
include_directories(${ARMADILLO_DIR}/include)

# boost
option(Boost_USE_STATIC_LIBS "link with boost static library" ON) 
option(Boost_USE_MULTITHREADED "link with multithreaded library" ON)  
option(Boost_USE_STATIC_RUNTIME "link with static c runtime library" OFF) 
find_package(Boost REQUIRED COMPONENTS filesystem system unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

###############################################################################
#
#   Add Target
#
###############################################################################
add_subdirectory(src)

if(SMFE_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
