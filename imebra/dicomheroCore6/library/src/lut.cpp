/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/lut.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/LUTImpl.h"

namespace dicomhero
{

LUT::LUT(const std::shared_ptr<implementation::lut>& pLut): m_pLut(pLut)
{
}

LUT::LUT(const LUT& source): m_pLut(getLUTImplementation(source))
{
}

const std::shared_ptr<dicomhero::implementation::lut>& getLUTImplementation(const LUT& lut)
{
    return lut.m_pLut;
}

LUT::~LUT()
{
}

std::wstring LUT::getDescription() const
{
    return m_pLut->getDescription();
}

ReadingDataHandlerNumeric LUT::getReadingDataHandler() const
{
    DICOMHERO_FUNCTION_START();

    return ReadingDataHandlerNumeric(m_pLut->getReadingDataHandler());

    DICOMHERO_FUNCTION_END_LOG();
}

size_t LUT::getBits() const
{
    DICOMHERO_FUNCTION_START();

    return m_pLut->getBits();

    DICOMHERO_FUNCTION_END_LOG();
}

size_t LUT:: getSize() const
{
    DICOMHERO_FUNCTION_START();

    return m_pLut->getSize();

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t LUT::getFirstMapped() const
{
    DICOMHERO_FUNCTION_START();

    return m_pLut->getFirstMapped();

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t LUT::getMappedValue(std::int32_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pLut->getMappedValue(index);

    DICOMHERO_FUNCTION_END_LOG();
}

}

