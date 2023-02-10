/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file ageImpl.cpp
    \brief Implementation of the class age.

*/

#include "ageImpl.h"
#include "exceptionImpl.h"
#include "../include/dicomhero6/exceptions.h"

namespace dicomhero
{

namespace implementation
{

age::age(std::uint32_t initialAge, ageUnit_t initialUnits):
    m_age(initialAge), m_units(initialUnits)
{
}

double age::getYears() const
{
    DICOMHERO_FUNCTION_START();

    switch(m_units)
    {
    case ageUnit_t::years:
        return (double)m_age;
    case ageUnit_t::months:
        return m_age / (double)12;
    case ageUnit_t::weeks:
        return m_age / 52.142857;
    case ageUnit_t::days:
        return m_age / (double)365;
    default:
        DICOMHERO_THROW(DataHandlerCorruptedBufferError, "Invalid age units");
    }

    DICOMHERO_FUNCTION_END();
}

std::uint32_t age::getAgeValue() const
{
    return m_age;
}

ageUnit_t age::getAgeUnits() const
{
    return m_units;
}

} // namespace implementation

} // namespace dicomhero

