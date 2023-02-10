/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcNSError__INCLUDED_)
#define dicomheroObjcNSError__INCLUDED_

#include <dicomhero6/exceptions.h>
#import <dicomhero6_objc/dicomhero_exceptions.h>
#import <Foundation/Foundation.h>

#include <stdexcept>

namespace dicomhero
{
    void setNSError(const std::runtime_error& error, NSError** pError, Class errorClass);
}

#define OBJC_DICOMHERO_FUNCTION_START() try {

#define OBJC_DICOMHERO_FUNCTION_END() } \
    catch(dicomhero::LutCorruptedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroLutCorruptedError class]);\
    }\
    catch(dicomhero::LutError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroLutError class]);\
    }\
    catch(dicomhero::MissingGroupError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMissingGroupError class]);\
    }\
    catch(dicomhero::MissingTagError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMissingTagError class]);\
    }\
    catch(dicomhero::MissingBufferError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMissingBufferError class]);\
    }\
    catch(dicomhero::MissingItemError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMissingItemError class]);\
    }\
    catch(dicomhero::MissingDataElementError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMissingDataElementError class]);\
    }\
    catch(dicomhero::StreamReadError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroStreamReadError class]);\
    }\
    catch(dicomhero::StreamWriteError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroStreamWriteError class]);\
    }\
    catch(dicomhero::TCPConnectionRefused& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroTCPConnectionRefused class]);\
    }\
    catch(dicomhero::TCPAddressAlreadyInUse& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroTCPAddressAlreadyInUse class]);\
    }\
    catch(dicomhero::PermissionDeniedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroPermissionDeniedError class]);\
    }\
    catch(dicomhero::StreamOpenError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroStreamOpenError class]);\
    }\
    catch(dicomhero::AddressTryAgainError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAddressTryAgainError class]);\
    }\
    catch(dicomhero::AddressNoNameError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAddressNoNameError class]);\
    }\
    catch(dicomhero::AddressServiceNotSupportedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAddressServiceNotSupportedError class]);\
    }\
    catch(dicomhero::AddressError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAddressError class]);\
    }\
    catch(dicomhero::DictionaryUnknownTagError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDictionaryUnknownTagError class]);\
    }\
    catch(dicomhero::DictionaryUnknownDataTypeError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDictionaryUnknownDataTypeError class]);\
    }\
    catch(dicomhero::DictionaryError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDictionaryError class]);\
    }\
    catch(dicomhero::CharsetConversionNoTableError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCharsetConversionNoTableError class]);\
    }\
    catch(dicomhero::CharsetConversionNoSupportedTableError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCharsetConversionNoSupportedTableError class]);\
    }\
    catch(dicomhero::CharsetConversionCannotConvert& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCharsetConversionCannotConvert class]);\
    }\
    catch(dicomhero::CharsetConversionError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCharsetConversionError class]);\
    }\
    catch(dicomhero::CodecWrongFormatError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCodecWrongFormatError class]);\
    }\
    catch(dicomhero::CodecCorruptedFileError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCodecCorruptedFileError class]);\
    }\
    catch(dicomhero::CodecWrongTransferSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCodecWrongTransferSyntaxError class]);\
    }\
    catch(dicomhero::CodecImageTooBigError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCodecImageTooBigError class]);\
    }\
    catch(dicomhero::InvalidSequenceItemError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroInvalidSequenceItemError class]);\
    }\
    catch(dicomhero::DataHandlerConversionError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataHandlerConversionError class]);\
    }\
    catch(dicomhero::DataHandlerCorruptedBufferError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataHandlerCorruptedBufferError class]);\
    }\
    catch(dicomhero::DataHandlerInvalidDataError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataHandlerInvalidDataError class]);\
    }\
    catch(dicomhero::DataHandlerError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataHandlerError class]);\
    }\
    catch(dicomhero::DataSetDifferentFormatError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetDifferentFormatError class]);\
    }\
    catch(dicomhero::DataSetUnknownTransferSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetUnknownTransferSyntaxError class]);\
    }\
    catch(dicomhero::DataSetWrongFrameError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetWrongFrameError class]);\
    }\
    catch(dicomhero::DataSetImageDoesntExistError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetImageDoesntExistError class]);\
    }\
    catch(dicomhero::DataSetImagePaletteColorIsReadOnly& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetImagePaletteColorIsReadOnly class]);\
    }\
    catch(dicomhero::DataSetCorruptedOffsetTableError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetCorruptedOffsetTableError class]);\
    }\
    catch(dicomhero::DataSetError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDataSetError class]);\
    }\
    catch(dicomhero::DicomDirCircularReferenceError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDicomDirCircularReferenceError class]);\
    }\
    catch(dicomhero::DicomDirError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDicomDirError class]);\
    }\
    catch(dicomhero::ImageUnknownDepthError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroImageUnknownDepthError class]);\
    }\
    catch(dicomhero::ImageUnknownColorSpaceError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroImageUnknownColorSpaceError class]);\
    }\
    catch(dicomhero::ImageInvalidSizeError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroImageInvalidSizeError class]);\
    }\
    catch(dicomhero::ImageError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroImageError class]);\
    }\
    catch(dicomhero::TransformInvalidAreaError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroTransformInvalidAreaError class]);\
    }\
    catch(dicomhero::TransformDifferentHighBitError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroTransformDifferentHighBitError class]);\
    }\
    catch(dicomhero::ColorTransformWrongColorSpaceError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroColorTransformWrongColorSpaceError class]);\
    }\
    catch(dicomhero::ColorTransformsFactoryNoTransformError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroColorTransformsFactoryNoTransformError class]);\
    }\
    catch(dicomhero::ColorTransformsFactoryError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroColorTransformsFactoryError class]);\
    }\
    catch(dicomhero::TransformDifferentColorSpacesError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroTransformDifferentColorSpacesError class]);\
    }\
    catch(dicomhero::ColorTransformError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroColorTransformError class]);\
    }\
    catch(dicomhero::ModalityVOILUTError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroModalityVOILUTError class]);\
    }\
    catch(dicomhero::TransformError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroTransformError class]);\
    }\
    catch(dicomhero::StreamClosedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroStreamClosedError class]);\
    }\
    catch(dicomhero::StreamEOFError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroStreamEOFError class]);\
    }\
    catch(dicomhero::DicomCodecDepthLimitReachedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDicomCodecDepthLimitReachedError class]);\
    }\
    catch(dicomhero::DicomCodecError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDicomCodecError class]);\
    }\
    catch(dicomhero::JpegCodecCannotHandleSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroJpegCodecCannotHandleSyntaxError class]);\
    }\
    catch(dicomhero::JpegCodecError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroJpegCodecError class]);\
    }\
    catch(dicomhero::CodecError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroCodecError class]);\
    }\
    catch(dicomhero::MemorySizeError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMemorySizeError class]);\
    }\
    catch(dicomhero::MemoryError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroMemoryError class]);\
    }\
    catch(dicomhero::AcseCorruptedMessageError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseCorruptedMessageError class]);\
    }\
    catch(dicomhero::AcseNoTransferSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseNoTransferSyntaxError class]);\
    }\
    catch(dicomhero::AcsePresentationContextNotRequestedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcsePresentationContextNotRequestedError class]);\
    }\
    catch(dicomhero::AcseWrongRoleError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseWrongRoleError class]);\
    }\
    catch(dicomhero::AcseWrongResponseIdError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseWrongResponseIdError class]);\
    }\
    catch(dicomhero::AcseWrongCommandIdError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseWrongCommandIdError class]);\
    }\
    catch(dicomhero::AcseWrongIdError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseWrongIdError class]);\
    }\
    catch(dicomhero::AcseSCUNoReasonGivenError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCUNoReasonGivenError class]);\
    }\
    catch(dicomhero::AcseSCUApplicationContextNameNotSupportedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCUApplicationContextNameNotSupportedError class]);\
    }\
    catch(dicomhero::AcseSCUCallingAETNotRecognizedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCUCallingAETNotRecognizedError class]);\
    }\
    catch(dicomhero::AcseSCUCalledAETNotRecognizedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCUCalledAETNotRecognizedError class]);\
    }\
    catch(dicomhero::AcseSCPNoReasonGivenError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCPNoReasonGivenError class]);\
    }\
    catch(dicomhero::AcseSCPAcseProtocolVersionNotSupportedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCPAcseProtocolVersionNotSupportedError class]);\
    }\
    catch(dicomhero::AcseSCPPresentationReservedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCPPresentationReservedError class]);\
    }\
    catch(dicomhero::AcseSCPPresentationTemporaryCongestionError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCPPresentationTemporaryCongestionError class]);\
    }\
    catch(dicomhero::AcseSCPPresentationLocalLimitExcededError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseSCPPresentationLocalLimitExcededError class]);\
    }\
    catch(dicomhero::AcseTooManyOperationsPerformedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseTooManyOperationsPerformedError class]);\
    }\
    catch(dicomhero::AcseTooManyOperationsInvokedError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseTooManyOperationsInvokedError class]);\
    }\
    catch(dicomhero::AcseNoPayloadError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseNoPayloadError class]);\
    }\
    catch(dicomhero::AcseRejectedAssociationError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseRejectedAssociationError class]);\
    }\
    catch(dicomhero::AcseError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroAcseError class]);\
    }\
    catch(dicomhero::DimseInvalidCommand& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDimseInvalidCommand class]);\
    }\
    catch(dicomhero::DimseError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroDimseError class]);\
    }\
    catch(dicomhero::NonRegisteredUIDGenerator& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroNonRegisteredUIDGenerator class]);\
    }\
    catch(dicomhero::UIDGeneratorError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroUIDGeneratorError class]);\
    }\
    catch(const dicomhero::StreamError& e)\
    {\
        dicomhero::setNSError(e, pError, [DicomheroStreamError class]);\
    }


#define OBJC_DICOMHERO_FUNCTION_END_RETURN(returnValue) \
    OBJC_DICOMHERO_FUNCTION_END(); \
    return returnValue;

#endif // dicomheroObjcNSError__INCLUDED_
