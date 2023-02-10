/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcBaseStreamInput__INCLUDED_)
#define dicomheroObjcBaseStreamInput__INCLUDED_

#import <Foundation/Foundation.h>
#import "dicomhero_macros.h"

///
/// \brief This class represents a generic input stream.
///
/// Specialized classes derived from this one can read data from files stored
/// on the computer's disks (DicomheroFileStreamInput) or from memory
/// (DicomheroMemoryStreamInput).
///
/// The client application cannot read the data directly from a
/// DicomheroBaseStreamInput but must use a DicomheroStreamReader. Several
/// DicomheroStreamReader objects can read data from the same
/// DicomheroBaseStreamInput object.
///
/// The DicomheroStreamReader class is not thread-safe, but different
/// DicomheroStreamReader objects in different threads can access the same
/// DicomheroBaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroBaseStreamInput: NSObject

{
    @public
    define_dicomhero_object_holder(BaseStreamInput);
}

    -(id)initWithDicomheroBaseStreamInput:define_dicomhero_parameter(BaseStreamInput);

    -(void)dealloc;

@end


///
/// \brief Triggers a timeout on a selected stream if the class is not
///        deallocated within the specified amount of time.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroStreamTimeout: NSObject

{
    @public
    define_dicomhero_object_holder(StreamTimeout);
}

    ///
    /// \brief Initializer. Starts a separate thread that closes the stream in
    ///        the parameter if this class destructor is not called before the
    ///        timeout expires.
    ///
    /// \param pStream        stream that must be closed when the timeout
    ///                       expires
    /// \param timeoutSeconds timeout in seconds
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithInputStream:(DicomheroBaseStreamInput*)pStream timeoutSeconds:(unsigned int)timeoutSeconds;

    -(void)dealloc;

@end

#endif // !defined(dicomheroObjcBaseStreamInput__INCLUDED_)
