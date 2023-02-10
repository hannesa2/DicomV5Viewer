Definitions
===========

Introduction
------------

This chapter describes the auxiliary classes and definitions of the Dicomhero library.


The following classes are described in this chapter:

+--------------------------------------------------+---------------------------------------------+--------------------------------+
|C++ class                                         |Objective-C/Swift class                      |Description                     |
+==================================================+=============================================+================================+
|:cpp:class:`dicomhero::tagId_t`                   |:cpp:class:`DicomheroTagEnum`                |Enumerates the known DICOM      |
|                                                  |                                             |tags                            |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::ageUnit_t`                 |:cpp:class:`DicomheroAgeUnit`                |Enumerates the Age units        |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::tagVR_t`                   |:cpp:class:`DicomheroTagType`                |Enumerates the DICOM VRs        |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::imageQuality_t`            |:cpp:class:`DicomheroImageQuality`           |Enumerates the image quality    |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::bitDepth_t`                |:cpp:class:`DicomheroBitDepth`               |Enumerates the image bit depths |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::drawBitmapType_t`          |:cpp:class:`DicomheroDrawBitmapType`         |Enumerates the bitmap types     |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::OverlayType_t`             |:cpp:class:`DicomheroOverlayType`            |Enumerates the overlay types    |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::dicomVOIFunction_t`        |:cpp:class:`DicomheroDicomVOIFunction`       |Enumerates VOI functions        |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::fileParts_t`               |NSArray                                      |List of file path parts         |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::codecType_t`               |:cpp:class:`DicomheroCodecType`              |Enumerates the codec types      |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::vois_t`                    |NSArray                                      |List of VOIs descriptions       |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::dimseCommandType_t`        |:cpp:class:`DicomheroDimseCommandType`       |Enumerates the DIMSE commands   |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::dimseCommandPriority_t`    |:cpp:class:`DicomheroDimseCommandPriority`   |Enumerates the DIMSE priorities |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::dimseStatusCode_t`         |:cpp:class:`DicomheroDimseStatusCode`        |Enumerates the DIMSE status     |
|                                                  |                                             |codes                           |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::dimseStatus_t`             |:cpp:class:`DicomheroDimseStatus`            |Enumerates the DIMSE statuses   |
+--------------------------------------------------+---------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::attributeIdentifierList_t` |NSArray                                      |List of attribute identifiers   |
+--------------------------------------------------+---------------------------------------------+--------------------------------+


Tag related definitions
-----------------------

tagId_t
.......

C++
,,,

.. doxygenenum:: dicomhero::tagId_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroTagEnum


ageUnit_t
.........

C++
,,,

.. doxygenenum:: dicomhero::ageUnit_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroAgeUnit


tagVR_t
.......

C++
,,,

.. doxygenenum:: dicomhero::tagVR_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroTagType


Image related definitions
-------------------------

imageQuality_t
..............

C++
,,,

.. doxygenenum:: dicomhero::imageQuality_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroImageQuality


bitDepth_t
..........

C++
,,,

.. doxygenenum:: dicomhero::bitDepth_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroBitDepth


drawBitmapType_t
................

C++
,,,

.. doxygenenum:: dicomhero::drawBitmapType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDrawBitmapType


overlayType_t
................

C++
,,,

.. doxygenenum:: dicomhero::overlayType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroOverlayType_t


dicomVOIFunction_t
..................

C++
,,,

.. doxygenenum:: dicomhero::dicomVOIFunction_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDicomVOIFunction


DICOMDIR related definitions
----------------------------

fileParts_t
...........

C++
,,,

.. doxygentypedef:: dicomhero::fileParts_t


Codec Factory related definitions
---------------------------------

codecType_t
...........

C++
,,,

.. doxygenenum:: dicomhero::codecType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroCodecType


VOI related definitions
-----------------------

dicomVOIFunction_t
..................

C++
,,,

.. doxygenenum:: dicomhero::dicomVOIFunction_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDicomVOIFunction_t


vois_t
......

C++
,,,

.. doxygentypedef:: dicomhero::vois_t



DIMSE related definitions
-------------------------

dimseCommandType_t
..................

C++
,,,

.. doxygenenum:: dicomhero::dimseCommandType_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDimseCommandType


dimseCommandPriority_t
......................

C++
,,,

.. doxygenenum:: dicomhero::dimseCommandPriority_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDimseCommandPriority


dimseStatusCode_t
.................

C++
,,,

.. doxygenenum:: dicomhero::dimseStatusCode_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDimseStatusCode


dimseStatus_t
.............

C++
,,,

.. doxygenenum:: dicomhero::dimseStatus_t

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenenum:: DicomheroDimseStatus


attributeIdentifierList_t
.........................

C++
,,,

.. doxygentypedef:: dicomhero::attributeIdentifierList_t


