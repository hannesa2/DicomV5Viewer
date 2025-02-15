/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_readingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_readMemory.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/readingDataHandlerNumeric.h>
#include <dicomhero6/writingDataHandlerNumeric.h>

@implementation DicomheroReadingDataHandlerNumeric

-(DicomheroMemory*)getMemory:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroMemory alloc] initWithDicomheroMemory:new dicomhero::Memory(((dicomhero::ReadingDataHandlerNumeric*)get_dicomhero_object_holder(ReadingDataHandler))->getMemory())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)copyTo:(DicomheroWritingDataHandlerNumeric*)destination error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    ((dicomhero::ReadingDataHandlerNumeric*)get_dicomhero_object_holder(ReadingDataHandler))->copyTo(*((dicomhero::WritingDataHandlerNumeric*)get_other_dicomhero_object_holder(destination,WritingDataHandler)));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(unsigned int) unitSize
{
    return (unsigned int)((dicomhero::ReadingDataHandlerNumeric*)get_dicomhero_object_holder(ReadingDataHandler))->getUnitSize();
}

-(bool) isSigned
{
    return ((dicomhero::ReadingDataHandlerNumeric*)get_dicomhero_object_holder(ReadingDataHandler))->isSigned();
}

-(bool) isFloat
{
    return ((dicomhero::ReadingDataHandlerNumeric*)get_dicomhero_object_holder(ReadingDataHandler))->isFloat();
}

@end
