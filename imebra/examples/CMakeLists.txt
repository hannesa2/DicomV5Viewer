cmake_minimum_required(VERSION 3.12)


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

endif()

    ##############################################
    #
    # DICOM2JPEG example
    #
    ##############################################
    file(GLOB dicom2jpeg_sources "${CMAKE_CURRENT_SOURCE_DIR}/c++/dicom2jpeg/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(dicom2jpeg ${dicom2jpeg_sources})

    target_link_libraries(dicom2jpeg dicomhero6)


    ##############################################
    #
    # CHANGETRANSFERSYNTAX example
    #
    ##############################################
    file(GLOB changeTransferSyntax_sources "${CMAKE_CURRENT_SOURCE_DIR}/c++/changeTransferSyntax/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(changeTransferSyntax ${changeTransferSyntax_sources})

    target_link_libraries(changeTransferSyntax dicomhero6)


    ##############################################
    #
    # DICOMDIRITEMS example
    #
    ##############################################
    file(GLOB dicomdirItems_sources "${CMAKE_CURRENT_SOURCE_DIR}/c++/dicomdirItems/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(dicomDirItems ${dicomdirItems_sources})

    target_link_libraries(dicomDirItems dicomhero6)


    ##############################################
    #
    # scpExample example
    #
    ##############################################
    file(GLOB scpExample_sources "${CMAKE_CURRENT_SOURCE_DIR}/c++/scpExample/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(scpExample ${scpExample_sources})

    target_link_libraries(scpExample dicomhero6)


