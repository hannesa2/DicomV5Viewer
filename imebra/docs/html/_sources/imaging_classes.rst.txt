Imaging classes
===============

Introduction
------------

The classes described in this chapter are used to store and render images.

The following classes are described in this chapter:

+----------------------------------------+--------------------------------------+-------------------------------+
|C++ class                               |Objective-C/Swift class               |Description                    |
+========================================+======================================+===============================+
|:cpp:class:`imebra::Image`              |:cpp:class:`ImebraImage`              |Stores a decompressed image    |
+----------------------------------------+--------------------------------------+-------------------------------+
|:cpp:class:`imebra::MutableImage`       |:cpp:class:`ImebraMutableImage`       |A mutable decompressed image   |
+----------------------------------------+--------------------------------------+-------------------------------+
|:cpp:class:`imebra::Overlay`            |:cpp:class:`ImebraOverlay`            |Stores overlay data            |
+----------------------------------------+--------------------------------------+-------------------------------+
|:cpp:class:`imebra::MutableOverlay`     |:cpp:class:`ImebraMutableOverlay`     |A mutable overlay data         |
+----------------------------------------+--------------------------------------+-------------------------------+
|:cpp:class:`imebra::DrawBitmap`         |:cpp:class:`ImebraDrawBitmap`         |Render an image into a bitmap  |
+----------------------------------------+--------------------------------------+-------------------------------+

Images can be obtained from a :ref:`DataSet` object by calling the getImage or getImageApplyModality methods.

Before being rendered, an image may be processed by one or more :ref:`transform-classes`.


Image storage
-------------

Image
.....

C++
,,,

.. doxygenclass:: imebra::Image
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraImage
   :members:


MutableImage
............

C++
,,,

.. doxygenclass:: imebra::MutableImage
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMutableImage
   :members:


Overlay
.......

C++
,,,

.. doxygenclass:: imebra::Overlay
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraOverlay
   :members:


MutableOverlay
..............

C++
,,,

.. doxygenclass:: imebra::MutableOverlay
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMutableOverlay
   :members:


Image rendering
---------------

DrawBitmap
..........

C++
,,,

.. doxygenclass:: imebra::DrawBitmap
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDrawBitmap
   :members:
