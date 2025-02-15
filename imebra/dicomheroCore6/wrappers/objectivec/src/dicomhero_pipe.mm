/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_pipe.h"
#import "../include/dicomhero6_objc/dicomhero_baseStreamInput.h"
#import "../include/dicomhero6_objc/dicomhero_baseStreamOutput.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/pipeStream.h>
#include <dicomhero6/baseStreamInput.h>
#include <dicomhero6/baseStreamOutput.h>

@implementation DicomheroPipeStream

-(id)initWithBufferSize:(unsigned int)circularBufferSize
{
    reset_dicomhero_object_holder(PipeStream);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(PipeStream, new dicomhero::PipeStream((size_t)circularBufferSize));
    }
    return self;
}

-(void) close: (unsigned int) timeoutMilliseconds error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::PipeStream*)get_dicomhero_object_holder(PipeStream))->close(timeoutMilliseconds);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(DicomheroBaseStreamInput*) getStreamInput
{
    return [[DicomheroBaseStreamInput alloc] initWithDicomheroBaseStreamInput: new dicomhero::BaseStreamInput(get_dicomhero_object_holder(PipeStream)->getStreamInput())];
}

-(DicomheroBaseStreamOutput*) getStreamOutput
{
    return [[DicomheroBaseStreamOutput alloc] initWithDicomheroBaseStreamOutput: new dicomhero::BaseStreamOutput(get_dicomhero_object_holder(PipeStream)->getStreamOutput())];
}




@end
