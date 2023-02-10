/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_readWriteMemory.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/mutableMemory.h>

@implementation DicomheroMutableMemory

-(id)initWithDicomheroMutableMemory:define_dicomhero_parameter(MutableMemory)
{
    return [super initWithDicomheroMemory:get_dicomhero_parameter(MutableMemory)];
}

-(id)init
{
    return [super initWithDicomheroMemory:new dicomhero::MutableMemory()];
}

-(id)initWithSize:(unsigned int)size
{
    return [super initWithDicomheroMemory:new dicomhero::MutableMemory((size_t)size)];
}

-(id)initWithMemory:(DicomheroMemory*)source
{
    return [super initWithDicomheroMemory:(new dicomhero::MutableMemory(*get_other_dicomhero_object_holder(source, Memory)))];
}

-(id)initWithData:(NSData*)pSource
{
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Memory, new dicomhero::MutableMemory((char*)pSource.bytes, (size_t)pSource.length));
    }
    return self;
}

-(void)copyFrom:(DicomheroMemory*)source error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::MutableMemory*)get_dicomhero_object_holder(Memory))->copyFrom(*get_other_dicomhero_object_holder(source, Memory));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)clear:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::MutableMemory*)get_dicomhero_object_holder(Memory))->clear();

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)resize:(unsigned int)newSize error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::MutableMemory*)get_dicomhero_object_holder(Memory))->resize((size_t)newSize);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)reserve:(unsigned int)reserveSize error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::MutableMemory*)get_dicomhero_object_holder(Memory))->reserve((size_t)reserveSize);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)assign:(NSData*)pSource error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::MutableMemory*)get_dicomhero_object_holder(Memory))->assign((char*)pSource.bytes, (size_t)pSource.length);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)assignRegion:(NSData*)pSource offset:(unsigned int)destinationOffset error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::MutableMemory*)get_dicomhero_object_holder(Memory))->assignRegion((char*)pSource.bytes, (size_t)pSource.length, (size_t)destinationOffset);

    OBJC_DICOMHERO_FUNCTION_END();
}

@end
