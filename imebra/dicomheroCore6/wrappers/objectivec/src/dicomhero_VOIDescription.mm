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
#import "../include/dicomhero6_objc/dicomhero_VOIDescription.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_strings.h"
#include <dicomhero6/VOIDescription.h>

@implementation DicomheroVOIDescription

-(void)dealloc
{
    delete_dicomhero_object_holder(VOIDescription);
}

-(id)initWithDicomheroVOIDescription:define_dicomhero_parameter(VOIDescription)
{
    reset_dicomhero_object_holder(VOIDescription);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(VOIDescription, get_dicomhero_parameter(VOIDescription));
    }
    else
    {
        delete get_dicomhero_parameter(VOIDescription);
    }
    return self;
}

-(id)initWithCenter:(double)center width:(double)width function:(ImebraDicomVOIFunction)function description:(NSString*)description
{
    reset_dicomhero_object_holder(VOIDescription);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(VOIDescription, new dicomhero::VOIDescription(center, width, (dicomhero::dicomVOIFunction_t)function, dicomhero::NSStringToString(description)));
    }
    return self;
}

-(double)center
{
    return get_dicomhero_object_holder(VOIDescription)->getCenter();
}

-(double)width
{
    return get_dicomhero_object_holder(VOIDescription)->getWidth();
}

-(ImebraDicomVOIFunction)function
{
    return (ImebraDicomVOIFunction)(get_dicomhero_object_holder(VOIDescription)->getFunction());
}

-(NSString*)description
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(VOIDescription)->getDescription());
}

@end

