/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcModalityVOILUT__INCLUDED_)
#define dicomheroObjcModalityVOILUT__INCLUDED_

#import "dicomhero_transform.h"

@class DicomheroDataSet;

///
/// \brief The DicomheroModalityVOILUT transform applies the Modality VOI or LUT
///        to the input image.
///
/// The Modality VOI/LUT applies a rescale intercept and a slope
/// to transform the pixel values of the image into values that are meaningful
/// to the application.
///
/// For instance, the original pixel values could store a device specific
/// value that has a meaning only when used by the device that generated it:
/// applying the rescale slope/intercept to pixel value converts the original
/// values into optical density or other known measurement units
/// (e.g. Hounsfield).
///
/// When the transformation is not linear, then a LUT (lookup table) is
/// applied.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroModalityVOILUT: DicomheroTransform

    /// \brief Initializer.
    ///
    /// \param dataset the DicomheroDataSet from which the modality VOI or LUT data
    ///                is retrieved. If the modality VOI/LUT information is
    ///                stored in a functional group, then first
    ///                use DicomheroDataSet::getFunctionalGroupDataSet() to retrieve
    ///                the sequence item containing the modality VOI/LUT
    ///                information and pass that item as parameter to this
    ///                constructor
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithDataSet:(DicomheroDataSet*)pDataSet;

@end


#endif // dicomheroObjcModalityVOILUT__INCLUDED_
