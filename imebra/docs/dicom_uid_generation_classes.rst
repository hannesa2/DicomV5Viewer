UID generation classes
======================

Introduction
------------

This section describes the classes and methods used to generate new UID (unique identifiers) to be used as instance UIDs.

The following classes are described in this chapter:

+--------------------------------------------------+------------------------------------------------+-------------------------------+
|C++ class                                         |Objective-C/Swift class                         |Description                    |
+==================================================+================================================+===============================+
|:cpp:class:`dicomhero::UIDGeneratorFactory`       |:cpp:class:`DicomheroUIDGeneratorFactory`       |Stored a complete DICOM        |
|                                                  |                                                |structure                      |
+--------------------------------------------------+------------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::BaseUIDGenerator`          |:cpp:class:`DicomheroBaseUIDGenerator`          |Stores a single DICOM tag      |
+--------------------------------------------------+------------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::SerialNumberUIDGenerator`  |:cpp:class:`DicomheroSerialNumberUIDGenerator`  |Identifies a tag               |
+--------------------------------------------------+------------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::RandomUIDGenerator`        |:cpp:class:`DicomheroRandomUIDGenerator`        |Read data from a tag           |
+--------------------------------------------------+------------------------------------------------+-------------------------------+

.. figure:: images/uidgenerators.jpg
   :target: _images/uidgenerators.jpg
   :figwidth: 100%
   :alt: UID generators related classes

   Class diagram of the UID generators related classes

Dicomhero supplies two generators that are able to produce UIDs that can be used as SOP instances UID:

- :ref:`SerialNumberUIDGenerator`, to be used when the software has a mean to know its own serial number
- :ref:`RandomUIDGenerator`, to be used when the software is not able to retrieve its own serial number

In any case, the developer must acquire a root UID from the ISO authority.

Because the UID generators maintain an internal state which is necessary to generate unique IDs, the generators should
be allocated once when the program starts and then reused for the generation of every new UID.
:ref:`UIDGeneratorFactory` helps retrieving the generators allocated when the software started: register the allocated
generators in the :ref:`UIDGeneratorFactory` when the software starts and then get them from the factory when a new
UID is needed.


Factory
-------

.. _UIDGeneratorFactory:

UIDGeneratorFactory
...................

C++
,,,

.. doxygenclass:: dicomhero::UIDGeneratorFactory
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroUIDGeneratorFactory
   :members:


Generators
----------

.. _BaseUIDGenerator:

BaseUIDGenerator
................

C++
,,,

.. doxygenclass:: dicomhero::BaseUIDGenerator
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroBaseUIDGenerator
   :members:


.. _SerialNumberUIDGenerator:

SerialNumberUIDGenerator
........................

C++
,,,

.. doxygenclass:: dicomhero::SerialNumberUIDGenerator
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroSerialNumberUIDGenerator
   :members:


.. _RandomUIDGenerator:

RandomUIDGenerator
..................

C++
,,,

.. doxygenclass:: dicomhero::RandomUIDGenerator
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroRandomUIDGenerator
   :members:



