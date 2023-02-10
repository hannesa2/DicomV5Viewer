/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcMemoryStreamOutput__INCLUDED_)
#define imebraObjcMemoryStreamOutput__INCLUDED_

#import <Foundation/Foundation.h>
#import "imebra_baseStreamOutput.h"

@class ImebraMutableMemory;

///
/// \brief An output stream that writes data into a memory region.
///
/// When new data is written into the memory then it is resized as necessary.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraMemoryStreamOutput : ImebraBaseStreamOutput

    /// \brief Initializer.
    ///
    /// \param pMemory the memory region into which the stream will write the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithMutableMemory:(ImebraMutableMemory*)pMemory;

@end

#endif // imebraObjcMemoryStreamOutput__INCLUDED_


