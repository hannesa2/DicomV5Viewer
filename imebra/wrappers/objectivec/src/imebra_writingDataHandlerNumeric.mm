/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_writingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_readingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_readWriteMemory.h"
#import "../include/imebraobjc/imebra_readMemory.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/writingDataHandlerNumeric.h>
#include <imebra/readingDataHandlerNumeric.h>

@implementation ImebraWritingDataHandlerNumeric

-(ImebraMutableMemory*)getMemory:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    if(get_imebra_object_holder(WritingDataHandler) != nullptr)
    {
        return [[ImebraMutableMemory alloc] initWithImebraMutableMemory:new imebra::MutableMemory(((imebra::WritingDataHandlerNumeric*)get_imebra_object_holder(WritingDataHandler))->getMemory())];
    }
    else
    {
        return nil;
    }

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)assign:(NSData*)pSource error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    if(get_imebra_object_holder(WritingDataHandler) != nullptr)
    {
        ((imebra::WritingDataHandlerNumeric*)get_imebra_object_holder(WritingDataHandler))->assign((char*)pSource.bytes, (size_t)pSource.length);
    }

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)copyFrom:(ImebraReadingDataHandlerNumeric*)pSource error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    if(get_imebra_object_holder(WritingDataHandler) != nullptr)
    {
        ((imebra::WritingDataHandlerNumeric*)get_imebra_object_holder(WritingDataHandler))->copyFrom(*((imebra::ReadingDataHandlerNumeric*)get_other_imebra_object_holder(pSource, ReadingDataHandler)));
    }

    OBJC_IMEBRA_FUNCTION_END();
}

-(unsigned int) unitSize
{
    if(get_imebra_object_holder(WritingDataHandler) != nullptr)
    {
        return (unsigned int)((imebra::WritingDataHandlerNumeric*)get_imebra_object_holder(WritingDataHandler))->getUnitSize();
    }
    else
    {
        return 0;
    }
}

-(bool) isSigned
{
    if(get_imebra_object_holder(WritingDataHandler) != nullptr)
    {
        return ((imebra::WritingDataHandlerNumeric*)get_imebra_object_holder(WritingDataHandler))->isSigned();
    }
    else
    {
        return false;
    }
}

-(bool) isFloat
{
    if(get_imebra_object_holder(WritingDataHandler) != nullptr)
    {
        return ((imebra::WritingDataHandlerNumeric*)get_imebra_object_holder(WritingDataHandler))->isFloat();
    }
    else
    {
        return 0;
    }
}

@end
