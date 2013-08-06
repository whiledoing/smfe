cmake_minimum_required(VERSION 2.8.0)
project(test_using_smfe_library)

set(_target test_using_smfe_library)

###############################################################################
#
#   SMFE library
#
###############################################################################
list(APPEND CMAKE_MODULE_PATH ${SMFE_DIR})
if(NOT SMFE_DIR)
    message(FATAL_ERROR "please define SMFE_DIR variable into cmake")
endif()
include(support_smfe)

###############################################################################
#
#   Test target 
#
###############################################################################
add_executable(${_target} test.cpp)

# need set SMFE_DIR and BOOST_DIR variable before adding smfe library,
# otherwise, an error will occured
support_smfe(${_target})
