/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_streamWriter.h"
#import "../include/imebraobjc/imebra_baseStreamOutput.h"

#include "imebra_implementation_macros.h"
#include <imebra/streamWriter.h>
#include <imebra/baseStreamInput.h>
#include <imebra/baseStreamOutput.h>

@implementation ImebraStreamWriter: NSObject

-(id)initWithImebraStreamWriter:define_imebra_parameter(StreamWriter)
{
    reset_imebra_object_holder(StreamWriter);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(StreamWriter, get_imebra_parameter(StreamWriter));
    }
    else
    {
        delete get_imebra_parameter(StreamWriter);
    }
    return self;
}

-(id)initWithOutputStream:(ImebraBaseStreamOutput*)pOutput
{
    reset_imebra_object_holder(StreamWriter);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(StreamWriter, new imebra::StreamWriter(*get_other_imebra_object_holder(pOutput, BaseStreamOutput)));
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(StreamWriter);
}

@end



