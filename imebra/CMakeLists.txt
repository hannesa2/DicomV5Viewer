# Options:
# -DDICOMHERO_SHARED_STATIC=SHARED|STATIC (default = SHARED)
# -DDICOMHERO_BUILD_JPEG2000=0|1|2 include JPEG2000 codec (1=version 1.X 2=version2.X)
# -DADDITIONAL_INCLUDE_PATH=path to additional include folders (optional)
# -DADDITIONAL_LIB_PATH=path to additional libraries (optional)
# -DICOMHERO_JNI_FILE=path to the JNI file (optional)
# -DDICOMHERO_CHARSET_CONVERSION=ICONV|JAVA|WINDOWS (default = ICONV on posix, WINDOWS on Windows)
# -DDICOMHERO_OBJC=1|0 (default = 0)
# -DDICOMHERO_BUILD_DOCUMENTATION=ON|OFF (default = OFF) Build the documentation
# -DICOMHERO_FAST_TESTS=ON|OFF (default = OFF) Run the ctest i fast mode when ON (less iterations in expensive loops)

cmake_minimum_required(VERSION 3.12)

project("dicomhero6")

set(DICOMHERO_SHARED_STATIC "SHARED" CACHE STRING "Type of library to build (SHARED or STATIC)")
set(DICOMHERO_BUILD_JPEG2000 "0" CACHE STRING "Experimentally build the jpeg2000 codec (0=jpeg2000 disabled, 1=use OpenJpeg v1.x, 2=use OpenJpeg v2.x)")
set(DICOMHERO_BUILD_DOCUMENTATION OFF CACHE BOOL "If ON then build the DicomHero documentation. Needs Python and Doxygen installed")
set(DICOMHERO_JNI_FILE "" CACHE STRING "Path to the swig generated JNI file")
set(DICOMHERO_FAST_TESTS OFF CACHE BOOL "Run the ctest in fast mode when ON (less iterations in expensive loops)")
if(APPLE)
    set(DICOMHERO_OBJC ON CACHE BOOL "Build the objective-c wrapper")
else()
    set(DICOMHERO_OBJC OFF CACHE BOOL "Build the objective-c wrapper")
endif()
set(DICOMHERO_LOG_LEVEL "WARNING" CACHE STRING "Library LOG level. Valid values are: DISABLED, FATAL, ERROR, WARNING, INFO, DEBUG, TRACE")
set(DICOMHERO_EXCEPTION_TRACKING ON CACHE STRING "Enable the tracking of the exception as it travels up the stack")

# Check validity of DICOMHERO_LOG_LEVEL
list(APPEND DICOMHERO_LOG_LEVEL_LIST
    "DISABLED"
    "FATAL"
    "ERROR"
    "WARNING"
    "INFO"
    "DEBUG"
    "TRACE")
if(NOT ";${DICOMHERO_LOG_LEVEL_LIST};;" MATCHES ";${DICOMHERO_LOG_LEVEL};")
    message(FATAL_ERROR "Set DICOMHERO_LOG_LEVEL to a valid value (DISABLED, FATAL, ERROR, WARNING, INFO, DEBUG, TRACE)")
endif()


# Enable testing
#=========================================================================
enable_testing()

#
# Use C++11 by default. Set CMAKE_CXX_STANDARD to force other versions.
#
#=========================================================================
if("*${CMAKE_CXX_STANDARD}*" STREQUAL "**")
    set(CMAKE_CXX_STANDARD 11)
endif()

#
# The build type must be explicitly set
#
#=========================================================================
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if("*${CMAKE_BUILD_TYPE}*" STREQUAL "**")
    set(CMAKE_BUILD_TYPE "Debug") # Default build mode is debug
endif()

