cmake_minimum_required(VERSION 2.8.0)
project(test_using_smfe_library)

set(_target test_using_smfe_library)

###############################################################################
#
#   SMFE library
#
###############################################################################

# 设置smfe库所在的目录
# note: 还需要设置好boost, smfe在寻找lib的时候需要使用到boost
set(SMFE_DIR "F:/proj/sm-feature-extraction")
list(APPEND CMAKE_MODULE_PATH ${SMFE_DIR})
include(support_smfe)

add_executable(${_target} test.cpp)

# 加入smfe库
support_smfe(${_target})
