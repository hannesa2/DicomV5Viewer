/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcTransformHighBit__INCLUDED_)
#define dicomheroObjcTransformHighBit__INCLUDED_

#import "dicomhero_transform.h"

///
/// \brief DicomheroTransformHighBit shifts the input image's values
///        so they match the high-bit settings of the output image.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTransformHighBit: DicomheroTransform

    -(id)init;

@end


#endif // dicomheroObjcTransformHighBit__INCLUDED_
