/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import <Foundation/NSString.h>
#import "../include/imebraobjc/imebra_VOIDescription.h"
#include "imebra_implementation_macros.h"
#include "imebra_strings.h"
#include <imebra/VOIDescription.h>

@implementation ImebraVOIDescription

-(void)dealloc
{
    delete_imebra_object_holder(VOIDescription);
}

-(id)initWithImebraVOIDescription:define_imebra_parameter(VOIDescription)
{
    reset_imebra_object_holder(VOIDescription);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(VOIDescription, get_imebra_parameter(VOIDescription));
    }
    else
    {
        delete get_imebra_parameter(VOIDescription);
    }
    return self;
}

-(id)initWithCenter:(double)center width:(double)width function:(ImebraDicomVOIFunction)function description:(NSString*)description
{
    reset_imebra_object_holder(VOIDescription);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(VOIDescription, new imebra::VOIDescription(center, width, (imebra::dicomVOIFunction_t)function, imebra::NSStringToString(description)));
    }
    return self;
}

-(double)center
{
    return get_imebra_object_holder(VOIDescription)->getCenter();
}

-(double)width
{
    return get_imebra_object_holder(VOIDescription)->getWidth();
}

-(ImebraDicomVOIFunction)function
{
    return (ImebraDicomVOIFunction)(get_imebra_object_holder(VOIDescription)->getFunction());
}

-(NSString*)description
{
    return imebra::stringToNSString(get_imebra_object_holder(VOIDescription)->getDescription());
}

@end

