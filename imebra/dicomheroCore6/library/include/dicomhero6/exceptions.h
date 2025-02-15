/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(imebraExceptions__INCLUDED_)
#define imebraExceptions__INCLUDED_

#include <stdexcept>
#include <string>
#include "definitions.h"

namespace dicomhero
{


/// \brief Return the stack trace for the last exception thrown in the current
///        thread.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ExceptionsManager
{
public:
    /// \brief Return a message containing the stack trace for the last exception
    ///        thrown in the current thread.
    ///
    /// \return a message containing the stack trace
    ///
    ///////////////////////////////////////////////////////////////////////////////
    static std::string getExceptionTrace() noexcept;
};


///
/// \brief This is the base class for the exceptions thrown by the LUT class.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API LutError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit LutError(const std::string& message);

    LutError(const LutError& source);

    LutError& operator=(const LutError&) = delete;

    virtual ~LutError() noexcept;
};


///
/// \brief This exception is thrown by the lut class when the the LUT
///        information is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API LutCorruptedError: public LutError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit LutCorruptedError(const std::string& message);

    LutCorruptedError(const LutCorruptedError& source);

    LutCorruptedError& operator=(const LutCorruptedError&) = delete;

    virtual ~LutCorruptedError() noexcept;
};


/// \brief Base class for the exceptions that report a missing element
///        (Image, Tag, group, etc).
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MissingDataElementError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MissingDataElementError(const std::string& message);

    MissingDataElementError(const MissingDataElementError& source);

    MissingDataElementError& operator=(const MissingDataElementError&) = delete;

    virtual ~MissingDataElementError() noexcept;
};


/// \brief This exception is thrown when the client tries to read a tag from
///        a group that does not exist.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MissingGroupError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MissingGroupError(const std::string& message);

    MissingGroupError(const MissingGroupError& source);

    MissingGroupError& operator=(const MissingGroupError&) = delete;

    virtual ~MissingGroupError() noexcept;
};


/// \brief This exception is thrown when the client tries to read a value from
///        a tag that does not exist (inside an existing group).
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MissingTagError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MissingTagError(const std::string& message);

    MissingTagError(const MissingTagError& source);

    MissingTagError& operator=(const MissingTagError&) = delete;

    virtual ~MissingTagError() noexcept;
};


/// \brief This exception is thrown when the client tries to read a value from
///        a buffer that does not exist (inside an existing tag).
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MissingBufferError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MissingBufferError(const std::string& message);

    MissingBufferError(const MissingBufferError& source);

    MissingBufferError& operator=(const MissingBufferError&) = delete;

    virtual ~MissingBufferError() noexcept;
};


/// \brief This exception is thrown when the client tries to read a value from
///        an element that does not exist (inside an existing buffer).
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MissingItemError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MissingItemError(const std::string& message);

    MissingItemError(const MissingItemError& source);

    MissingItemError& operator=(const MissingItemError&) = delete;

    virtual ~MissingItemError() noexcept;
};


/// \brief The base exception for all the exceptions thrown by the function
///        in baseStream.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API StreamError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit StreamError(const std::string& message);

    StreamError(const StreamError& source);

    StreamError& operator=(const StreamError&) = delete;

    virtual ~StreamError() noexcept;
};


///
/// \brief Exception thrown when the stream cannot be open.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API StreamOpenError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit StreamOpenError(const std::string& message);

    StreamOpenError(const StreamOpenError& source);

    StreamOpenError& operator=(const StreamOpenError&) = delete;

    virtual ~StreamOpenError() noexcept;
};


///
/// \brief Exception thrown when there is an error during the read phase.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API StreamReadError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit StreamReadError(const std::string& message);

    StreamReadError(const StreamReadError& source);

    StreamReadError& operator=(const StreamReadError&) = delete;

    virtual ~StreamReadError() noexcept;
};


///
/// \brief Exception thrown when there is an error during the write phase.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API StreamWriteError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit StreamWriteError(const std::string& message);

    StreamWriteError(const StreamWriteError& source);

    StreamWriteError& operator=(const StreamWriteError&) = delete;

    virtual ~StreamWriteError() noexcept;
};


///
/// \brief The peer refused the attempted connection.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API TCPConnectionRefused: public StreamOpenError
{
public:
    explicit TCPConnectionRefused(const std::string& message);

    TCPConnectionRefused(const TCPConnectionRefused& source);

    TCPConnectionRefused& operator=(const TCPConnectionRefused&) = delete;

    virtual ~TCPConnectionRefused() noexcept;
};


///
/// \brief The specified address is already in use by another socket.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API TCPAddressAlreadyInUse: public StreamOpenError
{
public:
    explicit TCPAddressAlreadyInUse(const std::string& message);

    TCPAddressAlreadyInUse(const TCPAddressAlreadyInUse& source);

    TCPAddressAlreadyInUse& operator=(const TCPAddressAlreadyInUse&) = delete;

    virtual ~TCPAddressAlreadyInUse() noexcept;
};


