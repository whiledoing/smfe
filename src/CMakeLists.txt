set(_target smfe_lib)

file(GLOB_RECURSE _headers ${_smfe_include_dirs}/*.h ${_smfe_include_dirs}/*.hpp)
file(GLOB_RECURSE _sources *.cpp)
set(_files ${_headers} ${_sources})

if(BUILD_SHARED_LIBS)
    add_definitions(-DSMFE_BUILD)
endif()

include_directories(${_smfe_include_dirs})
add_library(${_target} ${_files})

target_link_libraries(${_target} ${Boost_LIBRARIES})
support_aquila(${_target})
