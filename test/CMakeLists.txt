set(_target smfe_test)

file(GLOB_RECURSE _headers *.h *.hpp)
file(GLOB_RECURSE _sources *.cpp)
set(_files ${_headers} ${_sources})

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/smfe_test_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    @only
)
list(APPEND _files "${CMAKE_CURRENT_BINARY_DIR}/config.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${_smfe_include_dirs})
add_executable(${_target} ${_files})

target_link_libraries(${_target} smfe_lib ${Boost_LIBRARIES})
support_aquila(${_target})
support_fftw(${_target})

# copy dependencies
acmake_append_runtime_dirs(${_target} ${Boost_LIBRARY_DIRS})
acmake_copy_dependencies(${_target})

add_test(
    NAME ${_target}
    COMMAND $<TARGET_FILE:${_target}>
)
