/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcReadMemory__INCLUDED_)
#define dicomheroObjcReadMemory__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

///
/// \brief Manages a read-only buffer of memory.
///
/// The buffer of memory is usually associated with a DicomheroTag buffer content.
///
/// The memory used by ImebraReadMemory and DicomheroMutableMemory is managed
/// by DicomheroMemoryPool.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroMemory: NSObject

{
    @public
    define_dicomhero_object_holder(Memory);
}
    -(id)initWithDicomheroMemory:define_dicomhero_parameter(Memory);

    -(id)init;

    /// \brief Construct a buffer of memory and copy the specified content into it.
    ///
    /// \param source a pointer to the source data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithData:(NSData*)source;

    /// \brief Copies the raw memory content into a NSData object and returns it.
    ///
    /// \return a NSData containing a copy of the memory managed by
    ///         ImebraReadMemory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSData*)data;

    -(void)dealloc;

    /// \brief Return true if the referenced memory is zero bytes long or hasn't
    ///        been allocated yet.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) bool empty;

@end

#endif // !defined(dicomheroObjcReadMemory__INCLUDED_)