#
# Generate vcs_version.h
#
#=========================================================================
find_package (Git)
set(VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version/dicomhero_vcs_version.h")
set(VERSION_FILE_RAW "${CMAKE_CURRENT_BINARY_DIR}/version.txt")
if (GIT_FOUND)
    message("git found: ${GIT_EXECUTABLE}")
    execute_process(COMMAND "${GIT_EXECUTABLE}" "branch"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE branches OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(NOT "*${branches}*" STREQUAL "**")

        string(REPLACE "\n" ";" branchesList "${branches}")
        foreach(checkBranch ${branchesList})
            message("checking ${checkBranch}")
            string(SUBSTRING ${checkBranch} 0 2 active)
            if("${active}" STREQUAL "* ")
                string(SUBSTRING ${checkBranch} 2 -1 branch)
            endif()
        endforeach()

        execute_process(COMMAND "${GIT_EXECUTABLE}" "rev-parse" "HEAD"
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                OUTPUT_VARIABLE hash OUTPUT_STRIP_TRAILING_WHITESPACE)

        if(NOT "$ENV{APPVEYOR_REPO_BRANCH}" STREQUAL "")
            set(branch $ENV{APPVEYOR_REPO_BRANCH})
        endif()
        message("Branch ${branch}")

        if((${branch} MATCHES "^[0-9]+\.[0-9.]*[0-9]+$") OR (${branch} MATCHES ".*/[0-9]+\.[0-9.]*[0-9]+$"))
            string(APPEND branch ".0.0.0.0")
            string(REGEX MATCHALL "[0-9]+" major_minor_build "${branch}")
            list(LENGTH major_minor_build version_length)
            list(GET major_minor_build 0 major)
            list(GET major_minor_build 1 minor)
            list(GET major_minor_build 2 patch)
            list(GET major_minor_build 3 build)
        else()
            set(major "0")
            set(minor "0")
            set(patch "0")
            set(build "0")
        endif()

        message("Version ${major}.${minor}.${build}")

        set(version_rc "${major},${minor},${patch},${build}")

        file(WRITE "${VERSION_FILE}" "#ifndef VERSION_FILE\n")
        file(APPEND "${VERSION_FILE}" "#define VERSION_FILE\n")
        file(APPEND "${VERSION_FILE}" "#define VCS_COMMIT_SHORTHASH \"${hash}\"\n")
        file(APPEND "${VERSION_FILE}" "#define VERSION_MAJOR ${major}\n")
        file(APPEND "${VERSION_FILE}" "#define VERSION_MINOR ${minor}\n")
        file(APPEND "${VERSION_FILE}" "#define VERSION_PATCH ${patch}\n")
        file(APPEND "${VERSION_FILE}" "#define VERSION_BUILD ${build}\n")
        file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION \"${major}.${minor}.${patch}\"\n")
        file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_FULL \"${major}.${minor}.${patch}.${build}\"\n")
        file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_FULL_W L\"${major}.${minor}.${patch}.${build}\"\n")
        file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_RC \"${version_rc}\"\n")
        file(APPEND "${VERSION_FILE}" "#endif\n")
        file(WRITE "${VERSION_FILE_RAW}" "${major}.${minor}.${patch}.${build}")

        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version/versionMajor.txt" "${major}")
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version/versionMinor.txt" "${minor}")
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version/versionPatch.txt" "${patch}")
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version/versionBuild.txt" "${build}")

    endif ()
endif ()
if("*${major}*" STREQUAL "**")
    file (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/dicomheroCore6/library/include/versionMajor.txt" major)
    file (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/dicomheroCore6/library/include/versionMinor.txt" minor)
    file (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/dicomheroCore6/library/include/versionPatch.txt" patch)
    file (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/dicomheroCore6/library/include/versionBuild.txt" build)
endif()

set(DICOMHERO_MAJOR_VERSION ${major})
set(DICOMHERO_VERSION "${major}.${minor}.${patch}.${build}")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version)


##############################################
#
# DOCUMENTATION
#
##############################################
find_package (Python3 COMPONENTS Interpreter)
if(${DICOMHERO_BUILD_DOCUMENTATION} AND ${Python3_FOUND})
    find_package (Doxygen REQUIRED)
    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import jinja2"
        RESULT_VARIABLE JINJA_EXIT_CODE
        OUTPUT_QUIET
    )

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import sphinx"
        RESULT_VARIABLE SPHINX_EXIT_CODE
        OUTPUT_QUIET
    )

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import breathe"
        RESULT_VARIABLE BREATHE_EXIT_CODE
        OUTPUT_QUIET
    )

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import sphinx_rtd_theme"
        RESULT_VARIABLE SPHINX_RTD_THEME_EXIT_CODE
        OUTPUT_QUIET
    )

    if(NOT ${JINJA_EXIT_CODE} EQUAL 0)
        message(WARNING "To build the documentation you need to install the python package jinja2 (Preferred version is 3.0.3)")
    endif()

    if(NOT ${SPHINX_EXIT_CODE} EQUAL 0)
        message(WARNING "To build the documentation you need to install the python package sphinx (Preferred version is 2.4.4)")
    endif()

    if(NOT ${BREATHE_EXIT_CODE} EQUAL 0)
        message(WARNING "To build the documentation you need to install the python package breathe (Preferred version is 4.14.2)")
    endif()

    if(NOT ${SPHINX_RTD_THEME_EXIT_CODE} EQUAL 0)
        message(WARNING "To build the documentation you need to install the python package sphinx_rtd_theme")
    endif()

    if(${JINJA_EXIT_CODE} EQUAL 0 AND ${SPHINX_EXIT_CODE} EQUAL 0 AND ${BREATHE_EXIT_CODE} EQUAL 0 AND ${SPHINX_RTD_THEME_EXIT_CODE} EQUAL 0)
        file(GLOB dicomhero_doc_sources "${CMAKE_SOURCE_DIR}/docs/*.*")
        file(GLOB dicomhero_doc_interface "${CMAKE_SOURCE_DIR}/dicomheroCore6/library/include/dicomhero6/*.h")

        add_custom_target(documentation ALL "sphinx-build" "-b" "html" "${CMAKE_CURRENT_SOURCE_DIR}/docs" "${CMAKE_CURRENT_BINARY_DIR}/docs/html"
            SOURCES ${dicomhero_doc_sources}
                    ${dicomhero_doc_interface})
    endif()

    # Source package
    #---------------
    add_custom_target(dicomhero_source_distribution
        COMMAND "${CMAKE_COMMAND}"
          --build "${CMAKE_BINARY_DIR}"
          --target package_source
        DEPENDS "documentation"
        VERBATIM
        USES_TERMINAL
      )

