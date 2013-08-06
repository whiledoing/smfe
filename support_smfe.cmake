macro(support_smfe target)

    if(NOT SMFE_DIR)
        message(FATAL_ERROR "please define SMFE_DIR")
    endif()

    if(NOT EXISTS ${SMFE_DIR})
        message(FATAL_ERROR "please define SMFE_DIR")
    endif()

    set(SMFE_INCLUDE_DIRS "${SMFE_DIR}/include")
    if(NOT EXISTS "${SMFE_INCLUDE_DIRS}")
        message(FATAL_ERROR "please define SMFE_DIR")
    endif()

    set(SMFE_LIBRARY_DIRS "${SMFE_DIR}/lib")
    if(NOT EXISTS "${SMFE_LIBRARY_DIRS}")
        message(FATAL_ERROR "please compile smfe first, and put builded libraries into `lib/debug` and `lib/release` directory")
    endif()

    ###############################################################################
    #
    #   Library
    #
    ###############################################################################
    list(APPEND CMAKE_MODULE_PATH ${SMFE_DIR}/cmake/modules)

    # smfe itself
    find_library(_smfe_debug_libs NAMES smfe_lib HINTS "${SMFE_LIBRARY_DIRS}/debug")
    find_library(_smfe_release_libs NAMES smfe_lib HINTS "${SMFE_LIBRARY_DIRS}/release")

    if(NOT _smfe_debug_libs OR NOT _smfe_release_libs)
        message(FATAL_ERROR "can't find smfe_lib in ${SMFE_DIR}/lib/debug(release), please compile it first")
    endif()

    include_directories(${SMFE_INCLUDE_DIRS})
    target_link_libraries(${target} debug ${_smfe_debug_libs})
    target_link_libraries(${target} optimized ${_smfe_release_libs})

    # aqulia
    set(AQUILA_DIR "${SMFE_DIR}/3rd/aquila")
    include(support_aquila)
    support_aquila(${target})

    # armadillo
    set(ARMADILLO_DIR "${SMFE_DIR}/3rd/armadillo")
    include_directories(${ARMADILLO_DIR}/include)

    # wavlet2d 
    set(WAVELET_DIR "${SMFE_DIR}/3rd/wavelet2d")
    include_directories(${WAVELET_DIR}/include)

    # fftw 
    set(FFTW_DIR "${SMFE_DIR}/3rd/fftw")
    include(support_fftw)
    support_fftw(${target})

    # boost 
    set(BOOST_DIR $ENV{BOOST_ROOT} CACHE PATH "boost root directory")
    if(NOT BOOST_DIR)
        message(FATAL_ERROR "please define BOOST_DIR variable into cmake")
    endif()

    option(Boost_USE_STATIC_LIBS "link with boost static library" ON)
    option(Boost_USE_MULTITHREADED "link with multithreaded library" ON)
    option(Boost_USE_STATIC_RUNTIME "link with static c runtime library" OFF)
    find_package(Boost REQUIRED COMPONENTS filesystem system unit_test_framework)
    include_directories(${Boost_INCLUDE_DIRS})
    list(APPEND SMFE_LIBRARIES ${Boost_LIBRARIES})

endmacro()
