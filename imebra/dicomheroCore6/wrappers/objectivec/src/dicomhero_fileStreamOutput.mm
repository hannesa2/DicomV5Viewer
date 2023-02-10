/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/dicomhero6_objc/dicomhero_fileStreamOutput.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include <dicomhero6/fileStreamOutput.h>

@implementation DicomheroFileStreamOutput

-(id)initWithName:(NSString*)fileName error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(BaseStreamOutput);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(BaseStreamOutput, new dicomhero::FileStreamOutput(dicomhero::NSStringToString(fileName)));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


@end
