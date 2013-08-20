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

# enable C++11 support in GNU compiler
if(CMAKE_COMPILER_IS_GNUCXX)
   SET(ENABLE_CXX11 "-std=c++11")

   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()

   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()

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

# wavlet2d dir
set(WAVELET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rd/wavelet2d")

# fftw dir
set(FFTW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rd/fftw")
include(support_fftw)

# boost
set(BOOST_DIR $ENV{BOOST_ROOT} CACHE PATH "boost root directory")
option(Boost_USE_STATIC_LIBS "link with boost static library" OFF)
option(Boost_USE_MULTITHREADED "link with multithreaded library" ON)
option(Boost_USE_STATIC_RUNTIME "link with static c runtime library" OFF)
find_package(Boost REQUIRED COMPONENTS filesystem system unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

# disable all auto link
add_definitions(-DBOOST_ALL_NO_LIB)

if(NOT Boost_USE_STATIC_LIBS)
    add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

# in *nix system, you need to define BOOST_TEST_DYN_LINK
# (http://abauchu.net/blog/post/2009/12/02/Unit-tests-with-BoostTest)
if(UNIX)
    add_definitions(-DBOOST_TEST_DYN_LINK)
endif()

###############################################################################
#
#   Output Directory
#
###############################################################################

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/debug")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/release")
endif()

if(MSVC)
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
        string(TOLOWER ${OUTPUTCONFIG} OUTPUTCONFIG_LOWER)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
            "${CMAKE_SOURCE_DIR}/lib/${OUTPUTCONFIG_LOWER}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
            "${CMAKE_SOURCE_DIR}/lib/${OUTPUTCONFIG_LOWER}")
    endforeach()
endif()

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
