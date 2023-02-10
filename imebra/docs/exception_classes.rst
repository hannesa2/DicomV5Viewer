Exceptions
==========

Introduction
------------

This chapter describes the exception classes thrown by Dicomhero.

The following classes are described in this chapter:

+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|C++ class                                                               |Objective-C/Swift class                                               |Description                                      |
+========================================================================+======================================================================+=================================================+
|:cpp:class:`dicomhero::ExceptionsManager`                               |N/A                                                                   |Keeps track of the methods travelled by the      |
|                                                                        |                                                                      |exception                                        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MissingDataElementError`                         |:cpp:class:`DicomheroMissingDataElementError`                         |Base class for the "missing data" exceptions     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MissingGroupError`                               |:cpp:class:`DicomheroMissingGroupError`                               |Thrown when a tag group is missing               |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MissingTagError`                                 |:cpp:class:`DicomheroMissingTagError`                                 |Thrown when a tag is missing                     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MissingBufferError`                              |:cpp:class:`DicomheroMissingBufferError`                              |Thrown when a tag's buffer is missing            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MissingItemError`                                |:cpp:class:`DicomheroMissingItemError`                                |Thrown when a sequence item is missing           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamError`                                     |:cpp:class:`DicomheroStreamError`                                     |Base class for stream related exceptions         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamOpenError`                                 |:cpp:class:`DicomheroStreamOpenError`                                 |Thrown when the stream cannot be open            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamReadError`                                 |:cpp:class:`DicomheroStreamReadError`                                 |Thrown when the stream cannot be read            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamWriteError`                                |:cpp:class:`DicomheroStreamWriteError`                                |Thrown when the stream cannot be written         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamClosedError`                               |:cpp:class:`DicomheroStreamClosedError`                               |Thrown when accessing a closed stream            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamEOFError`                                  |:cpp:class:`DicomheroStreamEOFError`                                  |Thrown when the end of the stream has been       |
|                                                                        |                                                                      |reached                                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::TCPConnectionRefused`                            |:cpp:class:`DicomheroTCPConnectionRefused`                            |Thrown when a TCP connection is refused          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::TCPAddressAlreadyInUse`                          |:cpp:class:`DicomheroTCPAddressAlreadyInUse`                          |Thrown when using an already used address        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::PermissionDeniedError`                           |:cpp:class:`DicomheroPermissionDeniedError`                           |Thrown when using a privileged TCP port          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AddressError`                                    |:cpp:class:`DicomheroAddressError`                                    |Base class for TCP address related exceptions    |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AddressTryAgainError`                            |:cpp:class:`DicomheroAddressTryAgainError`                            |Thrown when the address cannot momentarily be    |
|                                                                        |                                                                      |resolved                                         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AddressNoNameError`                              |:cpp:class:`DicomheroAddressNoNameError`                              |Thrown when the name cannot be resolved          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AddressServiceNotSupportedError`                 |:cpp:class:`DicomheroAddressServiceNotSupportedError`                 |Thrown when the requested service is unknown     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DictionaryError`                                 |:cpp:class:`DicomheroDictionaryError`                                 |Base class for Dictionary related exceptions     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DictionaryUnknownTagError`                       |:cpp:class:`DicomheroDictionaryUnknownTagError`                       |Thrown when the tag is unknown                   |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DictionaryUnknownDataTypeError`                  |:cpp:class:`DicomheroDictionaryUnknownDataTypeError`                  |Thrown when a data type is unknown               |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CharsetConversionError`                          |:cpp:class:`DicomheroCharsetConversionError`                          |Base class for charset conversion related        |
|                                                                        |                                                                      |exceptions                                       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CharsetConversionNoTableError`                   |:cpp:class:`DicomheroCharsetConversionNoTableError`                   |The charset table is unknown                     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CharsetConversionNoSupportedTableError`          |:cpp:class:`DicomheroCharsetConversionNoSupportedTableError`          |The charset table is not installed on the system |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CharsetConversionCannotConvert`                  |:cpp:class:`CharsetConversionCannotConvert`                           |Thrown when a string cannot be converted using   |
|                                                                        |                                                                      |the charsets declared in the dataset             |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CodecError`                                      |:cpp:class:`DicomheroCodecError`                                      |Base class for codec related exceptions          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CodecWrongFormatError`                           |:cpp:class:`DicomheroCodecWrongFormatError`                           |Thrown when a codec cannot parse the byte stream |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CodecCorruptedFileError`                         |:cpp:class:`DicomheroCodecCorruptedFileError`                         |Thrown when the byte stream is corrupted         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CodecWrongTransferSyntaxError`                   |:cpp:class:`DicomheroCodecWrongTransferSyntaxError`                   |Thrown when the transfer syntax is unknown       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::CodecImageTooBigError`                           |:cpp:class:`DicomheroCodecImageTooBigError`                           |Thrown when the image size is too big            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::InvalidSequenceItemError`                        |:cpp:class:`DicomheroInvalidSequenceItemError`                        |Thrown when a sequence has a wrong VR            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::StreamJpegTagInStreamError`                      |:cpp:class:`DicomheroStreamJpegTagInStreamError`                      |Thrown when a jpeg tag is in the wrong position  |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DicomCodecError`                                 |:cpp:class:`DicomheroDicomCodecError`                                 |Base class for DICOM codec exceptions            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DicomCodecDepthLimitReachedError`                |:cpp:class:`DicomheroDicomCodecDepthLimitReachedError`                |Thrown when too many sequences are embedded into |
|                                                                        |                                                                      |each other                                       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::JpegCodecError`                                  |:cpp:class:`DicomheroJpegCodecError`                                  |Base class for jpeg related exceptions           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::JpegCodecCannotHandleSyntaxError`                |:cpp:class:`DicomheroJpegCodecCannotHandleSyntaxError`                |Thrown when the JPEG SOF ID cannot be processed  |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataHandlerError`                                |:cpp:class:`DicomheroDataHandlerError`                                |Base class for data handler related exceptions   |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataHandlerConversionError`                      |:cpp:class:`DicomheroDataHandlerConversionError`                      |Thrown when the data cannot be converted         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataHandlerCorruptedBufferError`                 |:cpp:class:`DicomheroDataHandlerCorruptedBufferError`                 |Thrown when a data buffer is corrupted           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataHandlerInvalidDataError`                     |:cpp:class:`DicomheroDataHandlerInvalidDataError`                     |Thrown when trying to store invalid data         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetError`                                    |:cpp:class:`DicomheroDataSetError`                                    |Base class for DataSet related exceptions        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetDifferentFormatError`                     |:cpp:class:`DicomheroDataSetDifferentFormatError`                     |Thrown when the operation requires a change of   |
|                                                                        |                                                                      |transfer syntax                                  |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetUnknownTransferSyntaxError`               |:cpp:class:`DicomheroDataSetUnknownTransferSyntaxError`               |Thrown when none of the code support the         |
|                                                                        |                                                                      |transfer syntax                                  |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetWrongFrameError`                          |:cpp:class:`DicomheroDataSetWrongFrameError`                          |Thrown when storing the wrong frame              |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetImageDoesntExistError`                    |:cpp:class:`DicomheroDataSetImageDoesntExistError`                    |Thrown when attempting to retrieve a frame that  |
|                                                                        |                                                                      |does not exist                                   |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetImagePaletteColorIsReadOnly`              |:cpp:class:`DicomheroDataSetImagePaletteColorIsReadOnly`              |Thrown when trying to write a Palette image      |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DataSetCorruptedOffsetTableError`                |:cpp:class:`DicomheroDataSetCorruptedOffsetTableError`                |Thrown when the table offset for the images is   |
|                                                                        |                                                                      |corrupted                                        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DicomDirError`                                   |:cpp:class:`DicomheroDicomDirError`                                   |Base class for DICOMDIR related exceptions       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DicomDirCircularReferenceError`                  |:cpp:class:`DicomheroDicomDirCircularReferenceError`                  |Thrown when a dicomentry references a            |
|                                                                        |                                                                      |parent entry as a child                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::HuffmanError`                                    |:cpp:class:`DicomheroHuffmanError`                                    |Base class for huffman related exceptions        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::HuffmanCreateTableError`                         |:cpp:class:`DicomheroHuffmanCreateTableError`                         |Thrown when the Huffman table cannot be created  |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::HuffmanReadError`                                |:cpp:class:`DicomheroHuffmanReadError`                                |Thrown when an invalid Huffman code is read      |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::HuffmanWriteError`                               |:cpp:class:`DicomheroHuffmanWriteError`                               |Thrown when writing a value that is not in the   |
|                                                                        |                                                                      |Huffman table                                    |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ImageError`                                      |:cpp:class:`DicomheroImageError`                                      |Base class for Image related exceptions          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ImageUnknownDepthError`                          |:cpp:class:`DicomheroImageUnknownDepthError`                          |Thrown when the bit depth parameter is wrong     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ImageUnknownColorSpaceError`                     |:cpp:class:`DicomheroImageUnknownColorSpaceError`                     |Thrown when the color space is not recognized    |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ImageInvalidSizeError`                           |:cpp:class:`DicomheroImageInvalidSizeError`                           |Thrown when the image size is invalid            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::TransformError`                                  |:cpp:class:`DicomheroTransformError`                                  |Base class for Transform related exceptions      |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::TransformInvalidAreaError`                       |:cpp:class:`DicomheroTransformInvalidAreaError`                       |Thrown when the transform area is invalid        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::TransformDifferentHighBitError`                  |:cpp:class:`DicomheroTransformDifferentHighBitError`                  |Thrown when the high bit of the input image is   |
|                                                                        |                                                                      |different from the high bit of the output image  |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ColorTransformError`                             |:cpp:class:`DicomheroColorTransformError`                             |Base class for Color Transform related           |
|                                                                        |                                                                      |exceptions                                       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ColorTransformWrongColorSpaceError`              |:cpp:class:`DicomheroColorTransformWrongColorSpaceError`              |Thrown when the input or output images of a      |
|                                                                        |                                                                      |color transform have the wrong color space       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ColorTransformsFactoryError`                     |:cpp:class:`DicomheroColorTransformsFactoryError`                     |Base class for Color Transform Factory related   |
|                                                                        |                                                                      |exceptions                                       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ColorTransformsFactoryNoTransformError`          |:cpp:class:`DicomheroColorTransformsFactoryNoTransformError`          |Thrown when a conversion between the specified   |
|                                                                        |                                                                      |color spaces does not exist                      |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::TransformDifferentColorSpacesError`              |:cpp:class:`DicomheroTransformDifferentColorSpacesError`              |Thrown when the input and output images of a     |
|                                                                        |                                                                      |High Bit Transform have different color spaces   |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::ModalityVOILUTError`                             |:cpp:class:`DicomheroModalityVOILUTError`                             |Thrown when the input or output images of a      |
|                                                                        |                                                                      |VOILUT transform are not monochromatic           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DicomheroBadAlloc`                               |:cpp:class:`DicomheroBadAlloc`                                        |Thrown when Dicomhero cannot allocate memory     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MemoryError`                                     |:cpp:class:`DicomheroMemoryError`                                     |Base class for ReadMemory and ReadWriteMemory    |
|                                                                        |                                                                      |related exceptions                               |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::MemorySizeError`                                 |:cpp:class:`DicomheroMemorySizeError`                                 |Thrown when the allocated memory is too small    |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::LutError`                                        |:cpp:class:`DicomheroLutError`                                        |Base class for LUT related exceptions            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::LutCorruptedError`                               |:cpp:class:`DicomheroLutCorruptedError`                               |Thrown when the LUT content is corrupted         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseError`                                       |:cpp:class:`DicomheroAcseError`                                       |Base class for ACSE related exceptions           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseCorruptedMessageError`                       |:cpp:class:`DicomheroAcseCorruptedMessageError`                       |Thrown when an ACSE message is corrupted         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseNoTransferSyntaxError`                       |:cpp:class:`DicomheroAcseNoTransferSyntaxError`                       |Thrown when a transfer syntax is not available   |
|                                                                        |                                                                      |for the abstract syntax                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcsePresentationContextNotRequestedError`        |:cpp:class:`DicomheroAcsePresentationContextNotRequestedError`        |Thrown when the presentation context wasn't      |
|                                                                        |                                                                      |requested during the association negotiation     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseWrongRoleError`                              |:cpp:class:`DicomheroAcseWrongRoleError`                              |Thrown if the service is using the wrong role    |
|                                                                        |                                                                      |for the presentation context                     |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseWrongIdError`                                |:cpp:class:`DicomheroAcseWrongIdError`                                |Base class for wrong message ID exceptions       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseWrongResponseIdError`                        |:cpp:class:`DicomheroAcseWrongResponseIdError`                        |Thrown when a response has the wrong ID          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseWrongCommandIdError`                         |:cpp:class:`DicomheroAcseWrongCommandIdError`                         |Thrown when a command has the wrong ID           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseRejectedAssociationError`                    |:cpp:class:`DicomheroAcseRejectedAssociationError`                    |Base class for association negotiation related   |
|                                                                        |                                                                      |exceptions                                       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCUNoReasonGivenError`                       |:cpp:class:`DicomheroAcseSCUNoReasonGivenError`                       |Association rejected by SCU with no given        |
|                                                                        |                                                                      |reasons                                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCUApplicationContextNameNotSupportedError`  |:cpp:class:`DicomheroAcseSCUApplicationContextNameNotSupportedError`  |Association rejected by SCU because of wrong     |
|                                                                        |                                                                      |application context name                         |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCUCallingAETNotRecognizedError`             |:cpp:class:`DicomheroAcseSCUCallingAETNotRecognizedError`             |Association rejected by SCU because the calling  |
|                                                                        |                                                                      |AET was not recognized                           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCUCalledAETNotRecognizedError`              |:cpp:class:`DicomheroAcseSCUCalledAETNotRecognizedError`              |Association rejected by SCU because the called   |
|                                                                        |                                                                      |AET was not recognized                           |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCPNoReasonGivenError`                       |:cpp:class:`DicomheroAcseSCPNoReasonGivenError`                       |Association rejected by SCP with no given        |
|                                                                        |                                                                      |reasons                                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCPAcseProtocolVersionNotSupportedError`     |:cpp:class:`DicomheroAcseSCPAcseProtocolVersionNotSupportedError`     |Association rejected by SCP because the protocol |
|                                                                        |                                                                      |version was not supported                        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCPPresentationReservedError`                |:cpp:class:`DicomheroAcseSCPPresentationReservedError`                |Association rejected by SCP because of the usage |
|                                                                        |                                                                      |of a reserved presentation context ID            |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCPPresentationTemporaryCongestionError`     |:cpp:class:`DicomheroAcseSCPPresentationTemporaryCongestionError`     |Association rejected by SCP because of a         |
|                                                                        |                                                                      |temporary congestion                             |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseSCPPresentationLocalLimitExcededError`       |:cpp:class:`DicomheroAcseSCPPresentationLocalLimitExcededError`       |Association rejected by SCP because of a         |
|                                                                        |                                                                      |exustion of simultaneous connections             |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseTooManyOperationsPerformedError`             |:cpp:class:`DicomheroAcseTooManyOperationsPerformedError`             |Thrown when too many operations are being        |
|                                                                        |                                                                      |performed                                        |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseTooManyOperationsInvokedError`               |:cpp:class:`DicomheroAcseTooManyOperationsInvokedError`               |Thrown when too many operations are being        |
|                                                                        |                                                                      |invoked                                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::AcseNoPayloadError`                              |:cpp:class:`DicomheroAcseNoPayloadError`                              |Thrown when a payload was expected but is        |
|                                                                        |                                                                      |missing                                          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DimseError`                                      |:cpp:class:`DicomheroDimseError`                                      |Base class for DIMSE related exceptions          |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+
|:cpp:class:`dicomhero::DimseInvalidCommand`                             |:cpp:class:`DicomheroDimseInvalidCommand`                             |Thrown when an invalid command is received       |
+------------------------------------------------------------------------+----------------------------------------------------------------------+-------------------------------------------------+


