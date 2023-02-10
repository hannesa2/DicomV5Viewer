/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_readingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_writingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_readMemory.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/readingDataHandlerNumeric.h>
#include <imebra/writingDataHandlerNumeric.h>

@implementation ImebraReadingDataHandlerNumeric

-(ImebraMemory*)getMemory:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMemory alloc] initWithImebraMemory:new imebra::Memory(((imebra::ReadingDataHandlerNumeric*)get_imebra_object_holder(ReadingDataHandler))->getMemory())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)copyTo:(ImebraWritingDataHandlerNumeric*)destination error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::ReadingDataHandlerNumeric*)get_imebra_object_holder(ReadingDataHandler))->copyTo(*((imebra::WritingDataHandlerNumeric*)get_other_imebra_object_holder(destination,WritingDataHandler)));

    OBJC_IMEBRA_FUNCTION_END();
}

-(unsigned int) unitSize
{
    return (unsigned int)((imebra::ReadingDataHandlerNumeric*)get_imebra_object_holder(ReadingDataHandler))->getUnitSize();
}

-(bool) isSigned
{
    return ((imebra::ReadingDataHandlerNumeric*)get_imebra_object_holder(ReadingDataHandler))->isSigned();
}

-(bool) isFloat
{
    return ((imebra::ReadingDataHandlerNumeric*)get_imebra_object_holder(ReadingDataHandler))->isFloat();
}

@end
