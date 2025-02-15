DIMSE classes
=============

Introduction
------------

This chapter describes the classes and methods responsible for constructing and parsing DIMSE commands.

The following classes are described in this chapter:

+--------------------------------------------------+---------------------------------------------+-------------------------------+
|C++ class                                         |Objective-C/Swift class                      |Description                    |
+==================================================+=============================================+===============================+
|:cpp:class:`dicomhero::DimseService`              |:cpp:class:`DicomheroDimseService`           |Sends and receives DIMSE       |
|                                                  |                                             |commands and responses         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::DimseCommandBase`          |:cpp:class:`DicomheroDimseCommandBase`       |Base class for DIMSE           |
|                                                  |                                             |commands and responses         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::DimseCommand`              |:cpp:class:`DicomheroDimseCommand`           |Base class for DIMSE commands  |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::DimseResponse`             |:cpp:class:`DicomheroDimseResponse`          |Base class for DIMSE responses |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CStoreCommand`             |:cpp:class:`DicomheroCStoreCommand`          |DIMSE C-STORE command          |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CGetCommand`               |:cpp:class:`DicomheroCGetCommand`            |DIMSE C-GET command            |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CFindCommand`              |:cpp:class:`DicomheroCFindCommand`           |DIMSE C-FIND command           |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CMoveCommand`              |:cpp:class:`DicomheroCMoveCommand`           |DIMSE C-MOVE command           |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CEchoCommand`              |:cpp:class:`DicomheroCEchoCommand`           |DIMSE C-ECHO command           |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CCancelCommand`            |:cpp:class:`DicomheroCCancelCommand`         |DIMSE C-CANCEL command         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CPartialResponse`          |:cpp:class:`DicomheroCPartialResponse`       |Base clas for DIMSE partial    |
|                                                  |                                             |responses                      |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CStoreResponse`            |:cpp:class:`DicomheroCStoreResponse`         |DIMSE C-STORE response         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CGetResponse`              |:cpp:class:`DicomheroCGetResponse`           |DIMSE C-GET response           |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CFindResponse`             |:cpp:class:`DicomheroCFindResponse`          |DIMSE C-FIND response          |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CMoveResponse`             |:cpp:class:`DicomheroCMoveResponse`          |DIMSE C-MOVE response          |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::CEchoResponse`             |:cpp:class:`DicomheroCEchoResponse`          |DIMSE C-ECHO response          |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NEventReportCommand`       |:cpp:class:`DicomheroNEventReportCommand`    |DIMSE N-EVENT-REPORT command   |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NSetCommand`               |:cpp:class:`DicomheroNSetCommand`            |DIMSE N-SET command            |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NGetCommand`               |:cpp:class:`DicomheroNGetCommand`            |DIMSE N-GET command            |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NActionCommand`            |:cpp:class:`DicomheroNActionCommand`         |DIMSE N-ACTION command         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NCreateCommand`            |:cpp:class:`DicomheroNCreateCommand`         |DIMSE N-CREATE command         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NDeleteCommand`            |:cpp:class:`DicomheroNDeleteCommand`         |DIMSE N-DELETE command         |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NEventReportResponse`      |:cpp:class:`DicomheroNEventReportResponse`   |DIMSE N-EVENT-REPORT response  |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NSetResponse`              |:cpp:class:`DicomheroNSetResponse`           |DIMSE N-SET response           |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NGetCommand`               |:cpp:class:`DicomheroNGetCommand`            |DIMSE N-GET response           |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NActionResponse`           |:cpp:class:`DicomheroNActionResponse`        |DIMSE N-ACTION response        |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NCreateResponse`           |:cpp:class:`DicomheroNCreateResponse`        |DIMSE N-CREATE response        |
+--------------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::NDeleteResponse`           |:cpp:class:`DicomheroNDeleteResponse`        |DIMSE N-DELETE response        |
+--------------------------------------------------+---------------------------------------------+-------------------------------+


.. figure:: images/dimse.jpg
   :target: _images/dimse.jpg
   :figwidth: 100%
   :alt: DIMSE related classes

   Class diagram of the DIMSE related classes

The DIMSE classes (DICOM Service) take care of transmitting and receiving DICOM commands
through a DICOM association (a :ref:`AssociationBase` derived class).

The main DIMSE class is :ref:`DimseService`, through which all the DICOM commands
and responses are sent and received.

Dimse


Commands and responses transmission and reception
-------------------------------------------------

.. _DimseService:

DimseService
............

C++
,,,

.. doxygenclass:: dicomhero::DimseService
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDimseService
   :members:
   

Commands and response classes
-----------------------------

All the DIMSE commands are identified by an unique ID, which can be retrieved via the :ref:`DimseService` class.

DIMSE responses are built from the DIMSE command and have the same ID of the command they are related to.

After receiving a command, use :cpp:member:`dicomhero::DimseCommand::getCommandType` to retrieve the command type, then cast the
received command to the proper type (:cpp:class:`dicomhero::CStoreCommand`, :cpp:class:`dicomhero::CMoveCommand`,
:cpp:class:`dicomhero::CGetCommand`, :cpp:class:`dicomhero::CFindCommand`, :cpp:class:`dicomhero::CEchoCommand`, :cpp:class:`dicomhero::CCancelCommand`,
:cpp:class:`dicomhero::NActionCommand`, :cpp:class:`dicomhero::NEventReportCommand`, :cpp:class:`dicomhero::NCreateCommand`,
:cpp:class:`dicomhero::NDeleteCommand`, :cpp:class:`dicomhero::NSetCommand`, :cpp:class:`dicomhero::NGetCommand`).
Instead of casting (e.g. when using the Golang wrapper) you can also call one of the following functions:

- :cpp:member:`dicomhero::DimseCommand::getAsCStoreCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsCMoveCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsCGetCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsCFindCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsCEchoCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsCCancelCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsNActionCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsNEventReportCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsNCreateCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsNDeleteCommand`
- :cpp:member:`dicomhero::DimseCommand::getAsNSetCommand`
- :cpp:member:`dicomhero::DimseCommand::NGetCommand`


DimseCommandBase
................

C++
,,,

.. doxygenclass:: dicomhero::DimseCommandBase
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDimseCommandBase
   :members:


DimseCommand
............

C++
,,,

.. doxygenclass:: dicomhero::DimseCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDimseCommand
   :members:
   

DimseResponse
.............

C++
,,,

.. doxygenclass:: dicomhero::DimseResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDimseResponse
   :members:
   
   
C-Commands and responses
------------------------

.. figure:: images/dimseccommands.jpg
   :target: _images/dimseccommands.jpg
   :figwidth: 100%
   :alt: DIMSE C-Commands classes

   Class diagram of the DIMSE C commands classes


CStoreCommand
.............

C++
,,,

.. doxygenclass:: dicomhero::CStoreCommand
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCStoreCommand
   :members:


CGetCommand
...........

C++
,,,

.. doxygenclass:: dicomhero::CGetCommand
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCGetCommand
   :members:


CFindCommand
............

C++
,,,

.. doxygenclass:: dicomhero::CFindCommand
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCFindCommand
   :members:


CMoveCommand
............

C++
,,,

.. doxygenclass:: dicomhero::CMoveCommand
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCMoveCommand
   :members:


CEchoCommand
............

C++
,,,

.. doxygenclass:: dicomhero::CEchoCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCEchoCommand
   :members:
   

CCancelCommand
..............

C++
,,,

.. doxygenclass:: dicomhero::CCancelCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCCancelCommand
   :members:
   


CPartialResponse
................

C++
,,,

.. doxygenclass:: dicomhero::CPartialResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCPartialResponse
   :members:
   

CStoreResponse
..............

C++
,,,

.. doxygenclass:: dicomhero::CStoreResponse
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCStoreResponse
   :members:



CGetResponse
............

C++
,,,

.. doxygenclass:: dicomhero::CGetResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCGetResponse
   :members:
   


CFindResponse
.............

C++
,,,

.. doxygenclass:: dicomhero::CFindResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCFindResponse
   :members:
   
   

CMoveResponse
.............

C++
,,,

.. doxygenclass:: dicomhero::CMoveResponse
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCMoveResponse
   :members:


CEchoResponse
.............

C++
,,,

.. doxygenclass:: dicomhero::CEchoResponse
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCEchoResponse
   :members:



N-Commands and responses
------------------------
  
.. figure:: images/dimsencommands.jpg
   :target: _images/dimsencommands.jpg
   :figwidth: 100%
   :alt: DIMSE C-Commands classes

   Class diagram of the DIMSE N commands classes



NEventReportCommand
...................

C++
,,,

.. doxygenclass:: dicomhero::NEventReportCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNEventReportCommand
   :members:
   

NSetCommand
...........

C++
,,,

.. doxygenclass:: dicomhero::NSetCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNSetCommand
   :members:
   

NGetCommand
...........

C++
,,,

.. doxygenclass:: dicomhero::NGetCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNGetCommand
   :members:
   

NActionCommand
..............

C++
,,,

.. doxygenclass:: dicomhero::NActionCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNActionCommand
   :members:
   

NCreateCommand
..............

C++
,,,

.. doxygenclass:: dicomhero::NCreateCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNCreateCommand
   :members:
   

NDeleteCommand
..............

C++
,,,

.. doxygenclass:: dicomhero::NDeleteCommand
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNDeleteCommand
   :members:
   

NEventReportResponse
....................

C++
,,,

.. doxygenclass:: dicomhero::NEventReportResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNEventReportResponse
   :members:
   

NSetResponse
............

C++
,,,

.. doxygenclass:: dicomhero::NSetResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNSetResponse
   :members:
   

NGetResponse
............

C++
,,,

.. doxygenclass:: dicomhero::NGetResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNGetResponse
   :members:
   

NActionResponse
...............

C++
,,,

.. doxygenclass:: dicomhero::NActionResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNActionResponse
   :members:
   

NCreateResponse
...............

C++
,,,

.. doxygenclass:: dicomhero::NCreateResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNCreateResponse
   :members:
   

NDeleteResponse
...............

C++
,,,

.. doxygenclass:: dicomhero::NDeleteResponse
   :members:
   
Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroNDeleteResponse
   :members:
   