///
/// \brief The application does not have the permissions to carry out the
///        operation
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API PermissionDeniedError: public std::runtime_error
{
public:
    explicit PermissionDeniedError(const std::string& message);

    PermissionDeniedError(const PermissionDeniedError& source);

    PermissionDeniedError& operator=(const PermissionDeniedError&) = delete;

    virtual ~PermissionDeniedError() noexcept;
};


///
/// \brief Base class for the exceptions thrown by TCPAddress.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AddressError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AddressError(const std::string& message);

    AddressError(const AddressError& source);

    AddressError& operator=(const AddressError&) = delete;

    virtual ~AddressError() noexcept;
};


/// \brief Exception thrown by TCPAddress when a temporary malfunction
///        prevented the address resolution. Trying again may cancel the error
///        condition.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AddressTryAgainError: public AddressError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AddressTryAgainError(const std::string& message);

    AddressTryAgainError(const AddressTryAgainError& source);

    AddressTryAgainError& operator=(const AddressTryAgainError&) = delete;

    virtual ~AddressTryAgainError() noexcept;
};


/// \brief Exception thrown by TCPAddress when the name cannot be resolved.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AddressNoNameError: public AddressError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AddressNoNameError(const std::string& message);

    AddressNoNameError(const AddressNoNameError& source);

    AddressNoNameError& operator=(const AddressNoNameError&) = delete;

    virtual ~AddressNoNameError() noexcept;
};


/// \brief Exception thrown by TCPAddress when the specified service is
///        not supported.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AddressServiceNotSupportedError: public AddressError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AddressServiceNotSupportedError(const std::string& message);

    AddressServiceNotSupportedError(const AddressServiceNotSupportedError& source);

    AddressServiceNotSupportedError& operator=(const AddressServiceNotSupportedError&) = delete;

    virtual ~AddressServiceNotSupportedError() noexcept;
};


/// \brief Base class for the exceptions thrown by the DicomDictionary.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DictionaryError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DictionaryError(const std::string& message);

    DictionaryError(const DictionaryError& source);

    DictionaryError& operator=(const DictionaryError&) = delete;

    virtual ~DictionaryError() noexcept;
};


/// \brief This exception is thrown by the DicomDictionary when it must return
///        information for a tag that the DICOM standard does not define.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DictionaryUnknownTagError: public DictionaryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DictionaryUnknownTagError(const std::string& message);

    DictionaryUnknownTagError(const DictionaryUnknownTagError& source);

    DictionaryUnknownTagError& operator=(const DictionaryUnknownTagError&) = delete;

    virtual ~DictionaryUnknownTagError() noexcept;
};


/// \brief This exception is thrown by the DicomDictionary when it must return
///        information for a VR (data type) that the DICOM standard does not
///        define.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DictionaryUnknownDataTypeError: public DictionaryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DictionaryUnknownDataTypeError(const std::string& message);

    DictionaryUnknownDataTypeError(const DictionaryUnknownDataTypeError& source);

    DictionaryUnknownDataTypeError& operator=(const DictionaryUnknownDataTypeError&) = delete;

    virtual ~DictionaryUnknownDataTypeError() noexcept;
};


/// \brief Base class for the exceptions thrown by charsetConversion.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CharsetConversionError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CharsetConversionError(const std::string& message);

    CharsetConversionError(const CharsetConversionError& source);

    CharsetConversionError& operator=(const CharsetConversionError&) = delete;

    virtual ~CharsetConversionError() noexcept;
};


/// \brief Exception thrown when the requested charset is not supported by the
///        DICOM standard.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CharsetConversionNoTableError: public CharsetConversionError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CharsetConversionNoTableError(const std::string& message);

    CharsetConversionNoTableError(const CharsetConversionNoTableError& source);

    CharsetConversionNoTableError& operator=(const CharsetConversionNoTableError&) = delete;

    virtual ~CharsetConversionNoTableError() noexcept;
};


/// \brief Exception thrown when the requested charset is not supported by
///        the system.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CharsetConversionNoSupportedTableError: public CharsetConversionError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CharsetConversionNoSupportedTableError(const std::string& message);

    CharsetConversionNoSupportedTableError(const CharsetConversionNoSupportedTableError& source);

    CharsetConversionNoSupportedTableError& operator=(const CharsetConversionNoSupportedTableError&) = delete;

    virtual ~CharsetConversionNoSupportedTableError() noexcept;
};


/// \brief Exception thrown when none of the charsets declared in the DataSet
///        are able to convert a string to/from unicode.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CharsetConversionCannotConvert: public CharsetConversionError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CharsetConversionCannotConvert(const std::string& message);

    CharsetConversionCannotConvert(const CharsetConversionCannotConvert& source);

    CharsetConversionCannotConvert& operator=(const CharsetConversionCannotConvert&) = delete;

    virtual ~CharsetConversionCannotConvert() noexcept;
};


/// \brief This is the base class for the exceptions thrown by the codec derived classes.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CodecError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CodecError(const std::string& message);

    CodecError(const CodecError& source);

    CodecError& operator=(const CodecError&) = delete;

    virtual ~CodecError() noexcept;
};


/// \brief This exception is thrown when the file being parsed is not valid
///        for the codec.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CodecWrongFormatError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CodecWrongFormatError(const std::string& message);

    CodecWrongFormatError(const CodecWrongFormatError& source);

    CodecWrongFormatError& operator=(const CodecWrongFormatError&) = delete;

    virtual ~CodecWrongFormatError() noexcept;
};


/// \brief This exception is thrown when the file being parsed is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CodecCorruptedFileError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CodecCorruptedFileError(const std::string& message);

    CodecCorruptedFileError(const CodecCorruptedFileError& source);

    CodecCorruptedFileError& operator=(const CodecCorruptedFileError&) = delete;

    virtual ~CodecCorruptedFileError() noexcept;
};


/// \brief This exception is thrown when the transfer syntax is not recognized
///        by the codec.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CodecWrongTransferSyntaxError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CodecWrongTransferSyntaxError(const std::string& message);

    CodecWrongTransferSyntaxError(const CodecWrongTransferSyntaxError& source);

    CodecWrongTransferSyntaxError& operator=(const CodecWrongTransferSyntaxError&) = delete;

    virtual ~CodecWrongTransferSyntaxError() noexcept;
};


/// \brief This exception is thrown when the codec reads a file that contains
///        an image that is too big according to the codecFactory settings.
///
/// Consider using CodecFactory::setMaximumImageSize() to change the allowed
/// maximum image size.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API CodecImageTooBigError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit CodecImageTooBigError(const std::string& message);

    CodecImageTooBigError(const CodecImageTooBigError& source);

    CodecImageTooBigError& operator=(const CodecImageTooBigError&) = delete;

    virtual ~CodecImageTooBigError() noexcept;
};



/// \brief This exception is thrown when the codec is attempting to create a
///        sequence with an incompatible data type.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API InvalidSequenceItemError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit InvalidSequenceItemError(const std::string& message);

    InvalidSequenceItemError(const InvalidSequenceItemError& source);

    InvalidSequenceItemError& operator=(const InvalidSequenceItemError&) = delete;

    virtual ~InvalidSequenceItemError() noexcept;
};


/// \brief Base class for the exceptions thrown by the data handlers.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataHandlerError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataHandlerError(const std::string& message);

    DataHandlerError(const DataHandlerError& source);

    DataHandlerError& operator=(const DataHandlerError&) = delete;

    virtual ~DataHandlerError() noexcept;
};


/// \brief This exception is thrown when a data handler cannot convert a value from
///        one data type to a different data type.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataHandlerConversionError: public DataHandlerError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataHandlerConversionError(const std::string& message);

    DataHandlerConversionError(const DataHandlerConversionError& source);

    DataHandlerConversionError& operator=(const DataHandlerConversionError&) = delete;

    virtual ~DataHandlerConversionError() noexcept;
};


/// \brief This exception is thrown when the data handler's content is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataHandlerCorruptedBufferError: public DataHandlerError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataHandlerCorruptedBufferError(const std::string& message);

    DataHandlerCorruptedBufferError(const DataHandlerCorruptedBufferError& source);

    DataHandlerCorruptedBufferError& operator=(const DataHandlerCorruptedBufferError&) = delete;

    virtual ~DataHandlerCorruptedBufferError() noexcept;
};


/// \brief This exception is thrown when the client tries to write invalid data
///        into a data handler.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataHandlerInvalidDataError: public DataHandlerError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataHandlerInvalidDataError(const std::string& message);

    DataHandlerInvalidDataError(const DataHandlerInvalidDataError& source);

    DataHandlerInvalidDataError& operator=(const DataHandlerInvalidDataError&) = delete;

    virtual ~DataHandlerInvalidDataError() noexcept;
};

/// \brief This is the base class for the exceptions thrown by the dataSet.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetError(const std::string& message);

    DataSetError(const DataSetError& source);

    DataSetError& operator=(const DataSetError&) = delete;

    virtual ~DataSetError() noexcept;
};


/// \brief This exception is thrown when the application is trying to store an
///        image in the dataSet but the dataSet already stores other images
///        that have different attributes.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetDifferentFormatError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetDifferentFormatError(const std::string& message);

    DataSetDifferentFormatError(const DataSetDifferentFormatError& source);

    DataSetDifferentFormatError& operator=(const DataSetDifferentFormatError&) = delete;

    virtual ~DataSetDifferentFormatError() noexcept;
};


