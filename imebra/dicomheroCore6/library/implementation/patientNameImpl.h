/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file patientNameImpl.h
    \brief Declaration of the class patientName.

*/

#if !defined(imebraPatientName_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraPatientName_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include <cstdint>
#include "../include/dicomhero6/definitions.h"

namespace dicomhero
{

namespace implementation
{

template <class T>
class patientNameBase
{
public:
    /// \brief Constructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    patientNameBase(const T& alphabeticRepresentation,
        const T& ideographicRepresentation,
        const T& phoneticRepresentation):
        m_alphabeticRepresentation(alphabeticRepresentation),
        m_ideographicRepresentation(ideographicRepresentation),
        m_phoneticRepresentation(phoneticRepresentation)
    {}

    T getAlphabeticRepresentation() const
    {
        return m_alphabeticRepresentation;
    }

    T getIdeographicRepresentation() const
    {
        return m_ideographicRepresentation;
    }

    T getPhoneticRepresentation() const
    {
        return m_phoneticRepresentation;
    }

private:
    T m_alphabeticRepresentation;
    T m_ideographicRepresentation;
    T m_phoneticRepresentation;
};


class patientName: public patientNameBase<std::string>
{
public:
    using patientNameBase::patientNameBase;

};

class unicodePatientName: public patientNameBase<std::wstring>
{
public:
    using patientNameBase::patientNameBase;

};


} // namespace implementation

} // namespace dicomhero

#endif // !defined(imebraPatientName_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
