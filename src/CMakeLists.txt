set(_target smfe_lib)

file(GLOB_RECURSE _headers ${_smfe_include_dirs}/*.h ${_smfe_include_dirs}/*.hpp)
file(GLOB_RECURSE _sources *.cpp)

# add wavlet2d source
list(APPEND _headers "${WAVELET_DIR}/include/wavelet2d.h")
list(APPEND _sources "${WAVELET_DIR}/src/wavelet2d.cpp")
set(_files ${_headers} ${_sources})

if(BUILD_SHARED_LIBS)
    add_definitions(-DSMFE_BUILD)
endif()

include_directories(${WAVELET_DIR}/include)

include_directories(${_smfe_include_dirs})
add_library(${_target} ${_files})

list(APPEND _libs ${Boost_LIBRARIES})

target_link_libraries(${_target} ${_libs})

support_aquila(${_target})
support_fftw(${_target})
