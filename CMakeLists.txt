cmake_minimum_required(VERSION 3.20)
project(DA_PROJ_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp include/utils.h src/utils.cpp include/Menu.h src/Menu.cpp src/Company.cpp include/Company.h include/constants.h src/graph.cpp include/graph.h)

include_directories(DA_PROJ_2 include/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)