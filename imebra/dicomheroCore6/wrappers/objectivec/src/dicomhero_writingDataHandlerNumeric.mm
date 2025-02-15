/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_writingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_readWriteMemory.h"
#import "../include/dicomhero6_objc/dicomhero_readMemory.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/writingDataHandlerNumeric.h>
#include <dicomhero6/readingDataHandlerNumeric.h>

@implementation DicomheroWritingDataHandlerNumeric

-(DicomheroMutableMemory*)getMemory:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        return [[DicomheroMutableMemory alloc] initWithDicomheroMutableMemory:new dicomhero::MutableMemory(((dicomhero::WritingDataHandlerNumeric*)get_dicomhero_object_holder(WritingDataHandler))->getMemory())];
    }
    else
    {
        return nil;
    }

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)assign:(NSData*)pSource error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        ((dicomhero::WritingDataHandlerNumeric*)get_dicomhero_object_holder(WritingDataHandler))->assign((char*)pSource.bytes, (size_t)pSource.length);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)copyFrom:(DicomheroReadingDataHandlerNumeric*)pSource error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        ((dicomhero::WritingDataHandlerNumeric*)get_dicomhero_object_holder(WritingDataHandler))->copyFrom(*((dicomhero::ReadingDataHandlerNumeric*)get_other_dicomhero_object_holder(pSource, ReadingDataHandler)));
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(unsigned int) unitSize
{
    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        return (unsigned int)((dicomhero::WritingDataHandlerNumeric*)get_dicomhero_object_holder(WritingDataHandler))->getUnitSize();
    }
    else
    {
        return 0;
    }
}

-(bool) isSigned
{
    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        return ((dicomhero::WritingDataHandlerNumeric*)get_dicomhero_object_holder(WritingDataHandler))->isSigned();
    }
    else
    {
        return false;
    }
}

-(bool) isFloat
{
    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        return ((dicomhero::WritingDataHandlerNumeric*)get_dicomhero_object_holder(WritingDataHandler))->isFloat();
    }
    else
    {
        return 0;
    }
}

@end
