macro(support_aquila target)

    if(NOT AQUILA_DIR)
        message(FATAL_ERROR "please define AQUILA_DIR")
    endif()

    include_directories("${AQUILA_DIR}/include")

    set(_aquila_lib_path "${AQUILA_DIR}/lib")

    find_library(_aquila_debug_libs NAMES Aquila HINTS "${_aquila_lib_path}/debug")
    find_library(_aquila_release_libs NAMES Aquila HINTS "${_aquila_lib_path}/release")

    find_library(_ooura_debug_libs NAMES Ooura_fft HINTS "${_aquila_lib_path}/debug")
    find_library(_ooura_release_libs NAMES Ooura_fft HINTS "${_aquila_lib_path}/release")

    # list(APPEND _aquila_libs debug "${_aquila_lib_path}/Aquila_debug.lib")
    # list(APPEND _aquila_libs debug "${_aquila_lib_path}/Ooura_fft_debug.lib")

    # list(APPEND _aquila_libs optimized "${_aquila_lib_path}/Aquila_release.lib")
    # list(APPEND _aquila_libs optimized "${_aquila_lib_path}/Ooura_fft_release.lib")

    target_link_libraries(${target} debug ${_aquila_debug_libs})
    target_link_libraries(${target} debug ${_ooura_debug_libs})

    target_link_libraries(${target} optimized ${_aquila_release_libs})
    target_link_libraries(${target} optimized ${_ooura_release_libs})

endmacro()
