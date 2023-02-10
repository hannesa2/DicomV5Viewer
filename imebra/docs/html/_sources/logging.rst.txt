.. _logging-label:

Logging
=======

Imebra can log the most important operations to one of the following logging frameworks:

- log4cxx
- Android native logging
- Apple NSLog (MacOS or iOS)
- syslog (on Posix systems)
- standard output

The logging is disabled by default and can be enabled during the compilation phase of Imebra by setting IMEBRA_LOG_LEVEL
to one of the following values when launching cmake:

- *TRACE*
- *DEBUG*
- *INFO*
- *WARNING*
- *ERROR*
- *TRACE*

When the logging is enabled then Imebra will decide which logging framework to use, unless you override
the decision by defining setting IMEBRA_LOG_FRAMEWORK to one of the following values when launching cmake:

- *LOG4CXX*
- *SYSLOG*
- *COUT*
- *APPLE*
- *ANDROID*

The following list describes the logging framework used by Imebra, based on the operating system:

- On Apple systems: NSLog
- On Android: the Android logging system
- On Posix System (including Linux): syslog
- On all the other systems (including Windows): standard output


Linux specific instructions
---------------------------

When compiled on Linux then Imebra uses the syslog call to output the logs, unless a different logging framework is selected by setting
the CMAKE variable IMEBRA_LOG_FRAMEWORK to one of the following values:

- *LOG4CXX*
- *SYSLOG*
- *COUT*

The following example shows how to compile Imebra on Linux with the INFO logging level enabled. The logs will be produced using the posix syslog call:

::

    md artifacts
    cd artifacts
    cmake path/to/imebra_location -DIMEBRA_LOG_LEVEL=INFO
    cmake --build .
    sudo make install
    sudo ldconfig


The following example shows how to compile Imebra on Linux with the WARNING logging level enabled and output to log4cxx:

::

    md artifacts
    cd artifacts
    cmake path/to/imebra_location -DIMEBRA_LOG_LEVEL=INFO -DIMEBRA_LOG_FRAMEWORK=LOG4CXX
    cmake --build .
    sudo make install
    sudo ldconfig


Apple specific instructions
---------------------------

The following example shows how to compile Imebra for iPhone with the INFO logging level enabled. The logs will be produced using the NSLog call:

::

    md artifacts
    cd artifacts
    cmake path/to/imebra_location -DIMEBRA_LOG_LEVEL=INFO -DIOS=IPHONE 
    cmake --build .
    sudo make install
    sudo ldconfig


Android specific instructions
-----------------------------

On Android the INFO logging is enabled by default in DEBUG mode while logging is disabled in RELEASE mode.

To change the LOG settings you have to edit the file wrappers/javaWrapper/jni/Android.mk and replace the
*-DIMEBRA_LOG_LEVEL_INFO* with the desired log level.

The following example set the log level to WARNING:

::

    LOCAL_PATH := $(call my-dir)

    include $(CLEAR_VARS)

    LOCAL_MODULE := imebra_lib
    LOCAL_CPPFLAGS += -fexceptions -pthread -I$(LOCAL_PATH)/../../../library/include
    LOCAL_CPPFLAGS += -DIMEBRA_USE_JAVA -DIMEBRA_MEMORY_POOL_MAX_SIZE=4000000 -DIMEBRA_ANDROID -DIMEBRA_LOG_LEVEL_WARNING
    LOCAL_LDLIBS :=  -llog

    FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../library/src/*.cpp)
    FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../library/implementation/*.cpp)
    FILE_LIST += $(LOCAL_PATH)/../java_wrapper.cxx
    LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

    include $(BUILD_SHARED_LIBRARY)


Windows specific instructions
-----------------------------

When compiled on Windows then Imebra uses the standard output to output the logs, unless a different logging framework is selected by setting
the CMake variable IMEBRA_LOG_FRAMEWORK to one of the following values:

- *LOG4CXX*
- *COUT*

The following example shows how to compile Imebra on Linux with the INFO logging level enabled. The logs will be produced using the standard output:

::

    md artifacts
    cd artifacts
    cmake path/to/imebra_location -DIMEBRA_LOG_LEVEL=INFO
    cmake --build .


The following example shows how to compile Imebra on Windows with the WARNING logging level enabled and output to log4cxx:

::

    md artifacts
    cd artifacts
    cmake path/to/imebra_location -DIMEBRA_LOG_LEVEL=WARNING -DIMEBRA_LOG_FRAMEWORK=LOG4CXX
    cmake --build .




