/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_tcpListener.h"
#import "../include/imebraobjc/imebra_tcpStream.h"
#import "../include/imebraobjc/imebra_tcpAddress.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/tcpListener.h>
#include <imebra/tcpStream.h>

@implementation ImebraTCPListener

-(id)initWithAddress:(ImebraTCPPassiveAddress*)pAddress error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(TCPListener);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TCPListener, new imebra::TCPListener(*(imebra::TCPPassiveAddress*)get_other_imebra_object_holder(pAddress, TCPAddress)));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)dealloc
{
    delete_imebra_object_holder(TCPListener);
}

-(ImebraTCPStream*)waitForConnection:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraTCPStream alloc] initWithImebraTcpStream:new imebra::TCPStream(get_imebra_object_holder(TCPListener)->waitForConnection())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)terminate
{
    get_imebra_object_holder(TCPListener)->terminate();
}

@end


