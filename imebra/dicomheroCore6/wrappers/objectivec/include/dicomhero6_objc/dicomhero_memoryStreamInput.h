/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcMemoryStreamInput__INCLUDED_)
#define dicomheroObjcMemoryStreamInput__INCLUDED_

#import <Foundation/Foundation.h>
#import "dicomhero_baseStreamInput.h"

@class DicomheroMemory;

///
/// \brief An input stream that reads data from a memory region.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroMemoryStreamInput : DicomheroBaseStreamInput

    /// \brief Initializer.
    ///
    /// \param pMemory the memory region from which the stream will read the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithReadMemory:(DicomheroMemory*)pMemory;

@end

#endif // dicomheroObjcMemoryStreamInput__INCLUDED_


