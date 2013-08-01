macro(support_fftw target)

    if(NOT FFTW_DIR)
        message(FATAL_ERROR "please define FFTW_DIR")
    endif()

    include_directories("${FFTW_DIR}/include")

    set(_fftw_lib_dir "${FFTW_DIR}/lib")

    find_library(_fftw_lib NAMES libfftw3-3 fftw3-3 HINTS "${_fftw_lib_dir}")
    find_library(_fftwf_lib NAMES libfftw3f-3 fftw3f-3 HINTS "${_fftw_lib_dir}")

    set(_libs ${_fftw_lib} ${_fftwf_lib})
    target_link_libraries(${target} ${_libs})

endmacro()
