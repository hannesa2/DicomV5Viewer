/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_baseStreamOutput.h"
#include <imebra/baseStreamOutput.h>
#include "imebra_implementation_macros.h"

@implementation ImebraBaseStreamOutput

-(id)initWithImebraBaseStreamOutput:define_imebra_parameter(BaseStreamOutput)
{
    reset_imebra_object_holder(BaseStreamOutput);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(BaseStreamOutput, get_imebra_parameter(BaseStreamOutput));
    }
    else
    {
        delete get_imebra_parameter(BaseStreamOutput);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(BaseStreamOutput);
}

@end

