cmake_minimum_required(VERSION 3.12)

# Set the cxx version
#--------------------
add_definitions(-DDICOMHERO_CPP_VERSION=${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("*${CMAKE_CXX_STANDARD}*" STREQUAL "**")
    set(CMAKE_CXX_STANDARD 11)
endif()
if("*${CMAKE_C_STANDARD}*" STREQUAL "**")
    set(CMAKE_C_STANDARD 11)
endif()

if(APPLE)
    if("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS")
        set(CMAKE_OSX_DEPLOYMENT_TARGET "13" CACHE STRING "Minimum iOS deployment version" FORCE)
    else()
        set(CMAKE_OSX_DEPLOYMENT_TARGET "11" CACHE STRING "Minimum MacOS deployment version" FORCE)
    endif()
    message("Mimimum OS version: ${CMAKE_OSX_DEPLOYMENT_TARGET}")
endif()

# We need thread support
find_package(Threads REQUIRED)


# Add flags specific to the compiler
#-----------------------------------
set(dicomhero_libraries "")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    set(dicomhero_libraries ${dicomhero_libraries} Kernel32)

else()

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message("Debug mode, enabling coverage")
        add_compile_options(--coverage)
        set(dicomhero_libraries ${dicomhero_libraries} gcov)
    endif()
endif()


# Set the proper logging preprocessor macros
#-------------------------------------------
if(DICOMHERO_LOG_FRAMEWORK MATCHES LOG4CXX)
    add_definitions(-DDICOMHERO_LOGGING_LOG4CXX)
    set(dicomhero_libraries ${dicomhero_libraries} log4cxx) # Log4cxx needs additional libraries
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES SYSLOG)
    add_definitions(-DDICOMHERO_LOGGING_SYSLOG)
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES COUT)
    add_definitions(-DDICOMHERO_LOGGING_COUT)
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES APPLE)
    add_definitions(-DDICOMHERO_LOGGING_APPLE)
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES ANDROID)
    add_definitions(-DDICOMHERO_LOGGING_ANDROID)
endif(DICOMHERO_LOG_FRAMEWORK MATCHES LOG4CXX)

if(DICOMHERO_LOG_LEVEL)
    add_definitions(-DDICOMHERO_LOG_LEVEL_${DICOMHERO_LOG_LEVEL})
endif(DICOMHERO_LOG_LEVEL)

if(DICOMHERO_EXCEPTION_TRACKING)
    add_definitions(-DDICOMHERO_EXCEPTION_TRACKING)
endif()


# Set the charset conversion library
#-----------------------------------
if(WIN32)
    set(DICOMHERO_CHARSET_CONVERSION "WINDOWS" CACHE STRING "Charset conversion library to use")
else()
    set(DICOMHERO_CHARSET_CONVERSION "ICONV" CACHE STRING "Charset conversion library to use")
endif(WIN32)

if("*${DICOMHERO_CHARSET_CONVERSION}*" STREQUAL "*ICONV*")
    message("Using ICONV")
    add_definitions(-DDICOMHERO_USE_ICONV)
    if(APPLE)
        set(dicomhero_libraries ${dicomhero_libraries} iconv)
    endif(APPLE)
elseif("*${DICOMHERO_CHARSET_CONVERSION}*" STREQUAL "*JAVA*")
    message("Using JAVA")
    add_definitions(-DDICOMHERO_USE_JAVA)
elseif("*${DICOMHERO_CHARSET_CONVERSION}*" STREQUAL "*WINDOWS*")
    message("Using WINDOWS CHARSET CONVERSION")
    add_definitions(-DDICOMHERO_USE_WINDOWS_CHARSET)
else()
    message(FATAL_ERROR "Set DICOMHERO_CHARSET_CONVERSION to ICONV, WINDOWS or JAVA")
endif()

# Get sources
#------------
file(GLOB dicomhero_interface "${CMAKE_CURRENT_SOURCE_DIR}/library/include/dicomhero6/*.h")
file(GLOB imebra_interface "${CMAKE_CURRENT_SOURCE_DIR}/library/include/imebra/*.h")
file(GLOB dicomhero_include "${CMAKE_CURRENT_SOURCE_DIR}/library/src/*.h")
file(GLOB dicomhero_src "${CMAKE_CURRENT_SOURCE_DIR}/library/src/*.cpp")
file(GLOB dicomhero_implementation_src "${CMAKE_CURRENT_SOURCE_DIR}/library/implementation/*.cpp")
file(GLOB dicomhero_implementation_include "${CMAKE_CURRENT_SOURCE_DIR}/library/implementation/*.h")
set(dicomhero_jni_src "")
set(dicomhero_objc_src "")
set(dicomhero_implementation_src_objc "")
set(dicomhero_objc_include "")
set(dicomhero_objc_include_dir "")
set(dicomhero_objc_gnustep_dir "")

if(${DICOMHERO_OBJC})

    file(GLOB dicomhero_objc_src "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/src/*.*")
    file(GLOB dicomhero_implementation_src_objc "${CMAKE_CURRENT_SOURCE_DIR}/library/implementation/*.mm")
    file(GLOB dicomhero_objc_include "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/include/dicomhero6_objc/*.h")
    add_definitions(-DDICOMHERO_OBJC)

    set(dicomhero_objc_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/include)

    set(objc_compiler_flags "${CMAKE_CXX_FLAGS}")
    if(APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Foundation -framework CoreServices -framework CoreGraphics")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Foundation -framework CoreServices -framework CoreGraphics")
        set(objc_compiler_flags "${objc_compiler_flags} -fobjc-arc")
        if(IOS)
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework UIKit")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework UIKit")
        else()
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework AppKit")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
        endif()
    endif()

    if(NOT "${objc_compiler_flags}" STREQUAL "")

        foreach(objcfile ${dicomhero_objc_src})
            set_source_files_properties(${objcfile} PROPERTIES COMPILE_FLAGS ${objc_compiler_flags})
        endforeach(objcfile ${dicomhero_objc_src})

    endif(NOT "${objc_compiler_flags}" STREQUAL "")

endif()


if(NOT "${DICOMHERO_JNI_FILE}" STREQUAL "")
    set(dicomhero_jni_src "${DICOMHERO_JNI_FILE}")
endif()


if(NOT "${ADDITIONAL_LIB_PATH}" STREQUAL "")
    link_directories(${LINK_DIRECTORIES} ${ADDITIONAL_LIB_PATH})
endif(NOT "${ADDITIONAL_LIB_PATH}" STREQUAL "")

# Add jpeg2000 if specified
if("${JPEG2000}" STREQUAL "1")
    set(dicomhero_libraries ${dicomhero_libraries} openjpeg)
    add_definitions(-DJPEG2000)
    add_definitions(-DJPEG2000_V1)
    message(STATUS "Adding experimental Jpeg2000 codec (based on OpenJpeg v1.X)")
endif("${JPEG2000}" STREQUAL "1")

if("${JPEG2000}" STREQUAL "2")
    set(dicomhero_libraries ${dicomhero_libraries} openjp2)
    add_definitions(-DJPEG2000)
    add_definitions(-DJPEG2000_V2)
    message(STATUS "Adding experimental Jpeg2000 codec (based on OpenJpeg v2.X)")
endif("${JPEG2000}" STREQUAL "2")

add_library(dicomhero6 ${DICOMHERO_SHARED_STATIC}
    ${dicomhero_implementation_src}
    ${dicomhero_implementation_src_objc}
    ${dicomhero_implementation_include}
    ${dicomhero_objc_src}
    ${dicomhero_jni_src}
    ${dicomhero_objc_include}
    ${dicomhero_include}
    ${dicomhero_src}
    ${imebra_interface}
    ${dicomhero_interface}
)

get_target_property(library_flags dicomhero6 "COMPILE_OPTIONS")
get_target_property(cs dicomhero6 "CXX_STANDARD")
message("LIBRARY FLAGS ${library_flags} / ${cs}")

if(NOT "${ADDITIONAL_INCLUDE_PATH}" STREQUAL "")
    target_include_directories(dicomhero PRIVATE ${ADDITIONAL_INCLUDE_PATH})
endif(NOT "${ADDITIONAL_INCLUDE_PATH}" STREQUAL "")

if(${DICOMHERO_OBJC})
    set(HIDDEN_FLAGS "")
else()
    set(HIDDEN_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")
endif()

target_include_directories(dicomhero6 PRIVATE ${dicomhero_objc_gnustep_dir})

# Define dependency libraries
#----------------------------
target_link_libraries(dicomhero6 ${dicomhero_libraries} Threads::Threads)

message (STATUS "OBJC INCLUDE:${dicomhero_objc_include_dir}")
message (STATUS "GNU INCLUDE:${dicomhero_objc_gnustep_dir}")

# Define dicomhero public folder
#-------------------------------
target_include_directories(dicomhero6 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/library/include> $<INSTALL_INTERFACE:include>)
target_include_directories(dicomhero6 PUBLIC $<BUILD_INTERFACE:${dicomhero_objc_include_dir}> $<INSTALL_INTERFACE:include>)

set_target_properties(dicomhero6 PROPERTIES VERSION ${DICOMHERO_VERSION}
                                          SOVERSION ${DICOMHERO_MAJOR_VERSION})

if(APPLE)
    math(EXPR letterAsciiCode "65 + ${major}")
    string(ASCII ${letterAsciiCode} FRAMEWORK_LETTER_VERSION)

    set_target_properties(dicomhero6 PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION ${FRAMEWORK_LETTER_VERSION}
        MACOSX_FRAMEWORK_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/custom_framework.plist"
        MACOSX_FRAMEWORK_IDENTIFIER "com.dicomhero.dicomhero6"
        MACOSX_FRAMEWORK_BUNDLE_VERSION "${major}.${minor}.${build}"
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${major}.${minor}.${build}"
        # "current version" in semantic format in Mach-O binary file
        VERSION "${major}.${minor}.${build}"
        # "compatibility version" in semantic format in Mach-O binary file
        SOVERSION "${major}.0.0"
        PUBLIC_HEADER "${dicomhero_objc_include}"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.dicomhero.dicomhero6"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    )

endif()


if(NOT IOS)

  ##############################################
  #
  # TESTS
  #
  ##############################################

  # Find DCMTK for interoperability tests.
  find_package(DCMTK)
  if(${DCMTK_FOUND})
          message(STATUS "DCMTK found. Interoperability tests enabled")
  else(${DCMTK_FOUND})
          add_definitions(-DDISABLE_DCMTK_INTEROPERABILITY_TEST)
          message(WARNING "WARNING: DCMTK not found. Disabling interoperability tests")
  endif(${DCMTK_FOUND})

  # Enable ExternalProject CMake module (so we can load GoogleTest)
  include(ExternalProject)

  # Download and install GoogleTest
  ExternalProject_Add(
      GTest
      URL https://github.com/google/googletest/archive/release-1.12.1.zip
      CMAKE_ARGS "-Dgtest_force_shared_crt=ON" "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/gtest_install" "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}" "-DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}"
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
      INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/gtest_install
  )

  set(dicomhero_tests_objc_src "")
  file(GLOB dicomhero_tests_include "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")
  file(GLOB dicomhero_tests_src "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
  if(${DICOMHERO_OBJC})

      file(GLOB dicomhero_tests_objc_src "${CMAKE_CURRENT_SOURCE_DIR}/tests/objectivec/*.m*")

      if(NOT "${objc_compiler_flags}" STREQUAL "")

          foreach(objcfile ${dicomhero_tests_objc_src})
              set_source_files_properties(${objcfile} PROPERTIES COMPILE_FLAGS ${objc_compiler_flags})
          endforeach(objcfile ${dicomhero_objc_src})

      endif(NOT "${objc_compiler_flags}" STREQUAL "")

  endif()

  link_directories(${CMAKE_CURRENT_BINARY_DIR}/gtest_install/lib)
  add_executable(dicomheroTests
          ${dicomhero_tests_include}
          ${dicomhero_tests_src}
          ${dicomhero_tests_objc_src}
  )
  add_dependencies(dicomheroTests GTest)
  target_include_directories(dicomheroTests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gtest_install/include)
  target_link_libraries(dicomheroTests dicomhero6 "gtest")

  if(${DCMTK_FOUND})
      target_link_libraries(dicomheroTests dcmdata dcmimage)
  endif()

  #################################################################
  #
  # RUN TESTS
  #
  # The test dcmtkDicomOverlay fails with ASAN,
  # so it is not run by default.
  #################################################################
  if(DICOMHERO_FAST_TESTS)
    set(FAST_FLAG "--fast")
  endif()
  if(DICOMHERO_LOG_FRAMEWORK MATCHES LOG4CXX)
    add_test(RunDicomheroTestsExceptions dicomheroTests --gtest_filter=exceptionsTest.* --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles --testLogFile=${CMAKE_CURRENT_BINARY_DIR}/dicomheroTestLogFile.txt ${FAST_FLAG})
    add_test(RunDicomheroTestsNoExceptions dicomheroTests --gtest_filter=-exceptionsTest.*:dicomCodecInteroperabilityTest.dcmtkDicomOverlay --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles --testLogFile=${CMAKE_CURRENT_BINARY_DIR}/dicomheroTestLogFile.txt ${FAST_FLAG})
  else()
    add_test(RunDicomheroTestsExceptions dicomheroTests --gtest_filter=exceptionsTest.* --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles ${FAST_FLAG})
    add_test(RunDicomheroTestsNoExceptions dicomheroTests --gtest_filter=-exceptionsTest.*:dicomCodecInteroperabilityTest.dcmtkDicomOverlay --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles ${FAST_FLAG})
  endif()
  add_test(RunDicomheroTestsNOASAN dicomheroTests --gtest_filter=dicomCodecInteroperabilityTest.dcmtkDicomOverlay --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles --testLogFile=${CMAKE_CURRENT_BINARY_DIR}/dicomheroTestLogFile.txt ${FAST_FLAG})
  set_property(TEST RunDicomheroTestsNOASAN PROPERTY ENVIRONMENT "ASAN_OPTIONS=alloc_dealloc_mismatch=0")


endif()


