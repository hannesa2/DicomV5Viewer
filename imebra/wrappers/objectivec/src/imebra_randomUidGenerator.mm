/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/


#import "../include/imebraobjc/imebra_randomUidGenerator.h"
#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"
#include <imebra/randomUidGenerator.h>

@implementation ImebraRandomUIDGenerator

-(id)initWithRoot:(NSString*)root departmentId:(unsigned int)departmentId modelId:(unsigned int)modelId
{
    reset_imebra_object_holder(BaseUIDGenerator);
    self =  [super init];
    if(self)
    {
        set_imebra_object_holder(BaseUIDGenerator, new imebra::RandomUIDGenerator(
                                     imebra::NSStringToString(root),
                                     departmentId,
                                     modelId));
    }
    return self;
}


@end

