/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcTransformsChain__INCLUDED_)
#define dicomheroObjcTransformsChain__INCLUDED_

#import "dicomhero_transform.h"

///
/// \brief DicomheroTransformsChain applies a series of DicomheroTransforms to the
///        input image.
///
/// Transforms can be added to the chain by using addTransform().
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTransformsChain: DicomheroTransform

    -(id)init;

    -(void)addTransform:(DicomheroTransform*)pTransform;

@end


#endif // dicomheroObjcTransformsChain__INCLUDED_
