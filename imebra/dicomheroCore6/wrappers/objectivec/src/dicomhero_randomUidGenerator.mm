/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/


#import "../include/dicomhero6_objc/dicomhero_randomUidGenerator.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include <dicomhero6/randomUidGenerator.h>

@implementation DicomheroRandomUIDGenerator

-(id)initWithRoot:(NSString*)root departmentId:(unsigned int)departmentId modelId:(unsigned int)modelId
{
    reset_dicomhero_object_holder(BaseUIDGenerator);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(BaseUIDGenerator, new dicomhero::RandomUIDGenerator(
                                     dicomhero::NSStringToString(root),
                                     departmentId,
                                     modelId));
    }
    return self;
}


@end

