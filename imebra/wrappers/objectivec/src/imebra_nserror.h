/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcNSError__INCLUDED_)
#define imebraObjcNSError__INCLUDED_

#include <imebra/exceptions.h>
#import <imebraobjc/imebra_exceptions.h>
#import <Foundation/Foundation.h>

#include <stdexcept>

namespace imebra
{
    void setNSError(const std::runtime_error& error, NSError** pError, Class errorClass);
}

#define OBJC_IMEBRA_FUNCTION_START() try {

#define OBJC_IMEBRA_FUNCTION_END() } \
    catch(imebra::LutCorruptedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraLutCorruptedError class]);\
    }\
    catch(imebra::LutError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraLutError class]);\
    }\
    catch(imebra::MissingGroupError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMissingGroupError class]);\
    }\
    catch(imebra::MissingTagError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMissingTagError class]);\
    }\
    catch(imebra::MissingBufferError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMissingBufferError class]);\
    }\
    catch(imebra::MissingItemError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMissingItemError class]);\
    }\
    catch(imebra::MissingDataElementError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMissingDataElementError class]);\
    }\
    catch(imebra::StreamReadError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraStreamReadError class]);\
    }\
    catch(imebra::StreamWriteError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraStreamWriteError class]);\
    }\
    catch(imebra::TCPConnectionRefused& e)\
    {\
        imebra::setNSError(e, pError, [ImebraTCPConnectionRefused class]);\
    }\
    catch(imebra::TCPAddressAlreadyInUse& e)\
    {\
        imebra::setNSError(e, pError, [ImebraTCPAddressAlreadyInUse class]);\
    }\
    catch(imebra::PermissionDeniedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraPermissionDeniedError class]);\
    }\
    catch(imebra::StreamOpenError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraStreamOpenError class]);\
    }\
    catch(imebra::AddressTryAgainError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAddressTryAgainError class]);\
    }\
    catch(imebra::AddressNoNameError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAddressNoNameError class]);\
    }\
    catch(imebra::AddressServiceNotSupportedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAddressServiceNotSupportedError class]);\
    }\
    catch(imebra::AddressError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAddressError class]);\
    }\
    catch(imebra::DictionaryUnknownTagError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDictionaryUnknownTagError class]);\
    }\
    catch(imebra::DictionaryUnknownDataTypeError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDictionaryUnknownDataTypeError class]);\
    }\
    catch(imebra::DictionaryError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDictionaryError class]);\
    }\
    catch(imebra::CharsetConversionNoTableError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCharsetConversionNoTableError class]);\
    }\
    catch(imebra::CharsetConversionNoSupportedTableError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCharsetConversionNoSupportedTableError class]);\
    }\
    catch(imebra::CharsetConversionCannotConvert& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCharsetConversionCannotConvert class]);\
    }\
    catch(imebra::CharsetConversionError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCharsetConversionError class]);\
    }\
    catch(imebra::CodecWrongFormatError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCodecWrongFormatError class]);\
    }\
    catch(imebra::CodecCorruptedFileError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCodecCorruptedFileError class]);\
    }\
    catch(imebra::CodecWrongTransferSyntaxError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCodecWrongTransferSyntaxError class]);\
    }\
    catch(imebra::CodecImageTooBigError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCodecImageTooBigError class]);\
    }\
    catch(imebra::InvalidSequenceItemError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraInvalidSequenceItemError class]);\
    }\
    catch(imebra::DataHandlerConversionError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataHandlerConversionError class]);\
    }\
    catch(imebra::DataHandlerCorruptedBufferError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataHandlerCorruptedBufferError class]);\
    }\
    catch(imebra::DataHandlerInvalidDataError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataHandlerInvalidDataError class]);\
    }\
    catch(imebra::DataHandlerError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataHandlerError class]);\
    }\
    catch(imebra::DataSetDifferentFormatError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetDifferentFormatError class]);\
    }\
    catch(imebra::DataSetUnknownTransferSyntaxError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetUnknownTransferSyntaxError class]);\
    }\
    catch(imebra::DataSetWrongFrameError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetWrongFrameError class]);\
    }\
    catch(imebra::DataSetImageDoesntExistError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetImageDoesntExistError class]);\
    }\
    catch(imebra::DataSetImagePaletteColorIsReadOnly& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetImagePaletteColorIsReadOnly class]);\
    }\
    catch(imebra::DataSetCorruptedOffsetTableError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetCorruptedOffsetTableError class]);\
    }\
    catch(imebra::DataSetError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDataSetError class]);\
    }\
    catch(imebra::DicomDirCircularReferenceError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDicomDirCircularReferenceError class]);\
    }\
    catch(imebra::DicomDirError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDicomDirError class]);\
    }\
    catch(imebra::ImageUnknownDepthError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraImageUnknownDepthError class]);\
    }\
    catch(imebra::ImageUnknownColorSpaceError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraImageUnknownColorSpaceError class]);\
    }\
    catch(imebra::ImageInvalidSizeError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraImageInvalidSizeError class]);\
    }\
    catch(imebra::ImageError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraImageError class]);\
    }\
    catch(imebra::TransformInvalidAreaError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraTransformInvalidAreaError class]);\
    }\
    catch(imebra::TransformDifferentHighBitError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraTransformDifferentHighBitError class]);\
    }\
    catch(imebra::ColorTransformWrongColorSpaceError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraColorTransformWrongColorSpaceError class]);\
    }\
    catch(imebra::ColorTransformsFactoryNoTransformError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraColorTransformsFactoryNoTransformError class]);\
    }\
    catch(imebra::ColorTransformsFactoryError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraColorTransformsFactoryError class]);\
    }\
    catch(imebra::TransformDifferentColorSpacesError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraTransformDifferentColorSpacesError class]);\
    }\
    catch(imebra::ColorTransformError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraColorTransformError class]);\
    }\
    catch(imebra::ModalityVOILUTError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraModalityVOILUTError class]);\
    }\
    catch(imebra::TransformError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraTransformError class]);\
    }\
    catch(imebra::StreamClosedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraStreamClosedError class]);\
    }\
    catch(imebra::StreamEOFError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraStreamEOFError class]);\
    }\
    catch(imebra::DicomCodecDepthLimitReachedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDicomCodecDepthLimitReachedError class]);\
    }\
    catch(imebra::DicomCodecError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDicomCodecError class]);\
    }\
    catch(imebra::JpegCodecCannotHandleSyntaxError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraJpegCodecCannotHandleSyntaxError class]);\
    }\
    catch(imebra::JpegCodecError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraJpegCodecError class]);\
    }\
    catch(imebra::CodecError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraCodecError class]);\
    }\
    catch(imebra::MemorySizeError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMemorySizeError class]);\
    }\
    catch(imebra::MemoryError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraMemoryError class]);\
    }\
    catch(imebra::AcseCorruptedMessageError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseCorruptedMessageError class]);\
    }\
    catch(imebra::AcseNoTransferSyntaxError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseNoTransferSyntaxError class]);\
    }\
    catch(imebra::AcsePresentationContextNotRequestedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcsePresentationContextNotRequestedError class]);\
    }\
    catch(imebra::AcseWrongRoleError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseWrongRoleError class]);\
    }\
    catch(imebra::AcseWrongResponseIdError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseWrongResponseIdError class]);\
    }\
    catch(imebra::AcseWrongCommandIdError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseWrongCommandIdError class]);\
    }\
    catch(imebra::AcseWrongIdError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseWrongIdError class]);\
    }\
    catch(imebra::AcseSCUNoReasonGivenError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCUNoReasonGivenError class]);\
    }\
    catch(imebra::AcseSCUApplicationContextNameNotSupportedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCUApplicationContextNameNotSupportedError class]);\
    }\
    catch(imebra::AcseSCUCallingAETNotRecognizedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCUCallingAETNotRecognizedError class]);\
    }\
    catch(imebra::AcseSCUCalledAETNotRecognizedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCUCalledAETNotRecognizedError class]);\
    }\
    catch(imebra::AcseSCPNoReasonGivenError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCPNoReasonGivenError class]);\
    }\
    catch(imebra::AcseSCPAcseProtocolVersionNotSupportedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCPAcseProtocolVersionNotSupportedError class]);\
    }\
    catch(imebra::AcseSCPPresentationReservedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCPPresentationReservedError class]);\
    }\
    catch(imebra::AcseSCPPresentationTemporaryCongestionError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCPPresentationTemporaryCongestionError class]);\
    }\
    catch(imebra::AcseSCPPresentationLocalLimitExcededError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseSCPPresentationLocalLimitExcededError class]);\
    }\
    catch(imebra::AcseTooManyOperationsPerformedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseTooManyOperationsPerformedError class]);\
    }\
    catch(imebra::AcseTooManyOperationsInvokedError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseTooManyOperationsInvokedError class]);\
    }\
    catch(imebra::AcseNoPayloadError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseNoPayloadError class]);\
    }\
    catch(imebra::AcseRejectedAssociationError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseRejectedAssociationError class]);\
    }\
    catch(imebra::AcseError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraAcseError class]);\
    }\
    catch(imebra::DimseInvalidCommand& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDimseInvalidCommand class]);\
    }\
    catch(imebra::DimseError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraDimseError class]);\
    }\
    catch(imebra::NonRegisteredUIDGenerator& e)\
    {\
        imebra::setNSError(e, pError, [ImebraNonRegisteredUIDGenerator class]);\
    }\
    catch(imebra::UIDGeneratorError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraUIDGeneratorError class]);\
    }\
    catch(const imebra::StreamError& e)\
    {\
        imebra::setNSError(e, pError, [ImebraStreamError class]);\
    }


#define OBJC_IMEBRA_FUNCTION_END_RETURN(returnValue) \
    OBJC_IMEBRA_FUNCTION_END(); \
    return returnValue;

#endif // imebraObjcNSError__INCLUDED_
