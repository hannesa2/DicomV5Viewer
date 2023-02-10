/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/


#import "../include/dicomhero6_objc/dicomhero_tcpStream.h"
#import "../include/dicomhero6_objc/dicomhero_tcpAddress.h"
#import "../include/dicomhero6_objc/dicomhero_baseStreamInput.h"
#import "../include/dicomhero6_objc/dicomhero_baseStreamOutput.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/tcpStream.h>
#include <dicomhero6/tcpAddress.h>

@implementation DicomheroTCPStream

-(id)initWithDicomheroTcpStream:define_dicomhero_parameter(TCPStream)
{
    reset_dicomhero_object_holder(TCPStream);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TCPStream, get_dicomhero_parameter(TCPStream));
    }
    else
    {
        delete get_dicomhero_parameter(TCPStream);
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(TCPStream);
}

-(id)initWithAddress:(DicomheroTCPActiveAddress*)pAddress error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(TCPStream);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TCPStream, new dicomhero::TCPStream(*(dicomhero::TCPActiveAddress*)get_other_dicomhero_object_holder(pAddress, TCPAddress)));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroTCPAddress*) getPeerAddress: (NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroTCPAddress alloc] initWithDicomheroTCPAddress:new dicomhero::TCPAddress(get_dicomhero_object_holder(TCPStream)->getPeerAddress())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroBaseStreamInput*) getStreamInput
{
    return [[DicomheroBaseStreamInput alloc] initWithDicomheroBaseStreamInput: new dicomhero::BaseStreamInput(get_dicomhero_object_holder(TCPStream)->getStreamInput())];
}

-(DicomheroBaseStreamOutput*) getStreamOutput
{
    return [[DicomheroBaseStreamOutput alloc] initWithDicomheroBaseStreamOutput: new dicomhero::BaseStreamOutput(get_dicomhero_object_holder(TCPStream)->getStreamOutput())];
}



@end


