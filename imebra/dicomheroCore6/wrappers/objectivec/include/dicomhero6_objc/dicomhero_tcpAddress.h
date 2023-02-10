/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcTcpAddress__INCLUDED_)
#define dicomheroObjcTcpAddress__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

///
/// \brief Represents a TCP address.
///
/// Use DicomheroTCPActiveAddress to manage an address of an active socket
/// (a socket that initiates the connection) and DicomheroTCPPassiveAddress for
/// a passive socket (a socket that listens for incoming connections).
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTCPAddress: NSObject

{
    @public
    define_dicomhero_object_holder(TCPAddress);
}

    -(id)initWithDicomheroTCPAddress:define_dicomhero_parameter(TCPAddress);

    -(void)dealloc;

    ///
    /// \brief Returns the node part of the TCP address.
    ///
    /// The TCP address is composed by two parts:
    /// - the node which identifies the machine in the network
    /// - the service which identifies one of the ports (services) in the
    ///   machine
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* node;

    ///
    /// \brief Returns the service part of the TCP address (the port number or
    ///        name, eg. "80" or "HTTP").
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* service;

@end


///
/// \brief Represents an address of an active socket (a socket that initiates
///        the connection with the peer).
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTCPActiveAddress: DicomheroTCPAddress

    ///
    /// \brief Initializer.
    ///
    /// Constructs an active TCP address from a node and a service description.
    ///
    /// The node may be a host name or address (both IPv4 and IPv6) while the
    /// service name may be a port number (in string format) or name (e.g.
    /// "FTP").
    ///
    /// \param node    the host name or address (e.g. "192.168.10.20" or
    ///                "example.com"). Use an empty string to refer to the
    ///                local host.
    /// \param service the service port (in string format) or name (e.g.
    ///                "140" or "ftp").
    /// \param pError  set to a NSError derived class in case of errors
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithNode:(NSString*)node service:(NSString*)service error:(NSError**)pError;

@end


///
/// \brief Represents an address of a passive socket (a socket that listens
///        for connections initiated by the peers).
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroTCPPassiveAddress: DicomheroTCPAddress

    ///
    /// \brief Initializer.
    ///
    /// Constructs a passive TCP address from a node and a service description.
    ///
    /// The node may be a host name or address (both IPv4 and IPv6) while the
    /// service name may be a port number (in string format) or name (e.g.
    /// "FTP").
    ///
    /// \param node    the host name or address (e.g. "192.168.10.20" or
    ///                "example.com"). Use an empty string to refer to all the
    ///                TCP devices on the local host.
    /// \param service the service port (in string format) or name (e.g.
    ///                "140" or "ftp").
    /// \param pError  set to a NSError derived class in case of errors
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithNode:(NSString*)node service:(NSString*)service error:(NSError**)pError;

@end

#endif // dicomheroObjcTcpAddress__INCLUDED_
