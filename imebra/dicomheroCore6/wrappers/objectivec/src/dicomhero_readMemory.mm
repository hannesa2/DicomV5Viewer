/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_readMemory.h"

#include "dicomhero_implementation_macros.h"
#include <dicomhero6/memory.h>

@implementation DicomheroMemory

-(id)initWithDicomheroMemory:define_dicomhero_parameter(Memory)
{
    reset_dicomhero_object_holder(Memory);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Memory, get_dicomhero_parameter(Memory));
    }
    else
    {
        delete get_dicomhero_parameter(Memory);
    }
    return self;
}

-(id)init
{
    reset_dicomhero_object_holder(Memory);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Memory, new dicomhero::Memory());
    }
    return self;
}


-(id)initWithData:(NSData*)pSource
{
    reset_dicomhero_object_holder(Memory);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Memory, new dicomhero::Memory((char*)pSource.bytes, (size_t)pSource.length));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(Memory);
}

-(NSData*)data
{
    size_t dataSize;
    const char* pMemory(get_dicomhero_object_holder(Memory)->data(&dataSize));
    NSData* pData = [NSData dataWithBytes:pMemory length:dataSize];
    return pData;
}

-(bool)empty
{
    return get_dicomhero_object_holder(Memory)->empty();

}


@end


