/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/


#import "../include/imebraobjc/imebra_tcpStream.h"
#import "../include/imebraobjc/imebra_tcpAddress.h"
#import "../include/imebraobjc/imebra_baseStreamInput.h"
#import "../include/imebraobjc/imebra_baseStreamOutput.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/tcpStream.h>
#include <imebra/tcpAddress.h>

@implementation ImebraTCPStream

-(id)initWithImebraTcpStream:define_imebra_parameter(TCPStream)
{
    reset_imebra_object_holder(TCPStream);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TCPStream, get_imebra_parameter(TCPStream));
    }
    else
    {
        delete get_imebra_parameter(TCPStream);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(TCPStream);
}

-(id)initWithAddress:(ImebraTCPActiveAddress*)pAddress error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(TCPStream);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TCPStream, new imebra::TCPStream(*(imebra::TCPActiveAddress*)get_other_imebra_object_holder(pAddress, TCPAddress)));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraTCPAddress*) getPeerAddress: (NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraTCPAddress alloc] initWithImebraTCPAddress:new imebra::TCPAddress(get_imebra_object_holder(TCPStream)->getPeerAddress())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraBaseStreamInput*) getStreamInput
{
    return [[ImebraBaseStreamInput alloc] initWithImebraBaseStreamInput: new imebra::BaseStreamInput(get_imebra_object_holder(TCPStream)->getStreamInput())];
}

-(ImebraBaseStreamOutput*) getStreamOutput
{
    return [[ImebraBaseStreamOutput alloc] initWithImebraBaseStreamOutput: new imebra::BaseStreamOutput(get_imebra_object_holder(TCPStream)->getStreamOutput())];
}



@end


