.. _transform-classes:

Transforms classes
==================

Introduction
------------

This chapter describes the transform classes. Transform classes apply a transform algorithm to an input image and return the
result in an output image.

The following classes are described in this chapter:

+-----------------------------------------------+---------------------------------------------+-------------------------------+
|C++ class                                      |Objective-C/Swift class                      |Description                    |
+===============================================+=============================================+===============================+
|:cpp:class:`dicomhero::Transform`              |:cpp:class:`DicomheroTransform`              |Base class for all the         |
|                                               |                                             |transforms                     |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::TransformsChain`        |:cpp:class:`DicomheroTransformsChain`        |Apply a sequence of transforms |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::VOILUT`                 |:cpp:class:`DicomheroVOILUT`                 |Apply a presentation VOI or    |
|                                               |                                             |LUT                            |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::VOIDescription`         |:cpp:class:`DicomheroVOIDescription`         |Describes the VOI's parameters |
|                                               |                                             |(center, width, function)      |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::ModalityVOILUT`         |:cpp:class:`DicomheroModalityVOILUT`         |Apply the modality VOI or      |
|                                               |                                             |LUT                            |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::TransformHighBit`       |:cpp:class:`DicomheroTransformHighBit`       |Shift the pixels bits          |
+-----------------------------------------------+---------------------------------------------+-------------------------------+
|:cpp:class:`dicomhero::ColorTransformsFactory` |:cpp:class:`DicomheroColorTransformsFactory` |Transform the color space      |
+-----------------------------------------------+---------------------------------------------+-------------------------------+

.. figure:: images/transforms.jpg
   :target: _images/transforms.jpg
   :figwidth: 100%
   :alt: Transforms classes

   Class diagram of the transforms classes


Base Transform class
--------------------

Transform
.........

C++
,,,

.. doxygenclass:: dicomhero::Transform
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransform
   :members:


TransformsChain
...............

C++
,,,

.. doxygenclass:: dicomhero::TransformsChain
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransformsChain
   :members:


Modality and Presentation transforms
------------------------------------

VOILUT
......

C++
,,,

.. doxygenclass:: dicomhero::VOILUT
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroVOILUT
   :members:


VOIDescription
..............

C++
,,,

.. doxygenclass:: dicomhero::VOIDescription
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroVOIDescription
   :members:


LUT
...

C++
,,,

.. doxygenclass:: dicomhero::LUT
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroLUT
   :members:


ModalityVOILUT
..............

C++
,,,

.. doxygenclass:: dicomhero::ModalityVOILUT
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroModalityVOILUT
   :members:


Rendering transforms
--------------------

TransformHighBit
................

C++
,,,

.. doxygenclass:: dicomhero::TransformHighBit
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransformHighBit
   :members:


ColorTransformsFactory
......................

C++
,,,

.. doxygenclass:: dicomhero::ColorTransformsFactory
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroColorTransformsFactory
   :members:
