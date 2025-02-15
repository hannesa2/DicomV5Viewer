Definitions
===========

Introduction
------------

This chapter describes the auxiliary classes and definitions of the Imebra library.


The following classes are described in this chapter:

+-----------------------------------------------+---------------------------------------------+-------------------------------+
|C++ class                                      |Objective-C/Swift class                      |Description                    |
+===============================================+=============================================+===============================+
|:cpp:class:`imebra::tagId_t`                   |:cpp:class:`ImebraTagEnum`                   |Enumerates the known DICOM     |
|                                               |                                             |tags                           |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::ageUnit_t`                 |:cpp:class:`ImebraAgeUnit`                   |Enumerates the Age units       |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::tagVR_t`                   |:cpp:class:`ImebraTagType`                   |Enumerates the DICOM VRs       |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::imageQuality_t`            |:cpp:class:`ImebraImageQuality`              |Enumerates the image quality   |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::bitDepth_t`                |:cpp:class:`ImebraBitDepth`                  |Enumerates the image bit depths|
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::drawBitmapType_t`          |:cpp:class:`ImebraDrawBitmapType`            |Enumerates the bitmap types    |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::OverlayType_t`             |:cpp:class:`ImebraOverlayType`               |Enumerates the overlay types   |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::dicomVOIFunction_t`        |:cpp:class:`ImebraDicomVOIFunction`          |Enumerates VOI functions       |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::fileParts_t`               |NSArray                                      |List of file path parts        |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::codecType_t`               |:cpp:class:`ImebraCodecType`                 |Enumerates the codec types     |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::vois_t`                    |NSArray                                      |List of VOIs descriptions      |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::dimseCommandType_t`        |:cpp:class:`ImebraDimseCommandType`          |Enumerates the DIMSE commands  |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::dimseCommandPriority_t`    |:cpp:class:`ImebraDimseCommandPriority`      |Enumerates the DIMSE priorities|
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::dimseStatusCode_t`         |:cpp:class:`ImebraDimseStatusCode`           |Enumerates the DIMSE status    |
|                                               |                                             |codes                          |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::dimseStatus_t`             |:cpp:class:`ImebraDimseStatus`               |Enumerates the DIMSE statuses  |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`imebra::attributeIdentifierList_t` |NSArray                                      |List of attribute identifiers  |
+-----------------------------------------------+---------------------------------------------+-------------------------------+


Tag related definitions
-----------------------

tagId_t
.......

C++
,,,

.. doxygenenum:: imebra::tagId_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraTagEnum


ageUnit_t
.........

C++
,,,

.. doxygenenum:: imebra::ageUnit_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraAgeUnit


tagVR_t
.......

C++
,,,

.. doxygenenum:: imebra::tagVR_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraTagType


Image related definitions
-------------------------

imageQuality_t
..............

C++
,,,

.. doxygenenum:: imebra::imageQuality_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraImageQuality


bitDepth_t
..........

C++
,,,

.. doxygenenum:: imebra::bitDepth_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraBitDepth


drawBitmapType_t
................

C++
,,,

.. doxygenenum:: imebra::drawBitmapType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDrawBitmapType


overlayType_t
................

C++
,,,

.. doxygenenum:: imebra::overlayType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraOverlayType_t


dicomVOIFunction_t
..................

C++
,,,

.. doxygenenum:: imebra::dicomVOIFunction_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDicomVOIFunction


DICOMDIR related definitions
----------------------------

fileParts_t
...........

C++
,,,

.. doxygentypedef:: imebra::fileParts_t


Codec Factory related definitions
---------------------------------

codecType_t
...........

C++
,,,

.. doxygenenum:: imebra::codecType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraCodecType


VOI related definitions
-----------------------

dicomVOIFunction_t
..................

C++
,,,

.. doxygenenum:: imebra::dicomVOIFunction_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDicomVOIFunction_t


vois_t
......

C++
,,,

.. doxygentypedef:: imebra::vois_t



DIMSE related definitions
-------------------------

dimseCommandType_t
..................

C++
,,,

.. doxygenenum:: imebra::dimseCommandType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDimseCommandType


dimseCommandPriority_t
......................

C++
,,,

.. doxygenenum:: imebra::dimseCommandPriority_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDimseCommandPriority


dimseStatusCode_t
.................

C++
,,,

.. doxygenenum:: imebra::dimseStatusCode_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDimseStatusCode


dimseStatus_t
.............

C++
,,,

.. doxygenenum:: imebra::dimseStatus_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: ImebraDimseStatus


attributeIdentifierList_t
.........................

C++
,,,

.. doxygentypedef:: imebra::attributeIdentifierList_t


