DICOMDIR classes
================

Introduction
------------

This chapter describes the classes and methods used to read and write DICOMDIR files.

The following classes are described in this chapter:

+----------------------------------------------+--------------------------------------------+-----------------------------------+
|C++ class                                     |Objective-C/Swift class                     |Description                        |
+==============================================+============================================+===================================+
|:cpp:class:`dicomhero::DicomDir`              |:cpp:class:`DicomheroDicomDir`              |Allows to access the DICOMDIR      |
|                                              |                                            |entries stored in a :ref:`DataSet` |
+----------------------------------------------+--------------------------------------------+-----------------------------------+
|:cpp:class:`dicomhero::DicomDirEntry`         |:cpp:class:`DicomheroDicomDirEntry`         |Represents a single DICOMDIR       |
|                                              |                                            |entry                              |
+----------------------------------------------+--------------------------------------------+-----------------------------------+

.. figure:: images/dicomdir.jpg
   :target: _images/dicomdir.jpg
   :figwidth: 100%
   :alt: DICOMDIR related classes

   Class diagram of the DICOMDIR related classes

DICOMDIR classes
----------------

DicomDir
........

C++
,,,

.. doxygenclass:: dicomhero::DicomDir
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDicomDir
   :members:


DicomDirEntry
.............

C++
,,,

.. doxygenclass:: dicomhero::DicomDirEntry
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDicomDirEntry
   :members:


