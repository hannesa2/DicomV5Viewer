/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_readWriteMemory.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include <imebra/mutableMemory.h>

@implementation ImebraMutableMemory

-(id)initWithImebraMutableMemory:define_imebra_parameter(MutableMemory)
{
    return [super initWithImebraMemory:get_imebra_parameter(MutableMemory)];
}

-(id)init
{
    return [super initWithImebraMemory:new imebra::MutableMemory()];
}

-(id)initWithSize:(unsigned int)size
{
    return [super initWithImebraMemory:new imebra::MutableMemory((size_t)size)];
}

-(id)initWithMemory:(ImebraMemory*)source
{
    return [super initWithImebraMemory:(new imebra::MutableMemory(*get_other_imebra_object_holder(source, Memory)))];
}

-(id)initWithData:(NSData*)pSource
{
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Memory, new imebra::MutableMemory((char*)pSource.bytes, (size_t)pSource.length));
    }
    return self;
}

-(void)copyFrom:(ImebraMemory*)source error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableMemory*)get_imebra_object_holder(Memory))->copyFrom(*get_other_imebra_object_holder(source, Memory));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)clear:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableMemory*)get_imebra_object_holder(Memory))->clear();

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)resize:(unsigned int)newSize error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableMemory*)get_imebra_object_holder(Memory))->resize((size_t)newSize);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)reserve:(unsigned int)reserveSize error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableMemory*)get_imebra_object_holder(Memory))->reserve((size_t)reserveSize);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)assign:(NSData*)pSource error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableMemory*)get_imebra_object_holder(Memory))->assign((char*)pSource.bytes, (size_t)pSource.length);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)assignRegion:(NSData*)pSource offset:(unsigned int)destinationOffset error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableMemory*)get_imebra_object_holder(Memory))->assignRegion((char*)pSource.bytes, (size_t)pSource.length, (size_t)destinationOffset);

    OBJC_IMEBRA_FUNCTION_END();
}

@end
