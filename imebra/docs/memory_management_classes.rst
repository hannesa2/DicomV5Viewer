Memory management classes
=========================

Introduction
------------

This chapter describes the classes and methods responsible for allocating and accessing the memory used by the Dicomhero classes.

The following classes are described in this chapter:

+-----------------------------------------------+---------------------------------------------+-------------------------------+
|C++ class                                      |Objective-C/Swift class                      |Description                    |
+===============================================+=============================================+===============================+
|:cpp:class:`dicomhero::Memory`                 |:cpp:class:`DicomheroMemory`                 |Allows to read the memory      |
|                                               |                                             |content                        |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::MutableMemory`          |:cpp:class:`DicomheroMutableMemory`          |Allows to read and write the   |
|                                               |                                             |memory content                 |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::MemoryPool`             |:cpp:class:`DicomheroMemoryPool`             |Allocatess or reuse a memory   |
|                                               |                                             |block                          |
+-----------------------------------------------+---------------------------------------------+-------------------------------+

The inner working classes of the Dicomhero library use the :ref:`MemoryPool` class to allocate blocks of memory.

When a memory block allocated by :ref:`MemoryPool` is released then it is not deleted immediately but instead it is kept for
a while so it can be reused by classes than need a similar amount of memory.

.. figure:: images/memory.jpg
   :target: _images/memory.jpg
   :figwidth: 100%
   :alt: Memory related classes

   Class diagram of the memory classes


Memory access
-------------

Memory
......

C++
,,,

.. doxygenclass:: dicomhero::Memory
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMemory
   :members:


MutableMemory
.............

C++
,,,

.. doxygenclass:: dicomhero::MutableMemory
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMutableMemory
   :members:


Memory allocation
-----------------

.. _MemoryPool:

MemoryPool
..........

C++
,,,

.. doxygenclass:: dicomhero::MemoryPool
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMemoryPool
   :members:



