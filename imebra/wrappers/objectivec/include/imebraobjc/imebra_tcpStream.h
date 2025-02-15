/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTcpStream__INCLUDED_)
#define imebraObjcTcpStream__INCLUDED_

#import <Foundation/Foundation.h>

#include "imebra_macros.h"

@class ImebraTCPActiveAddress;
@class ImebraTCPAddress;
@class ImebraBaseStreamInput;
@class ImebraBaseStreamOutput;


///
/// \brief Represents a TCP stream.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraTCPStream: NSObject

{
    @public
    define_imebra_object_holder(TCPStream);
}

    -(id)initWithImebraTcpStream:define_imebra_parameter(TCPStream);

    -(void)dealloc;

    ///
    /// \brief Construct a TCP socket and connects it to the destination address.
    ///
    /// This is a non-blocking operation (the connection proceed after the
    /// constructor returns). Connection errors will be reported later while
    /// the communication happens.
    ///
    /// \param pAddress the address to which the socket has to be connected.
    /// \param pError   set to a StreamError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAddress:(ImebraTCPActiveAddress*)pAddress error:(NSError**)pError;

    ///
    /// \brief Returns the address of the connected peer.
    ///
    /// \param pError   set to a StreamError derived class in case of error
    /// \return the address of the connected peer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraTCPAddress*) getPeerAddress: (NSError**)pError;

    -(ImebraBaseStreamInput*) getStreamInput;

    -(ImebraBaseStreamOutput*) getStreamOutput;

@end


#endif // imebraObjcTcpStream__INCLUDED_
