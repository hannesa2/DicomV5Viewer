Adding Imebra to your project
=============================

Add Imebra to a C++ project
---------------------------

In order to use Imebra in your C++ applications your app must include the file imebra/imebra.h, which in turn includes
all the other necessary files. You should also link your project with the imebra library built following the instructions
outlined in :ref:`compiling-imebra-label`.

On Windows, the preprocessor macro NOMINMAX has to be defined before including the header file <windows.h>: you can
define the macro in the Solution's configuration (Connfiguration properties/C-C++/Preprocessor definitions).


Add Imebra to an Android project
--------------------------------

Imebra can be compiled as a AAR library which contains both the C++ source code and the necessary Java wrapper: 
a precompiled AAR library is available at http://imebra.com, or you can compile it yourself by following the instructions 
outlined in Compiling Imebra.

In order to use Imebra in your Android project, simply copy the imebrajni-debug|release.aar library in your project’s folder app/libs, then right click on the library in Android Studio and select “Add as library”.

In your code call System.loadLibrary(“imebra_lib”) before using any of the Imebra methods.

All the Imebra classes are in the package “com.imebra”.


Add Imebra to a Java project
----------------------------

Compile Imebra by following the instructions at :ref:`compiling-imebra-java-linux`.

In order to use Imebra in your Java project, simply add the Java source code in "wrappers/javaWrapper/src" to your application.

In your code call System.loadLibrary(“imebrajni”) before using any of the Imebra methods.
All the Imebra classes are in the package “com.imebra”.

When launching your application, define the property "java.library.path" with the value of the folder containing the Imebra JNI shared library (libimebrajni.so).


