/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcBaseStreamInput__INCLUDED_)
#define imebraObjcBaseStreamInput__INCLUDED_

#import <Foundation/Foundation.h>
#import "imebra_macros.h"

///
/// \brief This class represents a generic input stream.
///
/// Specialized classes derived from this one can read data from files stored
/// on the computer's disks (ImebraFileStreamInput) or from memory
/// (ImebraMemoryStreamInput).
///
/// The client application cannot read the data directly from a
/// ImebraBaseStreamInput but must use a ImebraStreamReader. Several
/// ImebraStreamReader objects can read data from the same
/// ImebraBaseStreamInput object.
///
/// The ImebraStreamReader class is not thread-safe, but different
/// ImebraStreamReader objects in different threads can access the same
/// ImebraBaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraBaseStreamInput: NSObject

{
    @public
    define_imebra_object_holder(BaseStreamInput);
}

    -(id)initWithImebraBaseStreamInput:define_imebra_parameter(BaseStreamInput);

    -(void)dealloc;

@end


///
/// \brief Triggers a timeout on a selected stream if the class is not
///        deallocated within the specified amount of time.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraStreamTimeout: NSObject

{
    @public
    define_imebra_object_holder(StreamTimeout);
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
    -(id)initWithInputStream:(ImebraBaseStreamInput*)pStream timeoutSeconds:(unsigned int)timeoutSeconds;

    -(void)dealloc;

@end

#endif // !defined(imebraObjcBaseStreamInput__INCLUDED_)
