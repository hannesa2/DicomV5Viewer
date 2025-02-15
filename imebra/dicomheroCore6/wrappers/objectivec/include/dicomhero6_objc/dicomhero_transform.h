/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcTransform__INCLUDED_)
#define dicomheroObjcTransform__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"


@class DicomheroImage;


///
/// \brief Represents a transform: a transform takes one DicomheroImage as input,
///        processes it and outputs the processed DicomheroImage.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTransform: NSObject

{
    @public
    define_dicomhero_object_holder(Transform);

}

    -(id)initWithDicomheroTransform:define_dicomhero_parameter(Transform);

    -(void)dealloc;

    /// \brief Allocate an image ready to accomodate the result of the
    ///        image processing performed by the runTransform() method.
    ///
    /// \param pInputImage the image that will be set as the input of the
    ///                    runTransform() method
    /// \param width       the width of the output image
    /// \param height      the height of the output image
    /// \param pError      set to a NSError derived class in case of error
    /// \return an image ready to be passed as outputImage to runTransform()
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroImage*) allocateOutputImage:
            (DicomheroImage*)pInputImage
            width:(unsigned int)width
            height:(unsigned int)height
            error:(NSError**)pError;

    /// \brief Run the processing function of the DicomheroTransform.
    ///
    /// \param inputImage the image to use as input
    /// \param inputTopLeftX the horizontal position of the top-left pixel to
    ///                      process
    /// \param inputTopLeftY the vertical position of the top-left pixel to
    ///                      process
    /// \param inputWidth    the horizontal number of pixels to process
    /// \param inputHeight   the vertical number of pixels to process
    /// \param outputTopLeftX the horizontal position on the output image of the
    ///                      top left processed pixel
    /// \param outputTopLeftY the vertical position on the output image of the top
    ///                      left processed pixel
    /// \param pError        set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) runTransform:
            (DicomheroImage*)pInputImage
            inputTopLeftX:(unsigned int)inputTopLeftX
            inputTopLeftY:(unsigned int)inputTopLeftY
            inputWidth:(unsigned int)inputWidth
            inputHeight:(unsigned int)inputHeight
            outputImage:(DicomheroImage*)pOutputImage
            outputTopLeftX:(unsigned int)outputTopLeftX
            outputTopLeftY:(unsigned int)outputTopLeftY
            error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Returns true if the transform doesn't perform any processing
    ///        (the output image will be identical to the input one).
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) BOOL isEmpty;

@end



#endif // dicomheroObjcTransform__INCLUDED_
