/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_lut.h"
#import "../include/imebraobjc/imebra_readingDataHandlerNumeric.h"
#include "imebra_implementation_macros.h"
#include "imebra_strings.h"
#include <imebra/lut.h>
#include <imebra/readingDataHandlerNumeric.h>

@implementation ImebraLUT

-(id)initWithImebraLut:define_imebra_parameter(LUT)
{
    reset_imebra_object_holder(LUT);
    self =  [super init];
    if(self)
    {
        set_imebra_object_holder(LUT, get_imebra_parameter(LUT));
    }
    else
    {
        delete get_imebra_parameter(LUT);
    }
    return self;

}

-(void)dealloc
{
    delete_imebra_object_holder(LUT);
}

-(ImebraReadingDataHandlerNumeric*) getReadingDataHandler
{
    return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:new imebra::ReadingDataHandlerNumeric(get_imebra_object_holder(LUT)->getReadingDataHandler())];
}

-(unsigned int)getMappedValue:(int)index
{
    return (unsigned int)get_imebra_object_holder(LUT)->getMappedValue((std::int32_t)index);
}

-(NSString*)description
{
    return imebra::stringToNSString(get_imebra_object_holder(LUT)->getDescription());
}

-(unsigned int) bits
{
    return (unsigned int)get_imebra_object_holder(LUT)->getBits();
}

-(unsigned int) size
{
    return (unsigned int)get_imebra_object_holder(LUT)->getSize();
}

-(int) firstMappedValue
{
    return (int)get_imebra_object_holder(LUT)->getFirstMapped();
}

@end


