Stream classes
==============

Introduction
------------

The classes described in this chapter are used to load and store DICOM data structures (represented by a :ref:`DataSet`)
and to send and receive DICOM messages.

The following classes are described in this chapter:

+-------------------------------------------+-----------------------------------------+--------------------------------+
|C++ class                                  |Objective-C/Swift class                  |Description                     |
+===========================================+=========================================+================================+
|:cpp:class:`dicomhero::CodecFactory`       |:cpp:class:`DicomheroCodecFactory`       |Load/Save a DICOM structure     |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::BaseStreamInput`    |:cpp:class:`DicomheroBaseStreamInput`    |Base class for input streams    |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::BaseStreamOutput`   |:cpp:class:`DicomheroBaseStreamOutput`   |Base class for output streams   |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::StreamReader`       |:cpp:class:`DicomheroStreamReader`       |Read from an input stream       |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::StreamWriter`       |:cpp:class:`DicomheroStreamWriter`       |Write into an output stream     |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::FileStreamInput`    |:cpp:class:`DicomheroFileStreamInput`    |File input stream               |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::FileStreamOutput`   |:cpp:class:`DicomheroFileStreamOutput`   |File output stream              |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::MemoryStreamInput`  |:cpp:class:`DicomheroMemoryStreamInput`  |Memory input stream             |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::MemoryStreamOutput` |:cpp:class:`DicomheroMemoryStreamOutput` |Memory output stream            |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::StreamTimeout`      |:cpp:class:`DicomheroStreamTimeout`      |Causes a stream to fail after   |
|                                           |                                         |a timeout has expired           |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::PipeStream`         |:cpp:class:`DicomheroPipeStream`         |Allow to implement custom       |
|                                           |                                         |input and output streams        |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::TCPStream`          |:cpp:class:`DicomheroTCPStream`          |Implement an input and output   |
|                                           |                                         |stream on a TCP connection      |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::TCPListener`        |:cpp:class:`DicomheroTCPListener`        |Listen for incoming TCP         |
|                                           |                                         |connections                     |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::TCPAddress`         |:cpp:class:`DicomheroTCPAddress`         |Represents a TCP address        |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::TCPPassiveAddress`  |:cpp:class:`DicomheroTCPPassiveAddress`  |Represents a passive TCP        |
|                                           |                                         |address (used by the connection |
|                                           |                                         |listener)                       |
+-------------------------------------------+-----------------------------------------+--------------------------------+
|:cpp:class:`dicomhero::TCPActiveAddress`   |:cpp:class:`DicomheroTCPActiveAddress`   |Represents an active TCP        |
|                                           |                                         |address (used to connect to     |
|                                           |                                         |a peer)                         |
+-------------------------------------------+-----------------------------------------+--------------------------------+

.. figure:: images/streams.jpg
   :target: _images/streams.jpg
   :figwidth: 100%
   :alt: Stream related classes

   Class diagram of the stream related classes

The easiest way to load or store a :ref:`DataSet` object is by using the static methods of the `CodecFactory`_ class.

All the Dicomhero Stream Classes (file, memory, tcp, pipe) derive from `BaseStreamInput`_ or/and `BaseStreamOutput`_.

`BaseStreamInput`_ represents an input stream (you can read from it) while `BaseStreamOutput`_ represents an output
stream (you can write into it). However, both classes don't expose reading and writing methods: in order to read or 
write from/to a stream the client application must use the `StreamReader`_ or `StreamWriter`_.

Several `StreamReader`_ or `StreamWriter`_ can share a single `BaseStreamInput`_ or `BaseStreamOutput`_.


Stream classes
--------------

CodecFactory
............

C++
,,,

.. doxygenclass:: dicomhero::CodecFactory
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCodecFactory
   :members:


BaseStreamInput
...............

C++
,,,

.. doxygenclass:: dicomhero::BaseStreamInput
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroBaseStreamInput
   :members:


BaseStreamOutput
................

C++
,,,

.. doxygenclass:: dicomhero::BaseStreamOutput
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroBaseStreamOutput
   :members:


StreamReader
............

C++
,,,

.. doxygenclass:: dicomhero::StreamReader
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamReader
   :members:


StreamWriter
............

C++
,,,

.. doxygenclass:: dicomhero::StreamWriter
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamWriter
   :members:


FileStreamInput
...............

C++
,,,

.. doxygenclass:: dicomhero::FileStreamInput
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroFileStreamInput
   :members:


FileStreamOutput
................

C++
,,,

.. doxygenclass:: dicomhero::FileStreamOutput
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroFileStreamOutput
   :members:


MemoryStreamInput
.................

C++
,,,

.. doxygenclass:: dicomhero::MemoryStreamInput
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMemoryStreamInput
   :members:


MemoryStreamOutput
..................

C++
,,,

.. doxygenclass:: dicomhero::MemoryStreamOutput
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMemoryStreamOutput
   :members:


StreamTimeout
.............

C++
,,,

.. doxygenclass:: dicomhero::StreamTimeout
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamTimeout
   :members:



Pipe classes
------------

The Pipe class can be used to provide custom streams for the ACSE and DIMSE services or for any operation that
takes a `StreamReader`_ or `StreamWriter`_ as parameter.

An example of custom stream could be:

- a secure TCP connection
- a connection through a dedicated custom network
- etc.

A separate thread must be used to feed a Pipe (to supply a custom reading stream) or to sink data from a Pipe
(to provide a custom writing stream).

.. figure:: images/sequence_customWritePipe.jpg
   :target: _images/sequence_customWritePipe.jpg
   :figwidth: 100%
   :alt: Sequence diagram for the implementation of a custom write pipe

   Sequence diagram for the implementation of a custom output pipe


Pipe
....

C++
,,,

.. doxygenclass:: dicomhero::PipeStream
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroPipeStream
   :members:



TCP classes
-----------

The TCP classes can be used with :cpp:class:`dicomhero::StreamWriter` and :cpp:class:`dicomhero::StreamReader` to
send and receive data through a TCP stream.

A TCP server socket (a socket that listen for incoming connection) can be realized with the class
:cpp:class:`dicomhero::TCPListener`, while a TCP client (a socket that initiates a connection with a
server) can be realized with the class :cpp:class:`dicomhero::TCPStream`.

:cpp:class:`dicomhero::TCPListener` creates a new :cpp:class:`dicomhero::TCPStream` for each accepted incoming connection.

Both :cpp:class:`dicomhero::TCPListener` and :cpp:class:`dicomhero::TCPStream` expose blocking methods (except for
the constructors which connect to the peer in non-blocking mode).
You can exit a blocking method by closing the socket or by calling the terminate() method.

.. _TCPStream:

TCPStream
.........

C++
,,,

.. doxygenclass:: dicomhero::TCPStream
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPStream
   :members:


TCPListener
...........

C++
,,,

.. doxygenclass:: dicomhero::TCPListener
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPListener
   :members:


TCPAddress
..........

C++
,,,

.. doxygenclass:: dicomhero::TCPAddress
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPAddress
   :members:


TCPPassiveAddress
.................

C++
,,,

.. doxygenclass:: dicomhero::TCPPassiveAddress
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPPassiveAddress
   :members:


TCPActiveAddress
................

C++
,,,

.. doxygenclass:: dicomhero::TCPActiveAddress
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPActiveAddress
   :members:



