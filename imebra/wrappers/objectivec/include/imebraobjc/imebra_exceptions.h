/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcExceptions__INCLUDED_)
#define imebraObjcExceptions__INCLUDED_

#import <Foundation/Foundation.h>


@interface ImebraLutError: NSError
@end

@interface ImebraLutCorruptedError: NSError
@end

@interface ImebraMissingDataElementError: NSError
@end

@interface ImebraMissingGroupError: ImebraMissingDataElementError
@end

@interface ImebraMissingTagError: ImebraMissingDataElementError
@end

@interface ImebraMissingBufferError: ImebraMissingDataElementError
@end

@interface ImebraMissingItemError: ImebraMissingDataElementError
@end

@interface ImebraStreamError: NSError
@end

@interface ImebraStreamOpenError : ImebraStreamError
@end

@interface ImebraStreamReadError : ImebraStreamError
@end

@interface ImebraStreamWriteError : ImebraStreamError
@end

@interface ImebraTCPConnectionRefused: ImebraStreamOpenError
@end

@interface ImebraTCPAddressAlreadyInUse: ImebraStreamOpenError
@end

@interface ImebraPermissionDeniedError: NSError
@end

@interface ImebraAddressError: NSError
@end

@interface ImebraAddressTryAgainError: ImebraAddressError
@end

@interface ImebraAddressNoNameError: ImebraAddressError
@end

@interface ImebraAddressServiceNotSupportedError: ImebraAddressError
@end

@interface ImebraDictionaryError: NSError
@end

@interface ImebraDictionaryUnknownTagError: ImebraDictionaryError
@end

@interface ImebraDictionaryUnknownDataTypeError: ImebraDictionaryError
@end

@interface ImebraCharsetConversionError: NSError
@end

@interface ImebraCharsetConversionNoTableError: ImebraCharsetConversionError
@end

@interface ImebraCharsetConversionNoSupportedTableError: ImebraCharsetConversionError
@end

@interface ImebraCharsetConversionCannotConvert: ImebraCharsetConversionError
@end

@interface ImebraCodecError: NSError
@end

@interface ImebraCodecWrongFormatError: ImebraCodecError
@end

@interface ImebraCodecCorruptedFileError: ImebraCodecError
@end

@interface ImebraCodecWrongTransferSyntaxError: ImebraCodecError
@end

@interface ImebraCodecImageTooBigError: ImebraCodecError
@end

@interface ImebraInvalidSequenceItemError: ImebraCodecError
@end

@interface ImebraDataHandlerError: NSError
@end

@interface ImebraDataHandlerConversionError: ImebraDataHandlerError
@end

@interface ImebraDataHandlerCorruptedBufferError: ImebraDataHandlerError
@end

@interface ImebraDataHandlerInvalidDataError: ImebraDataHandlerError
@end

@interface ImebraDataSetError: NSError
@end

@interface ImebraDataSetDifferentFormatError: ImebraDataSetError
@end

@interface ImebraDataSetUnknownTransferSyntaxError: ImebraDataSetError
@end

@interface ImebraDataSetWrongFrameError: ImebraDataSetError
@end

@interface ImebraDataSetImageDoesntExistError: ImebraDataSetError
@end

@interface ImebraDataSetImagePaletteColorIsReadOnly: ImebraDataSetError
@end

@interface ImebraDataSetCorruptedOffsetTableError: ImebraDataSetError
@end

@interface ImebraDicomDirError: NSError
@end

@interface ImebraDicomDirCircularReferenceError: ImebraDicomDirError
@end

@interface ImebraImageError: NSError
@end

@interface ImebraImageUnknownDepthError: ImebraImageError
@end

@interface ImebraImageUnknownColorSpaceError: ImebraImageError
@end

@interface ImebraImageInvalidSizeError: ImebraImageError
@end

@interface ImebraTransformError: NSError
@end

@interface ImebraTransformInvalidAreaError: ImebraTransformError
@end

@interface ImebraTransformDifferentHighBitError: ImebraTransformError
@end

@interface ImebraTransformDifferentColorSpacesError: ImebraTransformError
@end

@interface ImebraColorTransformError: ImebraTransformError
@end

@interface ImebraColorTransformWrongColorSpaceError: ImebraColorTransformError
@end

@interface ImebraColorTransformsFactoryError: ImebraTransformError
@end

@interface ImebraColorTransformsFactoryNoTransformError: ImebraColorTransformsFactoryError
@end

@interface ImebraStreamEOFError : ImebraStreamError
@end

@interface ImebraStreamClosedError: ImebraStreamEOFError
@end

@interface ImebraModalityVOILUTError: ImebraTransformError
@end

@interface ImebraDicomCodecError: ImebraCodecError
@end

@interface ImebraDicomCodecDepthLimitReachedError: ImebraDicomCodecError
@end

@interface ImebraJpegCodecError: ImebraCodecError
@end

@interface ImebraJpegCodecCannotHandleSyntaxError: ImebraJpegCodecError
@end

@interface ImebraBadAlloc: NSError
@end

@interface ImebraMemoryError: NSError
@end

@interface ImebraMemorySizeError: ImebraMemoryError
@end

@interface ImebraAcseError: NSError
@end

@interface ImebraAcseCorruptedMessageError: ImebraAcseError
@end

@interface ImebraAcseNoTransferSyntaxError: ImebraAcseError
@end

@interface ImebraAcsePresentationContextNotRequestedError: ImebraAcseError
@end

@interface ImebraAcseWrongRoleError: ImebraAcseError
@end

@interface ImebraAcseWrongIdError: ImebraAcseError
@end

@interface ImebraAcseWrongResponseIdError: ImebraAcseWrongIdError
@end

@interface ImebraAcseWrongCommandIdError: ImebraAcseWrongIdError
@end

@interface ImebraAcseRejectedAssociationError: ImebraAcseError
@end

@interface ImebraAcseSCUNoReasonGivenError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCUApplicationContextNameNotSupportedError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCUCallingAETNotRecognizedError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCUCalledAETNotRecognizedError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCPNoReasonGivenError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCPAcseProtocolVersionNotSupportedError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCPPresentationReservedError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCPPresentationTemporaryCongestionError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseSCPPresentationLocalLimitExcededError: ImebraAcseRejectedAssociationError
@end

@interface ImebraAcseTooManyOperationsPerformedError: ImebraAcseError
@end

@interface ImebraAcseTooManyOperationsInvokedError: ImebraAcseError
@end

@interface ImebraAcseNoPayloadError: ImebraAcseError
@end

@interface ImebraDimseError: NSError
@end

@interface ImebraDimseInvalidCommand: ImebraDimseError
@end

@interface ImebraUIDGeneratorError: NSError
@end

@interface ImebraNonRegisteredUIDGenerator: ImebraUIDGeneratorError
@end

#endif // imebraObjcExceptions__INCLUDED_
