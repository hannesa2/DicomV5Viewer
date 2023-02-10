#import <dicomhero6_objc/dicomhero_exceptions.h>


@implementation DicomheroLutError: NSError
@end

@implementation DicomheroLutCorruptedError: NSError
@end

@implementation DicomheroMissingDataElementError: NSError
@end

@implementation DicomheroMissingGroupError: DicomheroMissingDataElementError
@end

@implementation DicomheroMissingTagError: DicomheroMissingDataElementError
@end

@implementation DicomheroMissingBufferError: DicomheroMissingDataElementError
@end

@implementation DicomheroMissingItemError: DicomheroMissingDataElementError
@end

@implementation DicomheroStreamError: NSError
@end

@implementation DicomheroStreamOpenError : DicomheroStreamError
@end

@implementation DicomheroStreamReadError : DicomheroStreamError
@end

@implementation DicomheroStreamWriteError : DicomheroStreamError
@end

@implementation DicomheroTCPConnectionRefused: DicomheroStreamOpenError
@end

@implementation DicomheroTCPAddressAlreadyInUse: DicomheroStreamOpenError
@end

@implementation DicomheroPermissionDeniedError: NSError
@end

@implementation DicomheroAddressError: NSError
@end

@implementation DicomheroAddressTryAgainError: DicomheroAddressError
@end

@implementation DicomheroAddressNoNameError: DicomheroAddressError
@end

@implementation DicomheroAddressServiceNotSupportedError: DicomheroAddressError
@end

@implementation DicomheroDictionaryError: NSError
@end

@implementation DicomheroDictionaryUnknownTagError: DicomheroDictionaryError
@end

@implementation DicomheroDictionaryUnknownDataTypeError: DicomheroDictionaryError
@end

@implementation DicomheroCharsetConversionError: NSError
@end

@implementation DicomheroCharsetConversionNoTableError: DicomheroCharsetConversionError
@end

@implementation DicomheroCharsetConversionNoSupportedTableError: DicomheroCharsetConversionError
@end

@implementation DicomheroCharsetConversionCannotConvert: DicomheroCharsetConversionError
@end

@implementation DicomheroCodecError: NSError
@end

@implementation DicomheroCodecWrongFormatError: DicomheroCodecError
@end

@implementation DicomheroCodecCorruptedFileError: DicomheroCodecError
@end

@implementation DicomheroCodecWrongTransferSyntaxError: DicomheroCodecError
@end

@implementation DicomheroCodecImageTooBigError: DicomheroCodecError
@end

@implementation DicomheroInvalidSequenceItemError: DicomheroCodecError
@end

@implementation DicomheroDataHandlerError: NSError
@end

@implementation DicomheroDataHandlerConversionError: DicomheroDataHandlerError
@end

@implementation DicomheroDataHandlerCorruptedBufferError: DicomheroDataHandlerError
@end

@implementation DicomheroDataHandlerInvalidDataError: DicomheroDataHandlerError
@end

@implementation DicomheroDataSetError: NSError
@end

@implementation DicomheroDataSetDifferentFormatError: DicomheroDataSetError
@end

@implementation DicomheroDataSetUnknownTransferSyntaxError: DicomheroDataSetError
@end

@implementation DicomheroDataSetWrongFrameError: DicomheroDataSetError
@end

@implementation DicomheroDataSetImageDoesntExistError: DicomheroDataSetError
@end

@implementation DicomheroDataSetImagePaletteColorIsReadOnly: DicomheroDataSetError
@end

@implementation DicomheroDataSetCorruptedOffsetTableError: DicomheroDataSetError
@end

@implementation DicomheroDicomDirError: NSError
@end

@implementation DicomheroDicomDirCircularReferenceError: DicomheroDicomDirError
@end

@implementation DicomheroImageError: NSError
@end

@implementation DicomheroImageUnknownDepthError: DicomheroImageError
@end

@implementation DicomheroImageUnknownColorSpaceError: DicomheroImageError
@end

@implementation DicomheroImageInvalidSizeError: DicomheroImageError
@end

@implementation DicomheroTransformError: NSError
@end

@implementation DicomheroTransformInvalidAreaError: DicomheroTransformError
@end

@implementation DicomheroTransformDifferentHighBitError: DicomheroTransformError
@end

@implementation DicomheroColorTransformError: DicomheroTransformError
@end

@implementation DicomheroColorTransformWrongColorSpaceError: DicomheroColorTransformError
@end

@implementation DicomheroColorTransformsFactoryError: DicomheroTransformError
@end

@implementation DicomheroColorTransformsFactoryNoTransformError: DicomheroColorTransformsFactoryError
@end

@implementation DicomheroTransformDifferentColorSpacesError: DicomheroTransformError
@end

@implementation DicomheroStreamEOFError : DicomheroStreamError
@end

@implementation DicomheroStreamClosedError: DicomheroStreamEOFError
@end

@implementation DicomheroModalityVOILUTError: DicomheroTransformError
@end

@implementation DicomheroDicomCodecError: DicomheroCodecError
@end

@implementation DicomheroDicomCodecDepthLimitReachedError: DicomheroDicomCodecError
@end

@implementation DicomheroJpegCodecError: DicomheroCodecError
@end

@implementation DicomheroJpegCodecCannotHandleSyntaxError: DicomheroJpegCodecError
@end

@implementation DicomheroBadAlloc: NSError
@end

@implementation DicomheroMemoryError: NSError
@end

@implementation DicomheroMemorySizeError: DicomheroMemoryError
@end

@implementation DicomheroAcseError: NSError
@end

@implementation DicomheroAcseCorruptedMessageError: DicomheroAcseError
@end

@implementation DicomheroAcseNoTransferSyntaxError: DicomheroAcseError
@end

@implementation DicomheroAcsePresentationContextNotRequestedError: DicomheroAcseError
@end

@implementation DicomheroAcseWrongRoleError: DicomheroAcseError
@end

@implementation DicomheroAcseWrongIdError: DicomheroAcseError
@end

@implementation DicomheroAcseWrongResponseIdError: DicomheroAcseWrongIdError
@end

@implementation DicomheroAcseWrongCommandIdError: DicomheroAcseWrongIdError
@end

@implementation DicomheroAcseRejectedAssociationError: DicomheroAcseError
@end

@implementation DicomheroAcseSCUNoReasonGivenError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCUApplicationContextNameNotSupportedError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCUCallingAETNotRecognizedError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCUCalledAETNotRecognizedError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCPNoReasonGivenError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCPAcseProtocolVersionNotSupportedError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCPPresentationReservedError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCPPresentationTemporaryCongestionError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseSCPPresentationLocalLimitExcededError: DicomheroAcseRejectedAssociationError
@end

@implementation DicomheroAcseTooManyOperationsPerformedError: DicomheroAcseError
@end

@implementation DicomheroAcseTooManyOperationsInvokedError: DicomheroAcseError
@end

@implementation DicomheroAcseNoPayloadError: DicomheroAcseError
@end

@implementation DicomheroDimseError: NSError
@end

@implementation DicomheroDimseInvalidCommand: DicomheroDimseError
@end

@implementation DicomheroUIDGeneratorError: NSError
@end

@implementation DicomheroNonRegisteredUIDGenerator: DicomheroUIDGeneratorError
@end
