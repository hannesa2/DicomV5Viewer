Exceptions
==========

Introduction
------------

This chapter describes the exception classes thrown by Imebra.

The following classes are described in this chapter:

+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|C++ class                                                            |Objective-C/Swift class                                            |Description                                     |
+=====================================================================+===================================================================+================================================+
|:cpp:class:`imebra::ExceptionsManager`                               |N/A                                                                |Keeps track of the methods travelled by the     |
|                                                                     |                                                                   |exception                                       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MissingDataElementError`                         |:cpp:class:`ImebraMissingDataElementError`                         |Base class for the "missing data" exceptions    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MissingGroupError`                               |:cpp:class:`ImebraMissingGroupError`                               |Thrown when a tag group is missing              |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MissingTagError`                                 |:cpp:class:`ImebraMissingTagError`                                 |Thrown when a tag is missing                    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MissingBufferError`                              |:cpp:class:`ImebraMissingBufferError`                              |Thrown when a tag's buffer is missing           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MissingItemError`                                |:cpp:class:`ImebraMissingItemError`                                |Thrown when a sequence item is missing          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamError`                                     |:cpp:class:`ImebraStreamError`                                     |Base class for stream related exceptions        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamOpenError`                                 |:cpp:class:`ImebraStreamOpenError`                                 |Thrown when the stream cannot be open           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamReadError`                                 |:cpp:class:`ImebraStreamReadError`                                 |Thrown when the stream cannot be read           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamWriteError`                                |:cpp:class:`ImebraStreamWriteError`                                |Thrown when the stream cannot be written        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamClosedError`                               |:cpp:class:`ImebraStreamClosedError`                               |Thrown when accessing a closed stream           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamEOFError`                                  |:cpp:class:`ImebraStreamEOFError`                                  |Thrown when the end of the stream has been      |
|                                                                     |                                                                   |reached                                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::TCPConnectionRefused`                            |:cpp:class:`ImebraTCPConnectionRefused`                            |Thrown when a TCP connection is refused         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::TCPAddressAlreadyInUse`                          |:cpp:class:`ImebraTCPAddressAlreadyInUse`                          |Thrown when using an already used address       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::PermissionDeniedError`                           |:cpp:class:`ImebraPermissionDeniedError`                           |Thrown when using a privileged TCP port         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AddressError`                                    |:cpp:class:`ImebraAddressError`                                    |Base class for TCP address related exceptions   |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AddressTryAgainError`                            |:cpp:class:`ImebraAddressTryAgainError`                            |Thrown when the address cannot momentarily be   |
|                                                                     |                                                                   |resolved                                        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AddressNoNameError`                              |:cpp:class:`ImebraAddressNoNameError`                              |Thrown when the name cannot be resolved         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AddressServiceNotSupportedError`                 |:cpp:class:`ImebraAddressServiceNotSupportedError`                 |Thrown when the requested service is unknown    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DictionaryError`                                 |:cpp:class:`ImebraDictionaryError`                                 |Base class for Dictionary related exceptions    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DictionaryUnknownTagError`                       |:cpp:class:`ImebraDictionaryUnknownTagError`                       |Thrown when the tag is unknown                  |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DictionaryUnknownDataTypeError`                  |:cpp:class:`ImebraDictionaryUnknownDataTypeError`                  |Thrown when a data type is unknown              |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CharsetConversionError`                          |:cpp:class:`ImebraCharsetConversionError`                          |Base class for charset conversion related       |
|                                                                     |                                                                   |exceptions                                      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CharsetConversionNoTableError`                   |:cpp:class:`ImebraCharsetConversionNoTableError`                   |The charset table is unknown                    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CharsetConversionNoSupportedTableError`          |:cpp:class:`ImebraCharsetConversionNoSupportedTableError`          |The charset table is not installed on the system|
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CharsetConversionCannotConvert`                  |:cpp:class:`CharsetConversionCannotConvert`                        |Thrown when a string cannot be converted using  |
|                                                                     |                                                                   |the charsets declared in the dataset            |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CodecError`                                      |:cpp:class:`ImebraCodecError`                                      |Base class for codec related exceptions         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CodecWrongFormatError`                           |:cpp:class:`ImebraCodecWrongFormatError`                           |Thrown when a codec cannot parse the byte stream|
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CodecCorruptedFileError`                         |:cpp:class:`ImebraCodecCorruptedFileError`                         |Thrown when the byte stream is corrupted        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CodecWrongTransferSyntaxError`                   |:cpp:class:`ImebraCodecWrongTransferSyntaxError`                   |Thrown when the transfer syntax is unknown      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::CodecImageTooBigError`                           |:cpp:class:`ImebraCodecImageTooBigError`                           |Thrown when the image size is too big           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::InvalidSequenceItemError`                        |:cpp:class:`ImebraInvalidSequenceItemError`                        |Thrown when a sequence has a wrong VR           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::StreamJpegTagInStreamError`                      |:cpp:class:`ImebraStreamJpegTagInStreamError`                      |Thrown when a jpeg tag is in the wrong position |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DicomCodecError`                                 |:cpp:class:`ImebraDicomCodecError`                                 |Base class for DICOM codec exceptions           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DicomCodecDepthLimitReachedError`                |:cpp:class:`ImebraDicomCodecDepthLimitReachedError`                |Thrown when too many sequences are embedded into|
|                                                                     |                                                                   |each other                                      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::JpegCodecError`                                  |:cpp:class:`ImebraJpegCodecError`                                  |Base class for jpeg related exceptions          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::JpegCodecCannotHandleSyntaxError`                |:cpp:class:`ImebraJpegCodecCannotHandleSyntaxError`                |Thrown when the JPEG SOF ID cannot be processed |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataHandlerError`                                |:cpp:class:`ImebraDataHandlerError`                                |Base class for data handler related exceptions  |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataHandlerConversionError`                      |:cpp:class:`ImebraDataHandlerConversionError`                      |Thrown when the data cannot be converted        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataHandlerCorruptedBufferError`                 |:cpp:class:`ImebraDataHandlerCorruptedBufferError`                 |Thrown when a data buffer is corrupted          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataHandlerInvalidDataError`                     |:cpp:class:`ImebraDataHandlerInvalidDataError`                     |Thrown when trying to store invalid data        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetError`                                    |:cpp:class:`ImebraDataSetError`                                    |Base class for DataSet related exceptions       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetDifferentFormatError`                     |:cpp:class:`ImebraDataSetDifferentFormatError`                     |Thrown when the operation requires a change of  |
|                                                                     |                                                                   |transfer syntax                                 |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetUnknownTransferSyntaxError`               |:cpp:class:`ImebraDataSetUnknownTransferSyntaxError`               |Thrown when none of the code support the        |
|                                                                     |                                                                   |transfer syntax                                 |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetWrongFrameError`                          |:cpp:class:`ImebraDataSetWrongFrameError`                          |Thrown when storing the wrong frame             |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetImageDoesntExistError`                    |:cpp:class:`ImebraDataSetImageDoesntExistError`                    |Thrown when attempting to retrieve a frame that |
|                                                                     |                                                                   |does not exist                                  |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetImagePaletteColorIsReadOnly`              |:cpp:class:`ImebraDataSetImagePaletteColorIsReadOnly`              |Thrown when trying to write a Palette image     |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DataSetCorruptedOffsetTableError`                |:cpp:class:`ImebraDataSetCorruptedOffsetTableError`                |Thrown when the table offset for the images is  |
|                                                                     |                                                                   |corrupted                                       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DicomDirError`                                   |:cpp:class:`ImebraDicomDirError`                                   |Base class for DICOMDIR related exceptions      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DicomDirCircularReferenceError`                  |:cpp:class:`ImebraDicomDirCircularReferenceError`                  |Thrown when a dicomentry references a           |
|                                                                     |                                                                   |parent entry as a child                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::HuffmanError`                                    |:cpp:class:`ImebraHuffmanError`                                    |Base class for huffman related exceptions       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::HuffmanCreateTableError`                         |:cpp:class:`ImebraHuffmanCreateTableError`                         |Thrown when the Huffman table cannot be created |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::HuffmanReadError`                                |:cpp:class:`ImebraHuffmanReadError`                                |Thrown when an invalid Huffman code is read     |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::HuffmanWriteError`                               |:cpp:class:`ImebraHuffmanWriteError`                               |Thrown when writing a value that is not in the  |
|                                                                     |                                                                   |Huffman table                                   |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ImageError`                                      |:cpp:class:`ImebraImageError`                                      |Base class for Image related exceptions         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ImageUnknownDepthError`                          |:cpp:class:`ImebraImageUnknownDepthError`                          |Thrown when the bit depth parameter is wrong    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ImageUnknownColorSpaceError`                     |:cpp:class:`ImebraImageUnknownColorSpaceError`                     |Thrown when the color space is not recognized   |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ImageInvalidSizeError`                           |:cpp:class:`ImebraImageInvalidSizeError`                           |Thrown when the image size is invalid           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::TransformError`                                  |:cpp:class:`ImebraTransformError`                                  |Base class for Transform related exceptions     |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::TransformInvalidAreaError`                       |:cpp:class:`ImebraTransformInvalidAreaError`                       |Thrown when the transform area is invalid       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::TransformDifferentHighBitError`                  |:cpp:class:`ImebraTransformDifferentHighBitError`                  |Thrown when the high bit of the input image is  |
|                                                                     |                                                                   |different from the high bit of the output image |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ColorTransformError`                             |:cpp:class:`ImebraColorTransformError`                             |Base class for Color Transform related          |
|                                                                     |                                                                   |exceptions                                      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ColorTransformWrongColorSpaceError`              |:cpp:class:`ImebraColorTransformWrongColorSpaceError`              |Thrown when the input or output images of a     |
|                                                                     |                                                                   |color transform have the wrong color space      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ColorTransformsFactoryError`                     |:cpp:class:`ImebraColorTransformsFactoryError`                     |Base class for Color Transform Factory related  |
|                                                                     |                                                                   |exceptions                                      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ColorTransformsFactoryNoTransformError`          |:cpp:class:`ImebraColorTransformsFactoryNoTransformError`          |Thrown when a conversion between the specified  |
|                                                                     |                                                                   |color spaces does not exist                     |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::TransformDifferentColorSpacesError`              |:cpp:class:`ImebraTransformDifferentColorSpacesError`              |Thrown when the input and output images of a    |
|                                                                     |                                                                   |High Bit Transform have different color spaces  |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ModalityVOILUTError`                             |:cpp:class:`ImebraModalityVOILUTError`                             |Thrown when the input or output images of a     |
|                                                                     |                                                                   |VOILUT transform are not monochromatic          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::ImebraBadAlloc`                                  |:cpp:class:`ImebraBadAlloc`                                        |Thrown when Imebra cannot allocate memory       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MemoryError`                                     |:cpp:class:`ImebraMemoryError`                                     |Base class for ReadMemory and ReadWriteMemory   |
|                                                                     |                                                                   |related exceptions                              |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::MemorySizeError`                                 |:cpp:class:`ImebraMemorySizeError`                                 |Thrown when the allocated memory is too small   |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::LutError`                                        |:cpp:class:`ImebraLutError`                                        |Base class for LUT related exceptions           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::LutCorruptedError`                               |:cpp:class:`ImebraLutCorruptedError`                               |Thrown when the LUT content is corrupted        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseError`                                       |:cpp:class:`ImebraAcseError`                                       |Base class for ACSE related exceptions          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseCorruptedMessageError`                       |:cpp:class:`ImebraAcseCorruptedMessageError`                       |Thrown when an ACSE message is corrupted        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseNoTransferSyntaxError`                       |:cpp:class:`ImebraAcseNoTransferSyntaxError`                       |Thrown when a transfer syntax is not available  |
|                                                                     |                                                                   |for the abstract syntax                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcsePresentationContextNotRequestedError`        |:cpp:class:`ImebraAcsePresentationContextNotRequestedError`        |Thrown when the presentation context wasn't     |
|                                                                     |                                                                   |requested during the association negotiation    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseWrongRoleError`                              |:cpp:class:`ImebraAcseWrongRoleError`                              |Thrown if the service is using the wrong role   |
|                                                                     |                                                                   |for the presentation context                    |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseWrongIdError`                                |:cpp:class:`ImebraAcseWrongIdError`                                |Base class for wrong message ID exceptions      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseWrongResponseIdError`                        |:cpp:class:`ImebraAcseWrongResponseIdError`                        |Thrown when a response has the wrong ID         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseWrongCommandIdError`                         |:cpp:class:`ImebraAcseWrongCommandIdError`                         |Thrown when a command has the wrong ID          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseRejectedAssociationError`                    |:cpp:class:`ImebraAcseRejectedAssociationError`                    |Base class for association negotiation related  |
|                                                                     |                                                                   |exceptions                                      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCUNoReasonGivenError`                       |:cpp:class:`ImebraAcseSCUNoReasonGivenError`                       |Association rejected by SCU with no given       |
|                                                                     |                                                                   |reasons                                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCUApplicationContextNameNotSupportedError`  |:cpp:class:`ImebraAcseSCUApplicationContextNameNotSupportedError`  |Association rejected by SCU because of wrong    |
|                                                                     |                                                                   |application context name                        |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCUCallingAETNotRecognizedError`             |:cpp:class:`ImebraAcseSCUCallingAETNotRecognizedError`             |Association rejected by SCU because the calling |
|                                                                     |                                                                   |AET was not recognized                          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCUCalledAETNotRecognizedError`              |:cpp:class:`ImebraAcseSCUCalledAETNotRecognizedError`              |Association rejected by SCU because the called  |
|                                                                     |                                                                   |AET was not recognized                          |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCPNoReasonGivenError`                       |:cpp:class:`ImebraAcseSCPNoReasonGivenError`                       |Association rejected by SCP with no given       |
|                                                                     |                                                                   |reasons                                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCPAcseProtocolVersionNotSupportedError`     |:cpp:class:`ImebraAcseSCPAcseProtocolVersionNotSupportedError`     |Association rejected by SCP because the protocol|
|                                                                     |                                                                   |version was not supported                       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCPPresentationReservedError`                |:cpp:class:`ImebraAcseSCPPresentationReservedError`                |Association rejected by SCP because of the usage|
|                                                                     |                                                                   |of a reserved presentation context ID           |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCPPresentationTemporaryCongestionError`     |:cpp:class:`ImebraAcseSCPPresentationTemporaryCongestionError`     |Association rejected by SCP because of a        |
|                                                                     |                                                                   |temporary congestion                            |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseSCPPresentationLocalLimitExcededError`       |:cpp:class:`ImebraAcseSCPPresentationLocalLimitExcededError`       |Association rejected by SCP because of a        |
|                                                                     |                                                                   |exustion of simultaneous connections            |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseTooManyOperationsPerformedError`             |:cpp:class:`ImebraAcseTooManyOperationsPerformedError`             |Thrown when too many operations are being       |
|                                                                     |                                                                   |performed                                       |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseTooManyOperationsInvokedError`               |:cpp:class:`ImebraAcseTooManyOperationsInvokedError`               |Thrown when too many operations are being       |
|                                                                     |                                                                   |invoked                                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::AcseNoPayloadError`                              |:cpp:class:`ImebraAcseNoPayloadError`                              |Thrown when a payload was expected but is       |
|                                                                     |                                                                   |missing                                         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DimseError`                                      |:cpp:class:`ImebraDimseError`                                      |Base class for DIMSE related exceptions         |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+
|:cpp:class:`imebra::DimseInvalidCommand`                             |:cpp:class:`ImebraDimseInvalidCommand`                             |Thrown when an invalid command is received      |
+---------------------------------------------------------------------+-------------------------------------------------------------------+------------------------------------------------+


