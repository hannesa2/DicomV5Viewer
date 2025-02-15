.. _compiling-imebra-label:

Compiling Imebra
================

This section explains how to compile Imebra from the source distribution.
You can download the source distribution from https://imebra.com, or you can create a source distribution
by following the instructions at :ref:`build-distribution-label`

The result of the Imebra compilation is a shared library for your operating system of choice.

The Imebra Source Distribution includes:

- the source code for the library
- the source code for the tests
- pre-built documentation


Compiling the C++ version of Imebra
-----------------------------------

Prerequisites
.............

In order to build the library from the Imebra Source Distribution you need:

- the source distribution of Imebra, available here: https://imebra.com/get-it/
- a modern C++ compiler (GCC, clang, Visual Studio, etc)
- CMake version 2.8 or newer (https://cmake.org/)



Building Imebra
...............

The root folder of the source distributions contains a CMakeLists file, which contains the information
needed by CMake to generate a solution file for your platform (a make file, a VisualStudio solution, etc).

To generate the Imebra shared library, execute the following steps:

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Imebra's distributrion root folder as parameter
4. execute cmake with the --build option, and on Windows optionally specify the build configuration
5. run the tests with ctest -V .

For instance:

::

    md artifacts
    cd artifacts
    cmake imebra_location
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
For instance the following script will compile a Release 64 bit version of imebra using Visual Studio 14 (2015):

::

    mkdir artifacts_64bit_release
    cd artifacts_64bit_release
    cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release imebra_location
    cmake --build . --config Release

The following example will compile a Debug 64 bit version of imebra using Visual Studio 14 (2015):

::

    mkdir artifacts_64bit_debug
    cd artifacts_64bit_debug
    cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug imebra_location
    cmake --build . --config Debug

To generate the 32 bit version of the library, just omit the architecture after the name of the cmake generator:

::

    mkdir artifacts_32bit_debug
    cd artifacts_32bit_debug
    cmake -G "Visual Studio 14 2015" -DCMAKE_BUILD_TYPE=Debug  imebra_location
    cmake --build . --config Debug


OS-X/iOS specific instructions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

On macOS, CMake will generate a build for macOS or iOS.

It is recommended to use the CMake Xcode generator when generating the build script.

The build script for macOS is the default one and can be obtained by running the following commands
(replace PATH_TO_IMEBRA_DISTRIBUTION with the path to Imebra):

::

    mkdir build_imebra_macos
    cd build_imebra_macos
    cmake -GXcode -DCMAKE_BUILD_TYPE=Release PATH_TO_IMEBRA_DISTRIBUTION

The generated build script can be opened directly with Xcode or can be built by running the following command:

::

    cmake --build . --config Release

In order to generate a build for iOS you have to set the CMAKE_SYSTEM_NAME variable 
(replace PATH_TO_IMEBRA_DISTRIBUTION with the path to Imebra):

::

    mkdir build_imebra_macos
    cd build_imebra_macos
    cmake -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_BUILD_TYPE=Release PATH_TO_IMEBRA_DISTRIBUTION

As for the macOS build, the generated script can be opened directly with Xcode or can be built by running one of the following commands:

::

    cmake --build . --config Release

or (for the simulator build):

::

    cmake --build . --config Release -- -sdk iphonesimulator

.. warning:: iOS applications based on Imebra need to be linked also with libiconv.a or libiconv.tbd.

More information about the cross compilation for iOS can be found here: https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-ios-tvos-or-watchos


Using Imebra with Swift
'''''''''''''''''''''''
Imebra can be imported into a Swift project.

After compiling the library for OS-X or iOS, import the library's Objective-C header into your Swift project.

When using the command line add the flag -import-objc-header.
For instance, the following command line instruction launches the swift compiler and instructs it to load the imebra header and link with Imebra and iconv

::

    swiftc -import-objc-header imebra_location/wrappers/objectivec/include/imebraobjc/imebra.h myCode.swift -Lbuild_imebra_location -liconv -lc++ -limebra -o myCodeApp

When using XCode open the target Build Settings and under "Swift Compiler/ObjectiveC Bridging Header" specify the path to imebra_location/wrappers/objectivec/include/imebraobjc/imebra.h.


Compiling the Android version of Imebra
---------------------------------------

Prerequisites
.............

In order to build the Android version of Imebra you need:

- the source distribution of Imebra, available here: https://imebra.com/get-it/
- Android Studio
- Android SDK
- Android NDK

Building Imebra
...............

The Android version of the library needs both the Java source code (located in the wrappers/javaWrapper folder) and the C++ source code (located in the library folder)

To generate the Imebra Jar library:

- Launch Android Studio
- Open the gradle project in the wrappers/javaWrapper folder
- Build the project


.. _compiling-imebra-java-linux:

Compiling the Java version of Imebra for Linux
----------------------------------------------

Prerequisites
.............

In order to build the Java version of Imebra you need:

- the source distribution of Imebra, available here: https://imebra.com/get-it/
- a modern C++ compiler (GCC or clang)
- CMake version 2.8 or newer (https://cmake.org/)
- the Java JDK
- the Java JNI headers

Building Imebra
...............

The Java version of the library needs both the Java source code (located in the wrappers/javaWrapper folder) and the C++ source code (located in the library folder).

The C++ code will be compiled into a dynamic library, while the java code can be added directly to your app or can be compiled into a Jar.


Compiling the C++ code
,,,,,,,,,,,,,,,,,,,,,,

To generate the native Imebra dynamic library (libimebrajni):

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Imebra's "wrappers/javaWrapper" folder as parameter
4. execute cmake with the --build option

For instance:

::

    md artifacts
    cd artifacts
    cmake imebra_location/wrapper/javaWrappers
    cmake --build .

The first CMake command will generate a solution file for the your platform, the second CMake command with the --build option will launch make.


Compiling the Java code
,,,,,,,,,,,,,,,,,,,,,,,

The Java code is in the source distribution folder "wrappers/javaWrapper/src". Compile it with the java compiler (javac) and pack it into a Jar
or add it directly to your Java application.


Loading the native library
..........................

Before your application can call any method on any Imebra class it must load the native dynamic library.

In your application startup code add:

::

    System.loadLibrary("imebrajni");


When you launch the application, specify the folder containing the native dynamic library by setting the "java.library.path" property.


