DICOM dataSet & tags classes
============================

Introduction
------------

This section describes the classes and methods responsible for storing, retrieving and setting the information that composes the
DICOM structure, represented by the class :ref:`DataSet`.

The following classes are described in this chapter:

+--------------------------------------------------+------------------------------------------------+--------------------------------+
|C++ class                                         |Objective-C/Swift class                         |Description                     |
+==================================================+================================================+================================+
|:cpp:class:`dicomhero::DataSet`                   |:cpp:class:`DicomheroDataSet`                   |An DICOM structure              |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::Tag`                       |:cpp:class:`DicomheroTag`                       |A single DICOM tag              |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::TagId`                     |:cpp:class:`DicomheroTagId`                     |Identifies a tag                |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::ReadingDataHandler`        |:cpp:class:`DicomheroReadingDataHandler`        |Read data from a tag            |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::ReadingDataHandlerNumeric` |:cpp:class:`DicomheroReadingDataHandlerNumeric` |Read data from a numeric tag    |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::WritingDataHandler`        |:cpp:class:`DicomheroWritingDataHandler`        |Write into a tag                |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::WritingDataHandlerNumeric` |:cpp:class:`DicomheroWritingDataHandlerNumeric` |Write into a numeric tag        |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::Date`                      |:cpp:class:`DicomheroDate`                      |Stores a DICOM date/time        |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::Age`                       |:cpp:class:`DicomheroAge`                       |Stores a DICOM Age              |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::PatientName`               |:cpp:class:`DicomheroPatientName`               |Stores a patient name           |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::UnicodePatientName`        |                                                |Stores a patient name (unicode) |
+--------------------------------------------------+------------------------------------------------+--------------------------------+

.. figure:: images/data.jpg
   :target: _images/data.jpg
   :figwidth: 100%
   :alt: Data related classes

   Class diagram of the data related classes

:ref:`DataSet` is a collection of :ref:`Tag` objects. Each :ref:`Tag` is identified by a :ref:`TagId`.

:ref:`DataSet` supplies several functions that allow to easily read and write the value of the tags. However when advanced
functionalities are needed (e.g. when writing several items in one tag that accepts more than one value) then the classes
:ref:`ReadingDataHandler`, :ref:`ReadingDataHandlerNumeric`, :ref:`WritingDataHandler` and :ref:`WritingDataHandlerNumeric` should be used.

The difference between :ref:`ReadingDataHandlerNumeric` and :ref:`ReadingDataHandler` (and between :ref:`WritingDataHandlerNumeric` and
:ref:`WritingDataHandler`) is that the 'XXXNumeric' counterpart supplies functions to access the underlying memory buffer that stores
the data, allowing fast processing when dealing with images and large collections of data.


Data storage
------------

.. _DataSet:

DataSet
.......

C++
,,,

.. doxygenclass:: dicomhero::DataSet
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSet
   :members:


.. _Tag:

Tag
...

C++
,,,

.. doxygenclass:: dicomhero::Tag
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTag
   :members:



Data access
------------

The data handler allow to read and write the data stored in the tags.

In order to write data into a tag you can:

- use the helper methods in :ref:`DataSet`
- obtain a :ref:`WritingDataHandler` for the desidered tag and use it to write the data.

The :ref:`WritingDataHandler` has the advantage of being able to write multiple elements in the :ref:`Tag`, while
the helper methods in the :ref:`DataSet` can write only the first element.

The :ref:`WritingDataHandler` writes all the data into a new buffer, which replaces the old buffer in the :ref:`Tag`
only when the data handler is deleted.

.. figure:: images/sequence_createDataWithDataHandler.jpg
   :target: _images/sequence_createDataWithDataHandler.jpg
   :figwidth: 100%
   :alt: Data related classes

   Sequence diagram showing how to use a :ref:`WritingDataHandler`


.. _TagId:

TagId
.....

C++
,,,

.. doxygenclass:: dicomhero::TagId
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTagId
   :members:


.. _ReadingDataHandler:

ReadingDataHandler
..................

C++
,,,

.. doxygenclass:: dicomhero::ReadingDataHandler
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroReadingDataHandler
   :members:


.. _ReadingDataHandlerNumeric:

ReadingDataHandlerNumeric
.........................

C++
,,,

.. doxygenclass:: dicomhero::ReadingDataHandlerNumeric
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroReadingDataHandlerNumeric
   :members:


.. _WritingDataHandler:

WritingDataHandler
..................

C++
,,,

.. doxygenclass:: dicomhero::WritingDataHandler
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroWritingDataHandler
   :members:


.. _WritingDataHandlerNumeric:

WritingDataHandlerNumeric
.........................

C++
,,,

.. doxygenclass:: dicomhero::WritingDataHandlerNumeric
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroWritingDataHandlerNumeric
   :members:

Date
....

C++
,,,

.. doxygenclass:: dicomhero::Date
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDate
   :members:

Age
...

C++
,,,

.. doxygenclass:: dicomhero::Age
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAge
   :members:

PatientName
...........

C++
,,,

.. doxygenclass:: dicomhero::PatientName
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroPatientName
   :members:

UnicodePatientName
..................

C++
,,,

.. doxygenclass:: dicomhero::UnicodePatientName
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

Not available (:cpp:class:`DicomheroPatientName` uses Unicode on Objective-C/Swift)



