/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcStreamReader__INCLUDED_)
#define imebraObjcStreamReader__INCLUDED_

#import "imebra_baseStreamInput.h"
#import <Foundation/Foundation.h>
#include "imebra_macros.h"


///
/// \brief ImebraStreamReader is used to read data from a
///        ImebraBaseStreamInput object.
///
/// ImebraStreamReader can be mapped to only a portion of the
/// ImebraBaseStreamInput it manages: for instance this is used by the Imebra
/// classes to read Jpeg streams embedded into a DICOM stream.
///
/// \warning  The ImebraStreamReader object IS NOT THREAD-SAFE: however,
///           several ImebraStreamReader objects from different threads can
///           be connected to the same ImebraBaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraStreamReader: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    define_imebra_object_holder(StreamReader);
}

    -(id)initWithImebraStreamReader:define_imebra_parameter(StreamReader);
#endif

    /// \brief Initializer.
    ///
    /// \param pInput the ImebraBaseStreamInput object from which the ž
    ///               ImebraStreamReader will read
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithInputStream:(ImebraBaseStreamInput*)pInput;

    /// \brief Initializer.
    ///
    /// This version of the constructor limits the portion of the stream that
    /// the ImebraStreamReader will see.
    ///
    /// \param pInput the ImebraBaseStreamInput object from which the ž
    ///               ImebraStreamReader will read
    /// \param virtualStart  the first visible byte of the managed stream
    /// \param virtualLength the number of visible bytes in the managed stream
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithInputStream:(ImebraBaseStreamInput*)pInput virtualStart:(unsigned int)virtualStart virtualEnd:(unsigned int)virtualEnd;

    -(void)dealloc;

    ///
    /// \brief Returns a virtual stream that has a restricted view into the
    ///        stream.
    ///
    /// The reading position of this stream advances to the end of the virtual
    /// stream.
    ///
    /// \param virtualSize the number of bytes that the virtual
    ///                    stream can read
    /// \param pError      set to a NSError derived class in case of error
    /// \return a virtual stream that sees a limited number of bytes of this
    ///         stream
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraStreamReader*)getVirtualStream:(unsigned int)virtualSize error:(NSError**)pError;

    ///
    /// \brief Cause the controlled stream to set the ImebraStreamClosedError
    ///        during the next read operation.
    ///
    /// This can be used to cause reading threads to terminate.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)terminate;

@end

#endif // !defined(imebraObjcStreamReader__INCLUDED_)
