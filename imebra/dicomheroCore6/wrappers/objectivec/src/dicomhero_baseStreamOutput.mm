/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_baseStreamOutput.h"
#include <dicomhero6/baseStreamOutput.h>
#include "dicomhero_implementation_macros.h"

@implementation DicomheroBaseStreamOutput

-(id)initWithDicomheroBaseStreamOutput:define_dicomhero_parameter(BaseStreamOutput)
{
    reset_dicomhero_object_holder(BaseStreamOutput);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(BaseStreamOutput, get_dicomhero_parameter(BaseStreamOutput));
    }
    else
    {
        delete get_dicomhero_parameter(BaseStreamOutput);
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(BaseStreamOutput);
}

@end