endif()


if(NOT DEFINED DICOMHERO_SHARED_STATIC)
    set(DICOMHERO_SHARED_STATIC "SHARED")
endif(NOT DEFINED DICOMHERO_SHARED_STATIC)

##############################################
#
# LIBRARY
#
##############################################
add_definitions(-DDICOMHERO_DLL)
add_definitions(-DDICOMHERO_DLL_EXPORTS)
add_definitions(-DNOMINMAX)

# Add flags specific to the compiler
#-----------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message(STATUS "MSVC detected, adding compile flags")

    add_compile_options(
        /W4
        /bigobj
    )

else()

    message(STATUS "GNU or Clang detected, adding compile flags")

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wfloat-equal
    )

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        add_compile_options(
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wfloat-equal
            -fsanitize=address
        )

        add_link_options(
            -fsanitize=address
        )
    endif()
endif()

add_subdirectory(dicomheroCore6)

if(NOT IOS)
    add_subdirectory(examples)
endif()

##############################################
#
# PACKAGING
#
##############################################

set(CPACK_SOURCE_INSTALLED_DIRECTORIES
  "${CMAKE_SOURCE_DIR};/source;${CMAKE_CURRENT_BINARY_DIR}/dicomhero_vcs_version;/source/dicomheroCore6/library/include")

# Set packaging variables
#------------------------
set(CPACK_PACKAGE_NAME "dicomhero6")
set(CPACK_PACKAGE_CONTACT "paolo@binarno.com")
set(CPACK_PACKAGE_VERSION ${DICOMHERO_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "DICOMHero library for DICOM medical files")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/readme.rst")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://dicomhero.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Paolo Brandoli <paolo@binarno.com>")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

set(CPACK_RPM_PACKAGE_REQUIRES "libc6")

# Generate the control scripts
#-----------------------------
set(SHLIBS_FILE     "${CMAKE_CURRENT_BINARY_DIR}/shlibs")
set(POSTINST_SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/postinst")
set(PRERM_SCRIPT    "${CMAKE_CURRENT_BINARY_DIR}/prerm")
set(POSTRM_SCRIPT   "${CMAKE_CURRENT_BINARY_DIR}/postrm")

# Generate postinst, prerm and postrm hooks
file(WRITE "${POSTINST_SCRIPT}" "#!/bin/sh\n\nset -e\n")
file(WRITE "${PRERM_SCRIPT}"    "#!/bin/sh\n\nset -e\n")
file(WRITE "${POSTRM_SCRIPT}"   "#!/bin/sh\n\nset -e\n")

# Generate shlibs
file(WRITE "${SHLIBS_FILE}" "libdicomhero6 ${DICOMHERO_MAJOR_VERSION} ${CPACK_PACKAGE_NAME}\n")
file(APPEND "${POSTINST_SCRIPT}"
     "if [ \"$1\" = \"configure\" ]; then
        ldconfig
fi
")
file(APPEND "${POSTRM_SCRIPT}"
     "if [ \"$1\" = \"remove\" ]; then
        ldconfig
fi")

execute_process(COMMAND chmod 644 "${SHLIBS_FILE}")
execute_process(COMMAND chmod 755 "${POSTINST_SCRIPT}" "${PRERM_SCRIPT}" "${POSTRM_SCRIPT}")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${SHLIBS_FILE};${POSTINST_SCRIPT};${PRERM_SCRIPT};${POSTRM_SCRIPT}")

# Write license file
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/copyright"
     "Copyright (C) 2005-2021 ${CPACK_DEBIAN_PACKAGE_MAINTAINER}")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/copyright"
        DESTINATION "share/doc/${CPACK_PACKAGE_NAME}/"
        PERMISSIONS
        OWNER_WRITE OWNER_READ
        GROUP_READ
        WORLD_READ)

install(TARGETS dicomhero6 EXPORT dicomhero6Config LIBRARY DESTINATION lib
                                                 ARCHIVE DESTINATION lib
                                                 FRAMEWORK DESTINATION lib
                                                 RUNTIME DESTINATION bin
                                                 PUBLIC_HEADER DESTINATION include
                                                 COMPONENT "DICOMHERO Shared library")

if(${DICOMHERO_BUILD_DOCUMENTATION})
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs"
            DESTINATION "share/doc/${CPACK_PACKAGE_NAME}/")
endif()

install(FILES ${imebra_interface} DESTINATION include/imebra COMPONENT "DICOMHero legacy include files")
install(FILES ${dicomhero_interface} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")
install(FILES ${VERSION_FILE} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")
install(FILES ${VERSION_FILE_RAW} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")

if(${DICOMHERO_OBJC})
    install(FILES ${dicomhero_objc_include} DESTINATION include/dicomhero6_objc COMPONENT "DICOMHero objc include files")
endif()

install(EXPORT dicomhero6Config DESTINATION share/dicomhero6/cmake)

include(CPack)
