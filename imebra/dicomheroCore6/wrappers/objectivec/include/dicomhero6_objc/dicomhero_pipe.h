/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcPipe__INCLUDED_)
#define dicomheroObjcPipe__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

@class DicomheroBaseStreamInput;
@class DicomheroBaseStreamOutput;

///
/// \brief A pipe can be used to push and pull data to/from an Imebra codec.
///
/// This is useful when an Imebra codec must be used with a data source
/// or a data sink not supported by the library (e.g. a TLS stream).
///
/// In order to allow Imebra to read data from a custom data source:
/// - allocate a ImebraPipe class and use it as parameter for the
///   DicomheroStreamReader needed by the codec
/// - from a secondary thread feed the data to the data source by using an
///   DicomheroStreamWriter
///
/// In order to allow Imebra to write data to a custom data source:
/// - allocate a ImebraPipe class and use it as parameter for the
///   DicomheroStreamWriter needed by the codec
/// - from a secondary thread read the data by using an DicomheroStreamReader
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroPipeStream: NSObject
{
    @public
    define_dicomhero_object_holder(PipeStream);
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

    -(DicomheroBaseStreamInput*) getStreamInput;

    -(DicomheroBaseStreamOutput*) getStreamOutput;

@end

#endif // !defined(dicomheroObjcPipe__INCLUDED_)
