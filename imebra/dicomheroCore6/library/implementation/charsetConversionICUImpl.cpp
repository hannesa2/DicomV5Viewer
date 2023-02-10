/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file charsetConversionICU.cpp
    \brief Implementation of the charsetConversion class using the ICU library.

*/

#include "configurationImpl.h"
#if defined(DICOMHERO_USE_ICU)

#include "exceptionImpl.h"
#include "charsetConversionICUImpl.h"
#include "../include/dicomhero6/exceptions.h"
#include <memory>

namespace dicomhero
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
charsetConversionICU::charsetConversionICU(const charsetInformation& charsetInformation)
{
    DICOMHERO_FUNCTION_START();

    UErrorCode errorCode(U_ZERO_ERROR);

    m_pIcuConverter = ucnv_open(charsetInformation.m_isoRegistration.c_str(), &errorCode);
    if(U_FAILURE(errorCode))
    {
        DICOMHERO_THROW(CharsetConversionNoSupportedTableError, "ICU library returned error " << errorCode << " for table " << charsetInformation.m_isoRegistration);
    }
    ucnv_setSubstChars(m_pIcuConverter, "?", 1, &errorCode);
    if(U_FAILURE(errorCode))
    {
        DICOMHERO_THROW(CharsetConversionNoSupportedTableError, "ICU library returned error " << errorCode << " while setting the substitution char for table " << charsetInformation.m_isoRegistration);
    }

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
charsetConversionICU::~charsetConversionICU()
{
    ucnv_close(m_pIcuConverter);
}



///////////////////////////////////////////////////////////
//
// Convert a string from unicode to multibyte
//
///////////////////////////////////////////////////////////
std::string charsetConversionICU::fromUnicode(const std::wstring& unicodeString) const
{
    DICOMHERO_FUNCTION_START();

    if(unicodeString.empty())
    {
        return std::string();
    }

    UnicodeString unicodeStringConversion;
    switch(sizeof(wchar_t))
    {
    case 2:
        unicodeStringConversion = UnicodeString((UChar*)&(unicodeString[0]), (std::int32_t)unicodeString.size());
        break;
    case 4:
        unicodeStringConversion = UnicodeString::fromUTF32((UChar32*)&(unicodeString[0]), (std::int32_t)unicodeString.size());
        break;
    }
    UErrorCode errorCode(U_ZERO_ERROR);
    int32_t conversionLength = unicodeStringConversion.extract(0, 0, m_pIcuConverter, errorCode);
    errorCode = U_ZERO_ERROR;
    std::string returnString((size_t)conversionLength, char(0));
    unicodeStringConversion.extract(&(returnString[0]), conversionLength, m_pIcuConverter, errorCode);
    if(U_FAILURE(errorCode))
    {
        DICOMHERO_THROW(CharsetConversionError, "ICU library returned error " << errorCode);
    }
    if(returnString == "?" && unicodeString != L"?")
    {
        return "";
    }
    return returnString;

	DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from multibyte to unicode
//
///////////////////////////////////////////////////////////
std::wstring charsetConversionICU::toUnicode(const std::string& asciiString) const
{
    DICOMHERO_FUNCTION_START();

    if(asciiString.empty())
    {
        return std::wstring();
    }

    UErrorCode errorCode(U_ZERO_ERROR);
    UnicodeString unicodeString(&(asciiString[0]), (std::int32_t)asciiString.size(), m_pIcuConverter, errorCode);
    if(sizeof(wchar_t) == 2)
    {
        std::wstring returnString((size_t)unicodeString.length(), wchar_t(0));
        unicodeString.extract((UChar*)&(returnString[0]), unicodeString.length(), errorCode);
        return returnString;
    }

	DICOMHERO_FUNCTION_END();
}



} // namespace dicomhero



#endif
