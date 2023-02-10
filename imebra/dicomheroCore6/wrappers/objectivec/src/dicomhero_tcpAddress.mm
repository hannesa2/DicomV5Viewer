/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_tcpAddress.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_strings.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/tcpAddress.h>

@implementation DicomheroTCPAddress

-(id)initWithDicomheroTCPAddress:define_dicomhero_parameter(TCPAddress)
{
    reset_dicomhero_object_holder(TCPAddress);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TCPAddress, get_dicomhero_parameter(TCPAddress));
    }
    else
    {
        delete get_dicomhero_parameter(TCPAddress);
    }
    return self;

}


-(void)dealloc
{
    delete_dicomhero_object_holder(TCPAddress);
}

-(NSString*) node
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(TCPAddress)->getNode());
}

-(NSString*) service
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(TCPAddress)->getService());
}

@end


@implementation DicomheroTCPActiveAddress

-(id)initWithNode:(NSString*)node service:(NSString*)service error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(TCPAddress);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TCPAddress, new dicomhero::TCPActiveAddress(dicomhero::NSStringToString(node), dicomhero::NSStringToString(service)));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end


@implementation DicomheroTCPPassiveAddress

-(id)initWithNode:(NSString*)node service:(NSString*)service error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(TCPAddress);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TCPAddress, new dicomhero::TCPPassiveAddress(dicomhero::NSStringToString(node), dicomhero::NSStringToString(service)));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end

