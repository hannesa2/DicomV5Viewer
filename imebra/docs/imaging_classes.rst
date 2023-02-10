Imaging classes
===============

Introduction
------------

The classes described in this chapter are used to store and render images.

The following classes are described in this chapter:

+----------------------------------------+--------------------------------------+-------------------------------+
|C++ class                               |Objective-C/Swift class               |Description                    |
+========================================+======================================+===============================+
|:cpp:class:`dicomhero::Image`           |:cpp:class:`DicomheroImage`           |Stores a decompressed image    |
+----------------------------------------+--------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::Overlay`         |:cpp:class:`DicomheroOverlay`         |Stores overlay data            |
+----------------------------------------+--------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::DrawBitmap`      |:cpp:class:`DicomheroDrawBitmap`      |Render an image into a bitmap  |
+----------------------------------------+--------------------------------------+-------------------------------+

Images can be obtained from a :ref:`DataSet` object by calling the getImage or getImageApplyModality methods.

Before being rendered, an image may be processed by one or more :ref:`transform-classes`.


Image storage
-------------

Image
.....

C++
,,,

.. doxygenclass:: dicomhero::Image
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroImage
   :members:


Overlay
.......

C++
,,,

.. doxygenclass:: dicomhero::Overlay
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroOverlay
   :members:


Image rendering
---------------

DrawBitmap
..........

C++
,,,

.. doxygenclass:: dicomhero::DrawBitmap
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDrawBitmap
   :members:
