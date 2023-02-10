/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebraobjc/imebra_baseStreamInput.h"
#include "imebra_implementation_macros.h"
#include <imebra/baseStreamInput.h>

@implementation ImebraBaseStreamInput

-(id)initWithImebraBaseStreamInput:define_imebra_parameter(BaseStreamInput)
{
    reset_imebra_object_holder(BaseStreamInput);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(BaseStreamInput, get_imebra_parameter(BaseStreamInput));
    }
    else
    {
        delete get_imebra_parameter(BaseStreamInput);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(BaseStreamInput);
}

@end


@implementation ImebraStreamTimeout

-(id)initWithInputStream:(ImebraBaseStreamInput*)pStream timeoutSeconds:(unsigned int)timeoutSeconds
{
    reset_imebra_object_holder(StreamTimeout);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(StreamTimeout, new imebra::StreamTimeout(*get_other_imebra_object_holder(pStream, BaseStreamInput), (std::uint32_t)timeoutSeconds));
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(StreamTimeout);
}

@end
