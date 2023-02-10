/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/dicomhero6_objc/dicomhero_dicomDictionary.h"
#include "../include/dicomhero6_objc/dicomhero_tagId.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include "dicomhero_implementation_macros.h"
#include <dicomhero6/dicomDictionary.h>

@implementation DicomheroDicomDictionary

+(NSString*)getTagDescription:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(dicomhero::DicomDictionary::getTagDescription(*get_other_dicomhero_object_holder(tagId, TagId)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

+(DicomheroTagType)getTagType:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (DicomheroTagType)(dicomhero::DicomDictionary::getTagType(*get_other_dicomhero_object_holder(tagId, TagId)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(DicomheroTagTypeAE);
}

+(unsigned int)getMultiplicityMin:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)(dicomhero::DicomDictionary::getMultiplicityMin(*get_other_dicomhero_object_holder(tagId, TagId)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

+(unsigned int)getMultiplicityMax:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)(dicomhero::DicomDictionary::getMultiplicityMax(*get_other_dicomhero_object_holder(tagId, TagId)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

+(unsigned int)getMultiplicityStep:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)(dicomhero::DicomDictionary::getMultiplicityStep(*get_other_dicomhero_object_holder(tagId, TagId)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

+(unsigned int)getWordSize:(DicomheroTagType)dataType
{
    return (unsigned int)dicomhero::DicomDictionary::getWordSize((dicomhero::tagVR_t)dataType);
}

+(unsigned int)getMaxSize:(DicomheroTagType)dataType
{
    return (unsigned int)dicomhero::DicomDictionary::getMaxSize((dicomhero::tagVR_t)dataType);
}

@end
