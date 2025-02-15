/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcPipe__INCLUDED_)
#define imebraObjcPipe__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

@class ImebraBaseStreamInput;
@class ImebraBaseStreamOutput;

///
/// \brief A pipe can be used to push and pull data to/from an Imebra codec.
///
/// This is useful when an Imebra codec must be used with a data source
/// or a data sink not supported by the library (e.g. a TLS stream).
///
/// In order to allow Imebra to read data from a custom data source:
/// - allocate a ImebraPipe class and use it as parameter for the
///   ImebraStreamReader needed by the codec
/// - from a secondary thread feed the data to the data source by using an
///   ImebraStreamWriter
///
/// In order to allow Imebra to write data to a custom data source:
/// - allocate a ImebraPipe class and use it as parameter for the
///   ImebraStreamWriter needed by the codec
/// - from a secondary thread read the data by using an ImebraStreamReader
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraPipeStream: NSObject
{
    @public
    define_imebra_object_holder(PipeStream);
}

    /// \brief Initializer.
    ///
    /// \param circularBufferSize the size of the buffer that stores the data
    ///                           fed to the Pipe until it is fetched
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithBufferSize:(unsigned int)circularBufferSize;

    ///
    /// \brief Wait for the specified amount of time or until the internal buffer
    ///        is empty (all the data fed has been retrieved by the StreamReader
    ///        or by sink()), whichever comes first, then call terminate().
    ///
    /// Subsequent read and write operations will fail by throwing the
    /// exception StreamClosedError.
    ///
    /// \param timeoutMilliseconds the maximum time to wait until the internal
    ///                            buffer is empty, in milliseconds
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) close: (unsigned int) timeoutMilliseconds error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(ImebraBaseStreamInput*) getStreamInput;

    -(ImebraBaseStreamOutput*) getStreamOutput;

@end

#endif // !defined(imebraObjcPipe__INCLUDED_)