Exceptions manager
------------------

ExceptionsManager
.................

C++
,,,

.. doxygenclass:: imebra::ExceptionsManager
   :members:


Missing data exceptions
-----------------------

MissingDataElementError
.......................

C++
,,,

.. doxygenclass:: imebra::MissingDataElementError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMissingDataElementError
   :members:


MissingGroupError
.................

C++
,,,

.. doxygenclass:: imebra::MissingGroupError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMissingGroupError
   :members:
   

MissingTagError
...............

C++
,,,

.. doxygenclass:: imebra::MissingTagError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMissingTagError
   :members:


MissingBufferError
..................

C++
,,,

.. doxygenclass:: imebra::MissingBufferError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMissingBufferError
   :members:


MissingItemError
................

C++
,,,

.. doxygenclass:: imebra::MissingItemError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMissingItemError
   :members:


Stream error exceptions
-----------------------

StreamError
...........

C++
,,,

.. doxygenclass:: imebra::StreamError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraStreamError
   :members:


StreamOpenError
...............

C++
,,,

.. doxygenclass:: imebra::StreamOpenError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraStreamOpenError
   :members:


StreamReadError
...............

C++
,,,

.. doxygenclass:: imebra::StreamReadError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraStreamReadError
   :members:


StreamWriteError
................

