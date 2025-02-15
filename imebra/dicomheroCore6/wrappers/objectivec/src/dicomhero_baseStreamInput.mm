/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/dicomhero6_objc/dicomhero_baseStreamInput.h"
#include "dicomhero_implementation_macros.h"
#include <dicomhero6/baseStreamInput.h>

@implementation DicomheroBaseStreamInput

-(id)initWithDicomheroBaseStreamInput:define_dicomhero_parameter(BaseStreamInput)
{
    reset_dicomhero_object_holder(BaseStreamInput);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(BaseStreamInput, get_dicomhero_parameter(BaseStreamInput));
    }
    else
    {
        delete get_dicomhero_parameter(BaseStreamInput);
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(BaseStreamInput);
}

@end


@implementation DicomheroStreamTimeout

-(id)initWithInputStream:(DicomheroBaseStreamInput*)pStream timeoutSeconds:(unsigned int)timeoutSeconds
{
    reset_dicomhero_object_holder(StreamTimeout);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(StreamTimeout, new dicomhero::StreamTimeout(*get_other_dicomhero_object_holder(pStream, BaseStreamInput), (std::uint32_t)timeoutSeconds));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(StreamTimeout);
}

@end
