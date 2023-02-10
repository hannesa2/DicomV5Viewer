/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebraobjc/imebra_dicomDictionary.h"
#include "../include/imebraobjc/imebra_tagId.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"
#include "imebra_implementation_macros.h"
#include <imebra/dicomDictionary.h>

@implementation ImebraDicomDictionary

+(NSString*)getTagDescription:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(imebra::DicomDictionary::getTagDescription(*get_other_imebra_object_holder(tagId, TagId)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

+(ImebraTagType)getTagType:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (ImebraTagType)(imebra::DicomDictionary::getTagType(*get_other_imebra_object_holder(tagId, TagId)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(ImebraTagTypeAE);
}

+(unsigned int)getMultiplicityMin:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)(imebra::DicomDictionary::getMultiplicityMin(*get_other_imebra_object_holder(tagId, TagId)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

+(unsigned int)getMultiplicityMax:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)(imebra::DicomDictionary::getMultiplicityMax(*get_other_imebra_object_holder(tagId, TagId)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

+(unsigned int)getMultiplicityStep:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)(imebra::DicomDictionary::getMultiplicityStep(*get_other_imebra_object_holder(tagId, TagId)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

+(unsigned int)getWordSize:(ImebraTagType)dataType
{
    return (unsigned int)imebra::DicomDictionary::getWordSize((imebra::tagVR_t)dataType);
}

+(unsigned int)getMaxSize:(ImebraTagType)dataType
{
    return (unsigned int)imebra::DicomDictionary::getMaxSize((imebra::tagVR_t)dataType);
}

@end
