/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dicomDictionary.cpp
    \brief Implementation of the class DicomDictionary class.

*/

#include "../include/dicomhero6/dicomDictionary.h"
#include "../include/dicomhero6/definitions.h"
#include "../include/dicomhero6/tagId.h"
#include "../implementation/dicomDictImpl.h"
#include "../implementation/charsetConversionImpl.h"
#include "../implementation/exceptionImpl.h"
#include <memory>

namespace dicomhero
{

std::wstring DicomDictionary::getUnicodeTagDescription(const TagId& id)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getTagDescription(id.getGroupId(), id.getTagId());

    DICOMHERO_FUNCTION_END_LOG();
}

std::string DicomDictionary::getTagDescription(const TagId& id)
{
    DICOMHERO_FUNCTION_START();

    std::wstring name = implementation::dicomDictionary::getDicomDictionary()->getTagDescription(id.getGroupId(), id.getTagId());
    charsetsList_t charsets;
    charsets.push_back(charsetDictionary::getDefaultCharset());
    return implementation::dicomConversion::convertFromUnicode(name, charsets);

    DICOMHERO_FUNCTION_END_LOG();
}

tagVR_t DicomDictionary::getTagType(const TagId& id)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getTagType(id.getGroupId(), id.getTagId());

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DicomDictionary::getMultiplicityMin(const TagId& id)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getTagMultiplicityMin(id.getGroupId(), id.getTagId());

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DicomDictionary::getMultiplicityMax(const TagId& id)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getTagMultiplicityMax(id.getGroupId(), id.getTagId());

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DicomDictionary::getMultiplicityStep(const TagId& id)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getTagMultiplicityStep(id.getGroupId(), id.getTagId());

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DicomDictionary::getWordSize(tagVR_t dataType)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getWordSize(dataType);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DicomDictionary::getMaxSize(tagVR_t dataType)
{
    DICOMHERO_FUNCTION_START();

    return implementation::dicomDictionary::getDicomDictionary()->getMaxSize(dataType);

    DICOMHERO_FUNCTION_END_LOG();
}

}

