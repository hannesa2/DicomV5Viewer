/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_memoryStreamOutput.h"
#import "../include/dicomhero6_objc/dicomhero_readWriteMemory.h"
#include "dicomhero_implementation_macros.h"
#include <dicomhero6/memoryStreamOutput.h>
#include <dicomhero6/mutableMemory.h>

@implementation DicomheroMemoryStreamOutput

-(id)initWithMutableMemory:(DicomheroMutableMemory*)pMemory
{
    reset_dicomhero_object_holder(BaseStreamOutput);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(BaseStreamOutput, new dicomhero::MemoryStreamOutput(*(dicomhero::MutableMemory*)get_other_dicomhero_object_holder(pMemory, Memory)));
    }
    return self;
}


@end



