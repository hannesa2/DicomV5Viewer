Adding DICOMHERO to your project
================================

Add DICOMHERO to a C++ project
------------------------------

In order to use DICOMHERO your C++ applications must include the file dicomhero6/dicomhero6.h, which in turn includes
all the other necessary files. You should also link your project with the DICOMHERO library built following the instructions
outlined in :ref:`compiling-dicomhero-label`.

On Windows, the preprocessor macro NOMINMAX has to be defined before including the header file <windows.h>: you can
define the macro in the Solution's configuration (Configuration properties/C-C++/Preprocessor definitions).


Add DICOMHERO to an Android project
-----------------------------------

DICOMHERO can be compiled as a AAR library which contains both the C++ source code and the necessary Java wrapper: 
a precompiled AAR library is available at http://dicomhero.com, or you can compile it yourself by following the instructions 
outlined in Compiling DICOMHERO.

In order to use DICOMHERO in your Android project, simply copy the dicomhero6-debug|release-version.aar library in your project’s folder app/libs, then right click on the library in Android Studio and select “Add as library”.

In your code call System.loadLibrary(“dicomhero6”) before using any of the DICOMHERO methods.

All the DICOMHERO classes are in the package “com.dicomhero.api”.


Add DICOMHERO to an Xcode project
---------------------------------

Download the pre-compiled DICOMHERO XCFramework from https://dicomhero.com and add it to your Xcode project.

The XCFramework contains the library for macOS (x86_64 and arm64 architecture) and iOS (Simulator x86_64 and arm64 architecture, hardware arm64 architecture).

When using DICOMHERO from Swift then you have to add a bridge header to your project (in the Build Settings/Objective-C Bridging Header) including the framework
Header *<dicomhero6/dicomhero6.h>*.

