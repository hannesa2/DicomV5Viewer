/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcImage__INCLUDED_)
#define imebraObjcImage__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

/// \enum ImebraBitDepth
/// \brief Defines the size of the memory allocated for each
///        pixel's color component and its representation (signed/unsigned).
///
/// This enumeration does not specify the highest bit used:
/// in order to retrieve the highest used bit call ImebraImage.highBit.
///
/// The lower bit of the enumerations is 1 if it represents a signed depth,
/// 0 if it represents an unsigned depth,
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned int, ImebraBitDepth)
{
    ImebraBitDepthU8 = 0,  ///< 8 bit integer, unsigned
    ImebraBitDepthS8 = 1,  ///< 8 bit integer, signed
    ImebraBitDepthU16 = 2, ///< 16 bit integer, unsigned
    ImebraBitDepthS16 = 3, ///< 16 bit integer, signed
    ImebraBitDepthU32 = 4, ///< 32 bit integer, unsigned
    ImebraBitDepthS32 = 5  ///< 32 bit integer, signed
};

@class ImebraReadingDataHandlerNumeric;
@class ImebraWritingDataHandlerNumeric;


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
@interface ImebraImage: NSObject

{
    @public
    define_imebra_object_holder(Image);
}

    -(id)initWithImebraImage:define_imebra_parameter(Image);

    -(void)dealloc;

    /// \brief Retrieve a ImebraReadingDataHandlerNumeric object referencing the
    ///        image's memory (read only).
    ///
    /// The memory referenced by ImageReadingDataHandlerNumeric contains all the
    /// image's pixels. The color channels are interleaved.
    ///
    /// \return a ImebraReadingDataHandlerNumeric object referencing the Image's
    ///         memory in read-only mode
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError;

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
    @property (readonly) ImebraBitDepth depth;

    /// \brief Return the highest bit occupied by the channels' values.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int highBit;

@end


@interface ImebraMutableImage: ImebraImage

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
    -(id)initWithWidth:(unsigned int)width height:(unsigned int)height depth:(ImebraBitDepth)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit;

    /// \brief Retrieve a ImebraWritingDataHandlerNumeric object referencing the
    ///        image's memory (mutable).
    ///
    /// The memory referenced by the ImebraWritingDataHandlerNumeric object is
    /// uninitialized.
    ///
    /// When the ImebraWritingDataHandlerNumeric object is destroyed then the
    /// memory managed by the handler replaces the old image's memory.
    ///
    /// \return a ImebraWritingDataHandlerNumeric object referencing an
    ///         uninitialized memory buffer that the client has to fill the the
    ///         image's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError;

@end


#endif // imebraObjcImage__INCLUDED_


