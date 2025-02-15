/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(imebraCharsetConversion_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversion_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "configurationImpl.h"
#include "charsetConversionIconvImpl.h"
#include "charsetConversionICUImpl.h"
#include "charsetConversionWindowsImpl.h"
#include "charsetConversionJavaImpl.h"
#include "../include/dicomhero6/definitions.h"
#include <string>

namespace dicomhero
{

namespace implementation
{

class dicomConversion
{
public:
    static std::string convertFromUnicode(const std::wstring& unicodeString, const charsetsList_t& charsets);
    static std::wstring convertToUnicode(const std::string& value, const charsetsList_t& charsets);
};

}

}

#endif // imebraCharsetConversion_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

