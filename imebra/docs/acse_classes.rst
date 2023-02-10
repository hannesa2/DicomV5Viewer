ACSE classes
============

Introduction
------------

This chapter describes the ACSE related classes and methods. ACSE stands for (Association Control Service Element).

The following classes are described in this chapter:

+--------------------------------------------------+------------------------------------------------+--------------------------------+
|C++ class                                         |Objective-C/Swift class                         |Description                     |
+==================================================+================================================+================================+
|:cpp:class:`dicomhero::PresentationContext`       |:cpp:class:`DicomheroPresentationContext`       |Stores an abstract syntax and   |
|                                                  |                                                |the list of allowed transfer    |
|                                                  |                                                |syntaxes                        |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::PresentationContexts`      |:cpp:class:`DicomheroPresentationContexts`      |Stores a list of Presentation   |
|                                                  |                                                |contexts                        |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::AssociationMessage`        |:cpp:class:`DicomheroAssociationMessage`        |Stores a message sent through   |
|                                                  |                                                |an association                  |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::AssociationBase`           |:cpp:class:`DicomheroAssociationBase`           |Base class for the associations |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::AssociationSCU`            |:cpp:class:`DicomheroAssociationSCU`            |An SCU association (Service     |
|                                                  |                                                |user)                           |
+--------------------------------------------------+------------------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::AssociationSCP`            |:cpp:class:`DicomheroAssociationSCP`            |An SCP association (service     |
|                                                  |                                                |provider)                       |
+--------------------------------------------------+------------------------------------------------+--------------------------------+

.. figure:: images/acse.jpg
   :target: _images/acse.jpg
   :figwidth: 100%
   :alt: ACSE related classes

   Class diagram of the ACSE related classes


The ACSE classes (Association Control Service Element) take care of negotiating a DICOM association and transporting DICOM 
messages between DICOM entities connected through the association.

The client (Service User or SCU) must use :ref:`AssociationSCU` to connect, while the server (Service Provider or SCP) must
use :ref:`AssociationSCP` to connect with a client.

The association usually transmits and receive data via a :ref:`TCPStream`, therefore the sequence of operations needed to
connect an SCU to a remote SCP are as follow:

- Create a :ref:`TCPStream` which connects to the remote SCP
- Allocate a :ref:`StreamReader` and a :ref:`StreamWriter` connected to the :ref:`TCPStream` input and output streams
  (use :cpp:member:`dicomhero::DataSet::getStreamInput` and :cpp:member:`dicomhero::DataSet::getStreamOutput`)
- Allocate a :ref:`PresentationContexts` and fill it with :ref:`PresentationContext` objects that represent the requested
  presentation contexts (abstract syntaxes and supported transfer syntaxes)
- Allocate a :ref:`AssociationSCU` which in the constructor will perform the association negotiation through the
  :ref:`StreamReader` and :ref:`StreamWriter`

.. figure:: images/sequence_instantiateSCU.jpg
   :target: _images/sequence_instantiateSCU.jpg
   :figwidth: 100%
   :alt: Sequence diagram that shows how to instantiate an SCU

   Sequence diagram that shows how to instantiate an SCU

Once the association has been allocated, the client should use a DimseService in order to send and receive DICOM commands
and responses.


Presentation context classes
----------------------------

.. _PresentationContext:

PresentationContext
...................

C++
,,,

.. doxygenclass:: dicomhero::PresentationContext
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroPresentationContext
   :members:


PresentationContexts
....................

C++
,,,

.. doxygenclass:: dicomhero::PresentationContexts
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroPresentationContexts
   :members:



Association classes
-------------------

.. _AssociationBase:

AssociationBase
...............

C++
,,,

.. doxygenclass:: dicomhero::AssociationBase
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAssociationBase
   :members:


AssociationSCU
..............

C++
,,,

.. doxygenclass:: dicomhero::AssociationSCU
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAssociationSCU
   :members:


AssociationSCP
..............

C++
,,,

.. doxygenclass:: dicomhero::AssociationSCP
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAssociationSCP
   :members:


Message payload class
---------------------

AssociationMessage
..................

C++
,,,

.. doxygenclass:: dicomhero::AssociationMessage
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAssociationMessage
   :members:


