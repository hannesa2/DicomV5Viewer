/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/exceptions.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{

std::string ExceptionsManager::getExceptionTrace() noexcept
{
    std::string message(implementation::exceptionsManagerGetter::getExceptionsManagerGetter().getExceptionsManager().getMessage());
    return message;
}

LutError::LutError(const std::string& message): std::runtime_error(message)
{}

LutError::LutError(const LutError& source): std::runtime_error(source)
{}

LutError::~LutError() noexcept
{}


LutCorruptedError::LutCorruptedError(const std::string& message): LutError(message)
{}

LutCorruptedError::LutCorruptedError(const LutCorruptedError& source): LutError(source)
{}

LutCorruptedError::~LutCorruptedError() noexcept
{}


MissingDataElementError::MissingDataElementError(const std::string& message): std::runtime_error(message)
{}

MissingDataElementError::MissingDataElementError(const MissingDataElementError &source): std::runtime_error(source)
{}

MissingDataElementError::~MissingDataElementError() noexcept
{}


MissingGroupError::MissingGroupError(const std::string& message): MissingDataElementError(message)
{}

MissingGroupError::MissingGroupError(const MissingGroupError &source): MissingDataElementError(source)
{}

MissingGroupError::~MissingGroupError() noexcept
{}


MissingTagError::MissingTagError(const std::string& message): MissingDataElementError(message)
{}

MissingTagError::MissingTagError(const MissingTagError &source): MissingDataElementError(source)
{}

MissingTagError::~MissingTagError() noexcept
{}


MissingBufferError::MissingBufferError(const std::string& message): MissingDataElementError(message)
{}

MissingBufferError::MissingBufferError(const MissingBufferError& source): MissingDataElementError(source)
{}

MissingBufferError::~MissingBufferError() noexcept
{}


MissingItemError::MissingItemError(const std::string& message): MissingDataElementError(message)
{}

MissingItemError::MissingItemError(const MissingItemError &source): MissingDataElementError(source)
{}

MissingItemError::~MissingItemError() noexcept
{}


StreamError::StreamError(const std::string& message): std::runtime_error(message)
{}

StreamError::StreamError(const StreamError &source): std::runtime_error(source)
{}

StreamError::~StreamError() noexcept
{}


StreamOpenError::StreamOpenError(const std::string& message): StreamError(message)
{}

StreamOpenError::StreamOpenError(const StreamOpenError &source): StreamError(source)
{}

StreamOpenError::~StreamOpenError() noexcept
{}


StreamReadError::StreamReadError(const std::string& message): StreamError(message)
{}

StreamReadError::StreamReadError(const StreamReadError &source): StreamError(source)
{}

StreamReadError::~StreamReadError() noexcept
{}


StreamWriteError::StreamWriteError(const std::string& message): StreamError(message)
{}

StreamWriteError::StreamWriteError(const StreamWriteError &source): StreamError(source)
{}

StreamWriteError::~StreamWriteError() noexcept
{}


DictionaryError::DictionaryError(const std::string& message): std::runtime_error(message)
{}

DictionaryError::DictionaryError(const DictionaryError &source): std::runtime_error(source)
{}

DictionaryError::~DictionaryError() noexcept
{}


DictionaryUnknownTagError::DictionaryUnknownTagError(const std::string &message): DictionaryError(message)
{}

DictionaryUnknownTagError::DictionaryUnknownTagError(const DictionaryUnknownTagError &source): DictionaryError(source)
{}

DictionaryUnknownTagError::~DictionaryUnknownTagError() noexcept
{}


DictionaryUnknownDataTypeError::DictionaryUnknownDataTypeError(const std::string &message): DictionaryError(message)
{}

DictionaryUnknownDataTypeError::DictionaryUnknownDataTypeError(const DictionaryUnknownDataTypeError &source): DictionaryError(source)
{}

DictionaryUnknownDataTypeError::~DictionaryUnknownDataTypeError() noexcept
{}


CharsetConversionError::CharsetConversionError(const std::string& message): std::runtime_error(message)
{}

CharsetConversionError::CharsetConversionError(const CharsetConversionError &source): std::runtime_error(source)
{}

CharsetConversionError::~CharsetConversionError() noexcept
{}


CharsetConversionNoTableError::CharsetConversionNoTableError(const std::string& message): CharsetConversionError(message)
{}

CharsetConversionNoTableError::CharsetConversionNoTableError(const CharsetConversionNoTableError &source): CharsetConversionError(source)
{}

CharsetConversionNoTableError::~CharsetConversionNoTableError() noexcept
{}


CharsetConversionNoSupportedTableError::CharsetConversionNoSupportedTableError(const std::string& message): CharsetConversionError(message)
{}

CharsetConversionNoSupportedTableError::CharsetConversionNoSupportedTableError(const CharsetConversionNoSupportedTableError &source): CharsetConversionError(source)
{}

CharsetConversionNoSupportedTableError::~CharsetConversionNoSupportedTableError() noexcept
{}


CharsetConversionCannotConvert::CharsetConversionCannotConvert(const std::string& message): CharsetConversionError(message)
{}

CharsetConversionCannotConvert::CharsetConversionCannotConvert(const CharsetConversionCannotConvert &source): CharsetConversionError(source)
{}

CharsetConversionCannotConvert::~CharsetConversionCannotConvert() noexcept
{}


CodecError::CodecError(const std::string& message): std::runtime_error(message)
{}

CodecError::CodecError(const CodecError &source): std::runtime_error(source)
{}

CodecError::~CodecError() noexcept
{}


CodecWrongFormatError::CodecWrongFormatError(const std::string& message): CodecError(message)
{}

CodecWrongFormatError::CodecWrongFormatError(const CodecWrongFormatError &source): CodecError(source)
{}

CodecWrongFormatError::~CodecWrongFormatError() noexcept
{}


CodecCorruptedFileError::CodecCorruptedFileError(const std::string& message): CodecError(message)
{}

CodecCorruptedFileError::CodecCorruptedFileError(const CodecCorruptedFileError &source): CodecError(source)
{}

CodecCorruptedFileError::~CodecCorruptedFileError() noexcept
{}


CodecWrongTransferSyntaxError::CodecWrongTransferSyntaxError(const std::string& message): CodecError(message)
{}

CodecWrongTransferSyntaxError::CodecWrongTransferSyntaxError(const CodecWrongTransferSyntaxError &source): CodecError(source)
{}

CodecWrongTransferSyntaxError::~CodecWrongTransferSyntaxError() noexcept
{}


CodecImageTooBigError::CodecImageTooBigError(const std::string& message): CodecError(message)
{}

CodecImageTooBigError::CodecImageTooBigError(const CodecImageTooBigError &source): CodecError(source)
{}

CodecImageTooBigError::~CodecImageTooBigError() noexcept
{}


InvalidSequenceItemError::InvalidSequenceItemError(const std::string &message): CodecError(message)
{}

InvalidSequenceItemError::InvalidSequenceItemError(const InvalidSequenceItemError &source): CodecError(source)
{}

InvalidSequenceItemError::~InvalidSequenceItemError() noexcept
{}


DataHandlerError::DataHandlerError(const std::string& message): std::runtime_error(message)
{}

DataHandlerError::DataHandlerError(const DataHandlerError &source): std::runtime_error(source)
{}

DataHandlerError::~DataHandlerError() noexcept
{}


DataHandlerConversionError::DataHandlerConversionError(const std::string &message): DataHandlerError(message)
{}

DataHandlerConversionError::DataHandlerConversionError(const DataHandlerConversionError &source): DataHandlerError(source)
{}

DataHandlerConversionError::~DataHandlerConversionError() noexcept
{}


DataHandlerCorruptedBufferError::DataHandlerCorruptedBufferError(const std::string &message): DataHandlerError(message)
{}

DataHandlerCorruptedBufferError::DataHandlerCorruptedBufferError(const DataHandlerCorruptedBufferError &source): DataHandlerError(source)
{}

DataHandlerCorruptedBufferError::~DataHandlerCorruptedBufferError() noexcept
{}


DataHandlerInvalidDataError::DataHandlerInvalidDataError(const std::string &message): DataHandlerError(message)
{}

DataHandlerInvalidDataError::DataHandlerInvalidDataError(const DataHandlerInvalidDataError &source): DataHandlerError(source)
{}

DataHandlerInvalidDataError::~DataHandlerInvalidDataError() noexcept
{}


DataSetError::DataSetError(const std::string& message): std::runtime_error(message)
{}

DataSetError::DataSetError(const DataSetError &source): std::runtime_error(source)
{}

DataSetError::~DataSetError() noexcept
{}


DataSetDifferentFormatError::DataSetDifferentFormatError(const std::string& message): DataSetError(message)
{}

DataSetDifferentFormatError::DataSetDifferentFormatError(const DataSetDifferentFormatError &source): DataSetError(source)
{}

DataSetDifferentFormatError::~DataSetDifferentFormatError() noexcept
{}


DataSetUnknownTransferSyntaxError::DataSetUnknownTransferSyntaxError(const std::string& message): DataSetError(message)
{}

DataSetUnknownTransferSyntaxError::DataSetUnknownTransferSyntaxError(const DataSetUnknownTransferSyntaxError &source): DataSetError(source)
{}

DataSetUnknownTransferSyntaxError::~DataSetUnknownTransferSyntaxError() noexcept
{}


DataSetWrongFrameError::DataSetWrongFrameError(const std::string& message): DataSetError(message)
{}

DataSetWrongFrameError::DataSetWrongFrameError(const DataSetWrongFrameError &source): DataSetError(source)
{}

DataSetWrongFrameError::~DataSetWrongFrameError() noexcept
{}


DataSetImageDoesntExistError::DataSetImageDoesntExistError(const std::string& message): DataSetError(message)
{}

DataSetImageDoesntExistError::DataSetImageDoesntExistError(const DataSetImageDoesntExistError &source): DataSetError(source)
{}

DataSetImageDoesntExistError::~DataSetImageDoesntExistError() noexcept
{}


DataSetImagePaletteColorIsReadOnly::DataSetImagePaletteColorIsReadOnly(const std::string &message): DataSetError(message)
{}

DataSetImagePaletteColorIsReadOnly::DataSetImagePaletteColorIsReadOnly(const DataSetImagePaletteColorIsReadOnly &source): DataSetError(source)
{}

DataSetImagePaletteColorIsReadOnly::~DataSetImagePaletteColorIsReadOnly() noexcept
{}


DataSetCorruptedOffsetTableError::DataSetCorruptedOffsetTableError(const std::string& message): DataSetError(message)
{}

DataSetCorruptedOffsetTableError::DataSetCorruptedOffsetTableError(const DataSetCorruptedOffsetTableError &source): DataSetError(source)
{}

DataSetCorruptedOffsetTableError::~DataSetCorruptedOffsetTableError() noexcept
{}


DicomDirError::DicomDirError(const std::string& message): std::runtime_error(message)
{}

DicomDirError::DicomDirError(const DicomDirError &source): std::runtime_error(source)
{}

DicomDirError::~DicomDirError() noexcept
{}


DicomDirCircularReferenceError::DicomDirCircularReferenceError(const std::string& message): DicomDirError(message)
{}

DicomDirCircularReferenceError::DicomDirCircularReferenceError(const DicomDirCircularReferenceError &source): DicomDirError(source)
{}

DicomDirCircularReferenceError::~DicomDirCircularReferenceError() noexcept
{}


DicomDirNoEntryError::DicomDirNoEntryError(const std::string& message): DicomDirError(message)
{}

DicomDirNoEntryError::DicomDirNoEntryError(const DicomDirNoEntryError &source): DicomDirError(source)
{}

DicomDirNoEntryError::~DicomDirNoEntryError() noexcept
{}


ImageError::ImageError(const std::string& message): std::runtime_error(message)
{}

ImageError::ImageError(const ImageError &source): std::runtime_error(source)
{}

ImageError::~ImageError() noexcept
{}


ImageUnknownDepthError::ImageUnknownDepthError(const std::string& message): ImageError(message)
{}

ImageUnknownDepthError::ImageUnknownDepthError(const ImageUnknownDepthError &source): ImageError(source)
{}

ImageUnknownDepthError::~ImageUnknownDepthError() noexcept
{}


ImageUnknownColorSpaceError::ImageUnknownColorSpaceError(const std::string& message): ImageError(message)
{}

ImageUnknownColorSpaceError::ImageUnknownColorSpaceError(const ImageUnknownColorSpaceError &source): ImageError(source)
{}

ImageUnknownColorSpaceError::~ImageUnknownColorSpaceError() noexcept
{}


ImageInvalidSizeError::ImageInvalidSizeError(const std::string& message): ImageError(message)
{}

ImageInvalidSizeError::ImageInvalidSizeError(const ImageInvalidSizeError &source): ImageError(source)
{}

ImageInvalidSizeError::~ImageInvalidSizeError() noexcept
{}


TransformError::TransformError(const std::string& message): std::runtime_error(message)
{}

TransformError::TransformError(const TransformError &source): std::runtime_error(source)
{}

TransformError::~TransformError() noexcept
{}


TransformInvalidAreaError::TransformInvalidAreaError(const std::string& message): TransformError(message)
{}

TransformInvalidAreaError::TransformInvalidAreaError(const TransformInvalidAreaError &source): TransformError(source)
{}

TransformInvalidAreaError::~TransformInvalidAreaError() noexcept
{}


TransformDifferentHighBitError::TransformDifferentHighBitError(const std::string &message): TransformError(message)
{}

TransformDifferentHighBitError::TransformDifferentHighBitError(const TransformDifferentHighBitError &source): TransformError(source)
{}

TransformDifferentHighBitError::~TransformDifferentHighBitError() noexcept
{}


ColorTransformError::ColorTransformError(const std::string& message): TransformError(message)
{}

ColorTransformError::ColorTransformError(const ColorTransformError &source): TransformError(source)
{}

ColorTransformError::~ColorTransformError() noexcept
{}


ColorTransformWrongColorSpaceError::ColorTransformWrongColorSpaceError(const std::string& message): ColorTransformError(message)
{}

ColorTransformWrongColorSpaceError::ColorTransformWrongColorSpaceError(const ColorTransformWrongColorSpaceError &source): ColorTransformError(source)
{}

ColorTransformWrongColorSpaceError::~ColorTransformWrongColorSpaceError() noexcept
{}


ColorTransformsFactoryError::ColorTransformsFactoryError(const std::string& message): TransformError(message)
{}

ColorTransformsFactoryError::ColorTransformsFactoryError(const ColorTransformsFactoryError &source): TransformError(source)
{}

ColorTransformsFactoryError::~ColorTransformsFactoryError() noexcept
{}


ColorTransformsFactoryNoTransformError::ColorTransformsFactoryNoTransformError(const std::string& message): ColorTransformsFactoryError(message)
{}

ColorTransformsFactoryNoTransformError::ColorTransformsFactoryNoTransformError(const ColorTransformsFactoryNoTransformError &source): ColorTransformsFactoryError(source)
{}

ColorTransformsFactoryNoTransformError::~ColorTransformsFactoryNoTransformError() noexcept
{}


TransformDifferentColorSpacesError::TransformDifferentColorSpacesError(const std::string& message): TransformError(message)
{}

TransformDifferentColorSpacesError::TransformDifferentColorSpacesError(const TransformDifferentColorSpacesError &source): TransformError(source)
{}

TransformDifferentColorSpacesError::~TransformDifferentColorSpacesError() noexcept
{}


StreamEOFError::StreamEOFError(const std::string& message): StreamError(message)
{}

StreamEOFError::StreamEOFError(const StreamEOFError &source): StreamError(source)
{}

StreamEOFError::~StreamEOFError() noexcept
{}


StreamClosedError::StreamClosedError(const std::string& message): StreamEOFError(message)
{}

StreamClosedError::StreamClosedError(const StreamClosedError &source): StreamEOFError(source)
{}

StreamClosedError::~StreamClosedError() noexcept
{}


TCPConnectionRefused::TCPConnectionRefused(const std::string& message): StreamOpenError(message)
{}

TCPConnectionRefused::TCPConnectionRefused(const TCPConnectionRefused &source): StreamOpenError(source)
{}

TCPConnectionRefused::~TCPConnectionRefused() noexcept
{}


TCPAddressAlreadyInUse::TCPAddressAlreadyInUse(const std::string& message): StreamOpenError(message)
{}

TCPAddressAlreadyInUse::TCPAddressAlreadyInUse(const TCPAddressAlreadyInUse &source): StreamOpenError(source)
{}

TCPAddressAlreadyInUse::~TCPAddressAlreadyInUse() noexcept
{}


PermissionDeniedError::PermissionDeniedError(const std::string& message): std::runtime_error(message)
{}

PermissionDeniedError::PermissionDeniedError(const PermissionDeniedError &source): std::runtime_error(source)
{}

PermissionDeniedError::~PermissionDeniedError() noexcept
{}


AddressError::AddressError(const std::string &message): std::runtime_error(message)
{}

AddressError::AddressError(const AddressError &source): std::runtime_error(source)
{}

AddressError::~AddressError() noexcept
{}


AddressTryAgainError::AddressTryAgainError(const std::string &message): AddressError(message)
{}

AddressTryAgainError::AddressTryAgainError(const AddressTryAgainError &source): AddressError(source)
{}

AddressTryAgainError::~AddressTryAgainError() noexcept
{}


AddressNoNameError::AddressNoNameError(const std::string& message): AddressError(message)
{}

AddressNoNameError::AddressNoNameError(const AddressNoNameError &source): AddressError(source)
{}

AddressNoNameError::~AddressNoNameError() noexcept
{}


AddressServiceNotSupportedError::AddressServiceNotSupportedError(const std::string &message): AddressError(message)
{}

AddressServiceNotSupportedError::AddressServiceNotSupportedError(const AddressServiceNotSupportedError &source): AddressError(source)
{}

AddressServiceNotSupportedError::~AddressServiceNotSupportedError() noexcept
{}


ModalityVOILUTError::ModalityVOILUTError(const std::string& message): TransformError(message)
{}

ModalityVOILUTError::ModalityVOILUTError(const ModalityVOILUTError &source): TransformError(source)
{}

ModalityVOILUTError::~ModalityVOILUTError() noexcept
{}


DicomCodecError::DicomCodecError(const std::string& message): CodecError(message)
{}

DicomCodecError::DicomCodecError(const DicomCodecError &source): CodecError(source)
{}

DicomCodecError::~DicomCodecError() noexcept
{}


DicomCodecDepthLimitReachedError::DicomCodecDepthLimitReachedError(const std::string&message): DicomCodecError(message)
{}

DicomCodecDepthLimitReachedError::DicomCodecDepthLimitReachedError(const DicomCodecDepthLimitReachedError &source): DicomCodecError(source)
{}

DicomCodecDepthLimitReachedError::~DicomCodecDepthLimitReachedError() noexcept
{}


JpegCodecError::JpegCodecError(const std::string& message): CodecError(message)
{}

JpegCodecError::JpegCodecError(const JpegCodecError &source): CodecError(source)
{}

JpegCodecError::~JpegCodecError() noexcept
{}


JpegCodecCannotHandleSyntaxError::JpegCodecCannotHandleSyntaxError(const std::string& message): JpegCodecError(message)
{}

JpegCodecCannotHandleSyntaxError::JpegCodecCannotHandleSyntaxError(const JpegCodecCannotHandleSyntaxError &source): JpegCodecError(source)
{}

JpegCodecCannotHandleSyntaxError::~JpegCodecCannotHandleSyntaxError() noexcept
{}


MemoryError::MemoryError(const std::string& message): std::runtime_error(message)
{}

MemoryError::MemoryError(const MemoryError &source): std::runtime_error(source)
{}

MemoryError::~MemoryError() noexcept
{}


MemorySizeError::MemorySizeError(const std::string& message): MemoryError(message)
{}

MemorySizeError::MemorySizeError(const MemorySizeError &source): MemoryError(source)
{}

MemorySizeError::~MemorySizeError() noexcept
{}


AcseError::AcseError(const std::string& message): std::runtime_error(message)
{}

AcseError::AcseError(const AcseError &source): std::runtime_error(source)
{}

AcseError::~AcseError() noexcept
{}


AcseCorruptedMessageError::AcseCorruptedMessageError(const std::string &message): AcseError(message)
{}

AcseCorruptedMessageError::AcseCorruptedMessageError(const AcseCorruptedMessageError &source): AcseError(source)
{}

AcseCorruptedMessageError::~AcseCorruptedMessageError() noexcept
{}


AcseNoTransferSyntaxError::AcseNoTransferSyntaxError(const std::string& message): AcseError(message)
{}

AcseNoTransferSyntaxError::AcseNoTransferSyntaxError(const AcseNoTransferSyntaxError &source): AcseError(source)
{}

AcseNoTransferSyntaxError::~AcseNoTransferSyntaxError() noexcept
{}


AcsePresentationContextNotRequestedError::AcsePresentationContextNotRequestedError(const std::string& message): AcseError(message)
{}

AcsePresentationContextNotRequestedError::AcsePresentationContextNotRequestedError(const AcsePresentationContextNotRequestedError &source): AcseError(source)
{}

AcsePresentationContextNotRequestedError::~AcsePresentationContextNotRequestedError() noexcept
{}


AcseWrongRoleError::AcseWrongRoleError(const std::string& message): AcseError(message)
{}

AcseWrongRoleError::AcseWrongRoleError(const AcseWrongRoleError &source): AcseError(source)
{}

AcseWrongRoleError::~AcseWrongRoleError() noexcept
{}


AcseWrongIdError::AcseWrongIdError(const std::string& message): AcseError(message)
{}

AcseWrongIdError::AcseWrongIdError(const AcseWrongIdError &source): AcseError(source)
{}

AcseWrongIdError::~AcseWrongIdError() noexcept
{}


AcseWrongResponseIdError::AcseWrongResponseIdError(const std::string& message): AcseWrongIdError(message)
{}

AcseWrongResponseIdError::AcseWrongResponseIdError(const AcseWrongResponseIdError &source): AcseWrongIdError(source)
{}

AcseWrongResponseIdError::~AcseWrongResponseIdError() noexcept
{}


AcseWrongCommandIdError::AcseWrongCommandIdError(const std::string& message): AcseWrongIdError(message)
{}

AcseWrongCommandIdError::AcseWrongCommandIdError(const AcseWrongCommandIdError &source): AcseWrongIdError(source)
{}

AcseWrongCommandIdError::~AcseWrongCommandIdError() noexcept
{}


AcseRejectedAssociationError::AcseRejectedAssociationError(const std::string& message, bool bPermanent):
    AcseError(message), m_bPermanent(bPermanent)
{}

AcseRejectedAssociationError::AcseRejectedAssociationError(const AcseRejectedAssociationError &source): AcseError(source), m_bPermanent(source.m_bPermanent)
{}

AcseRejectedAssociationError::~AcseRejectedAssociationError() noexcept
{}

bool AcseRejectedAssociationError::isPermanent() const
{
    return m_bPermanent;
}

bool AcseRejectedAssociationError::isTemporary() const
{
    return !m_bPermanent;
}


AcseSCUNoReasonGivenError::AcseSCUNoReasonGivenError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCUNoReasonGivenError::AcseSCUNoReasonGivenError(const AcseSCUNoReasonGivenError &source): AcseRejectedAssociationError(source)
{}

AcseSCUNoReasonGivenError::~AcseSCUNoReasonGivenError() noexcept
{}


AcseSCUApplicationContextNameNotSupportedError::AcseSCUApplicationContextNameNotSupportedError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCUApplicationContextNameNotSupportedError::AcseSCUApplicationContextNameNotSupportedError(const AcseSCUApplicationContextNameNotSupportedError &source): AcseRejectedAssociationError(source)
{}

AcseSCUApplicationContextNameNotSupportedError::~AcseSCUApplicationContextNameNotSupportedError() noexcept
{}


AcseSCUCallingAETNotRecognizedError::AcseSCUCallingAETNotRecognizedError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCUCallingAETNotRecognizedError::AcseSCUCallingAETNotRecognizedError(const AcseSCUCallingAETNotRecognizedError &source): AcseRejectedAssociationError(source)
{}

AcseSCUCallingAETNotRecognizedError::~AcseSCUCallingAETNotRecognizedError() noexcept
{}


AcseSCUCalledAETNotRecognizedError::AcseSCUCalledAETNotRecognizedError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCUCalledAETNotRecognizedError::AcseSCUCalledAETNotRecognizedError(const AcseSCUCalledAETNotRecognizedError &source): AcseRejectedAssociationError(source)
{}

AcseSCUCalledAETNotRecognizedError::~AcseSCUCalledAETNotRecognizedError() noexcept
{}


AcseSCPNoReasonGivenError::AcseSCPNoReasonGivenError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCPNoReasonGivenError::AcseSCPNoReasonGivenError(const AcseSCPNoReasonGivenError &source): AcseRejectedAssociationError(source)
{}

AcseSCPNoReasonGivenError::~AcseSCPNoReasonGivenError() noexcept
{}


AcseSCPAcseProtocolVersionNotSupportedError::AcseSCPAcseProtocolVersionNotSupportedError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCPAcseProtocolVersionNotSupportedError::AcseSCPAcseProtocolVersionNotSupportedError(const AcseSCPAcseProtocolVersionNotSupportedError &source): AcseRejectedAssociationError(source)
{}

AcseSCPAcseProtocolVersionNotSupportedError::~AcseSCPAcseProtocolVersionNotSupportedError() noexcept
{}


AcseSCPPresentationReservedError::AcseSCPPresentationReservedError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCPPresentationReservedError::AcseSCPPresentationReservedError(const AcseSCPPresentationReservedError &source): AcseRejectedAssociationError(source)
{}

AcseSCPPresentationReservedError::~AcseSCPPresentationReservedError() noexcept
{}


AcseSCPPresentationTemporaryCongestionError::AcseSCPPresentationTemporaryCongestionError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCPPresentationTemporaryCongestionError::AcseSCPPresentationTemporaryCongestionError(const AcseSCPPresentationTemporaryCongestionError &source): AcseRejectedAssociationError(source)
{}

AcseSCPPresentationTemporaryCongestionError::~AcseSCPPresentationTemporaryCongestionError() noexcept
{}


AcseSCPPresentationLocalLimitExcededError::AcseSCPPresentationLocalLimitExcededError(const std::string& message, bool bPermanent):
    AcseRejectedAssociationError(message, bPermanent)
{}

AcseSCPPresentationLocalLimitExcededError::AcseSCPPresentationLocalLimitExcededError(const AcseSCPPresentationLocalLimitExcededError &source): AcseRejectedAssociationError(source)
{}

AcseSCPPresentationLocalLimitExcededError::~AcseSCPPresentationLocalLimitExcededError() noexcept
{}


AcseTooManyOperationsPerformedError::AcseTooManyOperationsPerformedError(const std::string& message):
    AcseError(message)
{}

AcseTooManyOperationsPerformedError::AcseTooManyOperationsPerformedError(const AcseTooManyOperationsPerformedError &source): AcseError(source)
{}

AcseTooManyOperationsPerformedError::~AcseTooManyOperationsPerformedError() noexcept
{}


AcseTooManyOperationsInvokedError::AcseTooManyOperationsInvokedError(const std::string& message):
    AcseError(message)
{}

AcseTooManyOperationsInvokedError::AcseTooManyOperationsInvokedError(const AcseTooManyOperationsInvokedError &source): AcseError(source)
{}

AcseTooManyOperationsInvokedError::~AcseTooManyOperationsInvokedError() noexcept
{}


AcseNoPayloadError::AcseNoPayloadError(const std::string& message):
    AcseError(message)
{}

AcseNoPayloadError::AcseNoPayloadError(const AcseNoPayloadError &source): AcseError(source)
{}

AcseNoPayloadError::~AcseNoPayloadError() noexcept
{}


DimseError::DimseError(const std::string &message):
    std::runtime_error(message)
{}

DimseError::DimseError(const DimseError &source): std::runtime_error(source)
{}

DimseError::~DimseError() noexcept
{}


DimseInvalidCommand::DimseInvalidCommand(const std::string &message):
    DimseError(message)
{}

DimseInvalidCommand::DimseInvalidCommand(const DimseInvalidCommand &source): DimseError(source)
{}

DimseInvalidCommand::~DimseInvalidCommand() noexcept
{}


UIDGeneratorError::UIDGeneratorError(const std::string& message):
    std::runtime_error(message)
{}

UIDGeneratorError::UIDGeneratorError(const UIDGeneratorError &source): std::runtime_error(source)
{}

UIDGeneratorError::~UIDGeneratorError() noexcept
{}


NonRegisteredUIDGenerator::NonRegisteredUIDGenerator(const std::string& message):
    UIDGeneratorError(message)
{}

NonRegisteredUIDGenerator::NonRegisteredUIDGenerator(const NonRegisteredUIDGenerator &source): UIDGeneratorError(source)
{}

NonRegisteredUIDGenerator::~NonRegisteredUIDGenerator() noexcept
{}


DicomheroBadAlloc::DicomheroBadAlloc()
{}

DicomheroBadAlloc::DicomheroBadAlloc(const DicomheroBadAlloc &source): std::bad_alloc(source)
{}

DicomheroBadAlloc::~DicomheroBadAlloc() noexcept
{}

}
