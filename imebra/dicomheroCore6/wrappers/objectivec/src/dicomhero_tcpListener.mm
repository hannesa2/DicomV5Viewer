/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_tcpListener.h"
#import "../include/dicomhero6_objc/dicomhero_tcpStream.h"
#import "../include/dicomhero6_objc/dicomhero_tcpAddress.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/tcpListener.h>
#include <dicomhero6/tcpStream.h>

@implementation DicomheroTCPListener

-(id)initWithAddress:(DicomheroTCPPassiveAddress*)pAddress error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(TCPListener);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TCPListener, new dicomhero::TCPListener(*(dicomhero::TCPPassiveAddress*)get_other_dicomhero_object_holder(pAddress, TCPAddress)));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)dealloc
{
    delete_dicomhero_object_holder(TCPListener);
}

-(DicomheroTCPStream*)waitForConnection:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroTCPStream alloc] initWithDicomheroTcpStream:new dicomhero::TCPStream(get_dicomhero_object_holder(TCPListener)->waitForConnection())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)terminate
{
    get_dicomhero_object_holder(TCPListener)->terminate();
}

@end


