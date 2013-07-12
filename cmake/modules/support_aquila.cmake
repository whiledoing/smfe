macro(support_aquila target)

include_directories("${AQUILA_DIR}/include")

set(_aquila_lib_path "${AQUILA_DIR}/lib")

list(APPEND _aquila_libs debug "${_aquila_lib_path}/Aquila_debug.lib")
list(APPEND _aquila_libs debug "${_aquila_lib_path}/Ooura_fft_debug.lib")

list(APPEND _aquila_libs optimized "${_aquila_lib_path}/Aquila_release.lib")
list(APPEND _aquila_libs optimized "${_aquila_lib_path}/Ooura_fft_release.lib")

target_link_libraries(${target} ${_aquila_libs})

endmacro()
