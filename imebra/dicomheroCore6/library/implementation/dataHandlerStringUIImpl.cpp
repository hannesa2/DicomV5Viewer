/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringUI.cpp
    \brief Implementation of the class dataHandlerStringUI.

*/

#include <cctype>
#include "dataHandlerStringUIImpl.h"

namespace dicomhero
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
//
// Normalize an UID
//
///////////////////////////////////////////////////////////
std::string normalizeUid(const std::string& uid)
{
    DICOMHERO_FUNCTION_START();

    std::string value;

    bool bAddDot(false);
    bool bStartNumber(true);

    for(size_t scanUid(0), endUid(uid.size()); scanUid != endUid; ++scanUid)
    {
        const char& nextChar(uid[scanUid]);

        if(std::isdigit(nextChar))
        {
            if(bAddDot)
            {
                if(value.empty())
                {
                    value.push_back('0');
                }
                value.push_back('.');
                bAddDot = false;
            }
            if(
                    !bStartNumber ||
                    nextChar != '0' ||
                    scanUid == endUid - 1 ||
                    !std::isdigit(uid[scanUid + 1]) )
            {
                value.push_back(nextChar);
                bStartNumber = false;
            }
        }
        else if(nextChar == '.')
        {
            if(bAddDot)
            {
                value.append(".0");
            }
            bAddDot = true;
            bStartNumber = true;
        }
        else
        {
            DICOMHERO_THROW(DataHandlerInvalidDataError, "Invalid char in UID " << uid);
        }
    }

    if(bAddDot)
    {
        value.append(".0");
    }

    return value;

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerStringUI
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringUI::readingDataHandlerStringUI(const memory& parseMemory):
    readingDataHandlerString(parseMemory, tagVR_t::UI, 0x0, 0x0)
{
}

std::string readingDataHandlerStringUI::getString(const size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return normalizeUid(readingDataHandlerString::getString(index));

    DICOMHERO_FUNCTION_END();
}

writingDataHandlerStringUI::writingDataHandlerStringUI(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerString(pBuffer, tagVR_t::UI, 0x0, 0, 64)
{
}

void writingDataHandlerStringUI::setString(const size_t index, const std::string& value)
{
    DICOMHERO_FUNCTION_START();

    writingDataHandlerString::setString(index, normalizeUid(value));

    DICOMHERO_FUNCTION_END();
}



} // namespace handlers

} // namespace implementation

} // namespace dicomhero
