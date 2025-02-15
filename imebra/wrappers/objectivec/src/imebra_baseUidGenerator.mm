/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_baseUidGenerator.h"
#include "imebra_implementation_macros.h"
#include "imebra_strings.h"
#include "imebra_nserror.h"
#include <imebra/baseUidGenerator.h>

@implementation ImebraBaseUIDGenerator

-(id)initWithImebraBaseUidGenerator:define_imebra_parameter(BaseUIDGenerator)
{
    reset_imebra_object_holder(BaseUIDGenerator);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(BaseUIDGenerator, get_imebra_parameter(BaseUIDGenerator));
    }
    else
    {
        delete get_imebra_parameter(BaseUIDGenerator);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(BaseUIDGenerator);
}

-(NSString*)getUID
{
    return imebra::stringToNSString(get_imebra_object_holder(BaseUIDGenerator)->getUID());
}

@end


