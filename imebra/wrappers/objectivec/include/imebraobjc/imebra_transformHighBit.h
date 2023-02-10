/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTransformHighBit__INCLUDED_)
#define imebraObjcTransformHighBit__INCLUDED_

#import "imebra_transform.h"

///
/// \brief ImebraTransformHighBit shifts the input image's values
///        so they match the high-bit settings of the output image.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraTransformHighBit: ImebraTransform

    -(id)init;

@end


#endif // imebraObjcTransformHighBit__INCLUDED_
