DicomHero
*********

Introduction
============

DicomHero is a C++ DICOM library able to:

- parse & build DICOM files
- decompress/compress/process the embedded DICOM images
- send and receive DIMSE commands and responses as an SCU or SCP

A JNI interface allows to use the library also with the JAVA language, including on Android OS.

Objective-C wrappers (compatible with Swift) are also available.


Versioning
==========

Public releases of DicomHero are versioned according to the rules defined in `Semantic versioning <http://semver.org/>`_.

Nightly releases are versioned as public releases but their minor version or patch number are set to 999 (the master branch
or the major version branches have a minor version set to 999, the minor version branches have a patch number set to 999).

For instance:

- version 5.1.999.45 indicates a nightly build of version 5.1, build from the commit number 45 in the branch.
- version 5.999.999.678 indicates a nightly build of version 5 (master branch), build from the commit number 678 in the branch.


Compiling DicomHero
===================

The result of the DicomHero compilation is a shared library for your operating system of choice.

Compiling the C++ version of DicomHero
--------------------------------------

Prerequisites
.............

In order to build the library you need:

- a modern C++ compiler supporting C++11 (GCC, clang, Visual Studio, etc)
- CMake version 3.12 or newer (https://cmake.org/)

Building DicomHero
..................

The library folder contains a CMakeLists file, which contains the information needed by
CMake to generate a solution file for your platform (a make file, a VisualStudio solution, etc).

To generate the DicomHero shared library, execute the following steps:

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the DicomHero's library folder as parameter
4. execute cmake with the --build option, and on Windows optionally specify the build configuration

For instance:

::

    md artifacts
    cd artifacts
    cmake dicomhero_location/library
    cmake --build .

The first CMake command will generate a solution file for the your platform: this will be a 
make file on Linux, a VisualStudio solution of Windows, an XCode project on Mac.

The second CMake command with the --build option will launch make, VisualStudio or the build
chain defined on your machine.

On Windows, the last cmake command can be followed by --config release or --config debug, like
this:

::

    cmake --build . --config release

or

::

    cmake --build . --config debug