Exceptions manager
------------------

ExceptionsManager
.................

C++
,,,

.. doxygenclass:: dicomhero::ExceptionsManager
   :members:


Missing data exceptions
-----------------------

MissingDataElementError
.......................

C++
,,,

.. doxygenclass:: dicomhero::MissingDataElementError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMissingDataElementError
   :members:


MissingGroupError
.................

C++
,,,

.. doxygenclass:: dicomhero::MissingGroupError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMissingGroupError
   :members:
   

MissingTagError
...............

C++
,,,

.. doxygenclass:: dicomhero::MissingTagError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMissingTagError
   :members:


MissingBufferError
..................

C++
,,,

.. doxygenclass:: dicomhero::MissingBufferError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMissingBufferError
   :members:


MissingItemError
................

C++
,,,

.. doxygenclass:: dicomhero::MissingItemError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMissingItemError
   :members:


Stream error exceptions
-----------------------

StreamError
...........

C++
,,,

.. doxygenclass:: dicomhero::StreamError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamError
   :members:


StreamOpenError
...............

C++
,,,

.. doxygenclass:: dicomhero::StreamOpenError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamOpenError
   :members:


StreamReadError
...............

C++
,,,

.. doxygenclass:: dicomhero::StreamReadError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamReadError
   :members:


StreamWriteError
................

C++
,,,

.. doxygenclass:: dicomhero::StreamWriteError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamWriteError
   :members:


StreamClosedError
.................

C++
,,,

.. doxygenclass:: dicomhero::StreamClosedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamClosedError
   :members:


StreamEOFError
..............

C++
,,,

.. doxygenclass:: dicomhero::StreamEOFError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroStreamEOFError
   :members:


TCP exceptions
--------------

TCPConnectionRefused
....................

C++
,,,

.. doxygenclass:: dicomhero::TCPConnectionRefused
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPConnectionRefused
   :members:


TCPAddressAlreadyInUse
......................

C++
,,,

.. doxygenclass:: dicomhero::TCPAddressAlreadyInUse
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTCPAddressAlreadyInUse
   :members:


PermissionDeniedError
.....................

C++
,,,

.. doxygenclass:: dicomhero::PermissionDeniedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroPermissionDeniedError
   :members:


AddressError
............

C++
,,,

.. doxygenclass:: dicomhero::AddressError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAddressError
   :members:


AddressTryAgainError
....................

C++
,,,

.. doxygenclass:: dicomhero::AddressTryAgainError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAddressTryAgainError
   :members:


AddressNoNameError
..................

C++
,,,

.. doxygenclass:: dicomhero::AddressNoNameError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAddressNoNameError
   :members:


AddressServiceNotSupportedError
...............................

C++
,,,

.. doxygenclass:: dicomhero::AddressServiceNotSupportedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAddressServiceNotSupportedError
   :members:


Dictionary exceptions
---------------------

DictionaryError
...............

C++
,,,

.. doxygenclass:: dicomhero::DictionaryError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDictionaryError
   :members:


DictionaryUnknownTagError
.........................

C++
,,,

.. doxygenclass:: dicomhero::DictionaryUnknownTagError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDictionaryUnknownTagError
   :members:


DictionaryUnknownDataTypeError
..............................

C++
,,,

.. doxygenclass:: dicomhero::DictionaryUnknownDataTypeError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDictionaryUnknownDataTypeError
   :members:


Charset conversion exceptions
-----------------------------

CharsetConversionError
......................

C++
,,,

.. doxygenclass:: dicomhero::CharsetConversionError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCharsetConversionError
   :members:


CharsetConversionNoTableError
.............................

C++
,,,

.. doxygenclass:: dicomhero::CharsetConversionNoTableError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCharsetConversionNoTableError
   :members:


CharsetConversionNoSupportedTableError
......................................

C++
,,,

.. doxygenclass:: dicomhero::CharsetConversionNoSupportedTableError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCharsetConversionNoSupportedTableError
   :members:


