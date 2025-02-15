/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_tcpAddress.h"

#include "imebra_implementation_macros.h"
#include "imebra_strings.h"
#include "imebra_nserror.h"

#include <imebra/tcpAddress.h>

@implementation ImebraTCPAddress

-(id)initWithImebraTCPAddress:define_imebra_parameter(TCPAddress)
{
    reset_imebra_object_holder(TCPAddress);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TCPAddress, get_imebra_parameter(TCPAddress));
    }
    else
    {
        delete get_imebra_parameter(TCPAddress);
    }
    return self;

}


-(void)dealloc
{
    delete_imebra_object_holder(TCPAddress);
}

-(NSString*) node
{
    return imebra::stringToNSString(get_imebra_object_holder(TCPAddress)->getNode());
}

-(NSString*) service
{
    return imebra::stringToNSString(get_imebra_object_holder(TCPAddress)->getService());
}

@end


@implementation ImebraTCPActiveAddress

-(id)initWithNode:(NSString*)node service:(NSString*)service error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(TCPAddress);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TCPAddress, new imebra::TCPActiveAddress(imebra::NSStringToString(node), imebra::NSStringToString(service)));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


@implementation ImebraTCPPassiveAddress

-(id)initWithNode:(NSString*)node service:(NSString*)service error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(TCPAddress);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TCPAddress, new imebra::TCPPassiveAddress(imebra::NSStringToString(node), imebra::NSStringToString(service)));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end

