#import <imebraobjc/imebra_exceptions.h>


@implementation ImebraLutError: NSError
@end

@implementation ImebraLutCorruptedError: NSError
@end

@implementation ImebraMissingDataElementError: NSError
@end

@implementation ImebraMissingGroupError: ImebraMissingDataElementError
@end

@implementation ImebraMissingTagError: ImebraMissingDataElementError
@end

@implementation ImebraMissingBufferError: ImebraMissingDataElementError
@end

@implementation ImebraMissingItemError: ImebraMissingDataElementError
@end

@implementation ImebraStreamError: NSError
@end

@implementation ImebraStreamOpenError : ImebraStreamError
@end

@implementation ImebraStreamReadError : ImebraStreamError
@end

@implementation ImebraStreamWriteError : ImebraStreamError
@end

@implementation ImebraTCPConnectionRefused: ImebraStreamOpenError
@end

@implementation ImebraTCPAddressAlreadyInUse: ImebraStreamOpenError
@end

@implementation ImebraPermissionDeniedError: NSError
@end

@implementation ImebraAddressError: NSError
@end

@implementation ImebraAddressTryAgainError: ImebraAddressError
@end

@implementation ImebraAddressNoNameError: ImebraAddressError
@end

@implementation ImebraAddressServiceNotSupportedError: ImebraAddressError
@end

@implementation ImebraDictionaryError: NSError
@end

@implementation ImebraDictionaryUnknownTagError: ImebraDictionaryError
@end

@implementation ImebraDictionaryUnknownDataTypeError: ImebraDictionaryError
@end

@implementation ImebraCharsetConversionError: NSError
@end

@implementation ImebraCharsetConversionNoTableError: ImebraCharsetConversionError
@end

@implementation ImebraCharsetConversionNoSupportedTableError: ImebraCharsetConversionError
@end

@implementation ImebraCharsetConversionCannotConvert: ImebraCharsetConversionError
@end

@implementation ImebraCodecError: NSError
@end

@implementation ImebraCodecWrongFormatError: ImebraCodecError
@end

@implementation ImebraCodecCorruptedFileError: ImebraCodecError
@end

@implementation ImebraCodecWrongTransferSyntaxError: ImebraCodecError
@end

@implementation ImebraCodecImageTooBigError: ImebraCodecError
@end

@implementation ImebraInvalidSequenceItemError: ImebraCodecError
@end

@implementation ImebraDataHandlerError: NSError
@end

@implementation ImebraDataHandlerConversionError: ImebraDataHandlerError
@end

@implementation ImebraDataHandlerCorruptedBufferError: ImebraDataHandlerError
@end

@implementation ImebraDataHandlerInvalidDataError: ImebraDataHandlerError
@end

@implementation ImebraDataSetError: NSError
@end

@implementation ImebraDataSetDifferentFormatError: ImebraDataSetError
@end

@implementation ImebraDataSetUnknownTransferSyntaxError: ImebraDataSetError
@end

@implementation ImebraDataSetWrongFrameError: ImebraDataSetError
@end

@implementation ImebraDataSetImageDoesntExistError: ImebraDataSetError
@end

@implementation ImebraDataSetImagePaletteColorIsReadOnly: ImebraDataSetError
@end

@implementation ImebraDataSetCorruptedOffsetTableError: ImebraDataSetError
@end

@implementation ImebraDicomDirError: NSError
@end

@implementation ImebraDicomDirCircularReferenceError: ImebraDicomDirError
@end

@implementation ImebraImageError: NSError
@end

@implementation ImebraImageUnknownDepthError: ImebraImageError
@end

@implementation ImebraImageUnknownColorSpaceError: ImebraImageError
@end

@implementation ImebraImageInvalidSizeError: ImebraImageError
@end

@implementation ImebraTransformError: NSError
@end

@implementation ImebraTransformInvalidAreaError: ImebraTransformError
@end

@implementation ImebraTransformDifferentHighBitError: ImebraTransformError
@end

@implementation ImebraColorTransformError: ImebraTransformError
@end

@implementation ImebraColorTransformWrongColorSpaceError: ImebraColorTransformError
@end

@implementation ImebraColorTransformsFactoryError: ImebraTransformError
@end

@implementation ImebraColorTransformsFactoryNoTransformError: ImebraColorTransformsFactoryError
@end

@implementation ImebraTransformDifferentColorSpacesError: ImebraTransformError
@end

@implementation ImebraStreamEOFError : ImebraStreamError
@end

@implementation ImebraStreamClosedError: ImebraStreamEOFError
@end

@implementation ImebraModalityVOILUTError: ImebraTransformError
@end

@implementation ImebraDicomCodecError: ImebraCodecError
@end

@implementation ImebraDicomCodecDepthLimitReachedError: ImebraDicomCodecError
@end

@implementation ImebraJpegCodecError: ImebraCodecError
@end

@implementation ImebraJpegCodecCannotHandleSyntaxError: ImebraJpegCodecError
@end

@implementation ImebraBadAlloc: NSError
@end

@implementation ImebraMemoryError: NSError
@end

@implementation ImebraMemorySizeError: ImebraMemoryError
@end

@implementation ImebraAcseError: NSError
@end

@implementation ImebraAcseCorruptedMessageError: ImebraAcseError
@end

@implementation ImebraAcseNoTransferSyntaxError: ImebraAcseError
@end

@implementation ImebraAcsePresentationContextNotRequestedError: ImebraAcseError
@end

@implementation ImebraAcseWrongRoleError: ImebraAcseError
@end

@implementation ImebraAcseWrongIdError: ImebraAcseError
@end

@implementation ImebraAcseWrongResponseIdError: ImebraAcseWrongIdError
@end

@implementation ImebraAcseWrongCommandIdError: ImebraAcseWrongIdError
@end

@implementation ImebraAcseRejectedAssociationError: ImebraAcseError
@end

@implementation ImebraAcseSCUNoReasonGivenError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCUApplicationContextNameNotSupportedError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCUCallingAETNotRecognizedError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCUCalledAETNotRecognizedError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCPNoReasonGivenError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCPAcseProtocolVersionNotSupportedError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCPPresentationReservedError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCPPresentationTemporaryCongestionError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseSCPPresentationLocalLimitExcededError: ImebraAcseRejectedAssociationError
@end

@implementation ImebraAcseTooManyOperationsPerformedError: ImebraAcseError
@end

@implementation ImebraAcseTooManyOperationsInvokedError: ImebraAcseError
@end

@implementation ImebraAcseNoPayloadError: ImebraAcseError
@end

@implementation ImebraDimseError: NSError
@end

@implementation ImebraDimseInvalidCommand: ImebraDimseError
@end

@implementation ImebraUIDGeneratorError: NSError
@end

@implementation ImebraNonRegisteredUIDGenerator: ImebraUIDGeneratorError
@end