/// \brief This exception is thrown when an unknown transfer syntax is being
///        used while reading or writing a stream.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetUnknownTransferSyntaxError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetUnknownTransferSyntaxError(const std::string& message);

    DataSetUnknownTransferSyntaxError(const DataSetUnknownTransferSyntaxError& source);

    DataSetUnknownTransferSyntaxError& operator=(const DataSetUnknownTransferSyntaxError&) = delete;

    virtual ~DataSetUnknownTransferSyntaxError() noexcept;
};


/// \brief This exception is thrown when the application is storing several
///        images in the dataSet but doesn't store them in the right order.
///
/// The application must store the images following the frame order,
/// without skipping frames.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetWrongFrameError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetWrongFrameError(const std::string& message);

    DataSetWrongFrameError(const DataSetWrongFrameError& source);

    DataSetWrongFrameError& operator=(const DataSetWrongFrameError&) = delete;

    virtual ~DataSetWrongFrameError() noexcept;
};


/// \brief This exception is thrown when the an image that doesn't exist is
///        requested.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetImageDoesntExistError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetImageDoesntExistError(const std::string& message);

    DataSetImageDoesntExistError(const DataSetImageDoesntExistError& source);

    DataSetImageDoesntExistError& operator=(const DataSetImageDoesntExistError&) = delete;

    virtual ~DataSetImageDoesntExistError() noexcept;
};

/// \brief This exception is thrown when the the client tries to store a
///        palette color image into the dataset.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetImagePaletteColorIsReadOnly: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetImagePaletteColorIsReadOnly(const std::string& message);

    DataSetImagePaletteColorIsReadOnly(const DataSetImagePaletteColorIsReadOnly& source);

    DataSetImagePaletteColorIsReadOnly& operator=(const DataSetImagePaletteColorIsReadOnly&) = delete;

    virtual ~DataSetImagePaletteColorIsReadOnly() noexcept;
};

/// \brief This exception is thrown when the basic offset table is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DataSetCorruptedOffsetTableError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DataSetCorruptedOffsetTableError(const std::string& message);

    DataSetCorruptedOffsetTableError(const DataSetCorruptedOffsetTableError& source);

    DataSetCorruptedOffsetTableError& operator=(const DataSetCorruptedOffsetTableError&) = delete;

    virtual ~DataSetCorruptedOffsetTableError() noexcept;
};


/// \brief Base class from which the exceptions thrown by DicomDirEntry and
///        DicomDir classes.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomDirError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DicomDirError(const std::string& message);

    DicomDirError(const DicomDirError& source);

    DicomDirError& operator=(const DicomDirError&) = delete;

    virtual ~DicomDirError() noexcept;
};


/// \brief This exception is thrown when a call to
///        DicomDir::setFirstRootRecord() or DicomDirEntry::setNextRecord()
///        or DicomDirEntry::setFirstChildRecord() causes a circular reference
///        between DicomDirEntry objects.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomDirCircularReferenceError: public DicomDirError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DicomDirCircularReferenceError(const std::string& message);

    DicomDirCircularReferenceError(const DicomDirCircularReferenceError& source);

    DicomDirCircularReferenceError& operator=(const DicomDirCircularReferenceError&) = delete;

    virtual ~DicomDirCircularReferenceError() noexcept;
};


/// \brief This exception is thrown when trying to retrieve a missing
///        DicomDir entry.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomDirNoEntryError: public DicomDirError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DicomDirNoEntryError(const std::string& message);

    DicomDirNoEntryError(const DicomDirNoEntryError& source);

    DicomDirNoEntryError& operator=(const DicomDirNoEntryError&) = delete;

    virtual ~DicomDirNoEntryError() noexcept;
};


/// \brief This is the base class for the exceptions thrown by the Image class.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ImageError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ImageError(const std::string& message);

    ImageError(const ImageError& source);

    ImageError& operator=(const ImageError&) = delete;

    virtual ~ImageError() noexcept;
};

/// \brief This exception is thrown when an unknown depth is specified as a
///        parameter.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ImageUnknownDepthError: public ImageError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ImageUnknownDepthError(const std::string& message);

    ImageUnknownDepthError(const ImageUnknownDepthError& source);

    ImageUnknownDepthError& operator=(const ImageUnknownDepthError&) = delete;

    virtual ~ImageUnknownDepthError() noexcept;
};


/// \brief This exception is thrown when an unknown color space is specified
///        in the function create().
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ImageUnknownColorSpaceError: public ImageError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ImageUnknownColorSpaceError(const std::string& message);

    ImageUnknownColorSpaceError(const ImageUnknownColorSpaceError& source);

    ImageUnknownColorSpaceError& operator=(const ImageUnknownColorSpaceError&) = delete;

    virtual ~ImageUnknownColorSpaceError() noexcept;
};


/// \brief This exception is thrown when an invalid size in pixels is
///        specified in the Image constructor.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ImageInvalidSizeError: public ImageError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ImageInvalidSizeError(const std::string& message);

    ImageInvalidSizeError(const ImageInvalidSizeError& source);

    ImageInvalidSizeError& operator=(const ImageInvalidSizeError&) = delete;

    virtual ~ImageInvalidSizeError() noexcept;
};


/// \brief Base class for the exceptions thrown by the transforms.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API TransformError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit TransformError(const std::string& message);

    TransformError(const TransformError& source);

    TransformError& operator=(const TransformError&) = delete;

    virtual ~TransformError() noexcept;
};

/// \brief Exception thrown when the image areas to be processed are out
///        of bounds.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API TransformInvalidAreaError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit TransformInvalidAreaError(const std::string& message);

    TransformInvalidAreaError(const TransformInvalidAreaError& source);

    TransformInvalidAreaError& operator=(const TransformInvalidAreaError&) = delete;

    virtual ~TransformInvalidAreaError() noexcept;
};


/// \brief Exception thrown when a Transform cannot process images with
///        different high bit.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API TransformDifferentHighBitError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit TransformDifferentHighBitError(const std::string& message);

    TransformDifferentHighBitError(const TransformDifferentHighBitError& source);

    TransformDifferentHighBitError& operator=(const TransformDifferentHighBitError&) = delete;

    virtual ~TransformDifferentHighBitError() noexcept;
};


/// \brief This is the base class for the exceptions thrown by
///        the color transform classes.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ColorTransformError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ColorTransformError(const std::string& message);

    ColorTransformError(const ColorTransformError& source);

    ColorTransformError& operator=(const ColorTransformError&) = delete;

    virtual ~ColorTransformError() noexcept;
};


/// \brief This exception is thrown when a color transform must convert between
///        two color spaces that it does not support.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ColorTransformWrongColorSpaceError: public ColorTransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ColorTransformWrongColorSpaceError(const std::string& message);

    ColorTransformWrongColorSpaceError(const ColorTransformWrongColorSpaceError& source);

    ColorTransformWrongColorSpaceError& operator=(const ColorTransformWrongColorSpaceError&) = delete;

    virtual ~ColorTransformWrongColorSpaceError() noexcept;
};


/// \brief This is the base class for the exceptions thrown by
///        colorTransformsFactory.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ColorTransformsFactoryError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ColorTransformsFactoryError(const std::string& message);

    ColorTransformsFactoryError(const ColorTransformsFactoryError& source);

    ColorTransformsFactoryError& operator=(const ColorTransformsFactoryError&) = delete;

    virtual ~ColorTransformsFactoryError() noexcept;
};


/// \brief This exception is thrown by the function
///        ColorTransformsFactory::getTransform() when it cannot find any
///        transform that can convert the specified color spaces.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ColorTransformsFactoryNoTransformError: public ColorTransformsFactoryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ColorTransformsFactoryNoTransformError(const std::string& message);

    ColorTransformsFactoryNoTransformError(const ColorTransformsFactoryNoTransformError& source);

    ColorTransformsFactoryNoTransformError& operator=(const ColorTransformsFactoryNoTransformError&) = delete;

    virtual ~ColorTransformsFactoryNoTransformError() noexcept;
};


class DICOMHERO_API TransformDifferentColorSpacesError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit TransformDifferentColorSpacesError(const std::string& message);

    TransformDifferentColorSpacesError(const TransformDifferentColorSpacesError& source);

    TransformDifferentColorSpacesError& operator=(const TransformDifferentColorSpacesError&) = delete;

    virtual ~ TransformDifferentColorSpacesError() noexcept;
};


/// \brief Exception thrown when an attempt to read past the end of the file
///        is made.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API StreamEOFError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit StreamEOFError(const std::string& message);

    StreamEOFError(const StreamEOFError& source);

    StreamEOFError& operator=(const StreamEOFError&) = delete;

    virtual ~StreamEOFError() noexcept;
};


/// \brief Exception thrown when a stream has been closed
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API StreamClosedError: public StreamEOFError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit StreamClosedError(const std::string& message);

    StreamClosedError(const StreamClosedError& source);

    StreamClosedError& operator=(const StreamClosedError&) = delete;

    virtual ~StreamClosedError() noexcept;
};


/// \brief This exception is thrown by modalityVOILUT when the images passed
///        to the transform are not monochromatic.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API ModalityVOILUTError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit ModalityVOILUTError(const std::string& message);

    ModalityVOILUTError(const ModalityVOILUTError& source);

    ModalityVOILUTError& operator=(const ModalityVOILUTError&) = delete;

    virtual ~ModalityVOILUTError() noexcept;
};


/// \brief This is the base class for the exceptions thrown by the dicom
///        codec (dicomCodec).
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomCodecError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DicomCodecError(const std::string& message);

    DicomCodecError(const DicomCodecError& source);

    DicomCodecError& operator=(const DicomCodecError&) = delete;

    virtual ~DicomCodecError() noexcept;
};


/// \brief This exception is thrown when dicomCodec::parseStream reaches the
///        maximum depth for embedded datasets.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomCodecDepthLimitReachedError: public DicomCodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DicomCodecDepthLimitReachedError(const std::string&message);

    DicomCodecDepthLimitReachedError(const DicomCodecDepthLimitReachedError& source);

    DicomCodecDepthLimitReachedError& operator=(const DicomCodecDepthLimitReachedError&) = delete;

    virtual ~DicomCodecDepthLimitReachedError() noexcept;

};


/// \brief Base class for the exceptions thrown by the jpeg codec.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API JpegCodecError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit JpegCodecError(const std::string& message);

    JpegCodecError(const JpegCodecError& source);

    JpegCodecError& operator=(const JpegCodecError&) = delete;

    virtual ~JpegCodecError() noexcept;
};


/// \brief Exception thrown when the jpeg variant cannot be handled.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API JpegCodecCannotHandleSyntaxError: public JpegCodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit JpegCodecCannotHandleSyntaxError(const std::string& message);

    JpegCodecCannotHandleSyntaxError(const JpegCodecCannotHandleSyntaxError& source);

    JpegCodecCannotHandleSyntaxError& operator=(const JpegCodecCannotHandleSyntaxError&) = delete;

    virtual ~JpegCodecCannotHandleSyntaxError() noexcept;
};


class DICOMHERO_API DicomheroBadAlloc: public std::bad_alloc
{
public:
    DicomheroBadAlloc();

    DicomheroBadAlloc(const DicomheroBadAlloc& source);

    DicomheroBadAlloc& operator=(const DicomheroBadAlloc&) = delete;

    virtual ~DicomheroBadAlloc() noexcept;
};


/// \brief Base exception for errors in Memory and MutableMemory.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MemoryError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MemoryError(const std::string& message);

    MemoryError(const MemoryError& source);

    MemoryError& operator=(const MemoryError&) = delete;

    virtual ~MemoryError() noexcept;
};


/// \brief Exception throw when the memory size is too small for the requested
///        operation.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MemorySizeError: public MemoryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MemorySizeError(const std::string& message);

    MemorySizeError(const MemorySizeError& source);

    MemorySizeError& operator=(const MemorySizeError&) = delete;

    virtual ~MemorySizeError() noexcept;
};


/// \brief Exception thrown by the ACSE services (negotiation).
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AcseError(const std::string& message);

    AcseError(const AcseError& source);

    AcseError& operator=(const AcseError&) = delete;

    virtual ~AcseError() noexcept;
};


/// \brief Exception thrown by the ACSE services when an ACSE message is
///        corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseCorruptedMessageError: public AcseError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AcseCorruptedMessageError(const std::string& message);

    AcseCorruptedMessageError(const AcseCorruptedMessageError& source);

    AcseCorruptedMessageError& operator=(const AcseCorruptedMessageError&) = delete;

    virtual ~AcseCorruptedMessageError() noexcept;
};


///
/// \brief Exception thrown when no transfer syntax was negotiated for a
///        presentation context.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseNoTransferSyntaxError: public AcseError
{
public:
    explicit AcseNoTransferSyntaxError(const std::string& message);

    AcseNoTransferSyntaxError(const AcseNoTransferSyntaxError& source);

    AcseNoTransferSyntaxError& operator=(const AcseNoTransferSyntaxError&) = delete;

    virtual ~AcseNoTransferSyntaxError() noexcept;
};


/// \brief Exception thrown by the ACSE services when the message's
///        presentation context was not requested during the
///        association negotiation.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcsePresentationContextNotRequestedError: public AcseError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AcsePresentationContextNotRequestedError(const std::string& message);

    AcsePresentationContextNotRequestedError(const AcsePresentationContextNotRequestedError& source);

    AcsePresentationContextNotRequestedError& operator=(const AcsePresentationContextNotRequestedError&) = delete;

    virtual ~AcsePresentationContextNotRequestedError() noexcept;
};


/// \brief Exception thrown by the ACSE services when a command is sent to
///        a destination that cannot accept it
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseWrongRoleError: public AcseError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit AcseWrongRoleError(const std::string& message);

    AcseWrongRoleError(const AcseWrongRoleError& source);

    AcseWrongRoleError& operator=(const AcseWrongRoleError&) = delete;

    virtual ~AcseWrongRoleError() noexcept;
};


///
/// \brief Base class for the exception related to a wrong message ID.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseWrongIdError: public AcseError
{
public:
    explicit AcseWrongIdError(const std::string& message);

    AcseWrongIdError(const AcseWrongIdError& source);

    AcseWrongIdError& operator=(const AcseWrongIdError&) = delete;

    virtual ~AcseWrongIdError() noexcept;
};


///
/// \brief Exception thrown when a response ID is related to a command that
///        has already been responded to or was never sent.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseWrongResponseIdError: public AcseWrongIdError
{
public:
    explicit AcseWrongResponseIdError(const std::string& message);

    AcseWrongResponseIdError(const AcseWrongResponseIdError& source);

    AcseWrongResponseIdError& operator=(const AcseWrongResponseIdError&) = delete;

    virtual ~AcseWrongResponseIdError() noexcept;
};


///
/// \brief Exception thrown when a command has a wrong message ID.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseWrongCommandIdError: public AcseWrongIdError
{
public:
    explicit AcseWrongCommandIdError(const std::string& message);

    AcseWrongCommandIdError(const AcseWrongCommandIdError& source);

    AcseWrongCommandIdError& operator=(const AcseWrongCommandIdError&) = delete;

    virtual ~AcseWrongCommandIdError() noexcept;
};


///
/// \brief Base class for the association rejection exceptions.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseRejectedAssociationError: public AcseError
{
public:
    explicit AcseRejectedAssociationError(const std::string& message, bool bPermanent);

    AcseRejectedAssociationError(const AcseRejectedAssociationError& source);

    AcseRejectedAssociationError& operator=(const AcseRejectedAssociationError&) = delete;

    virtual ~AcseRejectedAssociationError() noexcept;

    ///
    /// \brief Returns true if the rejection is permanent.
    ///
    /// \return true if the rejection is permanent, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool isPermanent() const;

    ///
    /// \brief Returns true if the rejection is temporary.
    ///
    /// \return true if the rejection is temporary, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool isTemporary() const;

protected:
    const bool m_bPermanent;
};


///
/// \brief Generic exception thrown when the association is rejected.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCUNoReasonGivenError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCUNoReasonGivenError(const std::string& message, bool bPermanent);

    AcseSCUNoReasonGivenError(const AcseSCUNoReasonGivenError& source);

    AcseSCUNoReasonGivenError& operator=(const AcseSCUNoReasonGivenError&) = delete;

    virtual ~AcseSCUNoReasonGivenError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected because the
///        application context name is not supported.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCUApplicationContextNameNotSupportedError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCUApplicationContextNameNotSupportedError(const std::string& message, bool bPermanent);

    AcseSCUApplicationContextNameNotSupportedError(const AcseSCUApplicationContextNameNotSupportedError& source);

    AcseSCUApplicationContextNameNotSupportedError& operator=(const AcseSCUApplicationContextNameNotSupportedError&) = delete;

    virtual ~AcseSCUApplicationContextNameNotSupportedError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected because the
///        calling AE title is not recognized.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCUCallingAETNotRecognizedError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCUCallingAETNotRecognizedError(const std::string& message, bool bPermanent);

    AcseSCUCallingAETNotRecognizedError(const AcseSCUCallingAETNotRecognizedError& source);

    AcseSCUCallingAETNotRecognizedError& operator=(const AcseSCUCallingAETNotRecognizedError&) = delete;

    virtual ~AcseSCUCallingAETNotRecognizedError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected because the
///        called AE title is not recognized.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCUCalledAETNotRecognizedError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCUCalledAETNotRecognizedError(const std::string& message, bool bPermanent);

    AcseSCUCalledAETNotRecognizedError(const AcseSCUCalledAETNotRecognizedError& source);

    AcseSCUCalledAETNotRecognizedError& operator=(const AcseSCUCalledAETNotRecognizedError&) = delete;

    virtual ~AcseSCUCalledAETNotRecognizedError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected by the SCP
///        without any particular reason given.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCPNoReasonGivenError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCPNoReasonGivenError(const std::string& message, bool bPermanent);

    AcseSCPNoReasonGivenError(const AcseSCPNoReasonGivenError& source);

    AcseSCPNoReasonGivenError& operator=(const AcseSCPNoReasonGivenError&) = delete;

    virtual ~AcseSCPNoReasonGivenError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected by the SCP
///        because it does not support the requested protocol version.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCPAcseProtocolVersionNotSupportedError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCPAcseProtocolVersionNotSupportedError(const std::string& message, bool bPermanent);

    AcseSCPAcseProtocolVersionNotSupportedError(const AcseSCPAcseProtocolVersionNotSupportedError& source);

    AcseSCPAcseProtocolVersionNotSupportedError& operator=(const AcseSCPAcseProtocolVersionNotSupportedError&) = delete;

    virtual ~AcseSCPAcseProtocolVersionNotSupportedError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected by the SCP
///        because the selected presentation context is reserved.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCPPresentationReservedError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCPPresentationReservedError(const std::string& message, bool bPermanent);

    AcseSCPPresentationReservedError(const AcseSCPPresentationReservedError& source);

    AcseSCPPresentationReservedError& operator=(const AcseSCPPresentationReservedError&) = delete;

    virtual ~AcseSCPPresentationReservedError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected by the SCP
///        because there is a temporary congestion.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCPPresentationTemporaryCongestionError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCPPresentationTemporaryCongestionError(const std::string& message, bool bPermanent);

    AcseSCPPresentationTemporaryCongestionError(const AcseSCPPresentationTemporaryCongestionError& source);

    AcseSCPPresentationTemporaryCongestionError& operator=(const AcseSCPPresentationTemporaryCongestionError&) = delete;

    virtual ~AcseSCPPresentationTemporaryCongestionError() noexcept;
};


///
/// \brief Exception thrown when the association is rejected by the SCP
///        because is out of resources.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseSCPPresentationLocalLimitExcededError: public AcseRejectedAssociationError
{
public:
    explicit AcseSCPPresentationLocalLimitExcededError(const std::string& message, bool bPermanent);

    AcseSCPPresentationLocalLimitExcededError(const AcseSCPPresentationLocalLimitExcededError& source);

    AcseSCPPresentationLocalLimitExcededError& operator=(const AcseSCPPresentationLocalLimitExcededError&) = delete;

    virtual ~AcseSCPPresentationLocalLimitExcededError() noexcept;
};


///
/// \brief Exception thrown when too many simultaneous operations have been
///        requested.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseTooManyOperationsPerformedError: public AcseError
{
public:
    explicit AcseTooManyOperationsPerformedError(const std::string& message);

    AcseTooManyOperationsPerformedError(const AcseTooManyOperationsPerformedError& source);

    AcseTooManyOperationsPerformedError& operator=(const AcseTooManyOperationsPerformedError&) = delete;

    virtual ~AcseTooManyOperationsPerformedError() noexcept;
};


///
/// \brief Exception thrown when too many simultaneous operations have been
///        invoked.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseTooManyOperationsInvokedError: public AcseError
{
public:
    explicit AcseTooManyOperationsInvokedError(const std::string& message);

    AcseTooManyOperationsInvokedError(const AcseTooManyOperationsInvokedError& source);

    AcseTooManyOperationsInvokedError& operator=(const AcseTooManyOperationsInvokedError&) = delete;

    virtual ~AcseTooManyOperationsInvokedError() noexcept;
};


///
/// \brief Exception thrown when a command does not have a payload but it
///        should have one.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API AcseNoPayloadError: public AcseError
{
public:
    explicit AcseNoPayloadError(const std::string& message);

    AcseNoPayloadError(const AcseNoPayloadError& source);

    AcseNoPayloadError& operator=(const AcseNoPayloadError&) = delete;

    virtual ~AcseNoPayloadError() noexcept;
};


///
/// \brief Base class for the exceptions thrown by the DIMSE services.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DimseError: public std::runtime_error
{
public:
    explicit DimseError(const std::string& message);

    DimseError(const DimseError& source);

    DimseError& operator=(const DimseError&) = delete;

    virtual ~DimseError() noexcept;
};


///
/// \brief Exception thrown when a DIMSE command cannot be validated.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DimseInvalidCommand: public DimseError
{
public:
    explicit DimseInvalidCommand(const std::string& message);

    DimseInvalidCommand(const DimseInvalidCommand& source);

    DimseInvalidCommand& operator=(const DimseInvalidCommand&) = delete;

    virtual ~DimseInvalidCommand() noexcept;
};


///
/// \brief Base class for the exceptions thrown by the UID generation classes.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API UIDGeneratorError: public std::runtime_error
{
public:
    explicit UIDGeneratorError(const std::string& message);

    UIDGeneratorError(const UIDGeneratorError& source);

    UIDGeneratorError& operator=(const UIDGeneratorError&) = delete;

    virtual ~UIDGeneratorError() noexcept;
};

///
/// \brief Exception thrown when the UIDGeneratorFactory class is trying to
///        retrieve a non registered UID generator.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API NonRegisteredUIDGenerator: public UIDGeneratorError
{
public:
    explicit NonRegisteredUIDGenerator(const std::string& message);

    NonRegisteredUIDGenerator(const NonRegisteredUIDGenerator& source);

    NonRegisteredUIDGenerator& operator=(const NonRegisteredUIDGenerator&) = delete;

    virtual ~NonRegisteredUIDGenerator() noexcept;
};

}

#endif // !defined(imebraExceptions__INCLUDED_)
