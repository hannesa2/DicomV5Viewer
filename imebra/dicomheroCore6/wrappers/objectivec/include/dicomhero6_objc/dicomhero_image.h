/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcImage__INCLUDED_)
#define dicomheroObjcImage__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

/// \enum DicomheroBitDepth
/// \brief Defines the size of the memory allocated for each
///        pixel's color component and its representation (signed/unsigned).
///
/// This enumeration does not specify the highest bit used:
/// in order to retrieve the highest used bit call DicomheroImage.highBit.
///
/// The lower bit of the enumerations is 1 if it represents a signed depth,
/// 0 if it represents an unsigned depth,
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned int, DicomheroBitDepth)
{
    DicomheroBitDepthU8 = 0,  ///< 8 bit integer, unsigned
    DicomheroBitDepthS8 = 1,  ///< 8 bit integer, signed
    DicomheroBitDepthU16 = 2, ///< 16 bit integer, unsigned
    DicomheroBitDepthS16 = 3, ///< 16 bit integer, signed
    DicomheroBitDepthU32 = 4, ///< 32 bit integer, unsigned
    DicomheroBitDepthS32 = 5  ///< 32 bit integer, signed
};

@class DicomheroReadingDataHandlerNumeric;
@class DicomheroWritingDataHandlerNumeric;


///
/// \brief Represents a DICOM image.
///
/// The class manages an uncompressed DICOM image. Images are compressed
/// when they are inserted into the DataSet via DataSet::setImage() and are
/// decompressed when they are referenced by the Image class.
///
/// The image is stored in a contiguous area of memory: each channel's value
/// can occupy 1, 2 or 4 bytes, according to the Image's data type.
///
/// Channels' values are always interleaved in the Image class, regardless
/// of how they are stored in the DataSet object.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroImage: NSObject

{
    @public
    define_dicomhero_object_holder(Image);
}

    -(id)initWithDicomheroImage:define_dicomhero_parameter(Image);

    /// \brief Initializer.
    ///
    /// The memory for the image is not allocated by the constructor but only when
    /// a WritingDataHandler is requested with getWritingDataHandler().
    ///
    /// \param width      the image width, in pixels
    /// \param height     the image height, in pixels
    /// \param depth      the channel values data types
    /// \param colorSpace the Image's color space
    /// \param highBit    the highest bit occupied by the channels' values
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithWidth:(unsigned int)width height:(unsigned int)height depth:(DicomheroBitDepth)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit;

    -(void)dealloc;

    /// \brief Retrieve a DicomheroReadingDataHandlerNumeric object referencing the
    ///        image's memory (read only).
    ///
    /// The memory referenced by ImageReadingDataHandlerNumeric contains all the
    /// image's pixels. The color channels are interleaved.
    ///
    /// \return a DicomheroReadingDataHandlerNumeric object referencing the Image's
    ///         memory in read-only mode
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError;

    /// \brief Retrieve the image's width, in pixels.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int width;

    /// \brief Retrieve the image's height, in pixels.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int height;

    /// \brief Retrieve the Image's color space
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* colorSpace;

    /// \brief Return the number of color channels contained by the image
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int channelsNumber;

    /// \brief Return the type of the channels' values.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) DicomheroBitDepth depth;

    /// \brief Return the highest bit occupied by the channels' values.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int highBit;

    /// \brief Retrieve a DicomheroWritingDataHandlerNumeric object referencing the
    ///        image's memory (mutable).
    ///
    /// The memory referenced by the DicomheroWritingDataHandlerNumeric object is
    /// uninitialized.
    ///
    /// When the DicomheroWritingDataHandlerNumeric object is destroyed then the
    /// memory managed by the handler replaces the old image's memory.
    ///
    /// \return a DicomheroWritingDataHandlerNumeric object referencing an
    ///         uninitialized memory buffer that the client has to fill the the
    ///         image's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError;

@end


#endif // dicomheroObjcImage__INCLUDED_


