/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcModalityVOILUT__INCLUDED_)
#define imebraObjcModalityVOILUT__INCLUDED_

#import "imebra_transform.h"

@class ImebraDataSet;

///
/// \brief The ImebraModalityVOILUT transform applies the Modality VOI or LUT
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
@interface ImebraModalityVOILUT: ImebraTransform

    /// \brief Initializer.
    ///
    /// \param dataset the ImebraDataSet from which the modality VOI or LUT data
    ///                is retrieved. If the modality VOI/LUT information is
    ///                stored in a functional group, then first
    ///                use ImebraDataSet::getFunctionalGroupDataSet() to retrieve 
    ///                the sequence item containing the modality VOI/LUT 
    ///                information and pass that item as parameter to this 
    ///                constructor
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithDataSet:(ImebraDataSet*)pDataSet;

@end


#endif // imebraObjcModalityVOILUT__INCLUDED_