CharsetConversionCannotConvert
..............................

C++
,,,

.. doxygenclass:: dicomhero::CharsetConversionCannotConvert
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: CharsetConversionCannotConvert
   :members:


Codec exceptions
----------------

CodecError
..........

C++
,,,

.. doxygenclass:: dicomhero::CodecError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCodecError
   :members:


CodecWrongFormatError
.....................

C++
,,,

.. doxygenclass:: dicomhero::CodecWrongFormatError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCodecWrongFormatError
   :members:


CodecCorruptedFileError
.......................

C++
,,,

.. doxygenclass:: dicomhero::CodecCorruptedFileError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCodecCorruptedFileError
   :members:


CodecWrongTransferSyntaxError
.............................

C++
,,,

.. doxygenclass:: dicomhero::CodecWrongTransferSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCodecWrongTransferSyntaxError
   :members:


CodecImageTooBigError
.....................

C++
,,,

.. doxygenclass:: dicomhero::CodecImageTooBigError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroCodecImageTooBigError
   :members:


InvalidSequenceItemError
........................

C++
,,,

.. doxygenclass:: dicomhero::InvalidSequenceItemError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroInvalidSequenceItemError
   :members:


DicomCodecError
...............

C++
,,,

.. doxygenclass:: dicomhero::DicomCodecError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDicomCodecError
   :members:


DicomCodecDepthLimitReachedError
................................

C++
,,,

.. doxygenclass:: dicomhero::DicomCodecDepthLimitReachedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDicomCodecDepthLimitReachedError
   :members:


JpegCodecError
..............

C++
,,,

.. doxygenclass:: dicomhero::JpegCodecError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroJpegCodecError
   :members:


JpegCodecCannotHandleSyntaxError
................................

C++
,,,

.. doxygenclass:: dicomhero::JpegCodecCannotHandleSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroJpegCodecCannotHandleSyntaxError
   :members:


Data handler exceptions
-----------------------

DataHandlerError
................

C++
,,,

.. doxygenclass:: dicomhero::DataHandlerError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataHandlerError
   :members:


DataHandlerConversionError
..........................

C++
,,,

.. doxygenclass:: dicomhero::DataHandlerConversionError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataHandlerConversionError
   :members:


DataHandlerCorruptedBufferError
...............................

C++
,,,

.. doxygenclass:: dicomhero::DataHandlerCorruptedBufferError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataHandlerCorruptedBufferError
   :members:


DataHandlerInvalidDataError
...........................

C++
,,,

.. doxygenclass:: dicomhero::DataHandlerInvalidDataError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataHandlerInvalidDataError
   :members:


DataSet exceptions
------------------

DataSetError
............

C++
,,,

.. doxygenclass:: dicomhero::DataSetError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetError
   :members:


DataSetDifferentFormatError
...........................

C++
,,,

.. doxygenclass:: dicomhero::DataSetDifferentFormatError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetDifferentFormatError
   :members:


DataSetUnknownTransferSyntaxError
.................................

C++
,,,

.. doxygenclass:: dicomhero::DataSetUnknownTransferSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetUnknownTransferSyntaxError
   :members:


DataSetWrongFrameError
......................

C++
,,,