C++
,,,

.. doxygenclass:: imebra::StreamWriteError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraStreamWriteError
   :members:


StreamClosedError
.................

C++
,,,

.. doxygenclass:: imebra::StreamClosedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraStreamClosedError
   :members:


StreamEOFError
..............

C++
,,,

.. doxygenclass:: imebra::StreamEOFError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraStreamEOFError
   :members:


TCP exceptions
--------------

TCPConnectionRefused
....................

C++
,,,

.. doxygenclass:: imebra::TCPConnectionRefused
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraTCPConnectionRefused
   :members:


TCPAddressAlreadyInUse
......................

C++
,,,

.. doxygenclass:: imebra::TCPAddressAlreadyInUse
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraTCPAddressAlreadyInUse
   :members:


PermissionDeniedError
.....................

C++
,,,

.. doxygenclass:: imebra::PermissionDeniedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraPermissionDeniedError
   :members:


AddressError
............

C++
,,,

.. doxygenclass:: imebra::AddressError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAddressError
   :members:


AddressTryAgainError
....................

C++
,,,

.. doxygenclass:: imebra::AddressTryAgainError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAddressTryAgainError
   :members:


AddressNoNameError
..................

C++
,,,

.. doxygenclass:: imebra::AddressNoNameError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAddressNoNameError
   :members:


AddressServiceNotSupportedError
...............................

C++
,,,

.. doxygenclass:: imebra::AddressServiceNotSupportedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAddressServiceNotSupportedError
   :members:


Dictionary exceptions
---------------------

DictionaryError
...............

C++
,,,

.. doxygenclass:: imebra::DictionaryError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDictionaryError
   :members:


DictionaryUnknownTagError
.........................

C++
,,,

.. doxygenclass:: imebra::DictionaryUnknownTagError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDictionaryUnknownTagError
   :members:


DictionaryUnknownDataTypeError
..............................

C++
,,,

.. doxygenclass:: imebra::DictionaryUnknownDataTypeError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDictionaryUnknownDataTypeError
   :members:


Charset conversion exceptions
-----------------------------

CharsetConversionError
......................

C++
,,,

.. doxygenclass:: imebra::CharsetConversionError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCharsetConversionError
   :members:


CharsetConversionNoTableError
.............................

C++
,,,

.. doxygenclass:: imebra::CharsetConversionNoTableError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCharsetConversionNoTableError
   :members:


CharsetConversionNoSupportedTableError
......................................

C++
,,,

.. doxygenclass:: imebra::CharsetConversionNoSupportedTableError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCharsetConversionNoSupportedTableError
   :members:


CharsetConversionCannotConvert
..............................

C++
,,,

.. doxygenclass:: imebra::CharsetConversionCannotConvert
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

.. doxygenclass:: imebra::CodecError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCodecError
   :members:


CodecWrongFormatError
.....................

C++
,,,

.. doxygenclass:: imebra::CodecWrongFormatError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCodecWrongFormatError
   :members:


CodecCorruptedFileError
.......................

C++
,,,

.. doxygenclass:: imebra::CodecCorruptedFileError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCodecCorruptedFileError
   :members:


CodecWrongTransferSyntaxError
.............................

C++
,,,

.. doxygenclass:: imebra::CodecWrongTransferSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCodecWrongTransferSyntaxError
   :members:


CodecImageTooBigError
.....................

C++
,,,

.. doxygenclass:: imebra::CodecImageTooBigError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraCodecImageTooBigError
   :members:


InvalidSequenceItemError
........................

C++
,,,

.. doxygenclass:: imebra::InvalidSequenceItemError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraInvalidSequenceItemError
   :members:


DicomCodecError
...............

C++
,,,

.. doxygenclass:: imebra::DicomCodecError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDicomCodecError
   :members:


DicomCodecDepthLimitReachedError
................................

C++
,,,

.. doxygenclass:: imebra::DicomCodecDepthLimitReachedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDicomCodecDepthLimitReachedError
   :members:


JpegCodecError
..............

C++
,,,

.. doxygenclass:: imebra::JpegCodecError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraJpegCodecError
   :members:


JpegCodecCannotHandleSyntaxError
................................

C++
,,,

.. doxygenclass:: imebra::JpegCodecCannotHandleSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraJpegCodecCannotHandleSyntaxError
   :members:


Data handler exceptions
-----------------------

DataHandlerError
................

C++
,,,

.. doxygenclass:: imebra::DataHandlerError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataHandlerError
   :members:


DataHandlerConversionError
..........................

C++
,,,

.. doxygenclass:: imebra::DataHandlerConversionError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataHandlerConversionError
   :members:


DataHandlerCorruptedBufferError
...............................

C++
,,,

.. doxygenclass:: imebra::DataHandlerCorruptedBufferError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataHandlerCorruptedBufferError
   :members:


DataHandlerInvalidDataError
...........................

C++
,,,

.. doxygenclass:: imebra::DataHandlerInvalidDataError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataHandlerInvalidDataError
   :members:


DataSet exceptions
------------------

DataSetError
............

C++
,,,

.. doxygenclass:: imebra::DataSetError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetError
   :members:


DataSetDifferentFormatError
...........................

C++
,,,

.. doxygenclass:: imebra::DataSetDifferentFormatError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetDifferentFormatError
   :members:


DataSetUnknownTransferSyntaxError
.................................

C++
,,,

.. doxygenclass:: imebra::DataSetUnknownTransferSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetUnknownTransferSyntaxError
   :members:


DataSetWrongFrameError
......................

C++
,,,

.. doxygenclass:: imebra::DataSetWrongFrameError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetWrongFrameError
   :members:


DataSetImageDoesntExistError
............................

C++
,,,

.. doxygenclass:: imebra::DataSetImageDoesntExistError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetImageDoesntExistError
   :members:


DataSetImagePaletteColorIsReadOnly
..................................

C++
,,,

.. doxygenclass:: imebra::DataSetImagePaletteColorIsReadOnly
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetImagePaletteColorIsReadOnly
   :members:


DataSetCorruptedOffsetTableError
................................

C++
,,,

.. doxygenclass:: imebra::DataSetCorruptedOffsetTableError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDataSetCorruptedOffsetTableError
   :members:


DICOMDIR exceptions
-------------------

DicomDirError
.............

C++
,,,

.. doxygenclass:: imebra::DicomDirError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDicomDirError
   :members:


DicomDirCircularReferenceError
..............................

C++
,,,

.. doxygenclass:: imebra::DicomDirCircularReferenceError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDicomDirCircularReferenceError
   :members:


Image exceptions
----------------

ImageError
..........

.. doxygenclass:: imebra::ImageError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraImageError
   :members:


ImageUnknownDepthError
......................

C++
,,,

.. doxygenclass:: imebra::ImageUnknownDepthError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraImageUnknownDepthError
   :members:


ImageUnknownColorSpaceError
...........................

C++
,,,

.. doxygenclass:: imebra::ImageUnknownColorSpaceError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraImageUnknownColorSpaceError
   :members:


ImageInvalidSizeError
.....................

C++
,,,

.. doxygenclass:: imebra::ImageInvalidSizeError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraImageInvalidSizeError
   :members:


Transform exceptions
--------------------

TransformError
..............

C++
,,,

.. doxygenclass:: imebra::TransformError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraTransformError
   :members:


TransformInvalidAreaError
.........................

C++
,,,

.. doxygenclass:: imebra::TransformInvalidAreaError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraTransformInvalidAreaError
   :members:


TransformDifferentHighBitError
..............................

C++
,,,

.. doxygenclass:: imebra::TransformDifferentHighBitError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraTransformDifferentHighBitError
   :members:


ColorTransformError
...................

C++
,,,

.. doxygenclass:: imebra::ColorTransformError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraColorTransformError
   :members:


ColorTransformWrongColorSpaceError
..................................

C++
,,,

.. doxygenclass:: imebra::ColorTransformWrongColorSpaceError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraColorTransformWrongColorSpaceError
   :members:


ColorTransformsFactoryError
...........................

C++
,,,

.. doxygenclass:: imebra::ColorTransformsFactoryError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraColorTransformsFactoryError
   :members:


ColorTransformsFactoryNoTransformError
......................................

C++
,,,

.. doxygenclass:: imebra::ColorTransformsFactoryNoTransformError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraColorTransformsFactoryNoTransformError
   :members:


TransformDifferentColorSpacesError
.........................................

C++
,,,

.. doxygenclass:: imebra::TransformDifferentColorSpacesError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraTransformDifferentColorSpacesError
   :members:


ModalityVOILUTError
...................

C++
,,,

.. doxygenclass:: imebra::ModalityVOILUTError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraModalityVOILUTError
   :members:


Memory exceptions
-----------------

ImebraBadAlloc
..............

C++
,,,

.. doxygenclass:: imebra::ImebraBadAlloc
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraBadAlloc
   :members:


MemoryError
...........

C++
,,,

.. doxygenclass:: imebra::MemoryError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMemoryError
   :members:


MemorySizeError
...............

C++
,,,

.. doxygenclass:: imebra::MemorySizeError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraMemorySizeError
   :members:


LUT exceptions
--------------

LutError
........

C++
,,,

.. doxygenclass:: imebra::LutError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraLutError
   :members:


LutCorruptedError
.................

C++
,,,

.. doxygenclass:: imebra::LutCorruptedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraLutCorruptedError
   :members:


ACSE exceptions
---------------

AcseError
.........

C++
,,,

.. doxygenclass:: imebra::AcseError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseError
   :members:


AcseCorruptedMessageError
.........................

C++
,,,

.. doxygenclass:: imebra::AcseCorruptedMessageError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseCorruptedMessageError
   :members:


AcseNoTransferSyntaxError
.........................

C++
,,,

.. doxygenclass:: imebra::AcseNoTransferSyntaxError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseNoTransferSyntaxError
   :members:


