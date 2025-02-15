/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcTcpListener__INCLUDED_)
#define dicomheroObjcTcpListener__INCLUDED_

#import <Foundation/Foundation.h>

#include "dicomhero_macros.h"

@class DicomheroTCPPassiveAddress;
@class DicomheroTCPStream;

///
/// \brief Represents listening TCP socket.
///
/// Once allocated the socket starts listening at the address declared in
/// the constructor.
///
/// A loop in the client application should call waitForConnection() in order
/// to retrieve all the connections accepted by the socket.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTCPListener: NSObject

{
    @public
    define_dicomhero_object_holder(TCPListener);
}

    /// \brief Initializer.
    ///
    /// Constructs a listening socket and starts listening for incoming
    /// connections.
    ///
    /// \param address the address to which the listening socket must be bound
    /// \param pError  set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAddress:(DicomheroTCPPassiveAddress*)pAddress error:(NSError**)pError;

    -(void)dealloc;

    /// \brief Waits for an incoming connection on the listening socket.
    ///
    /// The method blocks until a new connection is accepted or until the socket
    /// is closed, in which case pError is set to StreamClosedError.
    ///
    /// The socket is closed by the DicomheroTCPStream's destructor or by a call to
    /// terminate().
    ///
    /// \param pError set to a DicomheroStreamError derived class in case of error
    /// \return a new DicomheroTCPStream object bound to the new accepted connection.
    ///         The returned DicomheroTCPStream object will be owned by the caller
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroTCPStream*)waitForConnection:(NSError**)pError;

    ///
    /// \brief Instructs the listener to terminate any pending action.
    ///
    /// If a thread is in the method waitForConnection() then it will receive
    /// the exception StreamClosedError. StreamClosedError will be also be set
    /// for each subsequent call to waitForConnection().
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)terminate;

@end


#endif // dicomheroObjcTcpListener__INCLUDED_
