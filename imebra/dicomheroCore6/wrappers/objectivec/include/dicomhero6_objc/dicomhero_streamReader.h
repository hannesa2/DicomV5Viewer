/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcStreamReader__INCLUDED_)
#define dicomheroObjcStreamReader__INCLUDED_

#import "dicomhero_baseStreamInput.h"
#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"


///
/// \brief DicomheroStreamReader is used to read data from a
///        DicomheroBaseStreamInput object.
///
/// DicomheroStreamReader can be mapped to only a portion of the
/// DicomheroBaseStreamInput it manages: for instance this is used by the Imebra
/// classes to read Jpeg streams embedded into a DICOM stream.
///
/// \warning  The dicomheroStreamReader object IS NOT THREAD-SAFE: however,
///           several DicomheroStreamReader objects from different threads can
///           be connected to the same DicomheroBaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroStreamReader: NSObject

{
    @public
    define_dicomhero_object_holder(StreamReader);
}

    -(id)initWithDicomheroStreamReader:define_dicomhero_parameter(StreamReader);

    /// \brief Initializer.
    ///
    /// \param pInput the DicomheroBaseStreamInput object from which the ž
    ///               DicomheroStreamReader will read
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithInputStream:(DicomheroBaseStreamInput*)pInput;

    /// \brief Initializer.
    ///
    /// This version of the constructor limits the portion of the stream that
    /// the DicomheroStreamReader will see.
    ///
    /// \param pInput the DicomheroBaseStreamInput object from which the ž
    ///               DicomheroStreamReader will read
    /// \param virtualStart  the first visible byte of the managed stream
    /// \param virtualLength the number of visible bytes in the managed stream
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithInputStream:(DicomheroBaseStreamInput*)pInput virtualStart:(unsigned int)virtualStart virtualEnd:(unsigned int)virtualEnd;

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
    -(DicomheroStreamReader*)getVirtualStream:(unsigned int)virtualSize error:(NSError**)pError;

    ///
    /// \brief Cause the controlled stream to set the DicomheroStreamClosedError
    ///        during the next read operation.
    ///
    /// This can be used to cause reading threads to terminate.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)terminate;

@end

#endif // !defined(dicomheroObjcStreamReader__INCLUDED_)
