/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_streamReader.h"
#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include <imebra/streamReader.h>


@implementation ImebraStreamReader

-(id)initWithImebraStreamReader:define_imebra_parameter(StreamReader)
{
    reset_imebra_object_holder(StreamReader);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(StreamReader, get_imebra_parameter(StreamReader));
    }
    else
    {
        delete get_imebra_parameter(StreamReader);
    }
    return self;

}

-(id)initWithInputStream:(ImebraBaseStreamInput*)pInput
{
    reset_imebra_object_holder(StreamReader);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(StreamReader, new imebra::StreamReader(*get_other_imebra_object_holder(pInput, BaseStreamInput)));
    }
    return self;

}

-(id)initWithInputStream:(ImebraBaseStreamInput*)pInput virtualStart:(unsigned int)virtualStart virtualEnd:(unsigned int)virtualEnd
{
    reset_imebra_object_holder(StreamReader);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(StreamReader, new imebra::StreamReader(*get_other_imebra_object_holder(pInput, BaseStreamInput), virtualStart, virtualEnd));
    }
    return self;

}

-(void)dealloc
{
    delete_imebra_object_holder(StreamReader);
}

-(ImebraStreamReader*)getVirtualStream:(unsigned int)virtualSize error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraStreamReader alloc] initWithImebraStreamReader:new imebra::StreamReader(get_imebra_object_holder(StreamReader)->getVirtualStream(virtualSize))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)terminate
{
    get_imebra_object_holder(StreamReader)->terminate();
}

@end
