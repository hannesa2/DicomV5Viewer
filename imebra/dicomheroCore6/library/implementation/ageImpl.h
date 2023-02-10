/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file ageImpl.h
    \brief Declaration of the class age.

*/

#if !defined(imebraAge_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraAge_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include <cstdint>
#include "../include/dicomhero6/definitions.h"

namespace dicomhero
{

namespace implementation
{

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
class age
{
public:
    /// \brief Constructor.
    ///
    /// \param initialAge the initial age to assign to the object, in days, weeks,
    ///                   months or years, depending on the parameter initialUnits
    /// \param initialUnits the units of the value in initialAge
    ///
    ///////////////////////////////////////////////////////////////////////////////
    age(std::uint32_t initialAge, ageUnit_t initialUnits);

    /// \brief Return the age in years.
    ///
    /// \return the stored age converted to years.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    double getYears() const;

    std::uint32_t getAgeValue() const;
    ageUnit_t getAgeUnits() const;

private:
    std::uint32_t m_age;   ///< The age, in days, weeks, months or years according to units
    ageUnit_t     m_units; ///< The units of the value in age

};

} // namespace implementation

} // namespace dicomhero

#endif // !defined(imebraDate_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
