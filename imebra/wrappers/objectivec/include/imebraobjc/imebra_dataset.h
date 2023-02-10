/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDataSet__INCLUDED_)
#define imebraObjcDataSet__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

@class ImebraImage;
@class ImebraAge;
@class ImebraDate;
@class ImebraPatientName;
@class ImebraLUT;
@class ImebraReadingDataHandler;
@class ImebraWritingDataHandler;
@class ImebraReadingDataHandlerNumeric;
@class ImebraWritingDataHandlerNumeric;
@class ImebraTag;
@class ImebraMutableTag;
@class ImebraTagId;
@class ImebraVOIDescription;
@class ImebraStreamReader;
@class ImebraStreamWriter;
@class ImebraOverlay;

/// \enum ImebraTagType
/// \brief Enumerates the DICOM VRs (data types).
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, ImebraTagType)
{
    ImebraTagTypeAE = 0x4145, ///< Application Entity
    ImebraTagTypeAS = 0x4153, ///< Age String
    ImebraTagTypeAT = 0x4154, ///< Attribute Tag
    ImebraTagTypeCS = 0x4353, ///< Code String
    ImebraTagTypeDA = 0x4441, ///< Date
    ImebraTagTypeDS = 0x4453, ///< Decimal String
    ImebraTagTypeDT = 0x4454, ///< Date Time
    ImebraTagTypeFL = 0x464c, ///< Floating Point Single
    ImebraTagTypeFD = 0x4644, ///< Floating Point Double
    ImebraTagTypeIS = 0x4953, ///< Integer String
    ImebraTagTypeLO = 0x4c4f, ///< Long String
    ImebraTagTypeLT = 0x4c54, ///< Long Text
    ImebraTagTypeOB = 0x4f42, ///< Other Byte String
    ImebraTagTypeSB = 0x5342, ///< Non standard. Used internally for signed bytes
    ImebraTagTypeOD = 0x4f44, ///< Other Double String
    ImebraTagTypeOF = 0x4f46, ///< Other Float String
    ImebraTagTypeOL = 0x4f4c, ///< Other Long String
    ImebraTagTypeOV = 0x4f56, ///< Other Very long
    ImebraTagTypeOW = 0x4f57, ///< Other Word String
    ImebraTagTypePN = 0x504e, ///< Person Name
    ImebraTagTypeSH = 0x5348, ///< Short String
    ImebraTagTypeSL = 0x534c, ///< Signed Long
    ImebraTagTypeSQ = 0x5351, ///< Sequence of Items
    ImebraTagTypeSS = 0x5353, ///< Signed Short
    ImebraTagTypeST = 0x5354, ///< Short Text
    ImebraTagTypeSV = 0x5356, ///< Signed Very Long
    ImebraTagTypeTM = 0x544d, ///< Time
    ImebraTagTypeUC = 0x5543, ///< Unlimited characters
    ImebraTagTypeUI = 0x5549, ///< Unique Identifier
    ImebraTagTypeUL = 0x554c, ///< Unsigned Long
    ImebraTagTypeUN = 0x554e, ///< Unknown
    ImebraTagTypeUR = 0x5552, ///< Unified Resource Identifier
    ImebraTagTypeUS = 0x5553, ///< Unsigned Short
    ImebraTagTypeUT = 0x5554, ///< Unlimited Text
    ImebraTagTypeUV = 0x5556  ///< Unsigned Very Long
};

///
/// \enum ImebraImageQuality
/// \brief This enumeration specifies the quality of the compressed image
///        when a lossy compression format is used.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned int, ImebraImageQuality)
{
    ImebraImageQualityVeryHigh = 0,      ///< the image is saved with very high quality. No subsampling is performed and no quantization
    ImebraImageQualityHigh = 100,        ///< the image is saved with high quality. No subsampling is performed. Quantization ratios are low
    ImebraImageQualityAboveMedium = 200, ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are low
    ImebraImageQualityMedium = 300,      ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are medium
    ImebraImageQualityBelowMedium = 400, ///< the image is saved in medium quality. Horizontal and vertical subsampling are applied. Quantization ratios are medium
    ImebraImageQualityLow = 500,         ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are higher than the ratios used in the belowMedium quality
    ImebraImageQualityVeryLow = 600      ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are high
};


///
///  \brief This class represents an immutable DICOM dataset.
///
/// The information it contains is organized into groups and each group may
/// contain several tags.
///
/// You can create a ImebraDataSet from a DICOM file by using the
/// ImebraCodecFactory::load() function:
///
/// \code
/// NSError* error = nil;
/// ImebraDataSet* pDataSet = [ImebraCodecFactory load:@"dicomFile.dcm" error:&error];
/// \endcode
///
/// To retrieve the DataSet's content, use one of the following methods which
/// give direct access to the tags' values:
/// - getImage()
/// - getImageApplyModalityTransform()
/// - getSequenceItem()
/// - getInt64()
/// - getInt32()
/// - getInt16()
/// - getInt8()
/// - getUint64()
/// - getUint32()
/// - getUint16()
/// - getUint8()
/// - getDouble()
/// - getFloat()
/// - getString()
/// - getUnicodeString()
/// - getAge()
/// - getDate()
/// - getPatient()
///
/// In alternative, you can first retrieve a ImebraReadingDataHandler with
/// getReadingDataHandler() and then access the tag's content via the handler.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraDataSet: NSObject

{
    @public
    define_imebra_object_holder(DataSet);

}

    -(id)initWithImebraDataSet:define_imebra_parameter(DataSet);

    -(void)dealloc;

    /// \brief Returns a list of all the tags stored in the DataSet, ordered by
    ///        group and tag ID.
    ///
    /// \return an NSArray containing an ordered list of ImebraTagId objects
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSArray*)getTags;

    /// \brief Retrieve the Tag with the specified ID.
    ///
    /// \param tagId  the ID of the tag to retrieve
    /// \param pError set if an error occurs
    /// \return the Tag with the specified ID
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraTag*) getTag:(ImebraTagId*)tagId error:(NSError**)pError;

    /// \brief Retrieve an image from the dataset.
    ///
    /// Images should be retrieved in order (first frame 0, then frame 1, then
    /// frame 2 and so on).
    /// Images can be retrieved also in random order but this introduces
    /// performance penalties.
    ///
    /// Set pError and returns nil if the requested image does not exist.
    ///
    /// \note Images retrieved from the ImebraDataSet should be processed by the
    ///       ImebraModalityVOILUT transform, which converts the modality-specific
    ///       pixel values to values that the application can understand. Consider
    ///       using getImageApplyModalityTransform() to retrieve the image already
    ///       processed by ImebraModalityVOILUT.
    ///
    /// \param frameNumber the frame to retrieve (the first frame is 0)
    /// \param pError      a pointer to a NSError pointer which is set when an
    ///                    error occurs
    /// \return an ImebraImage object containing the decompressed image
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraImage*) getImage:(unsigned int) frameNumber error:(NSError**)pError;

    /// \brief Retrieve one of the DICOM overlays.
    ///
    /// Set pError to ImebraMissingGroupError if the requested overlay does not
    ///  exist.
    ///
    /// \param overlayNumber the number of the overlay to retrieve (0...127)
    /// \return the requested overlay
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraOverlay*) getOverlay:(unsigned int) overlayNumber error:(NSError**)pError;

    /// \brief Retrieve an image from the dataset and if necessary process it with
    ///        ImebraModalityVOILUT before returning it.
    ///
    /// Images should be retrieved in order (first frame 0, then frame 1, then
    ///  frame 2 and so on).
    /// Images can be retrieved also in random order but this introduces
    ///  performance penalties.
    ///
    /// Set pError and returns nil if the requested image does not exist.
    ///
    /// \param frameNumber the frame to retrieve (the first frame is 0)
    /// \param pError      a pointer to a NSError pointer which is set when an
    ///                    error occurs
    /// \return an ImebraImage object containing the decompressed image
    ///         processed by ImebraModalityVOILUT (if present)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraImage*) getImageApplyModalityTransform:(unsigned int) frameNumber error:(NSError**)pError;

    /// \brief Return the list of VOI settings stored in the DataSet.
    ///
    /// Each VOI setting includes the center & width values that can be used with
    /// the VOILUT transform to highlight different parts of an Image.
    ///
    /// If the VOI/LUT information is stored in a functional group, then first use
    /// getFunctionalGroupDataSet() to retrieve the sequence item containing the
    /// VOI/LUT information, then call getVOIs() on the returned dataset.
    ///
    /// \param pError      a pointer to a NSError pointer which is set when an
    ///                    error occurs
    /// \return an NSArray containing a list of ImebraVOIDescription objects
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSArray*) getVOIs:(NSError**)pError;

    /// \brief In case the dataset uses functional groups to store imaging
    ///        information, then this method returns the sequence item containing
    ///        imaging information for a specific frame.
    ///
    /// The method looks first for a frame specific functional group sequence item,
    /// then for a common functional group sequence item if the specific one is
    /// missing.
    ///
    /// Throws MissingTagError is the dataset does not contain a functional
    /// group sequence.
    ///
    /// \param frameNumber the frame number for which the functional group sequence
    ///                    item is required
    /// \param pError a pointer to a NSError pointer which is set when an
    ///                error occurs
    /// \return the functional group sequence item for the requested frame.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*) getFunctionalGroupDataSet:(unsigned int)frameNumber error:(NSError**)pError;

    /// \brief Get a StreamReader connected to a buffer's data.
    ///
    /// \param pTagId     the tag's id for which the StreamReader is required
    /// \param bufferId   the id of the buffer for which the StreamReader is
    ///                    required. This parameter is usually 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return           the streamReader connected to the buffer's data.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraStreamReader*) getStreamReader:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

    /// \brief Retrieve a sequence item stored in a tag.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// If the specified tag does not contain the specified sequence item then
    ///  set pError to ImebraMissingItemError.
    ///
    /// \param pTagId the tag's id containing the sequence item
    /// \param itemId the sequence item to retrieve. The first item has an Id = 0
    /// \param pError a pointer to a NSError pointer which is set when an
    ///                error occurs
    /// \return the requested sequence item
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*) getSequenceItem:(ImebraTagId*)pTagId item:(unsigned int)itemId error:(NSError**)pError;

    /// \brief Retrieve a ImebraLUT stored in a sequence item.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// If the specified tag does not contain the specified sequence item then
    ///  set pError to ImebraMissingItemError.
    ///
    /// \param pTagId the tag's id containing the sequence that stores the LUTs
    /// \param itemId the sequence item to retrieve. The first item has an Id = 0
    /// \param pError a pointer to a NSError pointer which is set when an
    ///                error occurs
    /// \return the LUT stored in the requested sequence item
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraLUT*) getLUT:(ImebraTagId*)pTagId item:(unsigned int)itemId error:(NSError**)pError;

    /// \brief Retrieve an ImebraReadingDataHandler object connected to a
    ///        specific tag's buffer.
    ///
    /// If the specified tag does not exist then sets pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// If the specified tag does not contain the specified buffer item then
    ///  sets pError to ImebraMissingBufferError.
    ///
    /// \param tagId    the tag's id containing the requested buffer
    /// \param bufferId the buffer to connect to the ReadingDataHandler object.
    ///                 The first buffer has an Id = 0
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return an ImebraReadingDataHandler object connected to the requested
    ///         tag's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandler*) getReadingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

    /// \brief Retrieve a ImebraReadingDataHandlerNumeric object connected to a
    ///        specific tag's numeric buffer.
    ///
    /// If the tag's VR is not a numeric type then throws std::bad_cast.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// If the specified tag does not contain the specified buffer item then
    /// set pError to ImebraMissingItemError.
    ///
    /// \param tagId    the tag's id containing the requested buffer
    /// \param bufferId the buffer to connect to the ReadingDataHandler object.
    ///                 The first buffer has an Id = 0
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return a ImebraReadingDataHandlerNumeric object connected to the
    ///         requested tag's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerNumeric:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

    /// \brief Retrieve a ImebraReadingDataHandlerNumeric object connected to a
    ///        specific tag's buffer, no matter what the tag's data type.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// If the specified tag does not contain the specified buffer item then
    /// set pError to ImebraMissingItemError.
    ///
    /// \param tagId    the tag's id containing the requested buffer
    /// \param bufferId the buffer to connect to the ReadingDataHandler object.
    ///                 The first buffer has an Id = 0
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return a ImebraReadingDataHandlerNumeric object connected to the
    ///         requested tag's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerRaw:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

    /// \brief Retrieve a tag's value as signed very long integer (64 bit).
    ///
    /// If the tag's value cannot be converted to a signed very long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 64 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed long long)getInt64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed long integer (32 bit).
    ///
    /// If the tag's value cannot be converted to a signed long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 32 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed int)getInt32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Deprecated. Use getInt32() instead.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed short integer (16 bit).
    ///
    /// If the tag's value cannot be converted to a signed long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 16 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed short)getInt16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed char integer (8 bit).
    ///
    /// If the tag's value cannot be converted to a signed long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 8 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed char)getInt8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed very long integer (64 bit).
    ///
    /// If the tag's value cannot be converted to a signed very long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 64 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed long long)getInt64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed long long)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed long integer (32 bit).
    ///
    /// If the tag's value cannot be converted to a signed long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 32 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed int)getInt32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Deprecated. Use getInt32() instead.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed short integer (16 bit).
    ///
    /// If the tag's value cannot be converted to a signed long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 16 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed short)getInt16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed short)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as signed char integer (8 bit).
    ///
    /// If the tag's value cannot be converted to a signed long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a signed 8 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(signed char)getInt8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed char)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned very long integer (64 bit).
    ///
    /// If the tag's value cannot be converted to an unsigned very long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 64 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned long long)getUint64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned long integer (32 bit).
    ///
    /// When calling getUint32() on an AT tag (Attribute Tag) then the tag group
    /// is always in the high word of the returned value.
    ///
    /// If the tag's value cannot be converted to an unsigned long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 32 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int)getUint32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Deprecated. Use getUint32() instead.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned long integer (16 bit).
    ///
    /// If the tag's value cannot be converted to an unsigned long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 16 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned short)getUint16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned long integer (8 bit).
    ///
    /// If the tag's value cannot be converted to an unsigned long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 8 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned char)getUint8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned very long integer (64 bit).
    ///
    /// If the tag's value cannot be converted to an unsigned very long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 64 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned long long)getUint64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned long long)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned long integer (32 bit).
    ///
    /// When calling getUint32() on an AT tag (Attribute Tag) then the tag group
    /// is always in the high word of the returned value.
    ///
    /// If the tag's value cannot be converted to an unsigned long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 32 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int)getUint32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Deprecated. Use getUint32() instead.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned long integer (16 bit).
    ///
    /// If the tag's value cannot be converted to an unsigned long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 16 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned short)getUint16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned short)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as unsigned long integer (8 bit).
    ///
    /// If the tag's value cannot be converted to an unsigned long integer
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an unsigned 8 bit integer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned char)getUint8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned char)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as a double floating point.
    ///
    /// If the tag's value cannot be converted to double floating point
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a double floating point
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as a floating point value.
    ///
    /// If the tag's value cannot be converted to double floating point
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a floating point
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(float)getFloat:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as a double floating point.
    ///
    /// If the tag's value cannot be converted to double floating point
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a double floating point
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(double)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as a floating point value.
    ///
    /// If the tag's value cannot be converted to double floating point
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a floating point
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(float)getFloat:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(float)defaultValue error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a tag's value as a string.
    ///
    /// If the tag's value cannot be converted to a string
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a string
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    /// \brief Retrieve a tag's value as a string.
    ///
    /// If the tag's value cannot be converted to a string
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as a string
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(NSString*)defaultValue error:(NSError**)pError;

    /// \brief Retrieve a tag's value as an ImebraAge object.
    ///
    /// If the tag's value cannot be converted to an ImebraAge object
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an ImebraAge object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    /// \brief Retrieve a tag's value as an ImebraAge object.
    ///
    /// If the tag's value cannot be converted to an ImebraAge object
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an ImebraAge object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraAge*)defaultValue error:(NSError**)pError;

    /// \brief Retrieve a tag's value as an ImebraDate object.
    ///
    /// If the tag's value cannot be converted to an ImebraDate object
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an ImebraDate object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    /// \brief Retrieve a tag's value as an ImebraDate object.
    ///
    /// If the tag's value cannot be converted to an ImebraDate object
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an ImebraDate object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraDate*)defaultValue error:(NSError**)pError;

    /// \brief Retrieve a tag's value as an ImebraPatientName object.
    ///
    /// If the tag's value cannot be converted to an ImebraPatientName object
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an ImebraDate object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraPatientName*)getPatientName:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError;

    /// \brief Retrieve a tag's value as an ImebraPatientName object.
    ///
    /// If the tag's value cannot be converted to an ImebraPatientName object
    /// then sets pError to ImebraDataHandlerConversionError.
    ///
    /// If the specified tag does not exist then returns the default value
    /// set in the defaultValue parameter.
    ///
    /// \param tagId    the tag's id
    /// \param elementNumber the element number within the buffer
    /// \param defaultValue  the value to return if the tag doesn't exist
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's value as an ImebraDate object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraPatientName*)getPatientName:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraPatientName*)defaultValue error:(NSError**)pError;

    /// \brief Return the data type (VR) of the specified tag.
    ///
    /// If the specified tag does not exist then set pError to
    /// ImebraMissingTagError or ImebraMissingGroupError.
    ///
    /// \param tagId the id of the tag
    /// \param pError   a pointer to a NSError pointer which is set when an
    ///                  error occurs
    /// \return the tag's data type (VR)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraTagType)getDataType:(ImebraTagId*)tagId error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end


    ///
    ///  \brief This class represents a mutableDICOM dataset.
    ///
    /// The information it contains is organized into groups and each group may
    /// contain several tags.
    ///
    /// You can create an empty ImebraMutableDataSet that can be filled with data and
    /// images and then saved to a DICOM file via ImebraCodecFactory::save().
    ///
    /// When creating an empty ImebraMutableDataSet you should specify the proper transfer
    /// syntax in the init method.
    ///
    /// To set the ImebraMutableDataSet's content, use one of the following methods:
    /// - setImage()
    /// - appendSequenceItem()
    /// - setInt64()
    /// - setInt32()
    /// - setInt16()
    /// - setInt8()
    /// - setUint64()
    /// - setUint32()
    /// - setUint16()
    /// - setUint8()
    /// - setDouble()
    /// - setFloat()
    /// - setString()
    /// - setUnicodeString()
    /// - setAge()
    /// - setDate()
    /// - setPatientName()
    ///
    /// The previous methods allow to write just the first item in the tag's
    /// content and before writing wipe out the old tag's content (all the items).
    /// If you have to write more than one item in a tag, retrieve a
    /// ImebraWritingDataHandler with getWritingDataHandler() and then modify all
    /// the tag's items using the ImebraWritingDataHandler.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @interface ImebraMutableDataSet: ImebraDataSet

        /// \brief Construct an empty DICOM dataset with unspecified transfer syntax
        ///        (e.g. to be used in a sequence) charset "ISO 2022 IR 6".
        ///
        /// Use this method when creating a DataSet that will be embedded in a sequence
        /// item.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(id)init;

        /// \brief Construct an empty DICOM dataset with charset "ISO 2022 IR 6" and
        ///        the desidered transfer syntax.
        ///
        /// \param transferSyntax the dataSet's transfer syntax. The following transfer
        ///                       syntaxes are supported:
        ///                       - "1.2.840.10008.1.2" (Implicit VR little endian)
        ///                       - "1.2.840.10008.1.2.1" (Explicit VR little endian)
        ///                       - "1.2.840.10008.1.2.2" (Explicit VR big endian)
        ///                       - "1.2.840.10008.1.2.5" (RLE compression)
        ///                       - "1.2.840.10008.1.2.4.50" (Jpeg baseline 8 bit
        ///                         lossy)
        ///                       - "1.2.840.10008.1.2.4.51" (Jpeg extended 12 bit
        ///                         lossy)
        ///                       - "1.2.840.10008.1.2.4.57" (Jpeg lossless NH)
        ///                       - "1.2.840.10008.1.2.4.70" (Jpeg lossless NH first
        ///                         order prediction)
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(id)initWithTransferSyntax:(NSString*)transferSyntax;

        /// \brief Construct an empty DICOM dataset and specifies the default charsets.
        ///
        /// \param transferSyntax the dataSet's transfer syntax. The following transfer
        ///                       syntaxes are supported:
        ///                       - "1.2.840.10008.1.2" (Implicit VR little endian)
        ///                       - "1.2.840.10008.1.2.1" (Explicit VR little endian)
        ///                       - "1.2.840.10008.1.2.2" (Explicit VR big endian)
        ///                       - "1.2.840.10008.1.2.5" (RLE compression)
        ///                       - "1.2.840.10008.1.2.4.50" (Jpeg baseline 8 bit
        ///                         lossy)
        ///                       - "1.2.840.10008.1.2.4.51" (Jpeg extended 12 bit
        ///                         lossy)
        ///                       - "1.2.840.10008.1.2.4.57" (Jpeg lossless NH)
        ///                       - "1.2.840.10008.1.2.4.70" (Jpeg lossless NH first
        ///                         order prediction)
        ///
        /// \param pCharsets a NSArray of NSString specifying the charsets supported
        ///                  by the DataSet
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(id)initWithTransferSyntax:(NSString*)transferSyntax charsets:(NSArray*)pCharsets;

        /// \brief Retrieve the ImebraTag with the specified ID or create it if it
        ///        doesn't exist.
        ///
        /// \param tagId the ID of the tag to retrieve
        /// \param tagVR the VR to use for the new tag if one doesn't exist already
        /// \param pError set if an error occurs
        /// \return the Tag with the specified ID
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraMutableTag*) getTagCreate:(ImebraTagId*)tagId tagVR:(ImebraTagType)tagVR error:(NSError**)pError;

        /// \brief Retrieve the ImebraTag with the specified ID or create it if it
        ///        doesn't exist. Set the proper VR according to the tag ID.
        ///
        /// \param tagId the ID of the tag to retrieve
        /// \param pError set if an error occurs
        /// \return the Tag with the specified ID
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraMutableTag*) getTagCreate:(ImebraTagId*)tagId error:(NSError**)pError;

        /// \brief Insert an image into the dataset.
        ///
        /// In multi-frame datasets the images must be inserted in order: first insert
        ///  the frame 0, then the frame 1, then the frame 2 and so on.
        ///
        /// All the inserted images must have the same transfer syntax and the same
        ///  properties (size, color space, high bit, bits allocated).
        ///
        /// If the images are inserted in the wrong order then the
        ///  ImebraDataSetWrongFrameError is set in pError.
        ///
        /// If the image being inserted has different properties than the ones of the
        ///  images already in the dataset then the exception
        ///  ImebraDataSetDifferentFormatError is set in pError.
        ///
        /// \param frameNumber the frame number (the first frame is 0)
        /// \param image       the image
        /// \param quality     the quality to use for lossy compression. Ignored
        ///                    if lossless compression is used
        /// \param pError      a pointer to a NSError pointer which is set when an
        ///                    error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void) setImage:(unsigned int)frameNumber image:(ImebraImage*)image quality:(ImebraImageQuality)quality error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Insert an overlay into the dataset.
        ///
        /// \param overlayNumber   the overlay number (0...127)
        /// \param overlay         the overlay to insert into the dataset
        /// \param pError          a pointer to a NSError pointer which is set when an
        ///                         error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void) setOverlay:(unsigned int)overlayNumber overlay:(ImebraOverlay*)overlay error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Get a StreamWriter connected to a buffer's data.
        ///
        /// If the specified tag does not exist then it creates a new tag with the VR
        ///  specified in DICOM dictionary
        ///
        /// \param pTagId     the tag's id for which the StreamWriter is required
        /// \param bufferId   the id of the buffer for which the StreamWriter is
        ///                    required. This parameter is usually 0
        /// \param pError   set to a NSError derived class in case of error
        /// \return           the StreamWriter connected to the buffer's data.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraStreamWriter*) getStreamWriter:(ImebraTagId*)pTagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

        /// \brief Get a StreamWriter connected to a buffer's data.
        ///
        /// If the specified tag does not exist then it creates a new tag with the VR
        ///  specified in the tagVR parameter
        ///
        /// \param pTagId     the tag's id for which the StreamWriter is required
        /// \param bufferId   the id of the buffer for which the StreamWriter is
        ///                    required. This parameter is usually 0
        /// \param pError   set to a NSError derived class in case of error
        /// \return           the StreamWriter connected to the buffer's data.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraStreamWriter*) getStreamWriter:(ImebraTagId*)pTagId bufferId:(unsigned int)bufferId tagVR:(ImebraTagType)tagVR error:(NSError**)pError;

        /// \brief Append a sequence item.
        ///
        /// If the specified tag does not exist then creates a new one with VR
        ///  ImebraTagTypeSQ.
        ///
        /// \param pTagId the tag's id in which the sequence must be stored
        /// \param pError a pointer to a NSError pointer which is set when an
        ///                error occurs
        /// \return the dataset representing the appended sequence item
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraMutableDataSet*) appendSequenceItem:(ImebraTagId*)pTagId error:(NSError**)pError;

        /// \brief Retrieve an ImebraWritingDataHandler object connected to a specific
        ///        tag's buffer and sets its data type (VR).
        ///
        /// If the specified tag does not exist then it creates a new tag with the VR
        ///  specified in the tagVR parameter
        ///
        /// The returned ImebraWritingDataHandler is connected to a new buffer which
        /// is updated and stored into the tag when the ImebraWritingDataHandler
        /// object is destroyed.
        ///
        /// \param tagId    the tag's id containing the requested buffer
        /// \param bufferId the position where the new buffer has to be stored in the
        ///                 tag. The first buffer position is 0
        /// \param tagVR    the tag's VR
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        /// \return a ImebraWritingDataHandler object connected to a new tag's buffer
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId tagVR:(ImebraTagType)tagVR error:(NSError**)pError;

        /// \brief Retrieve a ImebraWritingDataHandler object connected to a specific
        ///        tag's buffer.
        ///
        /// If the specified tag does not exist then it creates a new tag with a
        ///  default VR retrieved from the ImebraDicomDictionary.
        ///
        /// The returned ImebraWritingDataHandler is connected to a new buffer which
        /// is updated and stored into the tag when the ImebraWritingDataHandler
        /// object is destroyed.
        ///
        /// \param tagId    the tag's id containing the requested buffer
        /// \param bufferId the position where the new buffer has to be stored in the
        ///                 tag. The first buffer position is 0
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        /// \return a ImebraWritingDataHandler object connected to a new tag's buffer
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError;

        /// \brief Retrieve a ImebraWritingDataHandlerNumeric object connected to
        ///        a specific tag's buffer.
        ///
        /// If the tag's VR is not a numeric type then throws std::bad_cast.
        ///
        /// If the specified tag does not exist then it creates a new tag with the VR
        ///  specified in the tagVR parameter
        ///
        /// The returned ImebraWritingDataHandlerNumeric is connected to a new buffer
        /// which is updated and stored into the tag when
        /// ImebraWritingDataHandlerNumeric is destroyed.
        ///
        /// \param tagId    the tag's id containing the requested buffer
        /// \param bufferId the position where the new buffer has to be stored in the
        ///                 tag. The first buffer position is 0
        /// \param tagVR    the tag's VR
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        /// \return a ImebraWritingDataHandlerNumeric object connected to a new tag's
        ///         buffer
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(ImebraTagId*)tagId bufferId:(unsigned long)bufferId tagVR:(ImebraTagType)tagVR error:(NSError**)pError;

        /// \brief Retrieve a ImebraWritingDataHandlerNumeric object connected to a
        ///        specific tag's buffer.
        ///
        /// If the tag's VR is not a numeric type then throws std::bad_cast.
        ///
        /// If the specified tag does not exist then it creates a new tag with a
        ///  default VR retrieved from the ImebraDicomDictionary.
        ///
        /// The returned ImebraWritingDataHandlerNumeric is connected to a new buffer
        /// which is updated and stored into the tag when
        /// ImebraWritingDataHandlerNumeric is destroyed.
        ///
        /// \param tagId    the tag's id containing the requested buffer
        /// \param bufferId the position where the new buffer has to be stored in the
        ///                 tag. The first buffer position is 0
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        /// \return a ImebraWritingDataHandlerNumeric object connected to a new tag's
        ///         buffer
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(ImebraTagId*)tagId bufferId:(unsigned long)bufferId error:(NSError**)pError;

        /// \brief Write a new signed 64 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt64:(ImebraTagId*)tagId newValue:(signed long long)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 32 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt32:(ImebraTagId*)tagId newValue:(signed int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \bried Deprecated. Use setInt32() instead.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 16 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt16:(ImebraTagId*)tagId newValue:(signed short)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 8 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt8:(ImebraTagId*)tagId newValue:(signed char)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 64 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt64:(ImebraTagId*)tagId newValue:(signed long long)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 32 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt32:(ImebraTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \bried Deprecated. Use setInt32() instead.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 16 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt16:(ImebraTagId*)tagId newValue:(signed short)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new signed 8 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setInt8:(ImebraTagId*)tagId newValue:(signed char)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 64 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint64:(ImebraTagId*)tagId newValue:(unsigned long long)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 32 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// When setting a value for an AT tag (Attribute Tag) then the tag's group
        /// must always be in the higher 16 bits of the value.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint32:(ImebraTagId*)tagId newValue:(unsigned int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Deprecated. Use setUint32() instead.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 16 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint16:(ImebraTagId*)tagId newValue:(unsigned short)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 8 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint8:(ImebraTagId*)tagId newValue:(unsigned char)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 64 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint64:(ImebraTagId*)tagId newValue:(unsigned long long)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 32 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// When setting a value for an AT tag (Attribute Tag) then the tag's group
        /// must always be in the higher 16 bits of the value.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint32:(ImebraTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Deprecated. Use setUint32() instead.
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 16 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint16:(ImebraTagId*)tagId newValue:(unsigned short)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new unsigned 8 bit integer value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setUint8:(ImebraTagId*)tagId newValue:(unsigned char)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new double floating point value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new floating point value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setFloat:(ImebraTagId*)tagId newValue:(float)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new double floating point value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new floating point value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setFloat:(ImebraTagId*)tagId newValue:(float)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new string value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new string value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new ImebraAge value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) AS.
        ///
        /// If the new value cannot be converted to the VR "AS"
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setAge:(ImebraTagId*)tagId newValue:(ImebraAge*)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new ImebraDate value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the specified data type (VR).
        ///
        /// If the new value cannot be converted to the specified VR
        /// then sets pError to ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param tagVR    the tag's type to use when a new tag is created.
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new ImebraDate value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) retrieved from the ImebraDicomDictionary.
        ///
        /// If the new value cannot be converted to the VR returned by the
        /// ImebraDicomDictionary then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

        /// \brief Write a new ImebraPatientName value into the element 0 of the
        ///        specified tag's buffer 0.
        ///
        /// If the specified tag doesn't exist then a new tag is created using
        /// the data type (VR) PN.
        ///
        /// If the new value cannot be converted to a patient name then sets pError to
        /// ImebraDataHandlerConversionError.
        ///
        /// \param tagId    the tag's id
        /// \param newValue the value to write into the tag
        /// \param pError   a pointer to a NSError pointer which is set when an
        ///                  error occurs
        ///
        ///////////////////////////////////////////////////////////////////////////////
        -(void)setPatientName:(ImebraTagId*)tagId newValue:(ImebraPatientName*)newValue error:(NSError**)pError
            __attribute__((swift_error(nonnull_error)));

    @end




#endif // imebraObjcDataSet__INCLUDED_


