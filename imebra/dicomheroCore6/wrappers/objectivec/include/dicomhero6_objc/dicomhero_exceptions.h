/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcExceptions__INCLUDED_)
#define dicomheroObjcExceptions__INCLUDED_

#import <Foundation/Foundation.h>


@interface DicomheroLutError: NSError
@end

@interface DicomheroLutCorruptedError: NSError
@end

@interface DicomheroMissingDataElementError: NSError
@end

@interface DicomheroMissingGroupError: DicomheroMissingDataElementError
@end

@interface DicomheroMissingTagError: DicomheroMissingDataElementError
@end

@interface DicomheroMissingBufferError: DicomheroMissingDataElementError
@end

@interface DicomheroMissingItemError: DicomheroMissingDataElementError
@end

@interface DicomheroStreamError: NSError
@end

@interface DicomheroStreamOpenError : DicomheroStreamError
@end

@interface DicomheroStreamReadError : DicomheroStreamError
@end

@interface DicomheroStreamWriteError : DicomheroStreamError
@end

@interface DicomheroTCPConnectionRefused: DicomheroStreamOpenError
@end

@interface DicomheroTCPAddressAlreadyInUse: DicomheroStreamOpenError
@end

@interface DicomheroPermissionDeniedError: NSError
@end

@interface DicomheroAddressError: NSError
@end

@interface DicomheroAddressTryAgainError: DicomheroAddressError
@end

@interface DicomheroAddressNoNameError: DicomheroAddressError
@end

@interface DicomheroAddressServiceNotSupportedError: DicomheroAddressError
@end

@interface DicomheroDictionaryError: NSError
@end

@interface DicomheroDictionaryUnknownTagError: DicomheroDictionaryError
@end

@interface DicomheroDictionaryUnknownDataTypeError: DicomheroDictionaryError
@end

@interface DicomheroCharsetConversionError: NSError
@end

@interface DicomheroCharsetConversionNoTableError: DicomheroCharsetConversionError
@end

@interface DicomheroCharsetConversionNoSupportedTableError: DicomheroCharsetConversionError
@end

@interface DicomheroCharsetConversionCannotConvert: DicomheroCharsetConversionError
@end

@interface DicomheroCodecError: NSError
@end

@interface DicomheroCodecWrongFormatError: DicomheroCodecError
@end

@interface DicomheroCodecCorruptedFileError: DicomheroCodecError
@end

@interface DicomheroCodecWrongTransferSyntaxError: DicomheroCodecError
@end

@interface DicomheroCodecImageTooBigError: DicomheroCodecError
@end

@interface DicomheroInvalidSequenceItemError: DicomheroCodecError
@end

@interface DicomheroDataHandlerError: NSError
@end

@interface DicomheroDataHandlerConversionError: DicomheroDataHandlerError
@end

@interface DicomheroDataHandlerCorruptedBufferError: DicomheroDataHandlerError
@end

@interface DicomheroDataHandlerInvalidDataError: DicomheroDataHandlerError
@end

@interface DicomheroDataSetError: NSError
@end

@interface DicomheroDataSetDifferentFormatError: DicomheroDataSetError
@end

@interface DicomheroDataSetUnknownTransferSyntaxError: DicomheroDataSetError
@end

@interface DicomheroDataSetWrongFrameError: DicomheroDataSetError
@end

@interface DicomheroDataSetImageDoesntExistError: DicomheroDataSetError
@end

@interface DicomheroDataSetImagePaletteColorIsReadOnly: DicomheroDataSetError
@end

@interface DicomheroDataSetCorruptedOffsetTableError: DicomheroDataSetError
@end

@interface DicomheroDicomDirError: NSError
@end

@interface DicomheroDicomDirCircularReferenceError: DicomheroDicomDirError
@end

@interface DicomheroImageError: NSError
@end

@interface DicomheroImageUnknownDepthError: DicomheroImageError
@end

@interface DicomheroImageUnknownColorSpaceError: DicomheroImageError
@end

@interface DicomheroImageInvalidSizeError: DicomheroImageError
@end

@interface DicomheroTransformError: NSError
@end

@interface DicomheroTransformInvalidAreaError: DicomheroTransformError
@end

@interface DicomheroTransformDifferentHighBitError: DicomheroTransformError
@end

@interface DicomheroTransformDifferentColorSpacesError: DicomheroTransformError
@end

@interface DicomheroColorTransformError: DicomheroTransformError
@end

@interface DicomheroColorTransformWrongColorSpaceError: DicomheroColorTransformError
@end

@interface DicomheroColorTransformsFactoryError: DicomheroTransformError
@end

@interface DicomheroColorTransformsFactoryNoTransformError: DicomheroColorTransformsFactoryError
@end

@interface DicomheroStreamEOFError : DicomheroStreamError
@end

@interface DicomheroStreamClosedError: DicomheroStreamEOFError
@end

@interface DicomheroModalityVOILUTError: DicomheroTransformError
@end

@interface DicomheroDicomCodecError: DicomheroCodecError
@end

@interface DicomheroDicomCodecDepthLimitReachedError: DicomheroDicomCodecError
@end

@interface DicomheroJpegCodecError: DicomheroCodecError
@end

@interface DicomheroJpegCodecCannotHandleSyntaxError: DicomheroJpegCodecError
@end

@interface DicomheroBadAlloc: NSError
@end

@interface DicomheroMemoryError: NSError
@end

@interface DicomheroMemorySizeError: DicomheroMemoryError
@end

@interface DicomheroAcseError: NSError
@end

@interface DicomheroAcseCorruptedMessageError: DicomheroAcseError
@end

@interface DicomheroAcseNoTransferSyntaxError: DicomheroAcseError
@end

@interface DicomheroAcsePresentationContextNotRequestedError: DicomheroAcseError
@end

@interface DicomheroAcseWrongRoleError: DicomheroAcseError
@end

@interface DicomheroAcseWrongIdError: DicomheroAcseError
@end

@interface DicomheroAcseWrongResponseIdError: DicomheroAcseWrongIdError
@end

@interface DicomheroAcseWrongCommandIdError: DicomheroAcseWrongIdError
@end

@interface DicomheroAcseRejectedAssociationError: DicomheroAcseError
@end

@interface DicomheroAcseSCUNoReasonGivenError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCUApplicationContextNameNotSupportedError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCUCallingAETNotRecognizedError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCUCalledAETNotRecognizedError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCPNoReasonGivenError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCPAcseProtocolVersionNotSupportedError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCPPresentationReservedError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCPPresentationTemporaryCongestionError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseSCPPresentationLocalLimitExcededError: DicomheroAcseRejectedAssociationError
@end

@interface DicomheroAcseTooManyOperationsPerformedError: DicomheroAcseError
@end

@interface DicomheroAcseTooManyOperationsInvokedError: DicomheroAcseError
@end

@interface DicomheroAcseNoPayloadError: DicomheroAcseError
@end

@interface DicomheroDimseError: NSError
@end

@interface DicomheroDimseInvalidCommand: DicomheroDimseError
@end

@interface DicomheroUIDGeneratorError: NSError
@end

@interface DicomheroNonRegisteredUIDGenerator: DicomheroUIDGeneratorError
@end

#endif // dicomheroObjcExceptions__INCLUDED_
