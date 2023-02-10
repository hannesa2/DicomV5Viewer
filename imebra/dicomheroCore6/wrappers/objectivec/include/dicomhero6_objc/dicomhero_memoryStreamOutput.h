/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcMemoryStreamOutput__INCLUDED_)
#define dicomheroObjcMemoryStreamOutput__INCLUDED_

#import <Foundation/Foundation.h>
#import "dicomhero_baseStreamOutput.h"

@class DicomheroMutableMemory;

///
/// \brief An output stream that writes data into a memory region.
///
/// When new data is written into the memory then it is resized as necessary.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroMemoryStreamOutput : DicomheroBaseStreamOutput

    /// \brief Initializer.
    ///
    /// \param pMemory the memory region into which the stream will write the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithMutableMemory:(DicomheroMutableMemory*)pMemory;

@end

#endif // dicomheroObjcMemoryStreamOutput__INCLUDED_