AcsePresentationContextNotRequestedError
........................................

C++
,,,

.. doxygenclass:: imebra::AcsePresentationContextNotRequestedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcsePresentationContextNotRequestedError
   :members:


AcseWrongRoleError
..................

C++
,,,

.. doxygenclass:: imebra::AcseWrongRoleError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseWrongRoleError
   :members:


AcseWrongIdError
................

C++
,,,

.. doxygenclass:: imebra::AcseWrongIdError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseWrongIdError
   :members:


AcseWrongResponseIdError
........................

C++
,,,

.. doxygenclass:: imebra::AcseWrongResponseIdError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseWrongResponseIdError
   :members:


AcseWrongCommandIdError
.......................

C++
,,,

.. doxygenclass:: imebra::AcseWrongCommandIdError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseWrongCommandIdError
   :members:


AcseRejectedAssociationError
............................

C++
,,,

.. doxygenclass:: imebra::AcseRejectedAssociationError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseRejectedAssociationError
   :members:


AcseSCUNoReasonGivenError
.........................

C++
,,,

.. doxygenclass:: imebra::AcseSCUNoReasonGivenError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCUNoReasonGivenError
   :members:


AcseSCUApplicationContextNameNotSupportedError
..............................................

C++
,,,

.. doxygenclass:: imebra::AcseSCUApplicationContextNameNotSupportedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCUApplicationContextNameNotSupportedError
   :members:


AcseSCUCallingAETNotRecognizedError
...................................

C++
,,,

.. doxygenclass:: imebra::AcseSCUCallingAETNotRecognizedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCUCallingAETNotRecognizedError
   :members:


AcseSCUCalledAETNotRecognizedError
..................................

C++
,,,

.. doxygenclass:: imebra::AcseSCUCalledAETNotRecognizedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCUCalledAETNotRecognizedError
   :members:


AcseSCPNoReasonGivenError
.........................

C++
,,,

.. doxygenclass:: imebra::AcseSCPNoReasonGivenError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCPNoReasonGivenError
   :members:


AcseSCPAcseProtocolVersionNotSupportedError
...........................................

C++
,,,

.. doxygenclass:: imebra::AcseSCPAcseProtocolVersionNotSupportedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCPAcseProtocolVersionNotSupportedError
   :members:


AcseSCPPresentationReservedError
................................

C++
,,,

.. doxygenclass:: imebra::AcseSCPPresentationReservedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCPPresentationReservedError
   :members:


AcseSCPPresentationTemporaryCongestionError
...........................................

C++
,,,

.. doxygenclass:: imebra::AcseSCPPresentationTemporaryCongestionError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCPPresentationTemporaryCongestionError
   :members:


AcseSCPPresentationLocalLimitExcededError
.........................................

C++
,,,

.. doxygenclass:: imebra::AcseSCPPresentationLocalLimitExcededError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseSCPPresentationLocalLimitExcededError
   :members:


AcseTooManyOperationsPerformedError
...................................

C++
,,,

.. doxygenclass:: imebra::AcseTooManyOperationsPerformedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseTooManyOperationsPerformedError
   :members:


AcseTooManyOperationsInvokedError
.................................

C++
,,,

.. doxygenclass:: imebra::AcseTooManyOperationsInvokedError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseTooManyOperationsInvokedError
   :members:


AcseNoPayloadError
..................

C++
,,,

.. doxygenclass:: imebra::AcseNoPayloadError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraAcseNoPayloadError
   :members:


DIMSE exceptions
----------------

DimseError
..........

C++
,,,

.. doxygenclass:: imebra::DimseError
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDimseError
   :members:


DimseInvalidCommand
...................

C++
,,,

.. doxygenclass:: imebra::DimseInvalidCommand
   :members:

Objective-C/Swift
,,,,,,,,,,,,,,,,,

.. doxygenclass:: ImebraDimseInvalidCommand
   :members:

