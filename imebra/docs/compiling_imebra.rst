.. _compiling-imebra-label:

Compiling Dicomhero
===================

This section explains how to compile Dicomhero from the source distribution.
You can download the source distribution from https://dicomhero.com, or you can create a source distribution
by following the instructions at :ref:`build-distribution-label`

The result of the Dicomhero compilation is a shared library for your operating system of choice.

The Dicomhero Source Distribution includes:

- the source code for the library
- the source code for the tests
- pre-built documentation


Compiling the C++ version of Dicomhero
--------------------------------------

Prerequisites
.............

In order to build the library from the Dicomhero Source Distribution you need:

- the source distribution of Dicomhero, available here: https://dicomhero.com/downloads
- a modern C++ compiler supporting at least C++11 (GCC, clang, Visual Studio, etc)
- CMake version 3.12 or newer (https://cmake.org/)



Building Dicomhero
..................

The root folder of the source distributions contains a CMakeLists file which contains the information
needed by CMake to generate a solution file for your platform (a make file, a VisualStudio solution, etc).

To generate the Dicomhero shared library, execute the following steps:

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Dicomhero's distributrion root folder as parameter
4. execute cmake with the --build option, and on Windows optionally specify the build configuration
5. run the tests with ctest -V .

For instance:

::

    md artifacts
    cd artifacts
    cmake dicomhero_location
    cmake --build .
    ctest -V .

The first CMake command will generate a solution file for the your platform: this will be a 
make file on Linux, a VisualStudio solution of Windows, an XCode project on Mac.

The second CMake command with the --build option will launch make, VisualStudio or the build
chain defined on your machine.

The CTest command will launch the test application.


Windows specific instructions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

On Windows cmake will, by default, generate a 32 bit solution for the most recent Visual Studio compiler installed on
the system.

It is possible to build a 64 bit version of the library by explicitly specifying a 64 bit generator when launching cmake.

The cmake generators available on Windows include:

- Visual Studio 16 2019 [arch] = Generates Visual Studio 2019 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 10 2010 [arch] = Generates Visual Studio 2010 project files.
                                 Optional [arch] can be "Win64" or "IA64".
- Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
- Visual Studio 8 2005 [arch]  = Generates Visual Studio 2005 project files.
                                 Optional [arch] can be "Win64".

To generate the 64 bit version of the library just specify the proper generator and architecture.
For instance the following script will compile a Release 64 bit version of DicomHero using Visual Studio 14 (2015):

::

    mkdir artifacts_64bit_release
    cd artifacts_64bit_release
    cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release dicomhero_location
    cmake --build . --config Release

The following example will compile a Debug 64 bit version of DicomHero using Visual Studio 14 (2015):

::

    mkdir artifacts_64bit_debug
    cd artifacts_64bit_debug
    cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug dicomhero_location
    cmake --build . --config Debug

To generate the 32 bit version of the library, just omit the architecture after the name of the cmake generator:

::

    mkdir artifacts_32bit_debug
    cd artifacts_32bit_debug
    cmake -G "Visual Studio 14 2015" -DCMAKE_BUILD_TYPE=Debug  dicomhero_location
    cmake --build . --config Debug


OS-X/iOS specific instructions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

On macOS, CMake will generate a build for macOS or iOS.

It is recommended to use the CMake Xcode generator when generating the build script.

The build script for macOS is the default one and can be obtained by running the following commands
(replace PATH_TO_DICOMHERO_DISTRIBUTION with the path to Dicomhero):

::

    mkdir build_dicomhero_macos
    cd build_dicomhero_macos
    cmake -GXcode -DCMAKE_BUILD_TYPE=Release PATH_TO_DICOMHERO_DISTRIBUTION

The generated build script can be opened directly with Xcode or can be built by running the following command:

::

    cmake --build . --config Release

In order to generate a build for iOS you have to set the CMAKE_SYSTEM_NAME variable 
(replace PATH_TO_DICOMHERO_DISTRIBUTION with the path to Dicomhero):

::

    mkdir build_dicomhero_macos
    cd build_dicomhero_macos
    cmake -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_BUILD_TYPE=Release PATH_TO_DICOMHERO_DISTRIBUTION

As for the macOS build, the generated script can be opened directly with Xcode or can be built by running one of the following commands:

::

    cmake --build . --config Release -- sdk=iphoneos

or (for the simulator build):

::

    cmake --build . --config Release -- sdk=iphonesimulator

.. warning:: iOS applications based on Dicomhero need to be linked also with libiconv.a or libiconv.tbd.


Using Dicomhero with Swift
'''''''''''''''''''''''
Dicomhero can be imported into a Swift project.

After compiling the library for OS-X or iOS, import the library's Objective-C header into your Swift project.

When using the command line add the flag -import-objc-header.
For instance, the following command line instruction launches the swift compiler and instructs it to load the DicomHHero header and link with Dicomhero and iconv

::

    swiftc -import-objc-header dicomhero_location/dicomheroCore6/wrappers/objectivec/include/dicomhero6_objc/dicomhero.h myCode.swift -Lbuild_dicomhero_location -liconv -lc++ -ldicomhero -o myCodeApp

When using XCode open the target Build Settings and under "Swift Compiler/ObjectiveC Bridging Header" specify the path to dicomhero_location/dicomheroCore6/wrappers/objectivec/include/dicomhero6_objc/dicomhero.h.


Compiling the Android version of Dicomhero
------------------------------------------

Prerequisites
.............

In order to build the Android version of Dicomhero you need:

- the source distribution of Dicomhero, available here: https://dicomhero.com/downloads
- Android Studio
- Android SDK
- Android NDK
- SWIG (https://www.swig.org/)

Building Dicomhero
...............

The Android version of the library needs both the Java source code (located in the wrappers/javaWrapper folder) and the C++ source code (located in the library folder)

To generate the Dicomhero Jar library:

- Launch Android Studio
- Open the gradle project
- Build the project


Loading the native library
..........................

Before your application can call any method on any Dicomhero class it must load the native dynamic library.

In your application startup code add:

::

    System.loadLibrary("dicomhero6");


All the DICOMHERO classes are in the package “com.dicomhero.api”.


