/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_lut.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandlerNumeric.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_strings.h"
#include <dicomhero6/lut.h>
#include <dicomhero6/readingDataHandlerNumeric.h>

@implementation DicomheroLUT

-(id)initWithDicomheroLut:define_dicomhero_parameter(LUT)
{
    reset_dicomhero_object_holder(LUT);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(LUT, get_dicomhero_parameter(LUT));
    }
    else
    {
        delete get_dicomhero_parameter(LUT);
    }
    return self;

}

-(void)dealloc
{
    delete_dicomhero_object_holder(LUT);
}

-(DicomheroReadingDataHandlerNumeric*) getReadingDataHandler
{
    return [[DicomheroReadingDataHandlerNumeric alloc] initWithDicomheroReadingDataHandler:new dicomhero::ReadingDataHandlerNumeric(get_dicomhero_object_holder(LUT)->getReadingDataHandler())];
}

-(unsigned int)getMappedValue:(int)index
{
    return (unsigned int)get_dicomhero_object_holder(LUT)->getMappedValue((std::int32_t)index);
}

-(NSString*)description
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(LUT)->getDescription());
}

-(unsigned int) bits
{
    return (unsigned int)get_dicomhero_object_holder(LUT)->getBits();
}

-(unsigned int) size
{
    return (unsigned int)get_dicomhero_object_holder(LUT)->getSize();
}

-(int) firstMappedValue
{
    return (int)get_dicomhero_object_holder(LUT)->getFirstMapped();
}

@end