.. doxygenclass:: dicomhero::DataSetWrongFrameError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetWrongFrameError
   :members:


DataSetImageDoesntExistError
............................

C++
,,,

.. doxygenclass:: dicomhero::DataSetImageDoesntExistError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetImageDoesntExistError
   :members:


DataSetImagePaletteColorIsReadOnly
..................................

C++
,,,

.. doxygenclass:: dicomhero::DataSetImagePaletteColorIsReadOnly
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetImagePaletteColorIsReadOnly
   :members:


DataSetCorruptedOffsetTableError
................................

C++
,,,

.. doxygenclass:: dicomhero::DataSetCorruptedOffsetTableError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDataSetCorruptedOffsetTableError
   :members:


DICOMDIR exceptions
-------------------

DicomDirError
.............

C++
,,,

.. doxygenclass:: dicomhero::DicomDirError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDicomDirError
   :members:


DicomDirCircularReferenceError
..............................

C++
,,,

.. doxygenclass:: dicomhero::DicomDirCircularReferenceError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDicomDirCircularReferenceError
   :members:


Image exceptions
----------------

ImageError
..........

.. doxygenclass:: dicomhero::ImageError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroImageError
   :members:


ImageUnknownDepthError
......................

C++
,,,

.. doxygenclass:: dicomhero::ImageUnknownDepthError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroImageUnknownDepthError
   :members:


ImageUnknownColorSpaceError
...........................

C++
,,,

.. doxygenclass:: dicomhero::ImageUnknownColorSpaceError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroImageUnknownColorSpaceError
   :members:


ImageInvalidSizeError
.....................

C++
,,,

.. doxygenclass:: dicomhero::ImageInvalidSizeError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroImageInvalidSizeError
   :members:


Transform exceptions
--------------------

TransformError
..............

C++
,,,

.. doxygenclass:: dicomhero::TransformError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransformError
   :members:


TransformInvalidAreaError
.........................

C++
,,,

.. doxygenclass:: dicomhero::TransformInvalidAreaError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransformInvalidAreaError
   :members:


TransformDifferentHighBitError
..............................

C++
,,,

.. doxygenclass:: dicomhero::TransformDifferentHighBitError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransformDifferentHighBitError
   :members:


ColorTransformError
...................

C++
,,,

.. doxygenclass:: dicomhero::ColorTransformError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroColorTransformError
   :members:


ColorTransformWrongColorSpaceError
..................................

C++
,,,

.. doxygenclass:: dicomhero::ColorTransformWrongColorSpaceError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroColorTransformWrongColorSpaceError
   :members:


ColorTransformsFactoryError
...........................

C++
,,,

.. doxygenclass:: dicomhero::ColorTransformsFactoryError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroColorTransformsFactoryError
   :members:


ColorTransformsFactoryNoTransformError
......................................

C++
,,,

.. doxygenclass:: dicomhero::ColorTransformsFactoryNoTransformError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroColorTransformsFactoryNoTransformError
   :members:


TransformDifferentColorSpacesError
.........................................

C++
,,,

.. doxygenclass:: dicomhero::TransformDifferentColorSpacesError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroTransformDifferentColorSpacesError
   :members:


ModalityVOILUTError
...................

C++
,,,

.. doxygenclass:: dicomhero::ModalityVOILUTError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroModalityVOILUTError
   :members:


Memory exceptions
-----------------

DicomheroBadAlloc
..............

C++
,,,

.. doxygenclass:: dicomhero::DicomheroBadAlloc
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroBadAlloc
   :members:


MemoryError
...........

C++
,,,

.. doxygenclass:: dicomhero::MemoryError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMemoryError
   :members:


MemorySizeError
...............

C++
,,,

.. doxygenclass:: dicomhero::MemorySizeError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroMemorySizeError
   :members:


LUT exceptions
--------------

LutError
........

C++
,,,

.. doxygenclass:: dicomhero::LutError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroLutError
   :members:


LutCorruptedError
.................

C++
,,,

.. doxygenclass:: dicomhero::LutCorruptedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroLutCorruptedError
   :members:


ACSE exceptions
---------------

AcseError
.........

C++
,,,

.. doxygenclass:: dicomhero::AcseError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseError
   :members:


AcseCorruptedMessageError
.........................

C++
,,,

.. doxygenclass:: dicomhero::AcseCorruptedMessageError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseCorruptedMessageError
   :members:


AcseNoTransferSyntaxError
.........................

C++
,,,

.. doxygenclass:: dicomhero::AcseNoTransferSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseNoTransferSyntaxError
   :members:


AcsePresentationContextNotRequestedError
........................................

C++
,,,

.. doxygenclass:: dicomhero::AcsePresentationContextNotRequestedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcsePresentationContextNotRequestedError
   :members:


AcseWrongRoleError
..................

C++
,,,

.. doxygenclass:: dicomhero::AcseWrongRoleError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseWrongRoleError
   :members:


AcseWrongIdError
................

C++
,,,

.. doxygenclass:: dicomhero::AcseWrongIdError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseWrongIdError
   :members:


AcseWrongResponseIdError
........................

C++
,,,

.. doxygenclass:: dicomhero::AcseWrongResponseIdError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseWrongResponseIdError
   :members:


AcseWrongCommandIdError
.......................

C++
,,,

.. doxygenclass:: dicomhero::AcseWrongCommandIdError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseWrongCommandIdError
   :members:


AcseRejectedAssociationError
............................

C++
,,,

.. doxygenclass:: dicomhero::AcseRejectedAssociationError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseRejectedAssociationError
   :members:


AcseSCUNoReasonGivenError
.........................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCUNoReasonGivenError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCUNoReasonGivenError
   :members:


AcseSCUApplicationContextNameNotSupportedError
..............................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCUApplicationContextNameNotSupportedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCUApplicationContextNameNotSupportedError
   :members:


AcseSCUCallingAETNotRecognizedError
...................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCUCallingAETNotRecognizedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCUCallingAETNotRecognizedError
   :members:


AcseSCUCalledAETNotRecognizedError
..................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCUCalledAETNotRecognizedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCUCalledAETNotRecognizedError
   :members:


AcseSCPNoReasonGivenError
.........................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCPNoReasonGivenError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCPNoReasonGivenError
   :members:


AcseSCPAcseProtocolVersionNotSupportedError
...........................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCPAcseProtocolVersionNotSupportedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCPAcseProtocolVersionNotSupportedError
   :members:


AcseSCPPresentationReservedError
................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCPPresentationReservedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCPPresentationReservedError
   :members:


AcseSCPPresentationTemporaryCongestionError
...........................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCPPresentationTemporaryCongestionError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCPPresentationTemporaryCongestionError
   :members:


AcseSCPPresentationLocalLimitExcededError
.........................................

C++
,,,

.. doxygenclass:: dicomhero::AcseSCPPresentationLocalLimitExcededError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseSCPPresentationLocalLimitExcededError
   :members:


AcseTooManyOperationsPerformedError
...................................

C++
,,,

.. doxygenclass:: dicomhero::AcseTooManyOperationsPerformedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseTooManyOperationsPerformedError
   :members:


AcseTooManyOperationsInvokedError
.................................

C++
,,,

.. doxygenclass:: dicomhero::AcseTooManyOperationsInvokedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseTooManyOperationsInvokedError
   :members:


AcseNoPayloadError
..................

C++
,,,

.. doxygenclass:: dicomhero::AcseNoPayloadError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroAcseNoPayloadError
   :members:


DIMSE exceptions
----------------

DimseError
..........

C++
,,,

.. doxygenclass:: dicomhero::DimseError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDimseError
   :members:


DimseInvalidCommand
...................

C++
,,,

.. doxygenclass:: dicomhero::DimseInvalidCommand
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: DicomheroDimseInvalidCommand
   :members:

