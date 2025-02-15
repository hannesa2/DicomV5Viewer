/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcVOILUT__INCLUDED_)
#define dicomheroObjcVOILUT__INCLUDED_

#import "dicomhero_transform.h"
#include "dicomhero_macros.h"

@class DicomheroImage;
@class DicomheroLUT;
@class DicomheroVOIDescription;


///
/// \brief A VOILUT transform enhances the visibility of a specific range of
///        brightness in an image.
///
/// The client can use VOILUT in three ways:
/// - by declaring the minimum and maximum values of the pixels that must be
///   visible via the method setCenterWidth()
/// - by declaring a LUT via the method setLUT()
/// - by letting the transform calculate the most appropriate center/width
///   values via the method applyOptimalVOI()
///
/// DicomheroDataSet may already supply suitable values for the methods
/// setCenterWidth() and setLUT().
///
/// In order to retrieve from the dataset the suggested center/width values,
/// call DicomheroDataSet::getVOIs().
///
/// To get from the dataset a list of LUTs that can be used with the VOILUT
/// transform use
/// DicomheroDataSet::getLUT(TagId(DicomheroTagIdVOILUTSequence_0028_3010), X)
/// where X is a 0 base index (the dataset may provide more than one LUT for
/// the VOILUT transform).
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroVOILUT: DicomheroTransform

    /// \brief Initializer.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithLUT:(DicomheroLUT*)lut;

    -(id)initWithVOIDescription:(DicomheroVOIDescription*)voiDescription;

    /// \brief Find the optimal VOI settings for a specific image's area and apply
    ///        it with setCenterWidth().
    ///
    /// \param pInputImage  the image to analyze
    /// \param topLeftX     the horizontal coordinate of the top-left angle of the
    ///                     area to analyze
    /// \param topLeftY     the vertical coordinate of the top-left angle of the
    ///                     area to analyze
    /// \param width        the width of the area to analyze
    /// \param height       the height of the area to analyze
    /// \param pError       set to a NSError derived class in case of error
    /// \return an DicomheroVOIDescription object describing the optimal VOI
    ///         parameters
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroVOIDescription*)getOptimalVOI:
        (DicomheroImage*)pInputImage
        inputTopLeftX:(unsigned int)inputTopLeftX
        inputTopLeftY:(unsigned int)inputTopLeftY
        inputWidth:(unsigned int)inputWidth
        inputHeight:(unsigned int)inputHeight
        error:(NSError**)pError

        __attribute__((swift_error(nonnull_error)));


@end


#endif // dicomheroObjcVOILUT__INCLUDED_
