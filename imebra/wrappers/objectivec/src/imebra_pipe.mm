/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_pipe.h"
#import "../include/imebraobjc/imebra_baseStreamInput.h"
#import "../include/imebraobjc/imebra_baseStreamOutput.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/pipeStream.h>
#include <imebra/baseStreamInput.h>
#include <imebra/baseStreamOutput.h>

@implementation ImebraPipeStream

-(id)initWithBufferSize:(unsigned int)circularBufferSize
{
    reset_imebra_object_holder(PipeStream);
    self =  [super init];
    if(self)
    {
        set_imebra_object_holder(PipeStream, new imebra::PipeStream((size_t)circularBufferSize));
    }
    return self;
}

-(void) close: (unsigned int) timeoutMilliseconds error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::PipeStream*)get_imebra_object_holder(PipeStream))->close(timeoutMilliseconds);

    OBJC_IMEBRA_FUNCTION_END();
}

-(ImebraBaseStreamInput*) getStreamInput
{
    return [[ImebraBaseStreamInput alloc] initWithImebraBaseStreamInput: new imebra::BaseStreamInput(get_imebra_object_holder(PipeStream)->getStreamInput())];
}

-(ImebraBaseStreamOutput*) getStreamOutput
{
    return [[ImebraBaseStreamOutput alloc] initWithImebraBaseStreamOutput: new imebra::BaseStreamOutput(get_imebra_object_holder(PipeStream)->getStreamOutput())];
}




@end
