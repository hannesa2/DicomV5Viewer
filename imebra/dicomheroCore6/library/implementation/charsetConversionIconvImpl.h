/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file charsetConversionIconv.h
    \brief Declaration of the class used to convert a string between different
            charsets using the Iconv library.

The class hides the platform specific implementations and supplies a common
 interface for the charsets translations.

*/

#if !defined(imebraCharsetConversionIconv_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversionIconv_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#if defined(DICOMHERO_USE_ICONV)

#include "charsetConversionBaseImpl.h"

#include <iconv.h>
#include <errno.h>


namespace dicomhero
{

class charsetConversionIconv: public charsetConversionBase
{
public:
    charsetConversionIconv(const charsetInformation& charsetInformation);
    virtual ~charsetConversionIconv() override;

    virtual std::string fromUnicode(const std::wstring& unicodeString) const override;

    virtual std::wstring toUnicode(const std::string& asciiString) const override;

protected:

#if defined(DICOMHERO_WINDOWS)
    std::string myIconv(iconv_t context, const char* inputString, size_t inputStringLengthBytes) const;
#else
    std::string myIconv(iconv_t context, char* inputString, size_t inputStringLengthBytes) const;
#endif
    iconv_t m_iconvToUnicode;
    iconv_t m_iconvFromUnicode;
};

typedef charsetConversionIconv defaultCharsetConversion;

} // namespace dicomhero

#endif // defined(DICOMHERO_USE_ICONV)

#endif // !defined(imebraCharsetConversionIconv_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
