/*
Copyright 2005 - 2019 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcOverlay__INCLUDED_)
#define imebraObjcOverlay__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

/// \enum ImebraOverlayType
///
/// \brief Defines the Overlay type.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned int, ImebraOverlayType)
{
    ImebraOverlayTypeGraphic = 0,  ///< The overlay is a superimposed graphic
    ImebraOverlayTypeROI = 1,      ///< 8The overlay specifies a region of interest
};

@class ImebraImage;


///
/// \brief Represents an immutable DICOM overlay.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraOverlay: NSObject

{
    @public
    define_imebra_object_holder(Overlay);
}

    -(id)initWithImebraOverlay:define_imebra_parameter(Overlay);

    -(void)dealloc;


    ///
    /// The overlay type.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) ImebraOverlayType type;

    ///
    /// The overlay subtype.
    ///
    /// Defined Term that identifies  the intended purpose of the Overlay Type.
    /// See Section C.9.2.1.3 for further explanation.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* subType;

    ///
    /// Overlay label.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* label;

    ///
    /// Overlay description.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* description;

    ///
    /// The zero based number of the first frame (Image) related to this
    ///  overlay,
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int firstFrame;

    ///
    /// The number of bitmaps stored in the overlay.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int framesCount;

    ///
    /// The zero-based horizontal position of the overlay bitmap into the
    ///  related DICOM image.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) int zeroBasedOriginX;

    ///
    /// The zero-based vertical position of the overlay bitmap into the
    ///  related DICOM image.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) int zeroBasedOriginY;

    ///
    /// \brief Return the ROI area if present, otherwise set pError to 
    ///         ImebraMissingTagError.
    ///
    /// \return the ROI area in pixels
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int) getROIArea:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Return the ROI mean if present, otherwise set pError to 
    ///         ImebraMissingTagError.
    ///
    /// \return the ROI mean value
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(double) getROIMean:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Return the ROI standard deviation if present, otherwise set pError
    ///         to ImebraMissingTagError.
    ///
    /// \return the ROI standard deviation
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(double) getROIStandardDeviation:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Return one of the overlay bitmaps if present, otherwise set pError
    ///         ImebraDataSetImageDoesntExistError.
    ///
    /// \param frameNumber    the number of frame to retrieve (zero based)
    /// \param pError         set to an error class in case of error
    /// \return the requested overlay image
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraImage*) getImage:(unsigned int)frameNumber error:(NSError**)pError;

@end


@interface ImebraMutableOverlay: ImebraOverlay

    /// \brief Initializer.
    ///
    /// \param type          the overlay type
    /// \param subType       the overlay sub type.
    ///                      Defined Term that identifies  the intended purpose of 
    ///                       the Overlay Type. See Section C.9.2.1.3 for further 
    ///                       explanation.
    /// \param firstFrame    first DICOM image related to this overlay (zero-based)
    /// \param zeroBasedOriginX the zero based horizontal position within the
    ///                       DICOM image
    /// \param zeroBasedOriginY the zero based vertical position within the
    ///                       DICOM image
    /// \param label          overlay label
    /// \param description    overlay description
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithType:(ImebraOverlayType)type subType:(NSString*)subType firstFrame:(unsigned int)firstFrame zeroBasedOriginX:(int)zeroBasedOriginX zeroBasedOriginY:(int)zeroBasedOriginY label:(NSString*)label description:(NSString*)description;

    ///
    /// \brief Set the number of pixels in the ROI area.
    ///
    /// \param roiArea number of pixels in the ROI area
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) setROIArea:(unsigned int)roiArea;

    ///
    /// \brief Set the mean value of the pixels in the ROI area.
    ///
    /// \param roiMean mean value of the pixels in the ROI area
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) setROIMean:(double)roiMean;
    
    ///
    /// \brief Set the standard deviation of the value of the pixels in the ROI
    ///        area.
    ///
    /// \param standardDeviation standard deviation of the value of the pixels in
    ///                          the ROI area
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) setROIStandardDeviation:(double)standardDeviation;

    ///
    /// \brief Add a bitmap to the overlay.
    ///
    /// \param frameNumber a zero based frame (relative to the overlay frames)
    /// \param image       the image for the overlay
    /// \param pError      set to an error object if an error occurs
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) setImage:(unsigned int)frameNumber image:(ImebraImage*)image error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));


@end


#endif // imebraObjcOverlay__INCLUDED_


